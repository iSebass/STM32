
#ifndef INC_LCD_H_
#define INC_LCD_H_


#include "stdint.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stdio.h"
#include "stdarg.h"


/************************************************************************/
/* Comportamiento de RS                                                 */
/************************************************************************/
#define _COMMAND_      0
#define _DATA_         1

/************************************************************************/
/* DEFINIR EL PUERTO DONDE SE VA CONECTAR LA LCD                        */
/************************************************************************/
#define E_ON   HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 1)
#define E_OFF  HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0)

#define RS_ON  HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 1)
#define RS_OFF HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 0)

#define D4_ON  HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 1)
#define D4_OFF HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0)
#define D5_ON  HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 1)
#define D5_OFF HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0)
#define D6_ON  HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1)
#define D6_OFF HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0)
#define D7_ON  HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 1)
#define D7_OFF HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0)



#define _LCD_nCOL_       20
#define _LCD_nROW_       4

/************************************************************************/
/*  MODO CELAR DISPLAY:  D7 D6 D5 D4 D3 D2 D1 D0                        */
/*                       0  0  0  0  0  0  0  1                         */
/************************************************************************/
#define _LCD_CLEARDISPLAY 0x01

/************************************************************************/
/*  MODO CELAR RETURN HOME:  D7 D6 D5 D4 D3 D2 D1 D0                    */
/*                           0  0  0  0  0  0  1  0                     */
/************************************************************************/
#define _LCD_RETURNHOME     0x02

/************************************************************************/
/*      ENTRAMOS EN MODE SET:  D7 D6 D5 D4 D3 D2 D1  D0                 */
/*      					   0  0  0  0  0  1  I/D  S                 */
/*----------------------------------------------------------------------*/
/*      I/D = 1: Inc                                                    */
/*		      0: Dec                                                    */
/*		S   = 1: SHIFT ON                                               */
/*            0: SHIFT OFF                                              */
/************************************************************************/
#define _LCD_ENTRYMODESET   0x04
#define _LCD_INCREMENT      0x02
#define _LCD_DECREMENT      0x00
#define _LCD_SHIFT_ON       0x01
#define _LCD_SHIFT_OFF      0x00

/************************************************************************/
/*      ENTRAMOS EN DISPLAY CONTROL:  D7 D6 D5 D4  D3 D2 D1 D0          */
/*      						      0  0  0  0   1  D  U  B           */
/*----------------------------------------------------------------------*/
/*      D   = 1: DISPLAY ON                                             */
/*		      0: DISPLAY OFF                                            */
/*		U   = 1: CURSOR ON                                              */
/*		      0: CURSOR OFF                                             */
/*		B   = 1: BLINK                                                  */
/*		      0: NO BLINK                                               */
/************************************************************************/
#define _LCD_DISPLAYCONTROL 0x08
#define _LCD_DISPLAY_ON     0x04
#define _LCD_DISPLAY_OFF    0x00
#define _LCD_CURSOR_ON      0x02
#define _LCD_CURSOR_OFF     0x00
#define _LCD_BLINK_ON       0x01
#define _LCD_BLINK_OFF      0x00

/************************************************************************/
/* ENTRAMOS EN CURSOR OR DISPLAY SHIFT:  D7 D6 D5 D4  D3 D2  D1 D0      */
/*      						         0  0  0  1  S/C R/L  *  *      */
/*----------------------------------------------------------------------*/
/*      S/C = 1: display shift                                          */
/*		      0: cursor move                                            */
/*		R/L = 1: shift to the right                                     */
/*		      0: shift to the left                                      */
/************************************************************************/
#define _LCD_CURSORDISPLAYSHIFT 0x10
#define _LCD_DISPLAY_SHIFT      0x08
#define _LCD_CURSOR_SHIFT       0x00
#define _LCD_MOVERIGHT          0x04
#define _LCD_MOVELEFT           0x00

/************************************************************************/
/*      ENTRAMOS EN FUNTIONS SET:  D7 D6 D5 D4  D3 D2 D1 D0             */
/*      						   0  0  1  D/L  N  F  *  *             */
/*----------------------------------------------------------------------*/
/*      D/L = 1: modo 8 bits                                            */
/*		      0: modo 4 btis                                            */
/*		N   = 1: MODO 2 Lineas                                          */
/*		      0: MODO 1 Linea                                           */
/*		F   = 1: MATRIZ 5x10                                            */
/*		      0: MATRIZ 5x7/5x8                                         */
/************************************************************************/
#define _LCD_FUNTIONSET 0x20
#define _LCD_8BITMODE   0x10
#define _LCD_4BITMODE   0x00
#define _LCD_2LINE      0x08
#define _LCD_1LINE      0x00
#define _LCD_5x10DOTS   0x04
#define _LCD_5x8DOTS    0x00


/************************************************************************/
/*      SET CGRAM:  D7 D6  D5  D4   D3   D2   D1   D0                   */
/*      			0  1   ACG ACG  ACG  ACG  ACG  ACG                  */
/*----------------------------------------------------------------------*/
/*      ACG -> CGRAM ADDRESS                                            */
/************************************************************************/
#define _LCD_SET_CGRAM_ADDR  0x40

/************************************************************************/
/*      SET DDRAM:  D7 D6  D5  D4   D3   D2   D1   D0                   */
/*      			1  0   ADD ADD  ADD  ADD  ADD  ADD                  */
/*----------------------------------------------------------------------*/
/*      ADD -> DDRAM ADDRESS                                            */
/************************************************************************/
#define _LCD_SET_DDRAM_ADDR  0x80

/************************************************************************/
/* METODOS DE LIBRERIA                                                  */
/************************************************************************/

void lcd_stm32_init(void);
void lcd_stm32_write(uint8_t letra);
void lcd_stm32_command(uint8_t cmd);

void lcd_stm32_puts(char *str);
void lcd_stm32_set_cursor(uint8_t row, uint8_t col);
void lcd_stm32_printf(char *str, ...);

void lcd_stm32_clear(void);
void lcd_stm32_return_home(void);
void lcd_stm32_on(void);
void lcd_stm32_off(void);

void lcd_stm32_enable_blink(void);
void lcd_stm32_disable_blink(void);

void lcd_stm32_enable_cursor(void);
void lcd_stm32_disable_cursor(void);

void lcd_stm32_scroll_left(void);
void lcd_stm32_scroll_right(void);

void lcd_stm32_custom_char(uint8_t mem, uint8_t *charmap);

void lcd_stm32_out(uint8_t r, uint8_t c, char *t);
void lcd_stm32_char(uint8_t r, uint8_t c, char t);



#endif /* INC_LCD_H_ */
