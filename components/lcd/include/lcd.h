#include <stdint.h>
#ifndef LCD_H
#define LCD_H

void lcd_write_byte(uint8_t data);
void lcd_clear(void);
void lcd_print(char *str);
char keypad_key(void);

#endif

