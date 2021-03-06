#ifndef SSD1306_H
#define SSD1306_H

void Init_lcd(void);
void Update_lcd(void);
void LCD_cls (void);
void LCD_clear_screen_buff(void);
void LCD_Set_pos (uint8_t x, uint8_t y);
void LCD_print_char(char c);
void LCD_print_str (uint8_t clm, uint8_t lin, char *str);
void LCD_print_hex (uint8_t b);

#endif