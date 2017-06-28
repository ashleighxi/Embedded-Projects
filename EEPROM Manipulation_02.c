/*
 * lab2p3.c
 *
 * Created: 6/7/2017 2:27:23 PM
 *  Author: Hunter
 */ 
 
 #include <asf.h>
 #include <avr/io.h>
 #include <avr/eeprom.h>

 int main (void)
 {
	 board_init();
	 uint8_t fahrenheit[20] = {32,34,36,37,39,41,43,45,46,48,50,52,54,55,57,59,61,63,64,66};
	 for (int i = 0; i < 20; i++) {
		 eeprom_write_byte((uint8_t *)i + 20, fahrenheit[i]); // writing to internalEEprom as an I/O Device via NVM Controller
	 }
	 
 }
 