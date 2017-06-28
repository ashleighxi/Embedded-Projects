#include <board.h>
#include <sysclk.h>
#include <st7565r.h>
#include <gfx_mono.h>
#include <sysfont.h>
#include <conf_usart_example.h>
#include <spi.h>


void setupSerial();
char usart_receiveByte();
void sendChar(char);

int main(void)
{
	//! the page address to write to
	uint8_t page_address;
	//! the column address, or the X pixel.
	uint8_t column_address;
	//! store the LCD controller start draw line
	uint8_t start_line_address = 0;
	uint8_t charH[] = {0,0,0,0,31,4,31,0};
	uint8_t charArray[] = {};
	int counter = 0;
	uint8_t receivedByte;
	int x = 0;
	int y = 0;
	

	board_init();
	sysclk_init();

	// initialize the interface (SPI), ST7565R LCD controller and LCD
	st7565r_init();
	gfx_mono_init();
	static usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SERIAL_EXAMPLE_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	

	usart_init_rs232(USART_SERIAL_EXAMPLE, &USART_SERIAL_OPTIONS);
	// set addresses at beginning of display
	st7565r_set_page_address(0);
	st7565r_set_column_address(0);
	PORTE_OUT = 255;
	st7565r_set_display_start_line_address(start_line_address);

	// fill display with lines
	/*
	for (page_address = 0; page_address <= 4; page_address++) {
		st7565r_set_page_address(page_address);
		for (column_address = 0; column_address < 128; column_address++) {
			st7565r_set_column_address(column_address);
			/* fill every other pixel in the display. This will produce
			horizontal lines on the display. 
			st7565r_write_data(0x00);
			}
	}













	*/



	// scroll the display using hardware support in the LCD controller
	while (true) {
		//st7565r_set_display_start_line_address(start_line_address++);
		//st7565r_write_data(myChar)
		
		receivedByte = usart_getchar(USART_SERIAL_EXAMPLE);
		if (receivedByte == '\r') {
			charArray[counter] = receivedByte;
			usart_putchar(USART_SERIAL_EXAMPLE, charArray[counter]);
			y += 10;
			x = 0;
			counter++;	
			PORTE_OUT = 0;
			delay_ms(100);
			PORTE_OUT = 255;
		} else {
			charArray[counter] = receivedByte;
			gfx_mono_draw_char(charArray[counter], x, y, &sysfont);
			x += 7;
			PORTE_OUT = 0;
			delay_ms(100);
			PORTE_OUT = 255;
			
		}
	}
}
