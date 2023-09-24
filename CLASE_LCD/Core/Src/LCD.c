#include "LCD.h"
#include "stdint.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stdio.h"
#include "stdarg.h"



static uint8_t _lcd_params;
static char _lcd_buffer_[_LCD_nCOL_+1];

void _write_nibble(uint8_t nibble);
void _send_byte(uint8_t value, uint8_t mode);

void _send_byte(uint8_t value, uint8_t mode){

	 switch(mode){
		 case 0: RS_OFF; break;
		 case 1: RS_ON;  break;
	 }
	_write_nibble(value>>4);
	_write_nibble(value&0x0F);
}



void _write_nibble(uint8_t nibble){

	if( (nibble & 1) == 0) D4_OFF; else D4_ON;
	if( (nibble & 2) == 0) D5_OFF; else D5_ON;
	if( (nibble & 4) == 0) D6_OFF; else D6_ON;
	if( (nibble & 8) == 0) D7_OFF; else D7_ON;

	E_OFF;
	E_ON;
	E_OFF;

	HAL_Delay(1);

}

void lcd_stm32_write(uint8_t letra){
	 _send_byte(letra,_DATA_);
}
void lcd_stm32_command(uint8_t cmd){
	 _send_byte(cmd,_COMMAND_);
}


void lcd_stm32_init(void){

	HAL_Delay(15);
	_write_nibble(0x03);
	HAL_Delay(5);
	_write_nibble(0x03);
	HAL_Delay(100);
	_write_nibble(0x03);
	_write_nibble(0x02);


	lcd_stm32_command( _LCD_FUNTIONSET | _LCD_4BITMODE | _LCD_2LINE |_LCD_5x8DOTS );
	HAL_Delay(2);

	_lcd_params = _LCD_DISPLAY_ON | _LCD_CURSOR_ON | _LCD_BLINK_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL | _lcd_params);
	HAL_Delay(2);

	lcd_stm32_command(_LCD_CLEARDISPLAY);
	HAL_Delay(2);

}

void  lcd_stm32_puts(char *str){
	while(*str){
		lcd_stm32_write(*str);
		str++;
	}
}

void lcd_stm32_set_cursor(uint8_t row, uint8_t col){
	static uint8_t local_mem[4]={0x00,0x40,0x14,0x54};
	lcd_stm32_command(_LCD_SET_DDRAM_ADDR | (local_mem[row-1]+(col-1)) );
}

void lcd_stm32_printf(char *str, ...){

	va_list args;
	va_start(args,str);
	vsnprintf(_lcd_buffer_, _LCD_nCOL_+1, str, args);
	va_end(args);
	lcd_stm32_puts(_lcd_buffer_);

}

void lcd_stm32_clear(void){
	lcd_stm32_command(_LCD_CLEARDISPLAY);
	HAL_Delay(2);
}
void lcd_stm32_return_home(void){
	lcd_stm32_command(_LCD_RETURNHOME);
	HAL_Delay(2);
}

void lcd_stm32_on(void){
	_lcd_params |=  _LCD_DISPLAY_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL |_lcd_params);
	HAL_Delay(2);
}
void lcd_stm32_off(void){
	_lcd_params &=  ~_LCD_DISPLAY_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL |_lcd_params);
	HAL_Delay(2);
}

void lcd_stm32_enable_blink(void){
	_lcd_params |= _LCD_BLINK_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL |_lcd_params);
	HAL_Delay(2);
}
void lcd_stm32_disable_blink(void){
	_lcd_params &= ~_LCD_BLINK_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL |_lcd_params);
	HAL_Delay(2);
}

void lcd_stm32_enable_cursor(void){
	_lcd_params |= _LCD_CURSOR_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL |_lcd_params);
	HAL_Delay(2);
}
void lcd_stm32_disable_cursor(void){
	_lcd_params &= ~_LCD_CURSOR_ON;
	lcd_stm32_command(_LCD_DISPLAYCONTROL |_lcd_params);
	HAL_Delay(2);
}

void lcd_stm32_scroll_left(void){
	 lcd_stm32_command(_LCD_CURSORDISPLAYSHIFT | _LCD_DISPLAY_SHIFT | _LCD_MOVELEFT);
	 HAL_Delay(2);
}
void lcd_stm32_scroll_right(void){
	 lcd_stm32_command(_LCD_CURSORDISPLAYSHIFT | _LCD_DISPLAY_SHIFT | _LCD_MOVERIGHT);
	 HAL_Delay(2);
}

void lcd_stm32_custom_char(uint8_t mem, uint8_t *charmap){
	lcd_stm32_command(_LCD_SET_CGRAM_ADDR |  ((mem&0x07)<<3) );
	for(uint8_t i=0; i<=7; i++){
		lcd_stm32_write(charmap[i]);
	}
	lcd_stm32_command(_LCD_SET_DDRAM_ADDR);
	HAL_Delay(1);
}

void lcd_stm32_out(uint8_t r, uint8_t c, char *t){
	lcd_stm32_set_cursor(r, c);
	while(*t){
		lcd_stm32_write(*t);
		t++;
	}
}
void lcd_stm32_char(uint8_t r, uint8_t c, char t){
	lcd_stm32_set_cursor(r, c);
	lcd_stm32_write(t);
}

