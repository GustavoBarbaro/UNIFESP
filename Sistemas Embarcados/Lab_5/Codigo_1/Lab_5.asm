
_main:

;Lab_5.c,1 :: 		void main() {
;Lab_5.c,8 :: 		unsigned char ucMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	MOVLW       63
	MOVWF       main_ucMask_L0+0 
	MOVLW       6
	MOVWF       main_ucMask_L0+1 
	MOVLW       91
	MOVWF       main_ucMask_L0+2 
	MOVLW       79
	MOVWF       main_ucMask_L0+3 
	MOVLW       102
	MOVWF       main_ucMask_L0+4 
	MOVLW       109
	MOVWF       main_ucMask_L0+5 
	MOVLW       125
	MOVWF       main_ucMask_L0+6 
	MOVLW       7
	MOVWF       main_ucMask_L0+7 
	MOVLW       127
	MOVWF       main_ucMask_L0+8 
	MOVLW       111
	MOVWF       main_ucMask_L0+9 
;Lab_5.c,22 :: 		ADCON1 = 0x0f;       // Configura todos canais como Digital.
	MOVLW       15
	MOVWF       ADCON1+0 
;Lab_5.c,25 :: 		TRISB.RB0=1;         // Define o pino RB0 do PORTB como entrada.
	BSF         TRISB+0, 0 
;Lab_5.c,26 :: 		TRISB.RB1=1;         // Define o pino RB1 Do PORTB como entrada.
	BSF         TRISB+0, 1 
;Lab_5.c,27 :: 		TRISB.RB2=1;         // Define o pino RB2 Do PORTB como entrada.
	BSF         TRISB+0, 2 
;Lab_5.c,29 :: 		TRISA.RA2=0;         // Define o pino RA2 do PORTA como saida(Sele??o Display 1).
	BCF         TRISA+0, 2 
;Lab_5.c,30 :: 		TRISA.RA3=0;         // Define o pino RA3 do PORTA como saida(Sele??o Display 2).
	BCF         TRISA+0, 3 
;Lab_5.c,31 :: 		TRISA.RA4=0;         // Define o pino RA4 do PORTA como saida(Sele??o Display 3).
	BCF         TRISA+0, 4 
;Lab_5.c,32 :: 		TRISA.RA5=0;         // Define o pino RA5 do PORTA como saida(Sele??o Display 4).
	BCF         TRISA+0, 5 
;Lab_5.c,35 :: 		TRISB.RB5=0;         // Define o pino RB5 do PORTA como saida (LED)
	BCF         TRISB+0, 5 
;Lab_5.c,36 :: 		TRISB.RB6=0;         // Define o pino RB6 do PORTA como saida (LED)
	BCF         TRISB+0, 6 
;Lab_5.c,37 :: 		TRISB.RB7=0;         // Define o pino RB7 do PORTA como saida (LED)
	BCF         TRISB+0, 7 
;Lab_5.c,39 :: 		TRISC.RC1=0;      //PORT C configurado como saída (BUZZER)
	BCF         TRISC+0, 1 
;Lab_5.c,41 :: 		TRISD = 0;           // Define todos os pinos Do PORTD como saida.
	CLRF        TRISD+0 
;Lab_5.c,44 :: 		cont_RB0 = 0;		//contadores inicializados zerados
	CLRF        main_cont_RB0_L0+0 
	CLRF        main_cont_RB0_L0+1 
;Lab_5.c,45 :: 		cont_RB1 = 0;
	CLRF        main_cont_RB1_L0+0 
	CLRF        main_cont_RB1_L0+1 
;Lab_5.c,46 :: 		cont_TOTAL = 0;
	CLRF        main_cont_TOTAL_L0+0 
	CLRF        main_cont_TOTAL_L0+1 
;Lab_5.c,48 :: 		flag_buzzer_led = 0;
	CLRF        main_flag_buzzer_led_L0+0 
	CLRF        main_flag_buzzer_led_L0+1 
;Lab_5.c,51 :: 		while (1) {
L_main0:
;Lab_5.c,58 :: 		if((PORTB.RB0==0)&&(trava_RB0==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
	BTFSC       PORTB+0, 0 
	GOTO        L_main4
	MOVF        main_trava_RB0_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main4
L__main37:
;Lab_5.c,59 :: 		trava_RB0=1;                       // Variavel de travamento do incremento.
	MOVLW       1
	MOVWF       main_trava_RB0_L0+0 
;Lab_5.c,60 :: 		cont_RB0++;                         // Esse operador aritmetico(++) realiza o mesmo que variavel = variavel + 1.
	INFSNZ      main_cont_RB0_L0+0, 1 
	INCF        main_cont_RB0_L0+1, 1 
;Lab_5.c,61 :: 		if(cont_RB0>9999){ // Define o valor maximo a ser mostrado no displays como 9999.
	MOVF        main_cont_RB0_L0+1, 0 
	SUBLW       39
	BTFSS       STATUS+0, 2 
	GOTO        L__main39
	MOVF        main_cont_RB0_L0+0, 0 
	SUBLW       15
L__main39:
	BTFSC       STATUS+0, 0 
	GOTO        L_main5
;Lab_5.c,62 :: 		cont_RB0=9999;
	MOVLW       15
	MOVWF       main_cont_RB0_L0+0 
	MOVLW       39
	MOVWF       main_cont_RB0_L0+1 
;Lab_5.c,63 :: 		}
L_main5:
;Lab_5.c,64 :: 		}
L_main4:
;Lab_5.c,65 :: 		if((PORTB.RB0==1)&&(trava_RB0==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
	BTFSS       PORTB+0, 0 
	GOTO        L_main8
	MOVF        main_trava_RB0_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main8
L__main36:
;Lab_5.c,66 :: 		trava_RB0=0;
	CLRF        main_trava_RB0_L0+0 
;Lab_5.c,67 :: 		}
L_main8:
;Lab_5.c,69 :: 		aux_cont1 = cont_RB0;
	MOVF        main_cont_RB0_L0+0, 0 
	MOVWF       main_aux_cont1_L0+0 
	MOVF        main_cont_RB0_L0+1, 0 
	MOVWF       main_aux_cont1_L0+1 
;Lab_5.c,72 :: 		if((PORTB.RB1==0)&&(trava_RB1==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
	BTFSC       PORTB+0, 1 
	GOTO        L_main11
	MOVF        main_trava_RB1_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main11
L__main35:
;Lab_5.c,73 :: 		trava_RB1=1;                       // Variavel de travamento do incremento.
	MOVLW       1
	MOVWF       main_trava_RB1_L0+0 
;Lab_5.c,74 :: 		cont_RB1++;                         // Esse operador aritmetico(++) realiza o mesmo que variavel = variavel + 1.
	INFSNZ      main_cont_RB1_L0+0, 1 
	INCF        main_cont_RB1_L0+1, 1 
;Lab_5.c,75 :: 		if(cont_RB1>9999){ // Define o valor maximo a ser mostrado no displays como 9999.
	MOVF        main_cont_RB1_L0+1, 0 
	SUBLW       39
	BTFSS       STATUS+0, 2 
	GOTO        L__main40
	MOVF        main_cont_RB1_L0+0, 0 
	SUBLW       15
L__main40:
	BTFSC       STATUS+0, 0 
	GOTO        L_main12
;Lab_5.c,76 :: 		cont_RB1=9999;
	MOVLW       15
	MOVWF       main_cont_RB1_L0+0 
	MOVLW       39
	MOVWF       main_cont_RB1_L0+1 
;Lab_5.c,77 :: 		}
L_main12:
;Lab_5.c,78 :: 		}
L_main11:
;Lab_5.c,79 :: 		if((PORTB.RB1==1)&&(trava_RB1==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
	BTFSS       PORTB+0, 1 
	GOTO        L_main15
	MOVF        main_trava_RB1_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main15
L__main34:
;Lab_5.c,80 :: 		trava_RB1=0;
	CLRF        main_trava_RB1_L0+0 
;Lab_5.c,81 :: 		}
L_main15:
;Lab_5.c,83 :: 		aux_cont2 = cont_RB1;
	MOVF        main_cont_RB1_L0+0, 0 
	MOVWF       main_aux_cont2_L0+0 
	MOVF        main_cont_RB1_L0+1, 0 
	MOVWF       main_aux_cont2_L0+1 
;Lab_5.c,86 :: 		if((PORTB.RB2==0)&&(trava_RB2==0)){   // Incrementa somente uma vez quando a tecla for pressionada.
	BTFSC       PORTB+0, 2 
	GOTO        L_main18
	MOVF        main_trava_RB2_L0+0, 0 
	XORLW       0
	BTFSS       STATUS+0, 2 
	GOTO        L_main18
L__main33:
;Lab_5.c,87 :: 		trava_RB2=1;                       // Variavel de travamento do incremento.
	MOVLW       1
	MOVWF       main_trava_RB2_L0+0 
;Lab_5.c,88 :: 		cont_RB0 = 0;					//zerando os contadores
	CLRF        main_cont_RB0_L0+0 
	CLRF        main_cont_RB0_L0+1 
;Lab_5.c,89 :: 		cont_RB1 = 0;
	CLRF        main_cont_RB1_L0+0 
	CLRF        main_cont_RB1_L0+1 
;Lab_5.c,90 :: 		flag_buzzer_led = 1;
	MOVLW       1
	MOVWF       main_flag_buzzer_led_L0+0 
	MOVLW       0
	MOVWF       main_flag_buzzer_led_L0+1 
;Lab_5.c,91 :: 		}
L_main18:
;Lab_5.c,92 :: 		if((PORTB.RB2==1)&&(trava_RB2==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
	BTFSS       PORTB+0, 2 
	GOTO        L_main21
	MOVF        main_trava_RB2_L0+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_main21
L__main32:
;Lab_5.c,93 :: 		trava_RB2=0;
	CLRF        main_trava_RB2_L0+0 
;Lab_5.c,94 :: 		}
L_main21:
;Lab_5.c,102 :: 		if ((aux_cont1 % 2) == 0){
	MOVLW       1
	ANDWF       main_aux_cont1_L0+0, 0 
	MOVWF       R1 
	MOVF        main_aux_cont1_L0+1, 0 
	MOVWF       R2 
	MOVLW       0
	ANDWF       R2, 1 
	MOVLW       0
	XORWF       R2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main41
	MOVLW       0
	XORWF       R1, 0 
L__main41:
	BTFSS       STATUS+0, 2 
	GOTO        L_main22
;Lab_5.c,103 :: 		PORTB.RB6 = 1;
	BSF         PORTB+0, 6 
;Lab_5.c,104 :: 		}
	GOTO        L_main23
L_main22:
;Lab_5.c,106 :: 		PORTB.RB6 = 0;
	BCF         PORTB+0, 6 
;Lab_5.c,107 :: 		}
L_main23:
;Lab_5.c,110 :: 		if ((aux_cont2 % 2) == 1){
	MOVLW       1
	ANDWF       main_aux_cont2_L0+0, 0 
	MOVWF       R1 
	MOVF        main_aux_cont2_L0+1, 0 
	MOVWF       R2 
	MOVLW       0
	ANDWF       R2, 1 
	MOVLW       0
	XORWF       R2, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main42
	MOVLW       1
	XORWF       R1, 0 
L__main42:
	BTFSS       STATUS+0, 2 
	GOTO        L_main24
;Lab_5.c,111 :: 		PORTB.RB7 = 1;
	BSF         PORTB+0, 7 
;Lab_5.c,112 :: 		}
	GOTO        L_main25
L_main24:
;Lab_5.c,114 :: 		PORTB.RB7 = 0;
	BCF         PORTB+0, 7 
;Lab_5.c,115 :: 		}
L_main25:
;Lab_5.c,118 :: 		if (flag_buzzer_led == 1){
	MOVLW       0
	XORWF       main_flag_buzzer_led_L0+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main43
	MOVLW       1
	XORWF       main_flag_buzzer_led_L0+0, 0 
L__main43:
	BTFSS       STATUS+0, 2 
	GOTO        L_main26
;Lab_5.c,120 :: 		PORTB.RB5 = 1;				//liga led
	BSF         PORTB+0, 5 
;Lab_5.c,121 :: 		PORTC.RC1 = 1;   //LIGA BUZZER
	BSF         PORTC+0, 1 
;Lab_5.c,123 :: 		delay_ms(100);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       4
	MOVWF       R12, 0
	MOVLW       186
	MOVWF       R13, 0
L_main27:
	DECFSZ      R13, 1, 1
	BRA         L_main27
	DECFSZ      R12, 1, 1
	BRA         L_main27
	DECFSZ      R11, 1, 1
	BRA         L_main27
	NOP
;Lab_5.c,125 :: 		PORTB.RB5 = 0;				//desliga led
	BCF         PORTB+0, 5 
;Lab_5.c,126 :: 		PORTC.RC1 = 0;   			//desliga BUZZER
	BCF         PORTC+0, 1 
;Lab_5.c,127 :: 		flag_buzzer_led = 0;
	CLRF        main_flag_buzzer_led_L0+0 
	CLRF        main_flag_buzzer_led_L0+1 
;Lab_5.c,128 :: 		}
L_main26:
;Lab_5.c,132 :: 		cont_TOTAL = aux_cont1 + aux_cont2;
	MOVF        main_aux_cont2_L0+0, 0 
	ADDWF       main_aux_cont1_L0+0, 0 
	MOVWF       R0 
	MOVF        main_aux_cont2_L0+1, 0 
	ADDWFC      main_aux_cont1_L0+1, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       main_cont_TOTAL_L0+0 
	MOVF        R1, 0 
	MOVWF       main_cont_TOTAL_L0+1 
;Lab_5.c,136 :: 		PORTD = ucMask[cont_TOTAL%10];              // Pega modulo da divisao por 10 e coloca o valor no PORTD.
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       main_ucMask_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR0L+0 
	MOVLW       hi_addr(main_ucMask_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0L+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTD+0 
;Lab_5.c,137 :: 		PORTA.RA5 = 1;                           // Liga o transistor associado ao display 1.
	BSF         PORTA+0, 5 
;Lab_5.c,138 :: 		Delay_ms(2);                             // Delay para escrita no display.
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main28:
	DECFSZ      R13, 1, 1
	BRA         L_main28
	DECFSZ      R12, 1, 1
	BRA         L_main28
	NOP
;Lab_5.c,139 :: 		PORTA.RA5 = 0;                           // Desliga o transistor associado ao display 1.
	BCF         PORTA+0, 5 
;Lab_5.c,140 :: 		cont_TOTAL/=10;                             // Divide variavel por 10 para definir a dezena.
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        main_cont_TOTAL_L0+0, 0 
	MOVWF       R0 
	MOVF        main_cont_TOTAL_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R0, 0 
	MOVWF       main_cont_TOTAL_L0+0 
	MOVF        R1, 0 
	MOVWF       main_cont_TOTAL_L0+1 
;Lab_5.c,142 :: 		PORTD = ucMask[cont_TOTAL%10];
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       main_ucMask_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR0L+0 
	MOVLW       hi_addr(main_ucMask_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0L+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTD+0 
;Lab_5.c,143 :: 		PORTA.RA4 = 1;
	BSF         PORTA+0, 4 
;Lab_5.c,144 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main29:
	DECFSZ      R13, 1, 1
	BRA         L_main29
	DECFSZ      R12, 1, 1
	BRA         L_main29
	NOP
;Lab_5.c,145 :: 		PORTA.RA4 = 0;
	BCF         PORTA+0, 4 
;Lab_5.c,146 :: 		cont_TOTAL/=10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        main_cont_TOTAL_L0+0, 0 
	MOVWF       R0 
	MOVF        main_cont_TOTAL_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R0, 0 
	MOVWF       main_cont_TOTAL_L0+0 
	MOVF        R1, 0 
	MOVWF       main_cont_TOTAL_L0+1 
;Lab_5.c,148 :: 		PORTD = ucMask[cont_TOTAL%10];
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       main_ucMask_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR0L+0 
	MOVLW       hi_addr(main_ucMask_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0L+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTD+0 
;Lab_5.c,149 :: 		PORTA.RA3 = 1;
	BSF         PORTA+0, 3 
;Lab_5.c,150 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main30:
	DECFSZ      R13, 1, 1
	BRA         L_main30
	DECFSZ      R12, 1, 1
	BRA         L_main30
	NOP
;Lab_5.c,151 :: 		PORTA.RA3 = 0;
	BCF         PORTA+0, 3 
;Lab_5.c,152 :: 		cont_TOTAL/=10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        main_cont_TOTAL_L0+0, 0 
	MOVWF       R0 
	MOVF        main_cont_TOTAL_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R0, 0 
	MOVWF       main_cont_TOTAL_L0+0 
	MOVF        R1, 0 
	MOVWF       main_cont_TOTAL_L0+1 
;Lab_5.c,154 :: 		PORTD = ucMask[cont_TOTAL%10];
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       main_ucMask_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR0L+0 
	MOVLW       hi_addr(main_ucMask_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0L+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTD+0 
;Lab_5.c,155 :: 		PORTA.RA2 = 1;
	BSF         PORTA+0, 2 
;Lab_5.c,156 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main31:
	DECFSZ      R13, 1, 1
	BRA         L_main31
	DECFSZ      R12, 1, 1
	BRA         L_main31
	NOP
;Lab_5.c,157 :: 		PORTA.RA2 = 0;
	BCF         PORTA+0, 2 
;Lab_5.c,161 :: 		}
	GOTO        L_main0
;Lab_5.c,162 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
