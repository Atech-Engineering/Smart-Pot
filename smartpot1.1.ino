/* SmartPot V 1.2
 * Прошивка для умного горшка.
 * Связь по блютуз и запись данных в EEPROM
 * Управление освещением горшка
*/
#include <DS3231.h>
#include <Wire.h>
#include <EEPROM.h>
int flag=0;
DS3231 Clock;
bool h12;
bool PM;
byte hour, minute, second;
void setup()
{
  Wire.begin();
  Serial.begin(9600); // Открываем Serial порт
}

void loop(){
  if (Serial.available()) {
opros();
  }
int second,minute,hour; 
second=Clock.getSecond();
minute=Clock.getMinute();
hour=Clock.getHour(h12, PM);
if(second==00){
info();
}
}
void info(){
  Serial.print("At the moment(");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(minute, DEC);
  Serial.println(")");
  delay(1000);
  }
void opros(){
    int inByte = Serial.parseInt();
    if (inByte==1){
      Serial.println("You specify the amount of irrigation 50 ml");
      EEPROM_int_write(2, 5000);
      Serial.print("Delay = ");
      Serial.println(EEPROM_int_read(2));

      }
          else if (inByte==2){
      Serial.println("You specify the amount of irrigation 100 ml");
      EEPROM_int_write(2, 10000);
      Serial.print("Delay = ");
      Serial.println(EEPROM_int_read(2));
      }
      else if (inByte==3){
      Serial.println("You specify the amount of irrigation 150 ml");
      EEPROM_int_write(2, 15000);
      Serial.print("Delay = ");
      Serial.println(EEPROM_int_read(2));
      }
      else if (inByte==4){
      Serial.println("You requested the current delay");
      Serial.print("Delay = ");
      Serial.println(EEPROM_int_read(2));
      }
      else if (inByte==6){
      Serial.println("Zadaem parametr yarkosti");
      Serial.print("Podsvetka = ");
      EEPROM_int_write(6, 150);
      Serial.println(EEPROM_int_read(6));
      }
      else if (inByte==7){
      Serial.println("Zadaem parametr yarkosti");
      Serial.print("Podsvetka = ");
      EEPROM_int_write(6, 5);
      Serial.println(EEPROM_int_read(6));
      }
      else if(inByte==128&&flag==0){  
      analogWrite(9,EEPROM_int_read(6)); 
      flag=1; 
      Serial.println("Podsvetka vkluchena");
      }
      else if(inByte==129&&flag==1){
      analogWrite(9,0); 
      flag=0; 
      Serial.println("Podsvetka vikluchena");
      }
      }

void pump(){
  digitalWrite(9, HIGH);
  delay(5000);
  int del = EEPROM_int_read(12);
  Serial.print(del);
  }

int EEPROM_int_read(int addr) {    
  byte raw[2];
  for(byte i = 0; i < 2; i++) raw[i] = EEPROM.read(addr+i);
  int &num = (int&)raw;
  return num;
}

void EEPROM_int_write(int addr, int num) {
  byte raw[2];
  (int&)raw = num;
  for(byte i = 0; i < 2; i++) EEPROM.write(addr+i, raw[i]);
}
void poliv(){
    analogWrite(9,250);
    delay(1000);
    analogWrite(9,0);
  }

