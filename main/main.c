#include <stdio.h>
#include <string.h>              // strcmp()

#include "freertos/task.h"       // vTaskDelay()

#include "led.h"
#include "lcd.h"
#include "keypad.h"   

//=================password===================
void app_main (void)
{

    char PASSWORD[5] = { '1', '2', '3', '4', '\0'};

    char input_pw[5];

    led_init();
    while(1) {

    input_password(input_pw);

    if (strcmp(input_pw, PASSWORD) == 0) {
        lcd_clear();
        lcd_print("Success!");
        led_green_on();
    }

    else {
        lcd_clear();
        lcd_print("Fail..");
        led_red_on();
    }

    keypad_wait_for_key();
    led_off();
    vTaskDelay(pdMS_TO_TICKS(500));
    }
}

