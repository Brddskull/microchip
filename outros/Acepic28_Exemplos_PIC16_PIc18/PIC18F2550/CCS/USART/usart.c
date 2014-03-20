/*******************************************************************************
*                        Kit de desenvolvimento ACEPIC 28                      *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Leitura dos canais anal�gicos AN0 (trimpot 0 a 5V) e AN3 (LM35-Tem- *
*          peratura) e envio do dados � porta serial.                          *
*Obs.: Ligar as chaves 1(ADC1) e 3 (TEMP) do DIP1 e chaves 7 (RA6-OSC1) e      *
*      8 (RA7-OSC2) do DIP2                                                    *
*******************************************************************************/
#include <18F2550.h>

#device ADC = 10              //Define 10 bits para o resultado da convers�o AD
#use delay (clock=8000000)    /*Defini��o da frequ�ncia do cristal para c�lculo 
                                ..dos delays*/
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 
//Defini��es para a comunica��o serial
#use RS232 (Baud=19200, xmit = PIN_C6, rcv = PIN_C7)

int32 ad0,ad1;           //Vari�veis para armazenamento da convers�o

void main()      
{
SETUP_ADC_PORTS(AN0_TO_AN3);    //Configura as entradas anal�gicas AN0, AN1 e AN3
 
/*Configura o a frequ�ncia do oscilador para o conversor A/D em fosc/8 (TAD = 1uS)*/
SETUP_ADC(ADC_CLOCK_DIV_8);

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("Microcontroladores PIC 18F2550.\r\n");

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("Leitura dos canais AN0 e AN3\r\n\r\n");


while(true)                   //Loop principal
   {  
   
   SET_ADC_CHANNEL(0);        //Configura o canal de leitura 0
   delay_us(100);             //Tempo de ajuste do canal (necess�rio) 
   ad0 = READ_ADC();          //Faz a convers�o AD e a salva na vari�vel ad0
   
   ad0 = (ad0 * 5000)/1023;
      
   SET_ADC_CHANNEL(3);         //Configura o canal de leitura 3
   delay_us(100);                //Tempo de ajuste do canal (necess�rio) 
   ad1 = READ_ADC();             //Faz a convers�o AD e a salva na vari�vel ad1
   
   ad1 = (ad1 * 500)/1023;
   
   printf("AN0 = %04lu mV - Temp: %02lu C\r\n",ad0, ad1);   
     
   delay_ms(1000);                  //Atraso de 300ms       
   }
}    
