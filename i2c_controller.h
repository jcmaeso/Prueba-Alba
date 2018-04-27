/*
 * i2c_controller.h
 *
 *  Created on: 16 abr. 2018
 *      Author: jcala
 */

#ifndef I2C_CONTROLLER_H_
#define I2C_CONTROLLER_H_

void I2C_setUp(unsigned int cpuInt,unsigned int slave_addr);
unsigned char I2C_transmit(unsigned int slave_addr,int data_length, unsigned char* data);
void I2C_receive(unsigned int slave_addr, int data_out_length, unsigned char* data,unsigned char* rx);
void I2C_test();
unsigned char I2C_reg_read();

#endif /* I2C_CONTROLLER_H_ */
