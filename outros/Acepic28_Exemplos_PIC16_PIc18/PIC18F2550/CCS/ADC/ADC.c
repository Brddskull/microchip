/*******************************************************************************
*                        Kit de desenvolvimento ACEPIC 28                      *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Leitura dos canais anal�gicos AN0 (trimpot 0 a 5V) e AN3 (LM35-Tem- *
*          peratura). Pressionando-se o bot�o B2, o circuito de aquecimento    *
*          ser� acionado e o resistor R28 ser� aquecido at� que o sensor leia  *
*          aproximadamente 40 graus Celsius.                                   *
*Obs.: Ligar chaves 1 e 3 do DIP1 e chaves 7 e 8 do DIP2                       *
********************************************************************************/
#include <18F2550.h>

#device ADC = 10              //Define 10 bits para o resultado da convers�o AD
#use delay (clock=8000000)    /*Defini��o da frequ�ncia do cristal para c�lculo 
                                ..dos delays*/
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 

#include "LCD_4B.c"      //inclui o arquio LCD8b.c (Biblioteca de fun��es do LCD)
 
int32 ad0,ad1;           //Vari�veis para armazenamento da convers�o
 
void main()              //Fun��o principal 
{                                  
lcd_ini();               //Chama a fun��o para inicializa��o do LCD     
               
SETUP_ADC_PORTS(AN0_TO_AN3);    //Configura as entradas anal�gicas AN0, AN1 e AN3
 
/*Configura o a frequ�ncia do oscilador para o conversor A/D em fosc/8 (TAD = 1uS)*/
SETUP_ADC(ADC_CLOCK_DIV_8);

Output_Low(PIN_C2);           //Desliga o aquecedor

while(true)                   //Loop principal
   {
   if (input(PIN_A4))         //Se pressionado o bot�o B0
       Output_High(PIN_C2);   //Liga o aquecedor
   
   SET_ADC_CHANNEL(0);        //Configura o canal de leitura 0
   delay_us(100);             //Tempo de ajuste do canal (necess�rio) 
   ad0 = READ_ADC();          //Faz a convers�o AD e a salva na vari�vel ad0
   
   ad0 = (ad0 * 5000)/1023;
      
   SET_ADC_CHANNEL(3);         //Configura o canal de leitura 3
   delay_us(100);                //Tempo de ajuste do canal (necess�rio) 
   ad1 = READ_ADC();             //Faz a convers�o AD e a salva na vari�vel ad1
   
   ad1 = (ad1 * 500)/1023;
   
   printf(lcd_escreve,"\fAN0 = %04lu mV",ad0);    //Mostra valor da convers�o do canal 0
   printf(lcd_escreve,"\nTEMP: %02lu%cC",ad1,0xDF);
   
   if (ad1>=40)                     //Sendo ad1 > 40 (400mV)                 
      { 
      
      Output_low(PIN_C2);           //Desliga aquecimento
      }  
   
   delay_ms(500);                  //Atraso de 300ms       
   }
}    
