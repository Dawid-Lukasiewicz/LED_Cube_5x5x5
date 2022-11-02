#include "wifi.hpp"

extern char ssid[];
extern char pass[];

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

void handle_connection(int conn_sock, cube &Cube)
{
    led received_led;
    std::string str_buff;
    while(1)
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
    }
    closesocket(conn_sock);
}

void run_server(cube &Cube)
{
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in listen_addr =
        {
            .sin_len = sizeof(struct sockaddr_in),
            .sin_family = AF_INET,
            .sin_port = htons(1234),
            .sin_addr = 0,
        };

    if (server_sock < 0)
    {
        printf("Unable to create socket: error %d", errno);
        return;
    }

    if (bind(server_sock, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0)
    {
        printf("Unable to bind socket: error %d\n", errno);
        return;
    }

    if (listen(server_sock, 1) < 0)
    {
        printf("Unable to listen on socket: error %d\n", errno);
        return;
    }

    printf("Starting server at %s on port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), ntohs(listen_addr.sin_port));

    while (true)
    {
        struct sockaddr_storage remote_addr;
        socklen_t len = sizeof(remote_addr);
        int conn_sock = accept(server_sock, (struct sockaddr *)&remote_addr, &len);
        if (conn_sock < 0)
        {
            printf("Unable to accept incoming connection: error %d\n", errno);
            return;
        }
        handle_connection(conn_sock, Cube);
    }
    vTaskDelete(NULL);
}

void wifi_connect(flag &success)
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
            success = 1;
            break;
        }
    }
    if (retries >= 10)
    {
        printf("Cannot connect\n");
        success = 0;
    }
    vTaskDelete(NULL);
}