/*******************************************************************************
*                        Kit de desenvolvimento ACEPIC 28                      *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Leitura dos canais anal�gicos AN0 (trimpot 0 a 5V) e AN3 (LM35-Tem- *
*          peratura                                                            *
*Obs.: Ligar chaves 1 e 3 do DIP1 e chaves 7 e 8 do DIP2                       *
********************************************************************************/
#include<16F876A.h>


#device ADC = 10                         //Define 10 bits para o resultado da convers�o AD
#use delay (clock=8000000)           /*Defini��o da frequ�ncia do cristal para c�lculo 
                                                 ..dos delays*/
#fuses HS, NOWDT, PUT,BROWNOUT, NOLVP  //Configura��o dos bits de controle

#include "LCD_4B.c"      //inclui o arquio LCD8b.c (Biblioteca de fun��es do LCD)
 
long int ad0,ad1;             //Vari�veis para armazenamento da convers�o
 
void main()                   //Fun��o principal 
{                                  
lcd_ini();                    //Chama a fun��o para inicializa��o do LCD     
               
SETUP_ADC_PORTS(AN0_AN1_AN3);    //Configura as entradas anal�gicas AN0, AN1 e AN3
 
/*Configura o a frequ�ncia do oscilador para o conversor A/D em fosc/8 (TAD = 1uS)*/
SETUP_ADC(ADC_CLOCK_DIV_8);

Output_Low(PIN_C2);           //Desliga o aquecedor

while(true)                            //Loop principal
   {
   if (input(PIN_A2))              //Se pressionado o bot�o B0
       Output_High(PIN_C2);         //Liga o aquecedor
   
   SET_ADC_CHANNEL(0);           //Configura o canal de leitura 0
   delay_us(100);                  //Tempo de ajuste do canal (necess�rio) 
   ad0 = READ_ADC();                //Faz a convers�o AD e a salva na vari�vel ad0
   
   printf(lcd_escreve,"\fS0=%lu",ad0);    //Mostra valor da convers�o do canal 0

   SET_ADC_CHANNEL(3);           //Configura o canal de leitura 3
   delay_us(100);                   //Tempo de ajuste do canal (necess�rio) 
   ad1 = READ_ADC();                //Faz a convers�o AD e a salva na vari�vel ad3
   
   printf(lcd_escreve,"\nS1=%lu",ad1);    //Mostra valor da convers�o do canal 3
   
   if (ad1>=80)                     //Sendo ad3 >= 80 (Aprox. 40mv)                 
      { 
      
      Output_low(PIN_C2);           //Desliga aquecimento
      }

  
   
   delay_ms(300);                  //Atraso de 300ms       
   }
}    
