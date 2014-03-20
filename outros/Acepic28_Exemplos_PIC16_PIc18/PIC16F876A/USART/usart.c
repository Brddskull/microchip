//******************************************************************************
//Kit de desenvolvimento ACEPIC 18
//Projeto: Usart.c
//Descri��o: recebe um caracter pela serial e o envia novamente
//Desenvolvimento: Eng.: Carlos Eduardo Sandrini Luz
//                 ACEPIC Tecnologia e Treinamento LTDA
//
//Obs.: Colocar em ON a chaves 8 (LED) do DIP1
//      e chaves 7 (RA6-OSC1) e 8 (RA7-OSC2) do DIP2
//******************************************************************************
#include <16F876A.h>
#use delay(clock=8000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
//Defini��es para a comunica��o serial
#use RS232 (Baud=4800, xmit = PIN_C6, rcv = PIN_C7)

char dado[10];    //matriz que receber� os caracteres 
int i;            //vari�vel de controle de �ndice para a matriz dado

void main()      
{
Output_B(0x00);                        //Limpa toda a porta D

for (i=0;i<10;i++) dado[i] = 0;        //Limpa todos os �ndices da matriz dado

i = 0;                                 //zera a vari�vel i

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("Microcontroladores PIC 16F887.\r\n");

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("LD1 - ACENDE L1.\r\n");

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("DL1 - APAGA L1.\r\n");

while(true)
        {
         dado[i] = getc();     /*Recebe um caractere de cada vez e armazena em dado 
                                              com a    posi��o i*/ 

         printf("%c",dado[i]);    //envia novamente o caractere recebido
                     
         if (dado[i] == 0x0D)     //Se o caractere 0x0D (CR) for recebido
            {
            //Se a string contida na matriz dado = LD1
            if (dado[0] == 'L' && dado[1] == 'D' && dado[2] == '1')
               Output_Bit(PIN_B0,1);                //Acende o LED L1
             
            //Se a string contida na matriz dado = DL1
            if (dado[0] == 'D' && dado[1] == 'L' && dado[2] == '1')
               Output_Bit(PIN_B0,0);                 //Apaga o LED L1
    
            for (i=0;i<10;i++) dado[i] = 0;      //Limpa toda a matriz
            i=0;               //retorna a vari�vel i a 0   
            }
         else i++ ;          /*Se o caractere recebido for diferente de 0x0d
            incrementa a vari�vel i;*/                   
         } 
}
