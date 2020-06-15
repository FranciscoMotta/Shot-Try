/*
 * File:   Principal.c
 * Author: Francisco Motta
 *
 * Created on 11 de junio de 2020, 09:38 AM
 */

#include <xc.h>
#include <stdint.h>
#include "configuracionFusibles.h"
#include "ADC_Inicializar.h"
#include "LCD_2X16.h"

#define _XTAL_FREQ 20000000UL

#define DATA_OUT LATCbits.LATC0
#define CLOCK_OUT LATCbits.LATC1
#define PUERTOS_OUT LATB
#define SERVO1 LATDbits.LATD7

void pinesInicio(void);
void pulsoReloj(void);
void shootMatrix(void);
void notShootMatrix(void);
void Escribir_Valor_En_Lcd(uint16_t valor);
void servo_rutina(void);
void happy_Face(void);
void sad_Face(void);


int cuenta_general = 0;
int intentos = 0;
int otroDato = 0;
int data = 0;

void main(void) {
    int cuentaAciertos = 0;
    Iniciar_Lcd();
    pinesInicio();
    Lcd_Escribir_Cadena("SHOOT TRY BY 4550");
    Posicion_Linea_Inferiror(0);
    Lcd_Escribir_Cadena("Aciertos:");
    Posicion_Linea_Inferiror(11);
    ADC_inicializacion(ADC_ON);
    char var = 0x00;
    int datoDeCuentaXD = 0;
PASO:
    Posicion_Linea_Superior(0);
    var = Leer_ADC(CANAL_AN0);
    Escribir_Valor_En_Lcd(var);
    if (var <= 43) {
        shootMatrix();
        intentos = intentos;
    } else {
        for (datoDeCuentaXD = 0; datoDeCuentaXD < 80; datoDeCuentaXD++) {
            notShootMatrix();
        }
        intentos++;
        cuentaAciertos++;
    }
    if (intentos == 5) {
        for (otroDato = 0; otroDato < 10; otroDato++) {
            for (datoDeCuentaXD = 0; datoDeCuentaXD < 80; datoDeCuentaXD++) {
                happy_Face();
            }
        }
        intentos = 0;
        data++;
    }
    if (data == 4) {
        for (otroDato = 0; otroDato < 10; otroDato++) {
            for (datoDeCuentaXD = 0; datoDeCuentaXD < 80; datoDeCuentaXD++) {
                sad_Face();
            }
        }
        data = 0;
    }
    Escribir_Valor_En_Lcd(cuentaAciertos);
    goto PASO;
    return;
}

void pulsoReloj(void) {
    CLOCK_OUT = 1;
    __delay_us(90);
    CLOCK_OUT = 0;
}

void pinesInicio(void) {
    TRISC = 0x00;
    TRISB = 0x00;
    TRISD = 0x00;
}

void Escribir_Valor_En_Lcd(uint16_t valor) {
    int Centenas_Del_Valor_Introducido = 0;
    int Decenas_Del_Valor_Introducido = 0;
    int Unidades_Del_Valor_Introducido = 0;

    /*FRACCIONAMIENTO EN DECENAS, UNIDADES Y CENTENAS*/
    Centenas_Del_Valor_Introducido = valor / 100; /*Dividimos en 100 para quedarnos con solo las centenas como parte entera*/
    Decenas_Del_Valor_Introducido = (valor % 100) / 10; /*Sacámos el módulo 100 al valor introducido y luego lo dividimos entre 10 para quedanos con las decenas como parte entera*/
    Unidades_Del_Valor_Introducido = (valor % 100) % 10; /*Sacámos el módulo 100 al valor introducido y sacamos el módulo 10 para quedanos con las unidades como parte entera*/

    Lcd_Escribir_Caracter(Centenas_Del_Valor_Introducido + 0x30); /*Se muestra el dato correspondiente y se le adiciona 0X30 para convertirlo a ASCII*/
    Lcd_Escribir_Caracter('.');
    Lcd_Escribir_Caracter(Decenas_Del_Valor_Introducido + 0x30); /*Se muestra el dato correspondiente y se le adiciona 0X30 para convertirlo a ASCII*/
    Lcd_Escribir_Caracter(Unidades_Del_Valor_Introducido + 0x30); /*Se muestra el dato correspondiente y se le adiciona 0X30 para convertirlo a ASCII*/
    Lcd_Escribir_Caracter('v');

    return;
}

void sad_Face(void) {
    DATA_OUT = 1;
    pulsoReloj();
    DATA_OUT = 0;
    PUERTOS_OUT = ~0x66;
    pulsoReloj();
    PUERTOS_OUT = ~0x00;
    pulsoReloj();
    PUERTOS_OUT = ~0x00;
    pulsoReloj();
    PUERTOS_OUT = ~0x3C;
    pulsoReloj();
    PUERTOS_OUT = ~0x7E;
    pulsoReloj();
    PUERTOS_OUT = ~0x42;
    pulsoReloj();
    PUERTOS_OUT = ~0x81;
    pulsoReloj();
    PUERTOS_OUT = ~0x66;
    pulsoReloj();
}

void happy_Face(void) {
    DATA_OUT = 1;
    pulsoReloj();
    DATA_OUT = 0;
    PUERTOS_OUT = ~0x66;
    pulsoReloj();
    PUERTOS_OUT = ~0x00;
    pulsoReloj();
    PUERTOS_OUT = ~0x00;
    pulsoReloj();
    PUERTOS_OUT = ~0x81;
    pulsoReloj();
    PUERTOS_OUT = ~0x42;
    pulsoReloj();
    PUERTOS_OUT = ~0x7E;
    pulsoReloj();
    PUERTOS_OUT = ~0x3c;
    pulsoReloj();
    PUERTOS_OUT = ~0x66;
    pulsoReloj();
}

void notShootMatrix(void) {
    DATA_OUT = 1;
    pulsoReloj();
    DATA_OUT = 0;
    PUERTOS_OUT = ~0x42;
    pulsoReloj();
    PUERTOS_OUT = ~0x24;
    pulsoReloj();
    PUERTOS_OUT = ~0x18;
    pulsoReloj();
    PUERTOS_OUT = ~0x18;
    pulsoReloj();
    PUERTOS_OUT = ~0x24;
    pulsoReloj();
    PUERTOS_OUT = ~0x42;
    pulsoReloj();
    PUERTOS_OUT = ~0x81;
    pulsoReloj();
    PUERTOS_OUT = ~0X81;
    pulsoReloj();
}

void shootMatrix(void) {
    DATA_OUT = 1;
    pulsoReloj();
    DATA_OUT = 0;
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0xFF;
    pulsoReloj();
    PUERTOS_OUT = ~0XFF;
    pulsoReloj();
}
