#ifndef APPTASK
#define APPTASK

#include "FreeRTOS.h"
#include "task.h"

namespace task_handlers
{
    TaskHandle_t main_thread;
    TaskHandle_t wifi_thread;
}

#endif /* APPTASK */