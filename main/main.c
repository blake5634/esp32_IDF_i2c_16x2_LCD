#include <stdio.h>
#include "driver/i2c.h"
#include "i2c_lcd.h"
#include "unistd.h"


// #define TwoSec  2000000
// #define OneSec  1000000
#define d100ms   100000
#define  d10ms    10000
#define   d1ms     1000


void app_main(void)
{
    lcd_init();                             // Initialize the LCD
    usleep(d100ms);

    int i=0;
    char numst[20];

    lcd_clear();                            // Clear the LCD screen
    usleep(d100ms);

    lcd_put_cursor(0, 0);                   // Set the cursor position to the first row, first column
    usleep(d100ms);

    lcd_send_string("Hello!");        // Display the string "Hello world!!!" on the LCD
    lcd_put_cursor(1, 0);                   // Set the cursor position to the second row, first column

    while (1){
        lcd_put_cursor(1, 0);                   // Set the cursor position to the second row, first column

        sprintf(numst, "N: %04d",i++);
        lcd_send_string(numst);     // Display the string "from @voidlooop" on the LCD
        usleep(3*d100ms);
        }
}
