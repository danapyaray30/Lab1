// 816030044
// Dana Pyaray

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"


char new_character;
char old_character = 0;
TickType_t last_input_time = 0;

void toggle(){
    //Get the current level of the GPIO pin
    int current_level = gpio_get_level(GPIO_NUM_2);
    
    //Set the GPIO pin to the opposite level
    gpio_set_level(GPIO_NUM_2, !current_level);
}

void initialize(){
    gpio_config_t io_conf;

    //Configure the GPIO pin as output
    io_conf.pin_bit_mask = (1ULL << GPIO_NUM_2);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);
    
    //Configure UART
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, 1024 * 2, 0, 0, NULL, 0);
}

void question15(){
    
    if (uart_read_bytes(UART_NUM_0, (uint8_t*)&new_character, 1, portMAX_DELAY) > 0) {
        TickType_t now = xTaskGetTickCount();

        if (old_character != new_character) {
            if ((now - last_input_time) <= (500/portTICK_PERIOD_MS)) {
                toggle();
            }
            else {
                if ((now - last_input_time) >= (500/portTICK_PERIOD_MS)) {
                    toggle();
                }
            }
        }
        else {
            if((now - last_input_time) > (500/portTICK_PERIOD_MS)) {
                toggle();
            }
        }
        last_input_time = now;
        old_character = new_character;
    }
}

void app_main() {
    initialize();
    while (1) {
        question15();
    }
}
