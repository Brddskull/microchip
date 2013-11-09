//******************************************************************************
//Kit de desenvolvimento ACEPIC 18_28
//Projeto: Usart.c
//Descri��o: recebe um caracter pela serial e o envia novamente
//Desenvolvimento: Eng.: Carlos Eduardo Sandrini Luz
//                 ACEPIC Tecnologia e Treinamento LTDA
//
//Obs.: Colocar em ON as chaves 6 (RA5-MCLR), 1 (RB1-RX) e 2 (RB2-TX) do DIP SW2
//******************************************************************************

#include <16F886.h>
#use delay(clock=4000000)
#fuses INTRC_IO,NOWDT,PUT,NOBROWNOUT,NOLVP
#use rs232(baud=4800, XMIT=PIN_C6, RCV=PIN_C7)

void main()
{
while(true)
     {
     printf("%c",getc());
     }
}     
