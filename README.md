# RTCclock_8x32leds

1st article: https://nicuflorica.blogspot.com/2023/08/ceas-rtc-pe-afisaj-8x32-cu-leduri.html

2nd article: https://nicuflorica.blogspot.com/2023/09/ceas-rtc-pe-afisaj-8x32-cu-leduri.html

![1](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEi3hnRkptmj2VVM_KXKLmfmUNOeLJxmhDZ5YPAQQWboDrAF-Oxsn9ZaXtxjS2a9DbH1wmKnLcAejZZop3bsV21cdrjUxyZFzwm7LOG_XmqJp1vLsDTEfs1BXf8F3KdspvBpgLEIEu4NfgFOKSlIgbP5_1T-pgL8oRqQkTrBmqwWOQi22WIQodr6CugLncGR/w200-h150/RTC_clock_wemos_02.jpg)
![2](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgra965x99Z_ZjJ1gaxm1Ckmlc9ivdnlmhMc1ngj2AbjxnHwXZUqhLABxVqHOVMfs4I8tS-V5huOSun20NNkQMJJcxWvZQdvOFbij21fWaV1YsfuewBZ-qEZ48f_Hjq1s8zOAZDbWiDXzONMWVdQ48EFH6EjEFIULWgdU4ieHhyXbbE28NHegIQVsJn4P7R/w200-h150/RTC_clock_wemos_01.jpg)

![schematic](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEgSBAhUybHtTLmnmhmUcjyQtSOwkIy4qLJHpd2rlpvvfH6gF0XjU_uS4DUUdgpXYtaMiTc4qda_ifiiSE8eyLTDL2qJhIxw4eNzycnHqKhmrPA1SrVHVHWwi3Q-V3IAMX5dt2UBUkZY-TcIFbKg8-cdspE7UGhClg4yD8BFIqV9jaRHB5-zQ-uiCCxzNJ8R/s1817/RTC_clock_DS18B20_8x32_ws2812_sch_v1.png)

RTC clock on 8x32 adressable led display using Wemos D1 board (ESP8266)

#define LED_PIN 12      // GPIO12= D6 for matrix pin

#define RTC_SDA 4       // GPIO4 = D2 for RTC module (DS3231/DS1307)

#define RTC_SCL 5       // GPIO5 = D1 for RTC module (DS3231/DS1307)

#define ONE_WIRE_BUS 14 // GPIO14= D5 for DS18B20 pin
