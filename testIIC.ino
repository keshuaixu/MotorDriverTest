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
long lastturn = 0;
//LiquidCrystal_I2C lcd(0x27,16,2);
//LiquidCrystal lcd(40,41,42,43,44,45);
void setup(){
	//  lcd.begin(16,2);
	pinMode(9,OUTPUT);
	digitalWrite(9,LOW);
	Wire.begin();
	Serial.begin(115200);
	delay(1000);
  //lcd.init();
  /*
  //lcd.setCursor(0,0); 	
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();	
  */
	c.begin();
	c.setAcceleration(1500,1000,2500,1000);
	c.coast();
	//c.goVelocity(i,0);
}


int i;
int j;


//PD for rotating 90 degs
const float kp = 1.3;
const float kd = 2.2;
/*

const float kp = 3.8;
const float kd = 1.5;
*/
int lasterr;
void loop(){
	
	long l;
	long r;
	long now = millis();

	if (now - lastpoll > 10){
		c.getEncoder(&l,&r);
		int err = i - r;
		int out = constrain((err)*kp + (err - lasterr)*kd,-90,90);
		c.goVelocity(0,out);
		Serial.println(err);
		lastpoll = now;
		lasterr = err;
	}

/*
	if (now - lastpoll > 10){
		c.getEncoder(&l,&r);
		int err = i - l;
		int out = constrain((err)*kp + (err - lasterr)*kd,-100,100);
		c.goVelocity(out,0);
		Serial.println(err);
		lastpoll = now;
		lasterr = err;
	}
*/
	//delay(1000);
	//


	if (now - lasthb > 4000){
		c.heartbeat();
		lasthb = now;	
		if (j++%2 == 1) digitalWrite(9,LOW);
		else analogWrite(9,0);
	}

	if (now - lastturn > 4000 && abs(lasterr) < 4){
		/*
		if (j++%2 == 1) i = 90;
		else i = 0;
		*/
		i += 90;
		lastturn = now;
		/*
		if (i > 1000){
			i = 1000;
		}
		*/

	}
}
