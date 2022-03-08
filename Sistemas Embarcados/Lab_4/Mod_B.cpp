// C++ code
// SLAVE


#include <LiquidCrystal.h>
#include <Wire.h> //i2c

//portas usadas pelo cristal LCD
LiquidCrystal lcd (7,6,5,4,3,2);

//portas usadas pelos demais componentes
const int led = 8;
const int buzzer = 11;
const int botao_1 = 9;
const int botao_2 = 10;

//estados dos componentes
int estado_led = LOW;
int estado_buzzer = LOW;
int power_botao_1 = 0;
int power_botao_2 = 0;

//variavies para tratamento do efeito debounce
int estado_botao_1;
int estado_anterior_botao_1 = LOW;
int estado_botao_2;
int estado_anterior_botao_2 = LOW;

unsigned long tempoUltimoApertoB1 = 0;
unsigned long tempoUltimoApertoB2 = 0;
unsigned long tempoDelayDeb = 5; // ms


int controle = 0; // receberá sinais de controle do master de 1 a 5
char mensagem_lcd[24]; //mensagem a ser exibida no lcd



void setup(){

	lcd.begin (16,2); // 2 linhas e 16 colunas
	lcd.clear();

	//Comunicação i2c
	Wire.begin(1); // Slave
	Wire.onReceive (Processa_Mensagem);
	Wire.onRequest (Muda_estado_Botoes_b1_b2);

	//demais atribuições das portas

	pinMode(led, OUTPUT);
	pinMode(buzzer, OUTPUT);
	pinMode(botao_1, INPUT);
	pinMode(botao_2, INPUT);
}



void loop(){


	digitalWrite (led, estado_led);
	digitalWrite (buzzer, estado_buzzer);

	// armazena a leitura dos dois botoes
	int read_botao_1 = digitalRead(botao_1);
	int read_botao_2 = digitalRead(botao_2);

	// verificando as mudanças de estado
	if (read_botao_1 != estado_anterior_botao_1){
		tempoUltimoApertoB1 = millis(); //salva o tempo
	}
	if (read_botao_2 != estado_anterior_botao_2){
		tempoUltimoApertoB2 = millis(); //salva o tempo
	}

	//tratamento do efeito debounce

	// PARA BOTAO 1
	if ((millis() - tempoUltimoApertoB1) > tempoDelayDeb){
		if (read_botao_1 != estado_botao_1){

			estado_botao_1 = read_botao_1;

			//informa Master sobre a mundaça de estado
			if (estado_botao_1 == HIGH){
				if (power_botao_1 == 1){
					power_botao_1 = 0;
				}
				else {
					power_botao_1 = 1;
				}
			}
		}
	}

	// PARA BOTAO 2
	if ((millis() - tempoUltimoApertoB2) > tempoDelayDeb){
		if (read_botao_2 != estado_botao_2){

			estado_botao_2 = read_botao_2;

			//informa Master sobre a mundaça de estado
			if (estado_botao_2 == HIGH){
				if (power_botao_2 == 1){
					power_botao_2 = 0;
				}
				else {
					power_botao_2 = 1;
				}
			}
		}
	}

	// os estados atuais serao os anteriores da proxima iteração
	estado_anterior_botao_1 = read_botao_1;
	estado_anterior_botao_2 = read_botao_2;	
}


void  Processa_Mensagem (int numBytes){
	if (Wire.available()){
		controle = Wire.read();

		switch (controle){
			case 0: // nao faz nada
				break;
			case 1: // LigarLed
				estado_led = HIGH;
				break;
			case 2: // DesligarLed
				estado_led = LOW;
				break;
			case 3: // LigarBuzzer
				estado_buzzer = HIGH;
				break;
			case 4: // DesligarBuzzer
				estado_buzzer = LOW;
				break;
			case 5: // mostrar mensagem no display LCD

				int i = 0;

				//fazendo a leitura da mensagem
				while (Wire.available()){
					char c = Wire.read();
					mensagem_lcd[i++] = c;
				}

				while (i < 24){
					mensagem_lcd[i++] = '\0'; //final de string
				}

				lcd.clear();
				lcd.setCursor(0,0);
				lcd.print(mensagem_lcd); //printando a mensagem
			break;
		}

	}
}


//informa o estado das chaves quando o Master solicita

void Muda_estado_Botoes_b1_b2(){

	Wire.write(power_botao_1);
	Wire.write(power_botao_2);
}