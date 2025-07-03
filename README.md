# 16x2 LCD via i2C working example
#### This  repo is modified from [*voidloopprobotech*'s](https://github.com/voidlooprobotech) [Excellent Github Resource:](https://github.com/voidlooprobotech/ESP32_ESP-IDF_Code/tree/main/14_I2C_LCD_16x2)      ["14_I2C_LCD_16x2"](https://github.com/voidlooprobotech/ESP32_ESP-IDF_Code/tree/main/14_I2C_LCD_16x2)

[Voidloop's  video](https://www.youtube.com/watch?v=L955fIgIHu8)


I am an experienced embedded software engineer (and Professor) and I was shocked at how difficult this was.    Using these devices on Arduino with the Arduino IDE "just works."    Pain points for ESP-IDF implementation were:

- "Old" and "New" i2c libraries for ESP-IDF.    Reading tutorials and example code is very confusing because most people don't identify what they are using. 
- Watch for subtle details of the examples out there.  For example, did they use an i2c backpack? or hard wire directly  to the LCD using 6 GPIO's (totally different sw). 
- AI "helpers" are also totally confused by these details so they are only occasionally helpful.
- Lots of advice out there on hardware problems like pullups and signal integrity, but they were a waste of time for me (using my oscilloscope).    If the hookup you have would work on an Arduino, (i.e. Arduino hardware), then it will work with the ESP32.   Of course check and double check your wiring but in the end there were no signal integrity roadblocks with this hardware setup and random looking wiring.
- Delays had to be added to main.c after lcd_init() lcd_clear() etc. to get clear stable output.  I used the microsecond sleep function, usleep(int), but in a real app these should be changed to vTaskDelay(ticks) calls because I believe usleep() is blocking the whole CPU. 

-  **Hardware:** 

    -  [Waveshare ESP32-C6-zero](https://www.waveshare.com/wiki/ESP32-C6-Zero)
    

    -  Cheap 16x2 LCD with backpack: [(example)](https://www.amazon.com/GeeekPi-Character-Backlight-Raspberry-Electrical/dp/B07S7PJYM6/ref=sr_1_5?adgrpid=1238050438773692&hvadid=77378320683510&hvbmt=bp&hvdev=c&hvlocphy=111279&hvnetw=s&hvqmt=p&hvtargid=kwd-77378420155715%3Aloc-190&hydadcr=9279_13641273&mcid=0ed11c3b48fd384eb13fcc365913a001&sr=8-5])

    -  Backpack port expander chip 8574A (or 8574)  

    -  SDA: Pin 5,  SCL: Pin 3

- **Software**: 
    
   - ESP 32-IDF toolchain (version     5.3.3)
       
   - OS: Ubuntu linux. 
              
   - IDE:  comand line and text editor
       
 Wiring Diagram:
 
  
```
 LCD Backpack                     ESP32-C6-Zero
┌─────────────┐                 ┌──────────────┐
│     GND     │ ◄────────────── │  GND         │
│     VCC     │ ◄────────────── │  +5V         │
|             |                 |  -           |
|             |                 |  -           |
|             |                 |  -           |
|             |                 |  -           |
│     SCL     │ ◄────────────── │ SCL GPIO-3   │
|             |                 |  -           |
│     SDA     │ ◄────────────── │ SDA GPIO-5   │
└─────────────┘                 └──────────────┘
```

 

## Tips:



-  **Modify i2c_lcd.h** according to your specific hardware as follows:
    
    - Check your backpack chip number and your i2c device address as follows (use one of these two
    defines):
         #define SLAVE_ADDRESS_LCD 0x3f      // 8574A
         #define SLAVE_ADDRESS_LCD 0x27      // 8574
    
   - Set up your GPIO pins according to your hardware connections.   To set according to my diagram above: 
	   // GPIO number used for I2C master clock
	   #define I2C_MASTER_SCL_IO           GPIO_NUM_3
	
	   // GPIO number used for I2C master data
	   #define I2C_MASTER_SDA_IO           GPIO_NUM_5

   - Do not modify i2c clockrate!   It is set right now  at 400kHz.  In theory, a slower 
clock rate could reduce any signal integrity issues but in actuality (at least with my hardware) the backpack doesn't work (scrambled characters) at e.g. 100kHz(!)     Change clock rate at your own risk. 
>       // I2C master clock frequency
>       #define I2C_MASTER_FREQ_HZ          400000
  
- Carefully **set up your idf build** as follows:
```bash
          >cd <Project Directory>
		  >rm -rf build/
		  >idf.py set-target esp32c6
		  >idf.py build
		  >idf.py flash monitor
	 
```

## Useful References:

- [Hitachi LCD controller](https://cdn.sparkfun.com/assets/9/5/f/7/b/HD44780.pdf)

- [Datasheet](https://pdf.direnc.net/upload/tc1602a.pdf) for a typical 16x2 LCD module

- [Hardware Info](https://alselectro.wordpress.com/2016/05/12/serial-lcd-i2c-module-pcf8574/) on backpack PCB 

- [Arduino-based 16x2 Tutorial](https://www.electronicsforu.com/technology-trends/learn-electronics/16x2-lcd-pinout-diagram) hookup, defining special characters, pinouts and commands. 



 
