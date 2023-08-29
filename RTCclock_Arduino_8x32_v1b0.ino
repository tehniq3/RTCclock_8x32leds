/* original design by niq_ro: https://github.com/tehniq3/
 * RTC clock v.0.a - added RTC (DS3231/DS1307)
 * v.0.b - added thermometer with DS18B20 sensor  
 * v.1 - added animation for temperature as at https://github.com/tehniq3/NTP_8x32leds2/blob/main/NTPclock_8x32_v2_1.ino
 * v.1.a - moving points
 * v.1.a2 - correct point syntax
 * v.1.b - added date and year in animation
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>  // https://github.com/adafruit/Adafruit_NeoMatrix
#include <Adafruit_NeoPixel.h>  
/*
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif
*/

#define LED_PIN 12      // GPIO12= D6  // matrix pin
#define RTC_SDA 4       // GPIO4 = D2
#define RTC_SCL 5       // GPIO5 = D1
#define ONE_WIRE_BUS 14 // GPIO14= D5  // DS18B20 pin

// MATRIX DECLARATION:
// Parameter 1 = width of the matrix
// Parameter 2 = height of the matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, LED_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);   // https://www.adafruit.com/product/2294

const uint16_t colors[] = {
  matrix.Color(255, 0, 0),    // red
  matrix.Color(0, 255, 0),    // green
  matrix.Color(255, 255, 0),  // yellow
  matrix.Color(0, 0, 255),    // blue 
  matrix.Color(255, 0, 255),  // mouve
  matrix.Color(0, 255, 255),  // bleu (ligh blue)
  matrix.Color(255, 255, 255) // white 
  };
const uint16_t culori[21] = {
  0,255,255,
  255,0,255,
  0,0,255,
  255,255,0,
  0,255,0,
  255,0,0,
  255,0,255};

// WS2812b day / night brightness.
#define NIGHTBRIGHTNESS 3      // Brightness level from 0 (off) to 255 (full brightness)
#define DAYBRIGHTNESS 20

String text = "RTC clock by niq_ro on 8x32 addressable led display !";
int ltext = 6*text.length();  // lengh of string
int x;

int ora = 20;
int minut = 24;
int secundar = 0;
int zi, zi2, luna, an;
unsigned long unixora;

byte culoare = 1;
byte schimbare = 1;

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

RTC_DS1307 rtc;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

float te = -23.2;  // demo temperature
float tempC;
byte semnminus = 0;
int te0, te1, te2;
int ltempe;
byte aratadata = 1;

const int secpl[] = {  7,  8,  23, 24, 39, 40, 55, 56, 71, 72,
                      87, 88, 103,104,119,120,135,136,151,152,
                     167,168,183,184,199,200,215,216,231,232}; 
byte culsec = 0;
byte culsec1 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("----");  

  sensors.begin();   // Start up the DS18B20 library

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

delay(1000);
DateTime now = rtc.now();
unixora = now.unixtime();
ora = now.hour();
minut = now.minute();
secundar = now.second();
zi = now.dayOfTheWeek();
zi2 = now.day();
an = now.year();
luna = now.month();
Serial.print(ora);
Serial.print(":");
Serial.print(minut);
Serial.print(" -> (");
Serial.print(zi);
Serial.print(") ");
Serial.print(zi2);
Serial.print("/");
Serial.print(luna);
Serial.print("/");
Serial.println(an);

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(NIGHTBRIGHTNESS);  // original 255
  matrix.setTextColor(colors[6]);
  matrix.fillScreen(0);
matrix.setCursor(1, 0);
matrix.print(F("v.1.b"));
//matrix.print(ceas);
matrix.setPixelColor(255, 150, 0, 0);
matrix.show();
delay(2000);

x    = matrix.width();
matrix.fillScreen(0);
  for (x; x > -ltext ; x--)
  {
  matrix.fillScreen(0); 
  matrix.setCursor(x, 0);
  matrix.print(text);  
  matrix.show();
  delay(30);
 }
    delay(500);

citiresenzor();
}

void loop() {
DateTime now = rtc.now();
ora = now.hour();
minut = now.minute();
secundar = now.second();
unixora = now.unixtime();
zi = now.dayOfTheWeek();
zi2 = now.day();
an = now.year();
luna = now.month();
Serial.print(ora);
Serial.print(":");
Serial.print(minut);
Serial.print(" -> (");
Serial.print(zi);
Serial.print(") ");
Serial.print(zi2);
Serial.print("/");
Serial.print(luna);
Serial.print("/");
Serial.print(an);
Serial.println(" -");

if ((secundar == 0) or (secundar == 55))
   {
   schimbare = 0;
   delay(600);
   }


if ((secundar > 35) and (aratadata == 1))
{
 if (schimbare == 0)
    {
    culoare++;
    if (culoare > 6) culoare = 0;
    schimbare = 1;
    }

String tempe;    
if (minut%2 == 0)
{
tempe = tempe + "temperature: ";
if (tempC > 0) tempe = tempe + "+";
tempe = tempe + te1 + ","+ te2;
tempe = tempe + ((char)247) + "C";  // https://forum.arduino.cc/t/degree-symbol/166709/9
ltempe = 6*tempe.length();  // 6*72;
}
else
{
tempe = tempe + weekDays[zi];  
tempe = tempe + ", ";
tempe = tempe + zi2;
tempe = tempe + ".";
tempe = tempe + months[luna-1];
tempe = tempe + ".";
tempe = tempe + an;
ltempe = 6*tempe.length();  // 6*72;
}

matrix.setTextColor(colors[culoare]);
x = matrix.width();
  for (x; x > -ltempe ; x--)
  {
  matrix.fillScreen(0); 
  matrix.setCursor(x, 0);
  matrix.print(tempe);  
  delay(100);

DateTime now = rtc.now();
secundar = now.second();
culsec = secundar%30;
Serial.print(culsec);
culsec1 = secpl[culsec];
Serial.print(" -> ");
Serial.println(culsec1);
matrix.setPixelColor(culsec1, culori[3*culoare], culori[3*culoare+1], culori[3*culoare+2]);  
matrix.show();
 } 
 aratadata = 0; 
  culoare++;
  if (culoare > 6) culoare = 0; 
}
else
{
matrix.fillScreen(0);
matrix.setTextColor(colors[culoare]);
matrix.setCursor(1, 0);
//matrix.print(F("_"));
matrix.print(ora/10);
matrix.print(ora%10);
 if (secundar%2 == 0)
      matrix.print(F(":"));
 else
      matrix.print(F(" "));
matrix.print(minut/10);
matrix.print(minut%10);
culsec = secundar%30;
Serial.print(culsec);
culsec1 = secpl[culsec];
Serial.print(" -> ");
Serial.println(culsec1);
matrix.setPixelColor(culsec1, culori[3*culoare], culori[3*culoare+1], culori[3*culoare+2]);   
matrix.show();
}

if (secundar == 57)
{
  citiresenzor();
}

if (secundar == 0) aratadata = 1;
delay(500);
}  // end main loop

void citiresenzor()
{
 // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
if (tempC < 0.)
    {
    semnminus = 1;
    te = -tempC;
    }
 else
    {
    semnminus = 0;
    te = tempC;
    }
    te0 = te *10.;
    te1 = te0/10;
    te2 = te0%10;    
}
