#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include "spi.h"
#include "ST7735.h"
#include "glcdfont.c"

int find_greatest_divisor(int n) {
  for (int i = 2000; i >= 1; i--) {
    if (n % i == 0) {
      return i;
    } 
  }
  return 1;
}

void fill_rect_with_color(int x, int y, int w, int h, uint16_t color) {
  ST7735_setAddrWindow(x, y, x + w - 1, y + h - 1, 0x6);
  int len = w * h;
  int arr_len = find_greatest_divisor(len);
  uint16_t tbuf[arr_len];
  for (int i = 0; i < len / arr_len; i++) {
    for (int j = 0; j < arr_len; j++) {
      tbuf[j] = color;
    }
    ST7735_pushColor(tbuf, arr_len);
  }
}

int get_bit_from_byte(int byte, int bit) {
  return byte & (1 << bit);
}

void display_character(int x, int y, char character) {
  int starting_index = character * 5; 
  int len = 5 * 8;
  uint16_t tbuf[len];
  ST7735_setAddrWindow(x, y, x + 4, y + 7, 0x6);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 5; j++) {
      int byte = ASCII[starting_index + j];
      if (get_bit_from_byte(byte, i)) {
        tbuf[5*i + j] = WHITE; // Letter color 
      } else {
        tbuf[5*i + j] = BLUE; // Background color 'BLUE' is red for some reason 
      } 
    }
  }
  ST7735_pushColor(tbuf, len);
}

void display_string(int x, int y, char *str, int len) {
  for (int i = 0; i < len; i++) {
    display_character(x + 6*i, y, str[i]);  
  }
}

void backlightInit(){
// Initialize backlight on PA01
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable peripheral Clocks
    // Enable clocks for GPIO Port A
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Configure Pins
    // Pin PA01 must be configured as an output
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}

int main(void) {
  ST7735_init();
  ST7735_backLight(0);
  fill_rect_with_color(0, 0, 128, 160, BLUE);
  display_string(20, 60, "Elegant Circuits", 16);
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line){
            /* Infinite loop */
                        /* Use GDB to find out why we're here */
                                        while(1);
}
#endif

