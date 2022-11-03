/*standard library*/
#include <stdio.h>
#include <cstdlib>
#include <ctime>

/*pico-sdk library*/
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

/*custom library*/
#include "cube.hpp"
#include "numbers.hpp"
#include "animations.hpp"
#include "wifi.hpp"
#include "password.hpp"

#include "FreeRTOS.h"
#include "task.h"

#ifndef RUN_FREERTOS_ON_CORE
    #define RUN_FREERTOS_ON_CORE 1
#endif

#define WIFI_INITIALIZE_TASK_PRIORITY (tskIDLE_PRIORITY + 1UL)
#define MAIN_TASK_PRIORITY (tskIDLE_PRIORITY)

#define SET_X(x) gpio_put((x), 0)
#define CLEAR_X(x) gpio_put((x), 1)

#define SET_Y(y) gpio_put((y), 0)
#define CLEAR_Y(y) gpio_put((y), 1)

#define SET_Z(z) gpio_put((z), 1)
#define CLEAR_Z(z) gpio_put((z), 0)

#define NUMBER_DISPLAY_TIME     SCALE_MS_TO_US(250)
#define DEBOUNCE_TIME           SCALE_MS_TO_US(50)

#define BUTTON_UP               7U
#define BUTTON_DOWN             8U
#define BUTTON_SELECT           9U

flag connected = 0;

extern const uint8_t X_table[5];
extern const uint8_t Y_table[5];
extern const uint8_t Z_table[5];

typedef uint8_t flag;

flag button_select_flag = 0;
flag select_mode = 0;

flag button_pushed = 0;
flag button_pushed_once = 0;
flag button_released = 0;

absolute_time_t pushed_start;
absolute_time_t released_start;

int8_t display_number = 0;
absolute_time_t number_display_start = get_absolute_time();

uint8_t x_coord = 0;

void init_leds()
{
    #ifdef pico_wireless
        // gpio_init(CYW43_WL_GPIO_LED_PIN);
        // gpio_set_dir(CYW43_WL_GPIO_LED_PIN, GPIO_OUT);
        // gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, GPIO_OUT);
    #else
        gpio_init(25U);
        gpio_set_dir(25U, GPIO_OUT);
        gpio_put(25U, 1);
    #endif
    for(int i = 0; i < 5; i++)
    {
        gpio_init(X_table[i]);
        gpio_init(Y_table[i]);
        gpio_init(Z_table[i]);

        gpio_set_dir(X_table[i], GPIO_OUT);
        gpio_set_dir(Y_table[i], GPIO_OUT);
        gpio_set_dir(Z_table[i], GPIO_OUT);

        CLEAR_X(X_table[i]);
        CLEAR_Y(Y_table[i]);
        CLEAR_Z(Z_table[i]);
    }
}

void init_buttons()
{
    gpio_init(BUTTON_UP);
    gpio_set_dir(BUTTON_UP, GPIO_IN);
    gpio_pull_up(BUTTON_UP);

    gpio_init(BUTTON_DOWN);
    gpio_set_dir(BUTTON_DOWN, GPIO_IN);
    gpio_pull_up(BUTTON_DOWN);

    // resolid the select button
    gpio_init(BUTTON_SELECT);
    gpio_set_dir(BUTTON_SELECT, GPIO_IN);
    gpio_pull_up(BUTTON_SELECT);
}

void send_to_queue(cube &Cube)
{   
    uint uIValueToSend = 0;

    if (Cube.xCubeQueue != NULL)
        printf("In send: Hanlder is not NULL\r\n");
    else
        printf("In send: Hanlder is not NULL\r\n");
    while (true) {
        uIValueToSend = 1;
        xQueueSend(Cube.xCubeQueue, &uIValueToSend, 0U);
        vTaskDelay(100);

        uIValueToSend = 0;
        xQueueSend(Cube.xCubeQueue, &uIValueToSend, 0U);
        vTaskDelay(100);
    }
}

static void main_thread()
{
    std::srand(std::time(nullptr));
    stdio_init_all();
    if (!cyw43_arch_init_with_country(uint32_t CYW43_COUNTRY_POLAND))
        printf("[SUCCESS] Succesfull Wi-fucking-Fi module init\n\r");
    else
        printf("[WARNING] WiFi module NOT INITIALIZED\n\r");
    init_leds();
    init_buttons();

    std::srand(std::time(nullptr));
    cube Cube(MAX_LED_AMOUNT);
    Cube.xCubeQueue = xQueueCreate(MAX_LED_AMOUNT, sizeof(led));


    while(1)
    {
        switch (display_number)
        {
        case 0:
            if (!select_mode)
                zero(Cube, X_table[x_coord]);
            else
            {
                random_led(Cube);
            }
            break;
        case 1:
            if (!select_mode)
                one(Cube, X_table[x_coord]);
            else
            {
                rain(Cube);
            }
            break;
        case 2:
            if (!select_mode)
                two(Cube, X_table[x_coord]);
            else
            {
                heavy_rain(Cube);
            }
            break;
        case 3:
            if (!select_mode)
                three(Cube, X_table[x_coord]);
            else
            {
                expanding_cube(Cube);
            }
            break;
        case 4:
            if (!select_mode)
                four(Cube, X_table[x_coord]);
            else
            {
                expanding_star(Cube);
            }

            break;
        case 5:
            if (!select_mode)
                five(Cube, X_table[x_coord]);
            else    {}

            break;
        case 6:
            if (!select_mode)
                six(Cube, X_table[x_coord]);
            else    {}

            break;
        case 7:
            if (!select_mode)
                seven(Cube, X_table[x_coord]);
            else    {}

            break;
        case 8:
            if (!select_mode)
                eight(Cube, X_table[x_coord]);
            else    {}

            break;
        case 9:
            if (!select_mode)
                nine(Cube, X_table[x_coord]);
            else
            {
                if (!connected)
                {
                    TaskHandle_t task2;
                    xTaskCreate((TaskFunction_t)wifi_connect, "Connect", configMINIMAL_STACK_SIZE*6, (void*)&connected, 1, &task2);
                    /* Instead of Delay try to make notification wait */
                    vTaskDelay(7500);
                    if (connected)
                    {
                        xTaskCreate((TaskFunction_t)run_server, "RunServer", configMINIMAL_STACK_SIZE*10, (void*)&Cube, 1, NULL);
                    }
                }
            }
            break;
        
        default:
            display_number = 0;
            break;
        }
        if(gpio_get(BUTTON_SELECT) == 0 && !button_pushed && !button_released)
        {
            printf("[INFO] Select button pushed\n\r");
            Cube.clr_leds();
            Cube.reset_display_state();
            select_mode ^= 1;
            button_pushed = 1;
            button_pushed_once = 1;
            pushed_start = get_absolute_time();
        }

        /* When Down button pushed first time  */
        if (gpio_get(BUTTON_DOWN) == 0 && !button_pushed && !button_released && !select_mode)
        {
            printf("[INFO] Down button pushed\n\r");
            Cube.clr_leds();
            Cube.reset_display_state();
            --display_number;
            button_pushed = 1;
            button_pushed_once = 1;
            pushed_start = get_absolute_time();
        }
        /* When UP button pushed first time  */
        else if (gpio_get(BUTTON_UP) == 0 && !button_pushed && !button_released && !select_mode)
        {
            printf("[INFO] Up button pushed\n\r");
            Cube.clr_leds();
            Cube.reset_display_state();
            ++display_number;
            button_pushed = 1;
            button_pushed_once = 1;
            pushed_start = get_absolute_time();
        }
        /* Button Up and Down logic */
        else if ( (gpio_get(BUTTON_UP) == 1 &&
                gpio_get(BUTTON_DOWN) == 1 &&
                button_pushed == 1 ) &&
                absolute_time_diff_us(pushed_start, get_absolute_time()) >= DEBOUNCE_TIME)
        {
            button_pushed = 0;
            button_released = 1;
            released_start = get_absolute_time();
        }
        else if (button_released && 
            absolute_time_diff_us(released_start, get_absolute_time()) >= DEBOUNCE_TIME)
        {
            button_released = 0;
        }
        
        /* Incrementing display number's X position */
        if (button_pushed_once ||
            (!button_pushed) &&
            ( Cube.get_display_state() == 1 &&
            absolute_time_diff_us(number_display_start,
                                get_absolute_time()) >= NUMBER_DISPLAY_TIME) &&
            !select_mode)
        {
            button_pushed_once = 0;
            ++x_coord;
            if (x_coord >= 5)   x_coord = 0;
            Cube.change_X(X_table[x_coord]);
            number_display_start = get_absolute_time();
        }
        if (display_number > 9)         display_number = 0;
        else if (display_number < 0)    display_number = 9;
        
        
    }
    vTaskDelete(NULL);
}

int main()
{
    TaskHandle_t task;
    xTaskCreate((TaskFunction_t)main_thread, "MainThread", configMINIMAL_STACK_SIZE*10, NULL, 1, &task);
    vTaskStartScheduler();
}