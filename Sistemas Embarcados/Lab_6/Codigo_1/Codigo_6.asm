
_main:

;Codigo_6.c,32 :: 		void main (){
;Codigo_6.c,37 :: 		PORTA = 255;
	MOVLW       255
	MOVWF       PORTA+0 
;Codigo_6.c,38 :: 		TRISA = 255;                 // Configura PORTA pins como entrada
	MOVLW       255
	MOVWF       TRISA+0 
;Codigo_6.c,40 :: 		ADCON0 = 0b00000001;  // Configura conversor A/D Canal 0, conversão desligada, A/D ligado.
	MOVLW       1
	MOVWF       ADCON0+0 
;Codigo_6.c,41 :: 		ADCON1 = 0b11001110;  // Configura todos canais como Digital menos AN0 e REF Interna.
	MOVLW       206
	MOVWF       ADCON1+0 
;Codigo_6.c,42 :: 		ADCON2 = 0b10111110;  // Configura conversor A/D para resultado justificado a direita, tempo de conversão de 20 TAD, clock de Fosc/64.
	MOVLW       190
	MOVWF       ADCON2+0 
;Codigo_6.c,45 :: 		PWM1_Init(5000);      // Inicializa módulo PWM com 5Khz
	BSF         T2CON+0, 0, 0
	BCF         T2CON+0, 1, 0
	MOVLW       99
	MOVWF       PR2+0, 0
	CALL        _PWM1_Init+0, 0
;Codigo_6.c,46 :: 		PWM1_Start();         // Start PWM
	CALL        _PWM1_Start+0, 0
;Codigo_6.c,49 :: 		Lcd_Init();                               //Inicializa módulo LCD
	CALL        _Lcd_Init+0, 0
;Codigo_6.c,50 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Codigo_6.c,51 :: 		Lcd_Cmd(_LCD_CLEAR);                      //Limpa display
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Codigo_6.c,52 :: 		CMCON = 0b00000111;//DESABILITA COMPARADORES INTERNOS
	MOVLW       7
	MOVWF       CMCON+0 
;Codigo_6.c,55 :: 		TRISB.RB0 = 0;
	BCF         TRISB+0, 0 
;Codigo_6.c,56 :: 		TRISB.RB1 = 0;
	BCF         TRISB+0, 1 
;Codigo_6.c,57 :: 		TRISB.RB2 = 0;
	BCF         TRISB+0, 2 
;Codigo_6.c,58 :: 		TRISB.RB3 = 0;
	BCF         TRISB+0, 3 
;Codigo_6.c,59 :: 		TRISB.RB4 = 0;
	BCF         TRISB+0, 4 
;Codigo_6.c,60 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,61 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,62 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,64 :: 		while(1){   // Aqui Definimos Uma Condição Sempre Verdadeira Como Parametro, Portanto Todo O Bloco Será Repetido Indefinidamente.
L_main0:
;Codigo_6.c,66 :: 		uiValorAD = ADC_Read(0);     // Lê Canal AD 0
	CLRF        FARG_ADC_Read_channel+0 
	CALL        _ADC_Read+0, 0
;Codigo_6.c,67 :: 		pot1 = uiValorAD;
	MOVF        R0, 0 
	MOVWF       _pot1+0 
	MOVF        R1, 0 
	MOVWF       _pot1+1 
;Codigo_6.c,69 :: 		duty_cycle = pot1 * 0.24;            // Converte valor para o duty cycle
	CALL        _word2double+0, 0
	MOVLW       143
	MOVWF       R4 
	MOVLW       194
	MOVWF       R5 
	MOVLW       117
	MOVWF       R6 
	MOVLW       124
	MOVWF       R7 
	CALL        _Mul_32x32_FP+0, 0
	CALL        _double2word+0, 0
	MOVF        R0, 0 
	MOVWF       _duty_cycle+0 
	MOVF        R1, 0 
	MOVWF       _duty_cycle+1 
;Codigo_6.c,70 :: 		PWM1_Set_Duty(duty_cycle);   		// Envia o valor lido de "duty_cycle" para o módulo CCP1 pwm
	MOVF        R0, 0 
	MOVWF       FARG_PWM1_Set_Duty_new_duty+0 
	CALL        _PWM1_Set_Duty+0, 0
;Codigo_6.c,72 :: 		IntToStr (pot1, pot1_string);
	MOVF        _pot1+0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVF        _pot1+1, 0 
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       _pot1_string+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(_pot1_string+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;Codigo_6.c,73 :: 		IntToStr (duty_cycle, char_duty_cycle);
	MOVF        _duty_cycle+0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVF        _duty_cycle+1, 0 
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       _char_duty_cycle+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(_char_duty_cycle+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;Codigo_6.c,75 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Codigo_6.c,77 :: 		Ltrim(pot1_string); //remove espaços em branco a esquerda
	MOVLW       _pot1_string+0
	MOVWF       FARG_Ltrim_string+0 
	MOVLW       hi_addr(_pot1_string+0)
	MOVWF       FARG_Ltrim_string+1 
	CALL        _Ltrim+0, 0
;Codigo_6.c,78 :: 		Lcd_Out(1,1, "T_E:");
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr1_Codigo_6+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr1_Codigo_6+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Codigo_6.c,79 :: 		Lcd_Out_Cp(pot1_string);
	MOVLW       _pot1_string+0
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVLW       hi_addr(_pot1_string+0)
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Codigo_6.c,82 :: 		Ltrim(char_duty_cycle); //remove espaços em branco a esquerda
	MOVLW       _char_duty_cycle+0
	MOVWF       FARG_Ltrim_string+0 
	MOVLW       hi_addr(_char_duty_cycle+0)
	MOVWF       FARG_Ltrim_string+1 
	CALL        _Ltrim+0, 0
;Codigo_6.c,83 :: 		Lcd_Out(2,1, "D_C:");
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr2_Codigo_6+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr2_Codigo_6+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Codigo_6.c,84 :: 		Lcd_Out_Cp(char_duty_cycle);
	MOVLW       _char_duty_cycle+0
	MOVWF       FARG_Lcd_Out_CP_text+0 
	MOVLW       hi_addr(_char_duty_cycle+0)
	MOVWF       FARG_Lcd_Out_CP_text+1 
	CALL        _Lcd_Out_CP+0, 0
;Codigo_6.c,95 :: 		if (pot1 > 231){ //led 0
	MOVLW       0
	MOVWF       R0 
	MOVF        _pot1+1, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main20
	MOVF        _pot1+0, 0 
	SUBLW       231
L__main20:
	BTFSC       STATUS+0, 0 
	GOTO        L_main2
;Codigo_6.c,96 :: 		TRISB.RB0 = 1; //acende led
	BSF         TRISB+0, 0 
;Codigo_6.c,97 :: 		if (pot1 > 330){
	MOVF        _pot1+1, 0 
	SUBLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L__main21
	MOVF        _pot1+0, 0 
	SUBLW       74
L__main21:
	BTFSC       STATUS+0, 0 
	GOTO        L_main3
;Codigo_6.c,98 :: 		TRISB.RB1 = 1; //acende led
	BSF         TRISB+0, 1 
;Codigo_6.c,99 :: 		if (pot1 > 429){
	MOVF        _pot1+1, 0 
	SUBLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L__main22
	MOVF        _pot1+0, 0 
	SUBLW       173
L__main22:
	BTFSC       STATUS+0, 0 
	GOTO        L_main4
;Codigo_6.c,100 :: 		TRISB.RB2 = 1; //acende led
	BSF         TRISB+0, 2 
;Codigo_6.c,101 :: 		if (pot1 > 528){
	MOVF        _pot1+1, 0 
	SUBLW       2
	BTFSS       STATUS+0, 2 
	GOTO        L__main23
	MOVF        _pot1+0, 0 
	SUBLW       16
L__main23:
	BTFSC       STATUS+0, 0 
	GOTO        L_main5
;Codigo_6.c,102 :: 		TRISB.RB3 = 1; //acende led
	BSF         TRISB+0, 3 
;Codigo_6.c,103 :: 		if (pot1 > 627){
	MOVF        _pot1+1, 0 
	SUBLW       2
	BTFSS       STATUS+0, 2 
	GOTO        L__main24
	MOVF        _pot1+0, 0 
	SUBLW       115
L__main24:
	BTFSC       STATUS+0, 0 
	GOTO        L_main6
;Codigo_6.c,104 :: 		TRISB.RB4 = 1; //acende led
	BSF         TRISB+0, 4 
;Codigo_6.c,105 :: 		if (pot1 > 726){
	MOVF        _pot1+1, 0 
	SUBLW       2
	BTFSS       STATUS+0, 2 
	GOTO        L__main25
	MOVF        _pot1+0, 0 
	SUBLW       214
L__main25:
	BTFSC       STATUS+0, 0 
	GOTO        L_main7
;Codigo_6.c,106 :: 		TRISB.RB5 = 1; //acende led
	BSF         TRISB+0, 5 
;Codigo_6.c,107 :: 		if (pot1 > 825){
	MOVF        _pot1+1, 0 
	SUBLW       3
	BTFSS       STATUS+0, 2 
	GOTO        L__main26
	MOVF        _pot1+0, 0 
	SUBLW       57
L__main26:
	BTFSC       STATUS+0, 0 
	GOTO        L_main8
;Codigo_6.c,108 :: 		TRISB.RB6 = 1; //acende led
	BSF         TRISB+0, 6 
;Codigo_6.c,109 :: 		if (pot1 > 924){
	MOVF        _pot1+1, 0 
	SUBLW       3
	BTFSS       STATUS+0, 2 
	GOTO        L__main27
	MOVF        _pot1+0, 0 
	SUBLW       156
L__main27:
	BTFSC       STATUS+0, 0 
	GOTO        L_main9
;Codigo_6.c,110 :: 		TRISB.RB7 = 1; //acende led
	BSF         TRISB+0, 7 
;Codigo_6.c,111 :: 		}
	GOTO        L_main10
L_main9:
;Codigo_6.c,113 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,114 :: 		}
L_main10:
;Codigo_6.c,115 :: 		}
	GOTO        L_main11
L_main8:
;Codigo_6.c,117 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,118 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,119 :: 		}
L_main11:
;Codigo_6.c,120 :: 		}
	GOTO        L_main12
L_main7:
;Codigo_6.c,122 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,123 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,124 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,125 :: 		}
L_main12:
;Codigo_6.c,126 :: 		}
	GOTO        L_main13
L_main6:
;Codigo_6.c,128 :: 		TRISB.RB4 = 0;
	BCF         TRISB+0, 4 
;Codigo_6.c,129 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,130 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,131 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,132 :: 		}
L_main13:
;Codigo_6.c,133 :: 		}
	GOTO        L_main14
L_main5:
;Codigo_6.c,135 :: 		TRISB.RB3 = 0;
	BCF         TRISB+0, 3 
;Codigo_6.c,136 :: 		TRISB.RB4 = 0;
	BCF         TRISB+0, 4 
;Codigo_6.c,137 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,138 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,139 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,140 :: 		}
L_main14:
;Codigo_6.c,141 :: 		}
	GOTO        L_main15
L_main4:
;Codigo_6.c,143 :: 		TRISB.RB2 = 0;
	BCF         TRISB+0, 2 
;Codigo_6.c,144 :: 		TRISB.RB3 = 0;
	BCF         TRISB+0, 3 
;Codigo_6.c,145 :: 		TRISB.RB4 = 0;
	BCF         TRISB+0, 4 
;Codigo_6.c,146 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,147 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,148 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,149 :: 		}
L_main15:
;Codigo_6.c,150 :: 		}
	GOTO        L_main16
L_main3:
;Codigo_6.c,152 :: 		TRISB.RB1 = 0;
	BCF         TRISB+0, 1 
;Codigo_6.c,153 :: 		TRISB.RB2 = 0;
	BCF         TRISB+0, 2 
;Codigo_6.c,154 :: 		TRISB.RB3 = 0;
	BCF         TRISB+0, 3 
;Codigo_6.c,155 :: 		TRISB.RB4 = 0;
	BCF         TRISB+0, 4 
;Codigo_6.c,156 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,157 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,158 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,159 :: 		}
L_main16:
;Codigo_6.c,160 :: 		}
	GOTO        L_main17
L_main2:
;Codigo_6.c,162 :: 		TRISB.RB0 = 0;
	BCF         TRISB+0, 0 
;Codigo_6.c,163 :: 		TRISB.RB1 = 0;
	BCF         TRISB+0, 1 
;Codigo_6.c,164 :: 		TRISB.RB2 = 0;
	BCF         TRISB+0, 2 
;Codigo_6.c,165 :: 		TRISB.RB3 = 0;
	BCF         TRISB+0, 3 
;Codigo_6.c,166 :: 		TRISB.RB4 = 0;
	BCF         TRISB+0, 4 
;Codigo_6.c,167 :: 		TRISB.RB5 = 0;
	BCF         TRISB+0, 5 
;Codigo_6.c,168 :: 		TRISB.RB6 = 0;
	BCF         TRISB+0, 6 
;Codigo_6.c,169 :: 		TRISB.RB7 = 0;
	BCF         TRISB+0, 7 
;Codigo_6.c,170 :: 		}
L_main17:
;Codigo_6.c,174 :: 		delay_ms(100);// AGUARDA 0,1 s
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       4
	MOVWF       R12, 0
	MOVLW       186
	MOVWF       R13, 0
L_main18:
	DECFSZ      R13, 1, 1
	BRA         L_main18
	DECFSZ      R12, 1, 1
	BRA         L_main18
	DECFSZ      R11, 1, 1
	BRA         L_main18
	NOP
;Codigo_6.c,175 :: 		}
	GOTO        L_main0
;Codigo_6.c,176 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
