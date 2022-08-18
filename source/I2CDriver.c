/*
 * I2CDriver.c
 *
 *  Created on: 10 ago. 2021
 *      Author: Alan Zamudio
 */

#include "MKL25Z4.h"

void I2C_vfnDriverInit(void)
{

	/*Configuracion de pines*/
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	/*Habilitar SCL pin B2*/
	PORTB->PCR[2] = 0x207;
	/*Habilitar pin B3*/
	PORTB->PCR[3] = 0x207;

	/*Habilitar reloj I2C*/
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	I2C0->F = 0x1F; //BaudRate inicial = 100 kbps

	I2C0->C1 |= I2C_C1_IICEN_MASK;
}

void I2C_vfnSlaveInit(void)
{
	I2C0->A1 = 0x3C;  //Direccion de OLED
	I2C0->F = 0x45; // BaudRate=300kbps    bus = 24MHz       mul = 2     SCL divider = 30
}

void I2C_vfnSendData (unsigned char *Data, unsigned char SizeData)
{
	//unsigned char Estado = 0;

	 /* Limpieza de posibles alertas */
	I2C0->S |= I2C_S_ARBL_MASK;		  //Operacion normal del bus y arbitraje
	I2C0->S |= I2C_S_IICIF_MASK;	  //Sin interrupciones pendientes

    /* Esperar a que la transferencia sea completada */
    while (!(I2C0->S & I2C_S_TCF_MASK)){}

    /* Verificar si el bus no esta utilizable*/
    if (I2C0->S & I2C_S_BUSY_MASK){
    }else{
        /* Mandamos señal de START */
        I2C0->C1 |= I2C_C1_MST_MASK | I2C_C1_TX_MASK;

        /*Mandar slave addres y corrimiento por R/W*/
        I2C0->D = (*Data++) << 1 | 0;
    }

    while (!(I2C0->S & I2C_S_IICIF_MASK)){} //verificar que no existan interrupciones pendientes

    /* Verificar error de transferencia */
	if(I2C0->S & I2C_S_ARBL_MASK){
		I2C0->S |= I2C_S_ARBL_MASK;
	}

	/* Verificar señal ACK*/
	if(I2C0->S & I2C_S_RXAK_MASK){
		I2C0->S |= I2C_S_RXAK_MASK;
	}

	SizeData--;

	/* Esperar a que este listo para transmitir*/
	while (!(I2C0->S & I2C_S_TCF_MASK)){}

	I2C0->S = I2C_S_IICIF_MASK;

	/* Preparar para transmitir */
	I2C0->C1 |= I2C_C1_TX_MASK;

	while(SizeData--)
	{
		I2C0->D = *Data++; //se manda el dato

		/* Transferencia completa */
		while (!(I2C0->S & I2C_S_IICIF_MASK)){}

		/* Clear the IICIF flag. */
		I2C0->S |= I2C_S_IICIF_MASK;

	}

	/* Dar comando de STOP */
	I2C0->C1 &= ~(I2C_C1_MST_MASK | I2C_C1_TX_MASK | I2C_C1_TXAK_MASK);

	while ((I2C0->S & I2C_S_BUSY_MASK)){}

}
