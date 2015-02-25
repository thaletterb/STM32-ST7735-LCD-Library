######################################################
#STM32F100 VL Discovery Board- ST7735 LCD Library    #
######################################################
http://elegantcircuits.com/2014/11/24/stm32f100-st7735-tft-lcd-library/

##Requirements:##
* STM32F100 Value Line Discovery Board
* 1.8" TFT LCD Module (ST7735R)
* ARM GCC Toolchain installed <TT> arm-none-eabi </TT>
* GDB Server
* Library contained in this repository


##Installation:##
* Clone or download a local copy of this repository 
* Inside of the <TT> ST7735LCD </TT> directory is the source code for the LCD library.
 * <TT> spi.c spi.h </TT> is the source for the SPI functions used to communicate with the LCD
 * <TT> ST7735.c ST7735.h </TT> is the source for the various ST7735 LCD functions
 * <TT> main.c </TT> Where main function resides

##Example Commands:##
* Compile: <TT>$make</TT> 

