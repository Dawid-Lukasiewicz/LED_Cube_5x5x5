#ifndef WIFI
#define WIFI

/* pico-sdk standard*/
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

/* FreeRTOS library*/
#include "FreeRTOS.h"
#include "task.h"

/* lwip library */
#include "lwip/apps/lwiperf.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include <lwip/sockets.h>

/* project files */
#include "cube.hpp"

void send_message(int socket, char *msg);
int handle_single_command(int conn_sock);
void handle_connection(int conn_sock);
void run_server();

void wifi_initialize();
void wifi_connect(flag &success);

#endif