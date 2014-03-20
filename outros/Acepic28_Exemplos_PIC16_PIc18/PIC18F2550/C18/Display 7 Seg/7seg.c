/*******************************************************************************
*                        Kit de desenvolvimento ACEPIC 28                      *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Contagem de 0 a 100 nos displays de 7 segmentos                      *
*Obs.:     Ligar chave 4, 5 e 6 do DIP DP1                                        *
********************************************************************************/
#include <p18F2550.h>
#include <delays.h>

// Frequencia do oscilador = 8MHz
// Ciclo de m�quina  = 1/(Fosc/4) = 0,5us

#pragma config FOSC = HS       		//Configura o oscilador a cristal
#pragma config CPUDIV = OSC1_PLL2 	//Postscale clock do sistema 
#pragma config WDT = OFF  			//Desabilita o Watchdog Timer (WDT).
#pragma config PWRT = ON   			//Habilita o Power-up Timer (PWRT).
#pragma config BOR = ON				//Habilita Brown-out reset 
#pragma config BORV = 1	        	//Tens�o do BOR � 4,33V.
#pragma config LVP = OFF       		//Desabilita o Low Voltage Program.


char digito[10] =
               {0b00111111, 	//D�gito 0
                0b00000110, 	//D�gito 1
                0b01011011, 	//D�gito 2
                0b01001111, 	//D�gito 3
                0b01100110, 	//D�gito 4
                0b01101101, 	//D�gito 5
                0b01111101, 	//D�gito 6
                0b00000111, 	//D�gito 7
                0b01111111, 	//D�gito 8
                0b01101111  	//D�gito 9
               };
char conta=0;				//Vari�vel de controle para os displays
short x = 0, d1 = 0, d2 = 0, d3 = 0;

#pragma code int_pr = 0x08	//vetor de interrup��o de alta prioridade
#pragma interrupt int_TIMER0
void int_TIMER0(void)		//Fun��o int_timer0 (tratamento da interrup��o)
{
conta++;			//Incrementa a vari�vel conta
if (conta>4) conta = 1;	//Se conta > 4, faz conta = 1

switch(conta)			//verifica o valor da vari�vel conta
          {
      	case 1: PORTB = digito[d1];	//Coloca na Porta D o valor referente ao 
                                                  //d�gito 1
                PORTC = 0X01;		//Liga o Display 1 e desliga os demais
                PORTA = 0x00;
				 
		        break;
        case 2: PORTB = digito[d2];	//Coloca na Porta D o valor referente ao 
                                                                       //d�gito 2
                PORTC = 0X02;		//Liga o Display 2 e desliga os demais
                break; 
        case 3: PORTB = digito[d3];	//Coloca na Porta D o valor referente ao 
                                                                       //d�gito 2
                PORTC = 0X00;		//Liga o Display 2 e desliga os demais
				PORTA = 0x20;
                		
          }

INTCONbits.TMR0IF = 0;	//Zera o flag de controle da interrup��o
TMR0L = 100;                 //Valor Inicial para o timer 0 	
}

void main()
{
ADCON1 = 0xFF;			//Faz todos os canais AD

TRISA = 0x00;			//Faz toda a porta A como sa�da	
TRISB = 0x00;			//Faz toda a porta B como sa�da
PORTB = 0x00;			//Zera toda a porta B
TRISC = 0x00;			//Faz toda a porta C como sa�da



T0CON = 0b11000100;      /*Configura o Registrador T0CON
                           TMR0ON = 1 -> Habilita o TIMER 0
                           T08BIT = 1 -> TIMER 0 no modo 8 bits
                           T0CS = 0 -> Incremento pelo ciclo de m�quina
                           ...0,5us para o cristal de 8MHz.
                           T0SE = 0 -> Incremento na orda de subida.
                           PSA = 0 -> Prescale aplicado ao Timer 0
                           PS2 = 1, PS1 = 0 e PS0 = 0 -> Prescale = 1:32*/

INTCON = 0b10100000;     /*Configura o registrador INTCON
                           GIE = 1 (bit7) -> Habilita a interrup��o global
                           TMR0IE = 1 (bit 5)-> Habilita a interrup��o do Timer 0
                           TMR0IF = 0 (bit 2)-> Flag de interrup��o do Timer 0 desligado */

TMR0L = 100;              //Valor Inicial para o timer 0


while(1)
		{
        d1 = x / 100;
        d2 = x / 10;
        d3 = x % 10;
        Delay10KTCYx(200);   	//Gera um delay de 1000ms  
        x++;
        if (x > 100) x = 0;
		}
}