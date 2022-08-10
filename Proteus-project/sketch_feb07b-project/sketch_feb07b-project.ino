#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
# include "DHT.h"                 //DHT library
# define DHTPIN 0                 //DHT pin
# define DHTTYPE DHT11            
DHT dht(DHTPIN, DHTTYPE);
float t;                                    // temperature in celcius
float h;                                   // humidity in percentage 


#define gas 1

#define echo 9
#define trigger 10
#define tank_pump 4
#define watering_pump 13
#define moisture_sensor A0
long duration;
int distance;
int moisture_value;
int distance_percent;
int moist_percent;
SoftwareSerial SIM900(2,3);
LiquidCrystal lcd(12,11,8,7,6,5);



void setup() {
 lcd.begin(20,4);
 dht.begin();
 SIM900.begin(9600);
 Serial.begin(9600);
 pinMode(gas , INPUT);
 pinMode(echo,INPUT);
 pinMode(moisture_sensor,INPUT);
 pinMode(trigger,OUTPUT);
 pinMode(trigger,LOW);
 pinMode(watering_pump,OUTPUT);
 pinMode(tank_pump,OUTPUT);
  pinMode(watering_pump,LOW);
   pinMode(tank_pump,LOW);
   lcd.setCursor(0,1);
   lcd.print("IRRIGATION PROJECT");
    lcd.setCursor(0,2);
   lcd.print("IoT Project");
    lcd.setCursor(0,3);
   lcd.print("Welcome");
   delay(1000);
   lcd.clear();
   
}

void loop() {
  if(digitalRead(gas) == HIGH){
    lcd.setCursor(0,0);
    lcd.print(" Gas Is Detected ");
   
  }
else{
  lcd.setCursor(0,0);
  lcd.print(" No Gas Detected ");
 
}
delay(1000);
lcd.clear();
 h = dht.readHumidity() ;                                                                                         
  t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C.");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print("% ");
  delay(1000);
digitalWrite(trigger,LOW);
delayMicroseconds(2);
digitalWrite(trigger,HIGH);
delayMicroseconds(10);
digitalWrite(trigger,LOW);
duration=pulseIn(echo,HIGH);
distance=duration*0.017;
distance_percent=map(distance,0,1023,0,100);
moisture_value=analogRead(moisture_sensor);
moist_percent=map(moisture_value,0,1023,0,100);
condition();

}


void sms(){
  SIM900.print("AT+CMGF=1");
  SIM900.println("AT+CMGS=\"+91xxxxxxxxxx\"");
  SIM900.println("watering pump is off");
  SIM900.println((char)26);
  Serial.println((char)26);
  SIM900.println();
}

void sms1(){
  SIM900.print("AT+CMGF=1");
  SIM900.println("AT+CMGS=\"+91xxxxxxxxxx\"");
  SIM900.println("tank pump is off");
  Serial.println("tank pump is off");
  SIM900.println((char)26);
  Serial.println((char)26);
  SIM900.println();
}

void sms2(){
  SIM900.print("AT+CMGF=1");
  SIM900.println("AT+CMGS=\"+91xxxxxxxxxx\"");
  SIM900.println("watering pump is on");
  Serial.print("watering pump is on");
  SIM900.println((char)26);
  Serial.println((char)26);
  SIM900.println();
}

void sms3(){
  SIM900.print("AT+CMGF=1");
  SIM900.println("AT+CMGS=\"+91xxxxxxxxxx\"");
  SIM900.println("tank pump is on");
  Serial.println("tank pump is on  ");
  SIM900.println((char)26);
  Serial.println((char)26);
  SIM900.println();
}

void condition(){
  if (distance_percent>65 && moist_percent<85){
    LCD_3();
    digitalWrite(tank_pump,LOW);
    digitalWrite(watering_pump,HIGH);
    sms1();
    sms2();
    delay(1000);
  }
  else if (distance_percent<65 && moist_percent>85){
    LCD_2();
     digitalWrite(tank_pump,HIGH);
    digitalWrite(watering_pump,LOW);
    sms3();
    sms();
    delay(1000);
  }
 else if (distance_percent>65 && moist_percent>85){
    LCD_4();
    digitalWrite(tank_pump,LOW);
    digitalWrite(watering_pump,LOW);
   sms1();
    sms2();
    delay(1000);
  }

else if (distance_percent<65 && moist_percent<85){
  LCD_1();
   digitalWrite(tank_pump,HIGH);
    digitalWrite(watering_pump,HIGH);
   sms3();
    sms2();
    delay(1000);
}
}


void LCD_1()
{ lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tank Level= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("moist Content= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("W pump status ");
lcd.print("ON");
lcd.setCursor(0,3);
lcd.print("T pump status");
lcd.print("ON");
}

void LCD_2()
{ lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tank Level= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("moist Content= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("W pump status ");
lcd.print("OFF");
lcd.setCursor(0,3);
lcd.print("T pump status");
lcd.print("ON");
}

void LCD_3()
{ lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tank Level= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("moist Content= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("W pump status ");
lcd.print("ON");
lcd.setCursor(0,3);
lcd.print("T pump status");
lcd.print("OFF");
}

void LCD_4()
{ lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tank Level= ");
lcd.print(distance_percent);
lcd.print("%");
lcd.setCursor(0,1);
lcd.print("moist Content= ");
lcd.print(moist_percent);
lcd.print("%");
lcd.setCursor(0,2);
lcd.print("W pump status ");
lcd.print("OFF");
lcd.setCursor(0,3);
lcd.print("T pump status");
lcd.print("OFF");
}
