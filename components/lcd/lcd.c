#include "driver/gpio.h"
#include "driver/i2c_master.h"   // I2C LCD 통신

#define LCD_SDA GPIO_NUM_22
#define LCD_SCL GPIO_NUM_23
#define LCD_ADDR 0x27
#define LCD_FREQ 100000

#define LCD_RS 0x01
#define LCD_RW 0x02
#define LCD_EN 0x04
#define LCD_BACKLIGHT 0x08

i2c_master_bus_handle_t i2c_bus= NULL;

i2c_master_dev_handle_t lcd_dev = NULL;

void lcd_write_byte(uint8_t data) {
    i2c_master_transmit(
        lcd_dev, &data, 1, pdMS_TO_TICKS(1000)
    );
}

void lcd_clear(void) {
    lcd_write_byte(0x01);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_print(char *str) {
    while (*str) {
        lcd_write_byte(*str);
        str++;
    }
}

char keypad_key(void) {
    char key = keypad_scan();

    if (key != '\0') {
        return key;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
}