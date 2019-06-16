# Overview
Simple watch with display. It can be used to check or set date and time. Watch has also function of alarm with three different sounds. 
# Description
LCD Display it is connected to STM32 and it gets actual information about time from RTC DS3231. 
# Tools
CubeMX v4.1.0
System Workbench for STM32
# How to run
### Software
Application on SM32 and Eclipse to run compiled code on SM32F407G. Computer is used to compile and transfer program.
### Hardware
SMT32F4-DISCOVERY board, 
LCD 2x16, driver compatible with HD44780
RTC DS3231 I2C with battery
Waveshare tile - 8 buttons
LM386M amplifier module with loudspeaker and potentiometers
### Connection instruction 
**RTC DS3231**  
(+) ---> 3V  
D ---> PB11  
C ---> PB10  
N/C ---> GND  
(-) ---> GND  
**LM386M**  
5V ---> 5V  
GND ---> GND  
GND ---> GND  
VCC ---> VDD  
GND ---> GND  
AIN ---> PA4  
**Waveshare tile**  
K0 ---> PB5	(printing time)  
K1 ---> PB4	(increasing setting hours or days)  
K2 ---> PA15	(increasing setting minutes or months)   
K3 ---> PA8	(confirmation of the alarm, date or time setting)  
K4 ---> PB2	(menu to set time)  
K5 ---> PB1	(menu to set alarm)  
K6 ---> PE7	(increasing setting years)   
K7 ---> PE9	(menu to set date)  
To turn off alarm press blue button on the board.   
**I2C with LCD**  
VCC ---> 5V  
SDA ---> PB7  
SCL ---> PB6  
GND--->GND  

# How to compile
You need only to copy the code.
# Future improvements
-add new alarm clocks
-improve case
# Attributions
Base code for LCD: https://www.controllerstech.com/i2c-lcd-in-stm32/  
Base code for DS3231: https://elektronika327.blogspot.com/2017/06/26-stm32f4-rtc-ds3231.html
# License
MIT
# Credits
Result of Arkadiusz Dudziak and Stanisław Kucznerowicz work.
The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor:Tomasz Mańkowski

