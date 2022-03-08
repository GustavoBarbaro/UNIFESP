// C++ code
//



int leds[5];

const int buzzer = 13;
const int sensor_temp = A0;
const int poten = A1;

int sensor_read;
int poten_read;
int time_control;
float temperatura;
float potencia_sleep;

//definindo os estados dos leds
int led_state = LOW;

unsigned long led_milis = 0;
unsigned long buzzer_milis = 0;


void setup (){

	//transmissao em bits por segundo
	Serial.begin(9600);

	int i;

	

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

	time_control = 1000;
	sensor_read = analogRead(sensor_temp);
	poten_read = analogRead(poten);

	//temperatura = map(sensor_read, 20, 358, -40, 125);

	temperatura = (sensor_read - 20) * (125.0 + 40.0) / (356 - 20) - 40;

	potencia_sleep = map (poten_read, 1, 1022, 2000, 10000);

	Serial.println(temperatura);
	

	for (i = 0; i < 5; i++){ 
		digitalWrite(leds[i], LOW); //desligando para garantir que estao todos desligados
	}

	if (temperatura >= 25 && temperatura < 27){ //leds que devem acender 1

		digitalWrite(leds[0], HIGH);
	}

	else if (temperatura >= 27 && temperatura < 29){ //leds que devem acender 2
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
	}

	else if (temperatura >= 29 && temperatura < 31){ //leds que devem acender 3
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
	}

	else if (temperatura >= 31 && temperatura < 34){ //leds que devem acender 4
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
		digitalWrite(leds[3], HIGH);
	}

	else if (temperatura >= 34 && temperatura < 35){ //leds que devem acender 5
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
		digitalWrite(leds[3], HIGH);
		digitalWrite(leds[4], HIGH);
	}

	else if (temperatura >= 35){ //caso acima onde o sistema deve piscar
		time_control = potencia_sleep;

		
		if ((millis() - led_milis) >= time_control/2){
			led_milis = millis();

			if(led_state == LOW){
				led_state = HIGH;
			}
			else{
				led_state = LOW;
			}

			if ((millis() - buzzer_milis) > time_control){

				buzzer_milis = millis();

				tone(buzzer, 235, 250);
			}

			for (i = 0; i < 5; i++){ 
				digitalWrite(leds[i], led_state);
			}
		}
		
	}


	


	delay(1000); //espera por 1 segundos

}