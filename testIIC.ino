#include <Wire.h>
#include "MotorControllerMaster.h"
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <L3G.h>

L3G gyro;

MotorControllerMaster c;
long lasthb = 0;
long lastpoll = 0;
long lastsc = 0;
int i = -400;
LiquidCrystal_I2C lcd(0x27,16,2);
//LiquidCrystal lcd(40,41,42,43,44,45);
void setup(){
	//  lcd.begin(16,2);
	Wire.begin();
	Serial.begin(115200);
	delay(1000);
  //lcd.init();
  
  //lcd.setCursor(0,0); 	
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();	
	c.begin();
	c.setAcceleration(1500,1000,2500,1000);
	c.coast();
	//c.goVelocity(i,0);
}



void loop(){
	
	long l;
	long r;


	if (millis() - lastpoll > 100){
		c.getEncoder(&l,&r);
		int8_t s = c.isStandby();
		Serial.println(l);
		Serial.println(r);
		Serial.println(s);
		Serial.println("");
		gyro.read();

		Serial.print("G ");
		Serial.print("X: ");
		Serial.print((int)gyro.g.x);
		Serial.print(" Y: ");
		Serial.print((int)gyro.g.y);
		Serial.print(" Z: ");
		Serial.println((int)gyro.g.z);
		lastpoll = millis();
	}

	if (millis() - lastsc > 4000){
		i += 200;
		//c.goVelocity(i,0);
		lastsc = millis();
	}
	//delay(1000);
	//


	if (millis() - lasthb > 2000){
		c.heartbeat();
		lasthb = millis();	
	}

}
