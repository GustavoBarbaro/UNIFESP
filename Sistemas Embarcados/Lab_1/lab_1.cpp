// C++ code
//


#define num_escolhido 4

//definindo os pinos do arduino
const int Buzzer = 10;
const int ch_1 = 2; //AMARELO
const int ch_2 = 4; //VERDE
const int ch_3 = 3; //RESET
const int led_vermelho = 13;
const int led_amarelo = 11;
const int led_verde = 12;

//definindo os estados
int estado_ch1 = LOW;
int estado_ch2 = LOW;
int estado_ch3 = LOW;
int last_est_ch1 = LOW;
int last_est_ch2 = LOW;
int last_est_ch3 = LOW;
int estado_led_amarelo = LOW;
int estado_led_vermelho = LOW;
int estado_led_verde = LOW;

//definindo os contadores das chaves
int cont_ch1 = 0;
int cont_ch2 = 0;

//para debounce
unsigned long cont_debounce_time_ch_1 = 0;
unsigned long cont_debounce_time_ch_2 = 0;
unsigned long cont_debounce_time_ch_3 = 0;
unsigned long debounce_time = 5; //ms

int reader_ch1; //usada para como leitora das coisas
int reader_ch2;
int reader_ch3;





void setup()
{
	//transmissao em bits por segundo
	Serial.begin(9600);

	//ENTRADAS E SAIDAS
	pinMode(ch_1, INPUT);
	pinMode(ch_2, INPUT);
	pinMode(ch_3, INPUT);
	pinMode(led_vermelho, OUTPUT);
	pinMode(led_verde, OUTPUT);
	pinMode(led_amarelo, OUTPUT);
	pinMode(Buzzer, OUTPUT);

	Serial.print("Chave 1: ");
	Serial.print(cont_ch1);
	Serial.print("     Chave 2: ");
	Serial.println(cont_ch2);

}

void loop()
{

	//  --------------- chave 1 --------------- //

	//lendo estado da chave 1
	reader_ch1 = digitalRead(ch_1);

	//verificando se houve troca de estado no botao
	if (reader_ch1 != last_est_ch1){
		//salva o tempo
		cont_debounce_time_ch_1 = millis();
	}

	//checa se o tempo de debouce foi atingido
	//ele so entrara nesse if se ja tiver dado o tempo de debouce
	if ((millis() - cont_debounce_time_ch_1) > debounce_time){

		//se o estado do botão 1 ainda nao foi atualizado
		if (reader_ch1 != estado_ch1){
			estado_ch1 = reader_ch1;

			//se a chave 1 esta HIGH atualiza o cont
			if (estado_ch1 == HIGH){
				cont_ch1++;

				//é necessario printar novamente os dados
				Serial.print("Chave 1: ");
				Serial.print(cont_ch1);
				Serial.print("     Chave 2: ");
				Serial.println(cont_ch2);

				//se o valor no contador for par
				if (cont_ch1 % 2 == 0){
					estado_led_amarelo = HIGH;
				}
				else{
					estado_led_amarelo = LOW;
				}
			}
		}
	}

	//armazena o ultimo estado do botao 1
	last_est_ch1 = reader_ch1;

	//mostrar o resultado no led amarelo
	digitalWrite(led_amarelo, estado_led_amarelo);

	//  --------------- chave 2 --------------- //

	//lendo estado da chave 2
	reader_ch2 = digitalRead(ch_2);

	//verificando se houve troca de estado no botao
	if (reader_ch2 != last_est_ch2){
		//salva o tempo
		cont_debounce_time_ch_2 = millis();
	}

	//checa se o tempo de debouce foi atingido
	//ele so entrara nesse if se ja tiver dado o tempo de debouce
	if ((millis() - cont_debounce_time_ch_2) > debounce_time){

		//se o estado do botão 2 ainda nao foi atualizado
		if (reader_ch2 != estado_ch2){
			estado_ch2 = reader_ch2;

			//se a chave 2 esta HIGH atualiza o cont
			if (estado_ch2 == HIGH){
				cont_ch2++;

				//é necessario printar novamente os dados
				Serial.print("Chave 1: ");
				Serial.print(cont_ch1);
				Serial.print("     Chave 2: ");
				Serial.println(cont_ch2);

				//se o valor no contador for impar
				if (cont_ch2 % 2 == 1){
					estado_led_verde = HIGH;
				}
				else{
					estado_led_verde = LOW;
				}
			}
		}
	}

	//armazena o ultimo estado do botao 1
	last_est_ch2 = reader_ch2;

	//mostrar o resultado no led verde
	digitalWrite(led_verde, estado_led_verde);


//  --------------- chave 3 --------------- //

	//lendo estado da chave 3
	reader_ch3 = digitalRead(ch_3);

	//verificando se houve troca de estado no botao
	if (reader_ch3 != last_est_ch3){
		//salva o tempo
		cont_debounce_time_ch_3 = millis();
	}

	//checa se o tempo de debouce foi atingido
	//ele so entrara nesse if se ja tiver dado o tempo de debouce
	if ((millis() - cont_debounce_time_ch_3) > debounce_time){

		//se o estado do botão 3 ainda nao foi atualizado
		if (reader_ch3 != estado_ch3){
			estado_ch3 = reader_ch3;

			//se a chave 3 esta HIGH atualiza o cont
			if (estado_ch3 == HIGH){
				//
				if ((cont_ch1 + cont_ch2) % num_escolhido == 0){
					estado_led_vermelho = HIGH;
					cont_ch1 = 0;
					cont_ch2 = 0;
					digitalWrite(led_vermelho, HIGH);
					delay(1000);
					digitalWrite(led_vermelho, LOW);
				}
				else{
					digitalWrite(led_vermelho, HIGH);
					tone(Buzzer, 235);
					delay(2000);
					digitalWrite(led_vermelho, LOW);
					noTone(Buzzer);
					delay(1000);
					digitalWrite(led_vermelho, HIGH);
					tone(Buzzer, 235);
					delay(2000);
					digitalWrite(led_vermelho, LOW);
					noTone(Buzzer);
				}

				//é necessario printar novamente os dados
				Serial.print("Chave 1: ");
				Serial.print(cont_ch1);
				Serial.print("     Chave 2: ");
				Serial.println(cont_ch2);

			}
		}
	}

	//armazena o ultimo estado do botao 1
	last_est_ch3 = reader_ch3;

}