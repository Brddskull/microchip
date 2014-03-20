/*******************************************************************************
*                        Kit de desenvolvimento ACEPIC 28                      *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Leitura dos canais anal�gicos AN0 e AN3 com visualiza��o no LCD     *
*Obs.:     Ligar chave 1 do DIP DP1 para Trimpot ADC1 para conex�o ao canal    *
*          anal�gico AN0 e chave 3 do DIP conecta o Sensor de Temperatura LM35 *
*          ao canal anal�gico AN3.                                             *
*		   A chave 6 do DIP DP2 conecta o circuito de aquecimento ao pino RC2. *                        *
********************************************************************************/
#include <p18F2550.h>
#include <delays.h>
#include <stdio.h>

// Frequencia do oscilador = 8MHz
// Ciclo de m�quina  = 1/(Fosc/4) = 0,5us

#pragma config FOSC = HS       		//Configura o oscilador a cristal
#pragma config CPUDIV = OSC1_PLL2 	//Postscale clock do sistema 
#pragma config WDT = OFF  			//Desabilita o Watchdog Timer (WDT).
#pragma config PWRT = ON   			//Habilita o Power-up Timer (PWRT).
#pragma config BOR = ON				//Habilita Brown-out reset 
#pragma config BORV = 1	        	//Tens�o do BOR � 4,33V.
#pragma config LVP = OFF       		//Desabilita o Low Voltage Program.

#include "lcd_4b.h"

unsigned long res_ad;	//vari�vel de armazenamento da convers�o AD
unsigned long res_temp;	//vari�vel de armazenamento da convers�o AD
unsigned long tensao;	//variavel de resultado em tens�o
unsigned long temp;     //vari�vel de resultado da temperatura
char buf_lcd[16];		//matriz de armazenamento da mensagem para o LCD 

void main()
{
int i;

TRISAbits.TRISA0 = 1;   //Direciona o pino 0 da porta A como entrada
TRISAbits.TRISA3 = 1;   //Direciona o pino 3 da porta A como entrada
TRISCbits.TRISC2 = 0;	//Direciona o pino 2 da porta C como sa�da (Aquecimento)
TRISAbits.TRISA4 = 1;   //Direciona o pino 4 da porta A como entrada (B2)  
                   
ADCON2 = 0b10100001;     /*ADFM1 = 1 -> Resultado da convers�o AD
                                    ... justificado � direita
                                    -
                                    ****Velocidade de aquisi��o em 8TAD
                                    ACQT2 = 1
                                    ACQT1 = 0
                                    ACQT0 = 0
                                    ****Fonte de clock em Fosc/8
                                    ADCS2 = 0
                                    ADCS1 = 0
                                    ADCS0 = 1*/        
 
  
ADCON1 = 0b00001011;      /* -
                           	 -
                             VCFG1 = 0 -> Vref- = terra
                             VCFG0 = 1 -> Vref+ = VDD
                             *****Seleciona os canais AN0 e AN3 como anal�gicos
                             PCFG3 = 1
                             PCFG2 = 1
                             PCFG1 = 0
                             PCFG0 = 1*/    
                                                
lcd_inicio();           //Inicializa o LCD

while(1)
     {
     if (PORTAbits.RA4)		//Se Chave B2 foi pressionada
		{
		PORTCbits.RC2 = 1;	//Liga circuito de aquecimento
  		}      

     ADCON0 = 0b00000001;  		/*Seleciona Canal 0 para convers�o
                                  ...e habilita o conversor AD*/
     Delay1KTCYx(2);			//Atraso de 1ms
     ADCON0bits.GO = 1;         //Inicializa a convers�o
     while(ADCON0bits.GO);      //Aguarda o t�rmino da convers�o
 
     res_ad = ADRES;            //atribui o valor convertido � vari�vel res_ad0
 
     tensao = (res_ad*5000) / 1023;    //Calcula o valor em mV para o resultado obtido
 
     sprintf(buf_lcd,"AN0  = %04lu mV   ",tensao);     /*Armazena na vari�vel buf_lcd a  
                                                       ...string formatada com valor da
                                                       ... tens�o. Ex: AN0 = 0568mV*/
     lcd_posicao(1,1);                                //Posiciona o cursor do LCD na coluna 1 da linha 1
     lcd_escreve_bf(buf_lcd);                         //Envia a vari�vel buf_lcd para o LCD 
     
 
     ADCON0 = 0b00001101;         /*Seleciona Canal 3 para convers�o        
                                   ...e habilita o conversor AD*/

     Delay1KTCYx(2);              //Atraso de 1ms
 
     ADCON0bits.GO = 1;           //Inicializa a convers�o
     while(ADCON0bits.GO);        //Agurarda o t�rmino da convers�o
 
     res_temp = ADRES;            //atribui o valor convertido � vari�vel res_temp
 
     temp = (res_temp*500) / 1023;    //Calcula o valor em mV para o resultado obtido

	 if (temp > 40)
		PORTCbits.RC2 = 0;			//Desliga circuito de aquecimento.
 
     sprintf(buf_lcd,"Temp = %02lu %cC    ",temp, 0XDF);/*Armazena na vari�vel buf_lcd a  
                                                      ...string formatada com valor da
                                                      ... tens�o. Ex: AN0 = 0568mV*/ 
     lcd_posicao(2,1);                                //Posiciona o cursor do LCD na coluna 1 da linha 2
     lcd_escreve_bf(buf_lcd);                         //Envia a vari�vel buf_lcd para o LCD 
 
     Delay10KTCYx(40);                                //Atraso de 200ms
     }  
}