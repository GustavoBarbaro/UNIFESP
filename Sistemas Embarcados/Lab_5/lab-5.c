void main() {

	unsigned int  cont_RB0;
	unsigned int  cont_RB1;
	unsigned int  cont_TOTAL;
	unsigned int  flag_buzzer_led;

	unsigned char ucMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	/* Variavel do tipo vetor que armazena os valores correspondentes ao numero
	para ser mostrado no display de 7 segmentos */


	//unsigned char ucStatus_inc; // Variavel de travamento do incremento.
	unsigned char trava_RB0; // Variavel de travamento do incremento.
	unsigned char trava_RB1; // Variavel de travamento do incremento.
	unsigned char trava_RB2; // Variavel de travamento do incremento.
	unsigned int  aux_cont1;      // Variavel auxiliar para exibido do contador.
	unsigned int  aux_cont2;      // Variavel auxiliar para exibido do contador.


	ADCON1 = 0x0f;       // Configura todos canais como Digital.


	TRISB.RB0=1;         // Define o pino RB0 do PORTB como entrada.
	TRISB.RB1=1;         // Define o pino RB1 Do PORTB como entrada.
	TRISB.RB2=1;         // Define o pino RB2 Do PORTB como entrada.

	TRISA.RA2=0;         // Define o pino RA2 do PORTA como saida(Sele??o Display 1).
	TRISA.RA3=0;         // Define o pino RA3 do PORTA como saida(Sele??o Display 2).
	TRISA.RA4=0;         // Define o pino RA4 do PORTA como saida(Sele??o Display 3).
	TRISA.RA5=0;         // Define o pino RA5 do PORTA como saida(Sele??o Display 4).


	TRISB.RB5=0;         // Define o pino RB5 do PORTA como saida (LED)
	TRISB.RB6=0;         // Define o pino RB6 do PORTA como saida (LED)
	TRISB.RB7=0;         // Define o pino RB7 do PORTA como saida (LED)

	TRISC.RC1=0;      //PORT C configurado como saída (BUZZER)

	TRISD = 0;           // Define todos os pinos Do PORTD como saida.


	cont_RB0 = 0;		//contadores inicializados zerados
	cont_RB1 = 0;
	cont_TOTAL = 0;
	flag_buzzer_led = 0;


	while (1) {
	

		// ==============     fazendo a leitura dos botoes     ==============


		// para BOTAO RB0
		if((PORTB.RB0==0)&&(trava_RB0==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
			trava_RB0=1;                       // Variavel de travamento do incremento.
			cont_RB0++;                         // Esse operador aritmetico(++) realiza o mesmo que variavel = variavel + 1.
			if(cont_RB0>9999){ // Define o valor maximo a ser mostrado no displays como 9999.
				cont_RB0=9999;
			}
		}
		if((PORTB.RB0==1)&&(trava_RB0==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
			trava_RB0=0;
		}

		aux_cont1 = cont_RB0;

		// para BOTAO RB1
		if((PORTB.RB1==0)&&(trava_RB1==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
			trava_RB1=1;                       // Variavel de travamento do incremento.
			cont_RB1++;                         // Esse operador aritmetico(++) realiza o mesmo que variavel = variavel + 1.
			if(cont_RB1>9999){ // Define o valor maximo a ser mostrado no displays como 9999.
				cont_RB1=9999;
			}
		}
		if((PORTB.RB1==1)&&(trava_RB1==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
			trava_RB1=0;
		}

		aux_cont2 = cont_RB1;

		// para BOTAO RB2
		if((PORTB.RB2==0)&&(trava_RB2==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
			trava_RB2=1;                       // Variavel de travamento do incremento.
			cont_RB0 = 0;					//zerando os contadores
			cont_RB1 = 0;
			flag_buzzer_led = 1;
		}
		if((PORTB.RB2==1)&&(trava_RB2==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
			trava_RB2=0;
		}


		// ==============     testando PAR ou IMPAR     ==============
	 
	 

		//EH PAR
		if ((aux_cont1 % 2) == 0){ 
			PORTB.RB6 = 1;
		}
		else{
			PORTB.RB6 = 0;
		}

		//EH IMPAR
		if ((aux_cont2 % 2) == 1){ 
			PORTB.RB7 = 1;	
		}
		else {
			PORTB.RB7 = 0;
		}

		//ligar BUZZER E LED
		if (flag_buzzer_led == 1){

			PORTB.RB5 = 1;				//liga led
			PORTC.RC1 = 1;   //LIGA BUZZER

			delay_ms(100);

			PORTB.RB5 = 0;				//desliga led
			PORTC.RC1 = 0;   			//desliga BUZZER			
			flag_buzzer_led = 0;
		}

		// ==============     Mostrando a soma total (7 seg)     ==============

		cont_TOTAL = aux_cont1 + aux_cont2;

		// Mostra valor da unidade.
		PORTD = ucMask[cont_TOTAL%10];              // Pega modulo da divisao por 10 e coloca o valor no PORTD.
		PORTA.RA5 = 1;                           // Liga o transistor associado ao display 1.
		Delay_ms(2);                             // Delay para escrita no display.
		PORTA.RA5 = 0;                           // Desliga o transistor associado ao display 1.
		cont_TOTAL/=10;                             // Divide variavel por 10 para definir a dezena.
		// Mostra valor da dezena.
		PORTD = ucMask[cont_TOTAL%10];
		PORTA.RA4 = 1;
		Delay_ms(2);
		PORTA.RA4 = 0;
		cont_TOTAL/=10;
		// Mostra valor da centena.
		PORTD = ucMask[cont_TOTAL%10];
		PORTA.RA3 = 1;
		Delay_ms(2);
		PORTA.RA3 = 0;
		cont_TOTAL/=10;
		// Mostra valor do milhar.
		PORTD = ucMask[cont_TOTAL%10];
		PORTA.RA2 = 1;
		Delay_ms(2);
		PORTA.RA2 = 0;



	}
}