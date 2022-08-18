/*
 * I2CDrive.h
 *
 *  Created on: 10 ago. 2021
 *      Author: Alan Zamudio
 */

#ifndef I2CDRIVE_H_
#define I2CDRIVE_H_

void I2C_vfnDriverInit(void);
void I2C_vfnSlaveInit(void);
void I2C_vfnSendData(unsigned char *Data, unsigned char SizeData);

#endif /* I2CDRIVE_H_ */
