// 816030044
// Dana Pyaray

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GPIO_PIN GPIO_NUM_2 // Replace with the GPIO pin number you want to control

void initialise(){
    gpio_config_t io_conf;

    // Configure the GPIO pin as output
    io_conf.pin_bit_mask = (1ULL << GPIO_PIN);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;

    gpio_config(&io_conf);
	
}
void toggle(){
        // Set the GPIO pin to high (logic level 1)
        gpio_set_level(GPIO_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second

        // Set the GPIO pin to low (logic level 0)
        gpio_set_level(GPIO_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second	
}

void app_main() {
	initialise();
    while (1) {
		toggle();
    }
}