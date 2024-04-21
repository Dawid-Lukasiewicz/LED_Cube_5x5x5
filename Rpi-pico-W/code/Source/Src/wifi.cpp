#include "wifi.hpp"
#include "apptasks.hpp"

#define BUFFER_RD_SIZE 4
#define BUFFER_LED_SIZE 64

extern char ssid[];
extern char pass[];

namespace task_handlers
{
    extern TaskHandle_t main_thread;
    extern TaskHandle_t wifi_thread;
}


void send_message(int socket, char *msg)
{
    int len = strlen(msg);
    int done = 0;
    int send = 0;
    while (done < len)
    {
        int done_now = send(socket, msg + done, len - done, 0);
        if (done_now <= 0)
            return;
        done += done_now;
    }
}

int handle_connection(int conn_sock, cube &Cube)
{
    led received_led;
    std::string str_buff;
    int read_size = 1;
    int current_size = 0;
    char buffer[BUFFER_RD_SIZE];
    EventBits_t notify_flag;
    while(read_size != 0)
    {

        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        notify_flag = xEventGroupWaitBits(Cube.CubeEventFlag, EVENT_FLAG_BIT, pdTRUE, pdTRUE, 1);
        if(!(notify_flag & EVENT_FLAG_BIT))
        {
            continue;
        }

        // printf("[DEV] Wifi task core: %d\n\r", get_core_num());
        // vTaskDelay(25);
        xSemaphoreTake(Cube.CubeStateSemaphore, portMAX_DELAY);
        current_size = Cube.__leds.size();
        for (int i = 0; i < current_size; i++)
        {
            /* Send X coordinate*/
            str_buff += "X" + std::to_string(Cube.__leds.at(i).__x) + ":";
            /* Send Y coordinate*/
            str_buff += "Y" + std::to_string(Cube.__leds.at(i).__y)+ ":";
            /* Send Z coordinate*/
            str_buff += "Z" + std::to_string(Cube.__leds.at(i).__z)+ ":";
        }
        xSemaphoreGive(Cube.CubeStateSemaphore);
        send_message(conn_sock, (char*)str_buff.c_str());
        send_message(conn_sock, "----\r\n");
        str_buff.clear();
        xEventGroupClearBits(Cube.CubeEventFlag, EVENT_FLAG_BIT);
        read_size = recv(conn_sock, buffer, BUFFER_RD_SIZE, 0);
    }
    return read_size;
}

void run_server_send_state(cube &Cube)
{
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in listen_addr =
        {
            .sin_len = sizeof(struct sockaddr_in),
            .sin_family = AF_INET,
            .sin_port = htons(1234),
            .sin_addr = 0
        };
    printf("server_sock = %d\n", server_sock);
    if (server_sock < 0)
    {
        printf("Unable to create socket: error %d", errno);
        return;
    }
    int binding = bind(server_sock, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
    printf("binding = %d\n", binding);
    if (binding < 0)
    {
        printf("Unable to bind socket: error %d\n", errno);
        return;
    }
    int listening = listen(server_sock, 1);
    printf("listening = %d\n", listening);
    if (listening < 0)
    {
        printf("Unable to listen on socket: error %d\n", errno);
        return;
    }

    printf("Starting server at %s on port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), ntohs(listen_addr.sin_port));
    int status = 1;
    while (status)
    {
        struct sockaddr_storage remote_addr;
        socklen_t len = sizeof(remote_addr);
        int conn_sock = accept(server_sock, (struct sockaddr *)&remote_addr, &len);
        if (conn_sock < 0)
        {
            printf("Unable to accept incoming connection: error %d\n", errno);
            return;
        }
        status = handle_connection(conn_sock, Cube);
        printf("[INFO] server status: %d\r\n", status);
    }
    shutdown(server_sock, SHUT_RDWR);
    printf("[INFO] server shut down\r\n");
    vTaskDelay(1500);
    closesocket(server_sock);
}

void wifi_send_state(cube &Cube)
{
    cyw43_arch_enable_sta_mode();

    printf("[INFO] Connecting to WiFi...\n");
    printf("[INFO] Wifi task core: %d\n\r", get_core_num());
    const int max_retries = 5;
    int retries = 1;
    for(retries; retries < max_retries; retries++)
    {
        int connection_status = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000);
        printf("[INFO] Connection status: %d\n", connection_status);
        if (connection_status)
        {
            printf("[ERROR] failed to connect. Retry: %d/%d\n", retries, max_retries);
        }
        else
        {
            printf("[INFO] Connected. After %d retries\n", retries);
            Cube.connected = 1;
            break;
        }
    }

    xTaskNotifyGive(task_handlers::main_thread);
    printf("[INFO] wifi -> main notification\n");

    if (!Cube.connected)
    {
        printf("[ERROR] Cannot connect\n");
        vTaskDelete(NULL);
        return;
    }

    run_server_send_state(Cube);
    Cube.connected = 0;
    printf("[INFO] Socket disconnected\n");
    task_handlers::wifi_thread = NULL;
    vTaskDelete(NULL);
    return;
}

/* RECEIVING DATA CONNECTION PART*/

void split_list(std::list<std::string> &list_string, std::string &in_string)
{
    size_t pos = 0;
    std::string delimeter = ":";
    std::string element;
    while ((pos = in_string.find(delimeter)) != std::string::npos)
    {
        element = in_string.substr(0, pos);
        list_string.push_back(element);
        in_string.erase(0, pos+delimeter.length());
    }
}

int receive_data(int conn_sock, cube &Cube)
{
    led received_led;
    std::list<std::string> str_list;
    char buffer[BUFFER_LED_SIZE];
    while (recv(conn_sock, buffer, BUFFER_LED_SIZE, 100))
    {
        std::string str_buff = buffer;
        split_list(str_list, str_buff);


        int X = Cube.pin_layouts.at(str_list.front());
        str_list.pop_front();
        int Y = Cube.pin_layouts.at(str_list.front());
        str_list.pop_front();
        int Z = Cube.pin_layouts.at(str_list.front());
        str_list.pop_front();

        // printf("LED X=%d Y=%d Z=%d\n", X, Y, Z );
        received_led.__set(X_table[X], Y_table[Y], Z_table[Z]);

        xQueueSend(Cube.xCubeQueueReceive, (const void*)&received_led, 0);
        str_buff.clear();
        str_list.clear();
        vTaskDelay(1000);
        send_message(conn_sock, "S\r\n");
    }
    return 0;
}

void run_server_receive_state(cube &Cube)
{
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in listen_addr =
        {
            .sin_len = sizeof(struct sockaddr_in),
            .sin_family = AF_INET,
            .sin_port = htons(1234),
            .sin_addr = 0
        };
    printf("server_sock = %d\n", server_sock);
    if (server_sock < 0)
    {
        printf("Unable to create socket: error %d", errno);
        return;
    }
    int binding = bind(server_sock, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
    printf("binding = %d\n", binding);
    if (binding < 0)
    {
        printf("Unable to bind socket: error %d\n", errno);
        return;
    }
    int listening = listen(server_sock, 1);
    printf("listening = %d\n", listening);
    if (listening < 0)
    {
        printf("Unable to listen on socket: error %d\n", errno);
        return;
    }

    printf("Starting server at %s on port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), ntohs(listen_addr.sin_port));
    int status = 1;
    while (status)
    {
        struct sockaddr_storage remote_addr;
        socklen_t len = sizeof(remote_addr);
        int conn_sock = accept(server_sock, (struct sockaddr *)&remote_addr, &len);
        if (conn_sock < 0)
        {
            printf("Unable to accept incoming connection: error %d\n", errno);
            return;
        }
        status = receive_data(conn_sock, Cube);
    }
    shutdown(server_sock, SHUT_RDWR);
    vTaskDelay(1500);
    closesocket(server_sock);
}

void wifi_receive_state(cube &Cube)
{
    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi...\n");
    int retries = 1;
    for(retries; retries < 11; retries++)
    {
        int connection_status = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 10000);
        printf("Connection status: %d\n", connection_status);
        if (connection_status)
        {
            printf("failed to connect. Retry: %d/10\n", retries);
        }
        else
        {
            printf("Connected. After %d retries\n", retries);
            Cube.connected = 1;
            break;
        }
    }
    if (retries >= 10)
    {
        printf("Cannot connect\n");
        Cube.connected = 0;
    }
    run_server_receive_state(Cube);
    Cube.connected = 0;
    printf("Destroying connection task\n");
    vTaskDelete(NULL);
}