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
#ifndef BUFFER_CIRCULAR_H
#define BUFFER_CIRCULAR_H

// Definir aqui el tamano para el buffer circular, mejor si son en factores
// de 2^n. Ej: 8, 16, 32, 64, etc
#define RX_BUFFER_SIZE 32    

unsigned char serialRead();         // Retorna 1 caracter del buffer de recepci�n
unsigned char serialAvailable();    // Retorna la cantidad de caracteres disponibles en el buffer de recepci�n
void serialFlush();                 // Borra el buffer de recepci�n

#endif
