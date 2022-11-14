#include "wifi.hpp"

extern char ssid[];
extern char pass[];

TaskHandle_t wifi_connect_handler;


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
    int status = 1;
    char buffer[4];
    while(status != 0)
    {
        if (Cube.xCubeQueue != NULL)
        {
            xQueueReceive(Cube.xCubeQueue, &received_led, portMAX_DELAY);

            /* Send X coordinate*/
            str_buff = std::to_string(received_led.__x);
            char *char_buff = (char*)str_buff.c_str();
            send_message(conn_sock, "X= ");
            send_message(conn_sock, char_buff);

            /* Send Y coordinate*/
            str_buff = std::to_string(received_led.__y);
            char_buff = (char*)str_buff.c_str();
            send_message(conn_sock, " Y= ");
            send_message(conn_sock, char_buff);

            /* Send Z coordinate*/
            str_buff = std::to_string(received_led.__z);
            char_buff = (char*)str_buff.c_str();
            send_message(conn_sock, " Z= ");
            send_message(conn_sock, char_buff);

            send_message(conn_sock, "\r\n");
        }
        else
        {
            printf("Queue handler is NULL\r\n");
        }
        if (!uxQueueMessagesWaiting(Cube.xCubeQueue))
        {
            send_message(conn_sock, "-------------------------\r\n");
        }
        status = recv(conn_sock, buffer, 4, 0);
        // printf("From client %s", buffer);
    }
    return status;
}

void run_server(cube &Cube)
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
    }
    shutdown(server_sock, SHUT_RDWR);
    vTaskDelay(1500);
    closesocket(server_sock);
    // vTaskDelete(NULL);
}

void wifi_connect(cube &Cube)
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

    run_server(Cube);
    Cube.connected = 0;
    printf("Destroying connection task\n");
    // cyw43_arch_deinit();
    vTaskDelete(NULL);
}