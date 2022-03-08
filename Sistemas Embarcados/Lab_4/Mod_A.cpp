// C++ code
// MASTER
// MODULO A

#include <Wire.h>

String comando_usuario; //comando inserido pelo usuario

char mensagem_LCD[24]; //p armazenar a mensagem pro LCD

//para fazer o controle das chaves
int botao_1 = 0;
int botao_2 = 0;


void setup(){

	Wire.begin(); //MASTER
	Serial.begin(9600); //inicia monitor serial
}

void loop(){

	int i = 0;
	char comando_usuario_aux[15];
	int mensagem_teste = 0;

	//ler a entrada do usuario no monitor serial

	comando_usuario = "";
	byte controle = 0; //indicará a ação a ser tomada baseado no comando inserido

	//fazendo a leitura
	if (Serial.available()){

		while (Serial.available() > 0){ //continua lendo enquanto tem conteudo
			comando_usuario_aux[i++] = Serial.read();
			delay(6);
		}

		while (i < 15){ //adiciona no final 
			comando_usuario_aux[i++] = '\0';
		}

		comando_usuario = comando_usuario_aux;
	}

	//agora posso checar qual comando foi inserido
	if (comando_usuario.compareTo("LigarLed") == 0){
		controle = 1;
		Serial.println ("Led Ligado");
	}

	if (comando_usuario.compareTo("DesligarLed") == 0){
		controle = 2;
		Serial.println ("Led Desligado");
	}

	if (comando_usuario.compareTo("LigarBuzzer") == 0){
		controle = 3;
		Serial.println ("Buzzer Ligado");
	}

	if (comando_usuario.compareTo("DesligarBuzzer") == 0){
		controle = 4;
		Serial.println ("Buzzer Desligado");
	}

	if (comando_usuario.compareTo("Display LCD") == 0){
		controle = 5;
		Serial.println ("Digite a mensagem desejada");
		i = 0;

		while (1){
			char c;
			while (Serial.available()){
				mensagem_teste = 1;
				c = Serial.read();
				mensagem_LCD[i++] = c;
				delay(25);
			}

			if (!Serial.available() && mensagem_teste){
				break; // porque toda mensagem ja foi lida
			}
		}

		mensagem_LCD[i] = '\0';
		Serial.println("Mensagem Alterada!");
	}

	// tratando agora dos dois botões
	Wire.requestFrom(1,2); //pede o estado do botao ao slave

	i = 0;

	while (Wire.available()){
		int status = Wire.read();

		if (i == 0){ //botao 1
			i++;

			if (status != botao_1){
				botao_1 = status;

				if (status == 1){
					Serial.println("Chave 1 ON");
				}
				else{
					Serial.println("Chave 1 OFF");
				}
			}
		}
		else{
			i = 0;
			if (status != botao_2){
				botao_2 = status;

				if (status == 1){
					Serial.println("Chave 2 ON");
				}
				else{
					Serial.println("Chave 2 OFF");
				}
			}
		}
	}


	Wire.beginTransmission(1); // inicia transmissão p dispositivo 1
	Wire.write(controle); //envia o sinal de controle para o slave

	if (controle == 5){
		Wire.write(mensagem_LCD); //envia mensagem para mostrar no LCD		
	}

	Wire.endTransmission();
	delay(500);

}