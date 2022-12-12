#ifndef WIFI
#define WIFI

#include <string>

/* pico-sdk standard*/
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

/* FreeRTOS library*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* lwip library */
#include "lwip/apps/lwiperf.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include <lwip/sockets.h>

/* project files */
#include "cube.hpp"

void send_message(int socket, char *msg);
int handle_single_command(int conn_sock);
int handle_connection(int conn_sock, cube &Cube);
void run_server(cube &Cube);

void wifi_initialize();
void wifi_connect(cube &Cube);

#endif