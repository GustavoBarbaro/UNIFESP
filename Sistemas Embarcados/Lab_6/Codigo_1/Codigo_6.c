
//configurando lcd no modo 4 bits

sbit LCD_RS at RE2_bit;// PINO 2 DO PORTD INTERLIGADO AO RS DO DISPLAY //dados
sbit LCD_EN at RE1_bit;// PINO 3 DO PORTD INTERLIGADO AO EN DO DISPLAY //habilitar/receber
sbit LCD_D7 at RD7_bit;// PINO 7 DO PORTD INTERLIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;// PINO 6 DO PORTD INTERLIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;// PINO 5 DO PORTD INTERLIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;// PINO 4 DO PORTD INTERLIGADO AO D4 DO DISPLAY

// Selecionando direção de fluxo de dados dos pinos utilizados para a comunicação com display LCD
sbit LCD_RS_Direction at TRISE2_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;  // SETA DIREÇÃO DO FLUXO DE DADOS DO PINO 4 DO PORTD



char pot1_string [8];// STRING PARA RECEBER O VALOR CONVERTIDO DA LEITURA DO POTENCIÔMETRO 1
char char_duty_cycle [8]; //string para receber o duty cycle convertido

char apagar [] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};//STRING PARA APAGAR O CONTEÚDO DAS RESPECTIVAS LINHAS

unsigned int pot1 = 0;// VARIAVEL PARA ARMAZENAR O VALOR OBTIDO PELO AN0 ou seja, do potenciomentro
unsigned int duty_cycle = 0; //variavel para armazenar o duty cycle ja calculado




void main (){

	unsigned int  uiValorAD;     // Variavel que armazena o valor do A/D.

	// ======		configuração inicial do pinos
	PORTA = 255;
	TRISA = 255;                 // Configura PORTA pins como entrada

	ADCON0 = 0b00000001;  // Configura conversor A/D Canal 0, conversão desligada, A/D ligado.
	ADCON1 = 0b11001110;  // Configura todos canais como Digital menos AN0 e REF Interna.
	ADCON2 = 0b10111110;  // Configura conversor A/D para resultado justificado a direita, tempo de conversão de 20 TAD, clock de Fosc/64.

	// para o pwm
	PWM1_Init(5000);      // Inicializa módulo PWM com 5Khz
	PWM1_Start();         // Start PWM

	// para o lCD
	Lcd_Init();                               //Inicializa módulo LCD
	Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
	Lcd_Cmd(_LCD_CLEAR);                      //Limpa display
	CMCON = 0b00000111;//DESABILITA COMPARADORES INTERNOS

	// para LEDs inicializando eles zerados
	TRISB.RB0 = 0;
	TRISB.RB1 = 0;
	TRISB.RB2 = 0;
	TRISB.RB3 = 0;
	TRISB.RB4 = 0;
	TRISB.RB5 = 0;
	TRISB.RB6 = 0;
	TRISB.RB7 = 0;

	while(1){   // Aqui Definimos Uma Condição Sempre Verdadeira Como Parametro, Portanto Todo O Bloco Será Repetido Indefinidamente.

		uiValorAD = ADC_Read(0);     // Lê Canal AD 0
		pot1 = uiValorAD;

		duty_cycle = pot1 * 0.24;            // Converte valor para o duty cycle
		PWM1_Set_Duty(duty_cycle);   		// Envia o valor lido de "duty_cycle" para o módulo CCP1 pwm

		IntToStr (pot1, pot1_string);
		IntToStr (duty_cycle, char_duty_cycle);

		Lcd_Cmd(_LCD_CLEAR);

		Ltrim(pot1_string); //remove espaços em branco a esquerda
		Lcd_Out(1,1, "T_E:");
		Lcd_Out_Cp(pot1_string);


		Ltrim(char_duty_cycle); //remove espaços em branco a esquerda
		Lcd_Out(2,1, "D_C:");
		Lcd_Out_Cp(char_duty_cycle);



		// =============		Logica para acender gradualmente os leds		=============
		// analisando a tensao de entrada para começar a girar e ir ate o maximo
		// 231 -> 1023

		//incremento de 99


		if (pot1 > 231){ //led 0
			TRISB.RB0 = 1; //acende led
			if (pot1 > 330){
				TRISB.RB1 = 1; //acende led
				if (pot1 > 429){
					TRISB.RB2 = 1; //acende led
					if (pot1 > 528){
						TRISB.RB3 = 1; //acende led
						if (pot1 > 627){
							TRISB.RB4 = 1; //acende led
							if (pot1 > 726){
								TRISB.RB5 = 1; //acende led
								if (pot1 > 825){
									TRISB.RB6 = 1; //acende led
									if (pot1 > 924){
										TRISB.RB7 = 1; //acende led
									}
									else {
										TRISB.RB7 = 0;
									}
								}
								else{
									TRISB.RB6 = 0;
									TRISB.RB7 = 0;
								}
							}
							else {
								TRISB.RB5 = 0;
								TRISB.RB6 = 0;
								TRISB.RB7 = 0;
							}
						}
						else {
							TRISB.RB4 = 0;
							TRISB.RB5 = 0;
							TRISB.RB6 = 0;
							TRISB.RB7 = 0;
						}
					}
					else {
						TRISB.RB3 = 0;
						TRISB.RB4 = 0;
						TRISB.RB5 = 0;
						TRISB.RB6 = 0;
						TRISB.RB7 = 0;
					}
				}
				else {
					TRISB.RB2 = 0;
					TRISB.RB3 = 0;
					TRISB.RB4 = 0;
					TRISB.RB5 = 0;
					TRISB.RB6 = 0;
					TRISB.RB7 = 0;
				}
			}
			else {
				TRISB.RB1 = 0;
				TRISB.RB2 = 0;
				TRISB.RB3 = 0;
				TRISB.RB4 = 0;
				TRISB.RB5 = 0;
				TRISB.RB6 = 0;
				TRISB.RB7 = 0;
			}
		}
		else {
			TRISB.RB0 = 0;
			TRISB.RB1 = 0;
			TRISB.RB2 = 0;
			TRISB.RB3 = 0;
			TRISB.RB4 = 0;
			TRISB.RB5 = 0;
			TRISB.RB6 = 0;
			TRISB.RB7 = 0;
		}



		delay_ms(100);// AGUARDA 0,1 s
	}
}