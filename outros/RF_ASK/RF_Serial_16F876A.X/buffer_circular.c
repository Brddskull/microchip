/* *******************************************************************************
 * Curso de Capacitaci�n "Redes Inal�mbricas Zigbee de Sensores con M�dulos XBee"
 * Proyecto 2. Comunicaci�n PC/Microcontrolador con XBee Coordinador y XBee
 * Ruteador en Modo Transparente.
 *
 * Recibe comandos de texto de la PC y transmite el estado de sus puertos a la
 * misma mediante un enlace serial con m�dulos XBee.
 *
 * Hace uso de las librer�as  UART provistas por el compilador PICC de Hi-Tech.
 * Las funciones serialRead(); serial Available(); y serialFlush(); son
 * adaptaciones por el autor, de las librer�as de la plataforma Arduino.
 *
 * Hardware:        PIC16F876A, M�dulo XBee Serie 2
 * Caracter�sticas: Clock: 4MHz (cristal externo), Frecuencia de operaci�n:
 * 2.4GHz (ZigBee), Data rate: 9600 bps
 * Funciones:       Software para control y monitoreo mediante red ZigBee con
 *                  m�dulos XBee.
 * Versi�n:         1.1 (21 de Octubre de 2013)
 * Autor:           Raul Alvarez Torrico (www.TecBolivia.com)
 * *******************************************************************************
 * Este c�digo se distribuye exclusivamente a los al�mnos del curso "Redes Inal�m-
 * bricas ZigBee de Sensores con M�dulos XBee" ofrecido en www.TecBolivia.com
 * Este c�digo es para uso personal de cada al�mno y QUEDA TERMINANTEMENTE PROHI-
 * BIDA LA DISTRIBUCI�N DE LOS ARCHIVOS INCLUIDOS EN ESTE PROYECTO A TERCEROS.
 * Los al�mnos inscritos en el curso tiene permiso de usar, modificar e incluir
 * el c�digo provisto en sus proyectos personales.
 *
 *********************************************************************************/
/* Inclusi�n de librer�as usadas en el programa */
#include <htc.h>        //Librer�a principal del compilador PICC
#include "buffer_circular.h"    // Libreria para buffer circular

/* Variables globales */
static unsigned char bufferRx[RX_BUFFER_SIZE];  // Buffer de recepci�n serial
unsigned char rx_buffer_head =0; //Indice "cabeza" para el buffer (escritura)
unsigned char rx_buffer_tail =0; //Indice "cola" para el buffer (lectura)

/*******************************************************************************
*                   FUNCION DE LECTURA DESDE EL BUFFER SERIAL
*
* Descripci�n   :   Permite la lectura de 1 caracter desde el buffer de
*                   recepci�n serial.
*
* Argumentos    :   Ninguno.
*
* Retorna       :   unsigned char c    Un caracter del buffer a la vez.
* Notas         :
*******************************************************************************/
unsigned char serialRead(void)
{
    unsigned char c;

    // si la cabeza no est� delante de la cola, no tenemos ning�n caracter
    if (rx_buffer_head == rx_buffer_tail) {
        return -1;
    } else {
        c = bufferRx[rx_buffer_tail];
        rx_buffer_tail = rx_buffer_tail + 1;
        rx_buffer_tail %= RX_BUFFER_SIZE;
        return c;
    }
}

/*******************************************************************************
*                   FUNCION DE VERIFICACION DE EXISTENCIA DE CARACTERES
*
* Descripci�n   :   Permite la verificaci�n de la existencia de al menos 1
*                   caracter disponible en el buffer de recepci�n serial.
*
* Argumentos    :   Ninguno.
*
* Retorna       :   unsigned char i    El n�mero de caracteres disponibles en el buffer.
* Notas         :
*******************************************************************************/
unsigned char serialAvailable(void)
{
    unsigned char i;

    i = RX_BUFFER_SIZE + rx_buffer_head - rx_buffer_tail;
    i %= RX_BUFFER_SIZE;

    return i;
}

/*******************************************************************************
*                   FUNCION DE VACIADO DEL BUFFER DE RECEPCION
*
* Descripci�n   :   Realiza el vaciado del buffer de recepci�n serial
*
* Argumentos    :   Ninguno.
*
* Retorna       :   Nada.
* Notas         :
*******************************************************************************/
void serialFlush(void)
{
    // no revertir el orden de esto o puede haber problemas si la interrupcion de RX
    // ocurre despues de leer el valor de rx_buffer_head pero antes de escribir
    // el valor a rx_buffer_tail; el valor previo de rx_buffer_head
    // puede ser escrito a rx_buffer_tail, haci�ndolo aparecer como si el buffer
    // estuviera lleno, no vac�o.
    rx_buffer_head = rx_buffer_tail;
}

/*******************************************************************************
*                   RUTINA DE INTERRUPCION
*
* Descripci�n   :   Rutina para la atenci�n de las interrupciones en el PIC
*                   implementada seg�n los requerimientos del compilador
*                   PICC de Hi-Tech
*
* Argumentos    :   Ninguno.
*
* Retorna       :   Nada
* Notas         :
*******************************************************************************/
void interrupt isr(void)    //Rutina de interrupcion de tx rx serial
{
    unsigned char i;

    if(RCIF)    //Si existe una interrupcion de rx serial,
    {
        i = rx_buffer_head + 1;
        i %= RX_BUFFER_SIZE;

        // si debieramos almacenar el caracter recibido en la localizaci�n
        // justo antes de la cola (lo cual significa que la cabeza debe avanzar
        // a la posici�n actual de la cola), estamos a punto de desbordar el buffer
        // por ello no escribimos el caracter ni avanzamos la cabeza.
        if (i != rx_buffer_tail) {
            bufferRx[rx_buffer_head] = RCREG;
            rx_buffer_head = i;
        }
    }
}
