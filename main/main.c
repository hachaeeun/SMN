#include <stdio.h>
#include <string.h>              // strcmp()

#include "freertos/FreeRTOS.h"   // pdMS_TO_TICKS()
#include "freertos/task.h"       // vTaskDelay()

#include "driver/gpio.h"         // gpio_set_level(), gpio_get_level()
#include "driver/i2c_master.h"   // I2C LCD 통신
#include "esp_log.h"

//==========LED==========
#define RED_GPIO GPIO_NUM_25
#define GREEN_GPIO GPIO_NUM_26

//==========LCD==========
#define LCD_SDA GPIO_NUM_22
#define LCD_SCL GPIO_NUM_23
#define LCD_ADDR 0x27
#define LCD_FREQ 100000

#define LCD_RS 0x01
#define LCD_RW 0x02
#define LCD_EN 0x04
#define LCD_BACKLIGHT 0x08

i2c_master_dev_handle_t i2c_bus= NULL;

i2c_master_dev_handle_t lcd_dev = NULL;

//==========KEYPAD==========
#define ROW_NUM 4
#define COLUMN_NUM 3
#define password "1234"

const gpio_num_t row_pin[ROW_NUM] =  {
    GPIO_NUM_21,
    GPIO_NUM_19,
    GPIO_NUM_18,
    GPIO_NUM_5
};

const gpio_num_t column_pin[COLUMN_NUM] =  {
    GPIO_NUM_17,
    GPIO_NUM_16,
    GPIO_NUM_4
};

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
}, password[5];

char user_password[5] = { '1', '2', '3', '4', '\0' };

//=================LCD======================

void lcd_write_byte(uint8_t data) {
    i2c_master_transmit(
        lcd_dev, &data, 1, pdMS_TO_TICKS(1000)
    );
}

void input_password(char *password) {
    lcd_clear();
    lcd_setCursor(4, 0);
    lcd_print("Password");
    lcd_setCursor(6, 1);
    lcd_cursor();

    lcd_clear();
    lcd_setCursor(5, 0);
    lcd_print("Fail");
    lcd_cursor();
    
    for(int i = 0; i < 4; i++) {
        char key = keypad_wait_for_key();
        password[i] = key;
    }
    password[5] = '\0';
    lcd_noCursor();
    delay(500);
}

//===============LED(초기화, on, off)===============
void led_init(void) {
    gpio_reset_pin(RED_GPIO);
    gpio_reset_pin(GREEN_GPIO);

    gpio_set_direction(RED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GREEN_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(RED_GPIO, 0);
    gpio_set_level(GREEN_GPIO, 0);
}

void led_on(void) {
    gpio_set_level(RED_GPIO, 1);
    gpio_set_level(GREEN_GPIO, 1);
}

void led_off(void) {
    gpio_set_level(RED_GPIO, 0);
    gpio_set_level(GREEN_GPIO, 0);
}

//========================================

void app_main (void)
{

    

}

