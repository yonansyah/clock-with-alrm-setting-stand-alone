
#include "DHT.h"

#define DHTPIN 18   // what pin we're connected to
#define DHTTYPE DHT22
DHT dht (DHTPIN, DHTTYPE);
int suhu;
int kelembaban;

#include <RTClib.h>
RTC_DS1307 rtc;
DateTime now;

// symbol temp
byte thermometer_symbol[8] = 
      {
        B00100,
        B01010,
        B01010,
        B01110,
        B01110,
        B11111,
        B11111,
        B01110
      };
  

#define led 5 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  lcd.createChar(1, thermometer_symbol);
  
  rtc.begin();
  Serial.println("Hello, ESP32!");
  pinMode(led, OUTPUT);

  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting");
  lcd.setCursor(0, 1);
  lcd.print("Github/yonansyah");
  delay(2000);
  lcd.clear();
}

void loop() {

  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);

  void getdataDHT();
  {
      // deklarasi
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      suhu = t;
      kelembaban = h;
      
      // Check
      if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

      Serial.print("Suhu = ");
      Serial.print(suhu);
      Serial.println();
      Serial.print("Kelembaban = ");;
      Serial.print(kelembaban);
      Serial.println();
      Serial.println("================");
      delay(1000);

      lcd.setCursor(0, 1);
      // lcd.print(char(1));
      lcd.print("T: ");
      lcd.print(suhu);     
      lcd.print((char)223); 
      lcd.print("C");

      // lcd.setCursor(9, 0); 
      // lcd.print("H: ");
      // lcd.print(kelembaban); 
      // lcd.print("%");
  }
  
  void getdataRTC();
  {
    now=rtc.now();
    char buf[25];
    lcd.setCursor(0,0); sprintf(
                                buf,"<%02d/%02d/%2d> %02d:%02d:%02d",
                                now.day(),
                                now.month(),
                                now.year()%100,
                                now.hour(),
                                now.minute()
                                //now.second()
                              );
    lcd.print(buf);
    Serial.println(buf);
  }

}
