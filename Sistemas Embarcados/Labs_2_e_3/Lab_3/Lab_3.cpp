// C++ code
//

#include <Servo.h>

const int sensor_LDR = A0;

Servo servo_1; //criando um objeto servo


int sensor_read;
int angulo;


void setup(){

	//transmissão em bits por segundo
	Serial.begin(9600);

	pinMode(sensor_LDR, INPUT);
	servo_1.attach(2); //entrada 2 do arduino

}

void loop(){


	sensor_read = analogRead(sensor_LDR);

	angulo = map(sensor_read, 2, 381, 0, 180);

	servo_1.write(angulo);

	Serial.println(angulo);

	delay(15); //aguarda o movimento do servo

}