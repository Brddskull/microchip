//******************************************************************************
//Kit de desenvolvimento ACEPIC 18_28
//Projeto: int_etx.c
//Descri��o: Ao pressionar o bot�o RB0, ser� gerada a interrup��o externa 
//           fazendo com que o LED L8 se alterne entre aceso e apagado dependendo
//           do pressionamento do bot�o;   
//Desenvolvimento: Eng.: Carlos Eduardo Sandrini Luz
//                 ACEPIC Tecnologia e Treinamento LTDA
//
//Obs.: Colocar em ON as chaves 6 (MCL1-MCLR) e 8 (LED) do DIP SW2
//******************************************************************************

#include <16F886.h>
#use delay(clock=4000000)
#fuses INTRC_IO,NOWDT,PUT,NOBROWNOUT,NOLVP

boolean led;

#INT_EXT
void trata_ext()
{
led = ~led;
OUTPUT_BIT(PIN_B7,led);
}

void main()
{
led = false;

EXT_INT_EDGE(H_TO_L);
ENABLE_INTERRUPTS(GLOBAL | INT_EXT);


while(true)
     {
     }
} 
