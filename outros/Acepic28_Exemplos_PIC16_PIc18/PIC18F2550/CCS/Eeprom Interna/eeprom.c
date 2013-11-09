/*******************************************************************************
*                        Kit de desenvolvimento ACEPIC 28                      *
*                      ACEPIC Tecnologia e Treinamento LTDA                    *
*                               www.acepic.com.br                              * 
*                                                                              *
*Objetivo: Programa de demonstra��o para armazenamento de dados na mem�ria     *
*          EEPROM do microcontrolador e informa��es enviadas pela serial.      *
*          Quando resetada a placa, s�o armazenados nos endere�os 0 a 5 da     * 
*          EEPROM os caracteres formando a palavra ACEPIC e ap�s isso,         *
*          o microcontrolador envia pela serial a informa��o que o usu�rio     *
*          deve pressionar o bot�o B1 para verificar o conte�do armazenado     *
*          nestes endere�os da EEPROM Interna do microcontrolador              *
*Obs.: Ligar as chaves 7 (RA6-OSC1) e 8 (RA7-OSC2) do DIP2                     *
*******************************************************************************/
#include <18F2550.h>
#use delay (clock=8000000)    /*Defini��o da frequ�ncia do cristal para c�lculo 
                                ..dos delays*/
#fuses HS, NOWDT, PUT, BROWNOUT, NOLVP, CPUDIV1 
//Defini��es para a comunica��o serial
#use RS232 (Baud=19200, xmit = PIN_C6, rcv = PIN_C7)


void main()      
{
//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("Microcontroladores PIC 18F2550.\r\n");

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("Gravando na  EEPROM...\r\n");

//Escrevendo na EEPROM
write_eeprom(0,'A');       //Escreve o caractere 'A' no endere�o 0
write_eeprom(1,'C');       //Escreve o caractere 'C' no endere�o 1
write_eeprom(2,'E');       //Escreve o caractere 'E' no endere�o 2
write_eeprom(3,'P');       //Escreve o caractere 'P' no endere�o 3
write_eeprom(4,'I');       //Escreve o caractere 'I' no endere�o 4
write_eeprom(5,'C');       //Escreve o caractere 'C' no endere�o 5
delay_ms(500);      //Atraso de 500ms

//Envia a string pela serial e muda o cursor para a pr�xima linha
printf("Pressione B1 para ver.\r\n");

while(true)
     {
     if (input(PIN_A2))      //Se o bot�o B0 for pressionado
        {
        /*Envia as strings pela serial formatadas com os valores lido dos enderecos
        0 at� 5 da EEPROM*/
        printf("Valor lido no endereco 0: %c\r\n",read_eeprom(0));
        printf("Valor lido no endereco 1: %c\r\n",read_eeprom(1));
        printf("Valor lido no endereco 2: %c\r\n",read_eeprom(2));
        printf("Valor lido no endereco 3: %c\r\n",read_eeprom(3));
        printf("Valor lido no endereco 4: %c\r\n",read_eeprom(4));
        printf("Valor lido no endereco 5: %c\r\n",read_eeprom(5));
        delay_ms(300);        //Atraso de 300ms
        }
     } 
}
