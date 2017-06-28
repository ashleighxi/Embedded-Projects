
 
#include <asf.h>
#include <avr/io.h>
#include <avr/eeprom.h>
int temp = 0;
uint8_t celsius[20] = {};
int main (void)
{
	// Insert system clock initialization code here (sysclk_init()). 
	board_init();
	uint8_t fahrenheit[20] = {32,34,36,37,39,41,43,45,46,48,50,52,54,55,57,59,61,63,64,66};
	for (int i = 0; i < 20; i++) {
		eeprom_write_byte((uint8_t *)i, fahrenheit[i]); // writing to internalEEprom as an I/O Device via NVM Controller
		temp = eeprom_read_byte((uint8_t *)i); // read from EEprom and assign to temp variable
		temp = (temp - 32) / 1.8; // convert from fahrenheit to celsius
		celsius[i] = temp; // put temp into the celsius array, which goes to SRAM
	}

}
