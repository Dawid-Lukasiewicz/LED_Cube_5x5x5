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
        printf("Sending %d\n", ++send);
        int done_now = send(socket, msg + done, len - done, 0);
        if (done_now <= 0)
            return;
        done += done_now;
    }
}

int handle_single_command(int conn_sock)
{
    char buffer[128];
    int done = 0;
    send_message(conn_sock, "Enter command: ");

    while (done < sizeof(buffer))
    {
        int done_now = recv(conn_sock, buffer + done, sizeof(buffer) - done, 0);
        if (done_now <= 0)
            return -1;
        done += done_now;
        char *end = strnstr(buffer, "\r", done);
        if (!end)
            continue;
        *end = 0;

        if (!strcmp(buffer, "on"))
        {
            cyw43_arch_gpio_put(0, true);
            send_message(conn_sock, "The LED is now on\r\n");
        }
        else if (!strcmp(buffer, "off"))
        {
            cyw43_arch_gpio_put(0, false);
            send_message(conn_sock, "The LED is now off\r\n");
        }
        else
        {
            send_message(conn_sock, "Unknown command\r\n");
        }
        break;
    }

    return 0;
}

void handle_connection(int conn_sock)
{
    while (!handle_single_command(conn_sock))
    {}

    closesocket(conn_sock);
}

void run_server()
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
        handle_connection(conn_sock);
    }
}

void wifi_initialize()
{
    if (!cyw43_arch_init_with_country(uint32_t CYW43_COUNTRY_POLAND))
        printf("[SUCCESS] Succesfull Wi-fucking-Fi module init\n\r");
    else
        printf("[WARNING] WiFi module NOT INITIALIZED\n\r");
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
    run_server();
    cyw43_arch_deinit();
    vTaskDelete(NULL);
}