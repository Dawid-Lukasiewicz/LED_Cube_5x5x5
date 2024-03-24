#ifndef WIFI
#define WIFI

#include <string>
#include <list>

/* pico-sdk standard*/
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

/* project files */
#include "cube.hpp"

/* lwip library */
#include "lwip/apps/lwiperf.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include <lwip/sockets.h>


void send_message(int socket, char *msg);
int handle_single_command(int conn_sock);
int handle_connection(int conn_sock, cube &Cube);
void run_server_send_state(cube &Cube);
void wifi_send_state(cube &Cube);

void wifi_receive_state(cube &Cube);
void run_server_receive_state(cube &Cube);

#endif