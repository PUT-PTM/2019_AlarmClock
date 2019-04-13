#ifndef DS3231_H_
#define DS3231_H_
#include "stm32f4xx_hal.h"
#include "sd3231.c"
#define DS3231_ADD  0xD0
#define DS3231_SECONDS_REGISTER 0x00
#define DS3231_ALARM1_SECONDS_REGISTER 0x07
#define DS3231_ALARM2_SECONDS_REGISTER 0x0B
#define DS3231_TEMPERATURE_MSB_REGISTER 0x11
#define DS3231_CONTROL_REGISTER 0x0F

#define secondREG  0x00
#define minuteREG   0x01
#define hourREG      0x02
#define dayREG        0x03
#define dateREG       0x04
#define monthREG    0x05
#define yearREG       0x06

extern uint8_t rtcData[8];
uint8_t I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buf, uint8_t sizebuf);
uint8_t I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buf, uint8_t sizebuf);
void getTimeAndDate(void);

extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart2;
//--------------------------------------
uint8_t rtcData[8];
char str[100];
uint8_t day=0, date=0, month=0, year=0;
uint8_t hour = 0, minute = 0, seconds = 0, amPmStateSet=0, hourFormat = 0;
//--------------------------------------

typedef enum ErrorStat
{
    I2C_Buf_Error = 0x00,
    I2C_Buf_OK = 0x01
}Error_Stat_Typedef;
typedef enum weekDay_Enum_Struct
{
    wdSunday = 0x01,
    wdMonday = 0x02,
    wdTuesday = 0x03,
    wdWednesday = 0x04,
    wdThursday = 0x05,
    wdFriday = 0x06,
    weSaturday = 0x07
}weekDay_t;
typedef struct
{
    uint8_t seconds;    	//00-59
    char secondsTab[2]; 	/*secondsTab[0]=liczba dziesiatek sekund(4.),
         	 	 	 	 	  seconds Tab[1]= liczba jednosci sekund(.5)*/
    uint8_t minutes;    	//00-59
    char minutesTab[2];
        uint8_t hours;      //00-23
    char hoursTab[2];
        uint8_t day;        /* Day in a week 1-7 */
    weekDay_t dayTab;
        uint8_t date;       //1-31
    char dateTab[2];
        uint8_t month;      //1-12
    char monthTab[2];       /* Contains coverted month data*/
        uint8_t year;       //00-99
    char yearTab[2];    	/**/
}DS3231_Time_t;
//--------------------------------------
DS3231_Time_t DS3231_Time;
//--------------------------------------
//czyszczenie bufora domy�lnymi warto�ciami
static uint8_t clearDS3231Buffer(void)
{
    DS3231_Time.seconds = 0;
    DS3231_Time.minutes = 0;
    DS3231_Time.hours = 0;
    DS3231_Time.day = 0;
    DS3231_Time.date = 0;
    DS3231_Time.month = 0;
    DS3231_Time.year = 0;
}
//--------------------------------------
//wypisywanie danych z ukladu
uint8_t I2C_WriteBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buf, uint8_t sizebuf)
{
    while(HAL_I2C_Master_Transmit(&hi, (uint16_t)DEV_ADDR,(uint8_t*)buf,
                (uint16_t)sizebuf, (uint32_t)500)!= HAL_OK)
    {
        if (HAL_I2C_GetError(&hi) != HAL_I2C_ERROR_AF)
        {
            return I2C_Buf_Error;
        }
    }
    return I2C_Buf_OK;
}
//--------------------------------------
//odbieranie danych z ukladu
uint8_t I2C_ReadBuffer(I2C_HandleTypeDef hi, uint8_t DEV_ADDR, uint8_t *buf, uint8_t sizebuf)
{
    while(HAL_I2C_Master_Receive(&hi, (uint16_t)DEV_ADDR, (uint8_t*)buf,
                (uint16_t)sizebuf, (uint32_t)500)!= HAL_OK)
    {
        if (HAL_I2C_GetError(&hi) != HAL_I2C_ERROR_AF)
        {
            return I2C_Buf_Error;
        }
    }
    return I2C_Buf_OK;
}
//-
uint8_t RTC_Init(void)
{
	uint8_t data[2] = {DS3231_CONTROL_REGISTER, 0x00};
	I2C_WriteBuffer(hi2c2, DS3231_ADD, data, sizeof(data));
}
//-----------------------------------------------
inline static uint8_t RTC_ConvertFromDec(uint8_t c)
{
    return ((c>>4)*10+(0x0F&c));
}
//-----------------------------------------------
inline static uint8_t RTC_ConvertFromBinDec(uint8_t c)
{
    return ((c/10)<<4)|(c%10);
}
//-----------------------------------------------
void getTimeAndDate(void)
{
	//clearDS3231Buffer();
	uint8_t rtcData[8];
    I2C_WriteBuffer(hi2c2, (uint16_t)0xD0, rtcData, 1);
    while(HAL_I2C_GetState(&hi2c2)!=HAL_I2C_STATE_READY) { }
    I2C_ReadBuffer(hi2c2, (uint16_t)0xD0, rtcData, 7);

    DS3231_Time.year = rtcData[6];
    DS3231_Time.year = RTC_ConvertFromDec(DS3231_Time.year);

    DS3231_Time.month = rtcData[5];
    DS3231_Time.month = RTC_ConvertFromDec(DS3231_Time.month);

    DS3231_Time.date = rtcData[4];
    DS3231_Time.date = RTC_ConvertFromDec(DS3231_Time.date);

    DS3231_Time.day = rtcData[3];
    DS3231_Time.day = RTC_ConvertFromDec(DS3231_Time.day);

    DS3231_Time.hours = rtcData[2];
    DS3231_Time.hours = RTC_ConvertFromDec(DS3231_Time.hours);

    DS3231_Time.minutes = rtcData[1];
    DS3231_Time.minutes = RTC_ConvertFromDec(DS3231_Time.minutes);

    DS3231_Time.seconds = rtcData[0];
    DS3231_Time.seconds = RTC_ConvertFromDec(DS3231_Time.seconds);
}

///////////USTAWIANIE CZASU

void DS3231_setTime(uint8_t hourToSet, uint8_t minuteToSet, uint8_t  secondToSet, uint8_t amPmStateSet, uint8_t hourFormat)
{
    unsigned char writeValue = 0;

    uint8_t data[2] = {secondREG, (RTC_ConvertFromBinDec(secondToSet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data, sizeof(data));

    uint8_t data2[2] = {minuteREG, (RTC_ConvertFromBinDec(minuteToSet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data2, sizeof(data2));

    uint8_t data3[2] = {hourREG, (RTC_ConvertFromBinDec(hourToSet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data3, sizeof(data3));
}

void DS3231_setDate(uint8_t daySet, uint8_t dateSet, uint8_t monthSet, uint8_t yearSet)
{
	uint8_t data[2] = {dayREG, (RTC_ConvertFromBinDec(daySet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data, sizeof(data));

    uint8_t data2[2] = {dateREG, (RTC_ConvertFromBinDec(dateSet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data2, sizeof(data2));

    uint8_t data3[2] = {monthREG, (RTC_ConvertFromBinDec(monthSet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data3, sizeof(data3));

    uint8_t data4[2] = {yearREG, (RTC_ConvertFromBinDec(yearSet))};
    I2C_WriteBuffer(hi2c2, DS3231_ADD, data4, sizeof(data4));
}

//
uint8_t hexadec_to_dec(uint8_t x)
{
      uint8_t decimal_number, remainder, count = 0;
      while(x > 0)
      {
            remainder = x % 10;
            decimal_number = decimal_number + remainder * pow(16, count);
            x = x / 10;
            count++;
      }
      return decimal_number;
}


#endif /* DS3231_H_ */
