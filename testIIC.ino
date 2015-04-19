#include <Wire.h>
#include "MotorControllerMaster.h"
#include <LiquidCrystal.h>

MotorControllerMaster c;
long lasthb = 0;
long lastpoll = 0;
LiquidCrystal lcd(40,41,42,43,44,45);
void setup(){
	  lcd.begin(16,2);
	Wire.begin();
	Serial.begin(115200);
	delay(1000);
	c.begin();
	c.setAcceleration(1500,1000,2500,1000);
	c.brake();
	c.goVelocity(0,90);
}



void loop(){
	
	long l;
	long r;


	if (millis() - lastpoll > 20){
		c.getEncoder(&l,&r);
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(l);
		lcd.setCursor(0,1);
		lcd.println((long)r);
		//Serial.println("");

		lastpoll = millis();	
		if (r > 360*10){
			c.brake();
		}
	}


	//delay(1000);
	//


	if (millis() - lasthb > 2000){
		c.heartbeat();
		lasthb = millis();	
	}

}
