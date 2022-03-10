#line 1 "C:/Users/gusta/Desktop/UNIFESP/Sistemas Embarcados/Labs/Lab_5/Codigo_1/Lab_5.c"
void main() {

 unsigned int cont_RB0;
 unsigned int cont_RB1;
 unsigned int cont_TOTAL;
 unsigned int flag_buzzer_led;

 unsigned char ucMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
#line 14 "C:/Users/gusta/Desktop/UNIFESP/Sistemas Embarcados/Labs/Lab_5/Codigo_1/Lab_5.c"
 unsigned char trava_RB0;
 unsigned char trava_RB1;
 unsigned char trava_RB2;
 unsigned int uiContador;
 unsigned int aux_cont1;
 unsigned int aux_cont2;


 ADCON1 = 0x0f;


 TRISB.RB0=1;
 TRISB.RB1=1;
 TRISB.RB2=1;

 TRISA.RA2=0;
 TRISA.RA3=0;
 TRISA.RA4=0;
 TRISA.RA5=0;


 TRISB.RB5=0;
 TRISB.RB6=0;
 TRISB.RB7=0;

 TRISC.RC1=0;

 TRISD = 0;


 cont_RB0 = 0;
 cont_RB1 = 0;
 cont_TOTAL = 0;

 flag_buzzer_led = 0;


 while (1) {






 if((PORTB.RB0==0)&&(trava_RB0==0)){
 trava_RB0=1;
 cont_RB0++;
 if(cont_RB0>9999){
 cont_RB0=9999;
 }
 }
 if((PORTB.RB0==1)&&(trava_RB0==1)){
 trava_RB0=0;
 }

 aux_cont1 = cont_RB0;


 if((PORTB.RB1==0)&&(trava_RB1==0)){
 trava_RB1=1;
 cont_RB1++;
 if(cont_RB1>9999){
 cont_RB1=9999;
 }
 }
 if((PORTB.RB1==1)&&(trava_RB1==1)){
 trava_RB1=0;
 }

 aux_cont2 = cont_RB1;


 if((PORTB.RB2==0)&&(trava_RB2==0)){
 trava_RB2=1;
 cont_RB0 = 0;
 cont_RB1 = 0;
 flag_buzzer_led = 1;
 }
 if((PORTB.RB2==1)&&(trava_RB2==1)){
 trava_RB2=0;
 }







 if ((aux_cont1 % 2) == 0){
 PORTB.RB6 = 1;
 }
 else{
 PORTB.RB6 = 0;
 }


 if ((aux_cont2 % 2) == 1){
 PORTB.RB7 = 1;
 }
 else {
 PORTB.RB7 = 0;
 }


 if (flag_buzzer_led == 1){

 PORTB.RB5 = 1;
 PORTC.RC1 = 1;

 delay_ms(100);

 PORTB.RB5 = 0;
 PORTC.RC1 = 0;
 flag_buzzer_led = 0;
 }



 cont_TOTAL = aux_cont1 + aux_cont2;



 PORTD = ucMask[cont_TOTAL%10];
 PORTA.RA5 = 1;
 Delay_ms(2);
 PORTA.RA5 = 0;
 cont_TOTAL/=10;

 PORTD = ucMask[cont_TOTAL%10];
 PORTA.RA4 = 1;
 Delay_ms(2);
 PORTA.RA4 = 0;
 cont_TOTAL/=10;

 PORTD = ucMask[cont_TOTAL%10];
 PORTA.RA3 = 1;
 Delay_ms(2);
 PORTA.RA3 = 0;
 cont_TOTAL/=10;

 PORTD = ucMask[cont_TOTAL%10];
 PORTA.RA2 = 1;
 Delay_ms(2);
 PORTA.RA2 = 0;



 }
}
