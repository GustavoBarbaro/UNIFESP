#line 1 "C:/Users/gusta/Desktop/UNIFESP/Sistemas Embarcados/Labs/Lab_6/Codigo_1/Codigo_6.c"



sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;


sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;



char pot1_string [8];
char char_duty_cycle [8];

char apagar [] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

unsigned int pot1 = 0;
unsigned int duty_cycle = 0;




void main (){

 unsigned int uiValorAD;


 PORTA = 255;
 TRISA = 255;

 ADCON0 = 0b00000001;
 ADCON1 = 0b11001110;
 ADCON2 = 0b10111110;


 PWM1_Init(5000);
 PWM1_Start();


 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Cmd(_LCD_CLEAR);
 CMCON = 0b00000111;


 TRISB.RB0 = 0;
 TRISB.RB1 = 0;
 TRISB.RB2 = 0;
 TRISB.RB3 = 0;
 TRISB.RB4 = 0;
 TRISB.RB5 = 0;
 TRISB.RB6 = 0;
 TRISB.RB7 = 0;

 while(1){

 uiValorAD = ADC_Read(0);
 pot1 = uiValorAD;

 duty_cycle = pot1 * 0.24;
 PWM1_Set_Duty(duty_cycle);

 IntToStr (pot1, pot1_string);
 IntToStr (duty_cycle, char_duty_cycle);

 Lcd_Cmd(_LCD_CLEAR);

 Ltrim(pot1_string);
 Lcd_Out(1,1, "T_E:");
 Lcd_Out_Cp(pot1_string);


 Ltrim(char_duty_cycle);
 Lcd_Out(2,1, "D_C:");
 Lcd_Out_Cp(char_duty_cycle);










 if (pot1 > 231){
 TRISB.RB0 = 1;
 if (pot1 > 330){
 TRISB.RB1 = 1;
 if (pot1 > 429){
 TRISB.RB2 = 1;
 if (pot1 > 528){
 TRISB.RB3 = 1;
 if (pot1 > 627){
 TRISB.RB4 = 1;
 if (pot1 > 726){
 TRISB.RB5 = 1;
 if (pot1 > 825){
 TRISB.RB6 = 1;
 if (pot1 > 924){
 TRISB.RB7 = 1;
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



 delay_ms(100);
 }
}
