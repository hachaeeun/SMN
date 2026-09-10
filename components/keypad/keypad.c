#include "driver/gpio.h"  
#include "lcd.h"


#define ROW_NUM 4
#define COLUMN_NUM 3

char PASSWORD[5] = { '1', '2', '3', '4', '\0'};

char input_pw[5];

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
};

void input_password(char *password) {
    lcd_clear();
    lcd_print("Password");
    
    for(int i = 0; i < 4; i++) {
        char key = keypad_key();
        password[i] = key;
    }
    password[4] = '\0';
    vTaskDelay(pdMS_TO_TICKS(500));
}
