#ifndef WIFI
#define WIFI

#include <string.h>
#include <stdlib.h>

#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

#define TCP_PORT 4242
#define DEBUG_printf printf
#define BUF_SIZE 2048
#define TEST_ITERATIONS 10
#define POLL_TIME_S 5

typedef struct TCP_SERVER_T_ {
    struct tcp_pcb *server_pcb;
    struct tcp_pcb *client_pcb;
    bool complete;
    uint8_t buffer_sent[BUF_SIZE];
    uint8_t buffer_recv[BUF_SIZE];
    int sent_len;
    int recv_len;
    int run_count;
} TCP_SERVER_T;

static TCP_SERVER_T* tcp_server_init(void);

static err_t tcp_server_close(void *arg);

static err_t tcp_server_result(void *arg, int status);

static err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);

// err_t tcp_server_send_data(char *data, uint len, void *arg, struct tcp_pcb *tpcb);
err_t tcp_server_send_data(void *arg, struct tcp_pcb *tpcb);

err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

static err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);

static void tcp_server_err(void *arg, err_t err);

static err_t tcp_server_accept(void *arg, struct tcp_pcb *client_pcb, err_t err);

static bool tcp_server_open(void *arg);

int connect_to_wifi(char *ssid, char *pass);

#endif