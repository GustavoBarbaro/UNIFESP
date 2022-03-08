// C++ code
//


// definindo os pinos do arduino
// leds:
/*const int led_0 = 8;
const int led_1 = 9;
const int led_2 = 10;
const int led_3 = 11;
const int led_4 = 12;*/

int leds[5];

const int buzzer = 13;
const int sensor_temp = A0;
const int poten = A1;

int sensor_read;
float temperatura;

/*//definindo os estados dos leds
int led_0 = LOW;
int led_1 = LOW;
int led_2 = LOW;
int led_3 = LOW;
int led_4 = LOW;
*/

void setup (){

	//transmissao em bits por segundo
	Serial.begin(9600);

	int i;

	/*pinMode(led_0, OUTPUT);
	pinMode(led_1, OUTPUT);
	pinMode(led_2, OUTPUT);
	pinMode(led_3, OUTPUT);
	pinMode(led_4, OUTPUT);*/

	for (i = 0; i < 5; i++){
		leds[i] = i + 8; //do 8 ao 12
		pinMode(leds[i], OUTPUT);
	}

	pinMode(buzzer, OUTPUT);
	pinMode(poten, INPUT);
	pinMode(sensor_temp, INPUT);


}


void loop (){

	int i;

	sensor_read = analogRead(sensor_temp);

	//temperatura = map(sensor_read, 20, 358, -40, 125);

	temperatura = (sensor_read - 20) * (125.0 + 40.0) / (356 - 20) - 40;

	Serial.println(temperatura);

	for (i = 0; i < 5; i++){ 
		digitalWrite(leds[i], LOW); //desligando para garantir que estao todos desligados
	}

	if (temperatura >= 25 && temperatura < 27){ //led 1

		digitalWrite(leds[0], HIGH);
	}

	else if (temperatura >= 27 && temperatura < 29){
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
	}

	else if (temperatura >= 29 && temperatura < 31){
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
	}

	else if (temperatura >= 31 && temperatura < 34){
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
		digitalWrite(leds[3], HIGH);
	}

	else if (temperatura == 34){
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
		digitalWrite(leds[3], HIGH);
		digitalWrite(leds[4], HIGH);
	}




	delay(1000); //espera por 2 segundos

}