/*
 * hdc100x.c
 *
 * Created: 21/01/2016 20:32:18
 *  Author: GroundLayer
 */ 

#include "modules/drivers/hdc100x.h"

bool HDC100x_init(void){
	
	unsigned char data[2];
	uint16_t config = HDC100X_CONFIG_RST | HDC100X_CONFIG_MODE | HDC100X_CONFIG_TRES_14 | HDC100X_CONFIG_HRES_14;
	data[0] = config >> 8;
	data[1] = config & 0xFF;
	HAL_I2C_write(HDC100X_I2CADDR , 2 , data );
	
	data[0] = HDC100X_MANUFID;
	HAL_I2C_write(HDC100X_I2CADDR , 1 ,data );
	HAL_I2C_read(HDC100X_I2CADDR , 2 , data);
	
	if(data[0] != 0x54 || data[1] != 0x49) {
		return false;
	}
	
	data[0] = HDC100X_DEVICEID;
	HAL_I2C_write(HDC100X_I2CADDR , 1 ,data );
	HAL_I2C_read(HDC100X_I2CADDR , 2 , data);
	
	if(data[0] != 0x10 || data[1] != 0x00) {
		return false;
	}
	
	return true;
}

bool HD100x_read_temp_humi(float* temp , float* humi) {
	unsigned char data[2];
	uint16_t buffer;
	
	data[0] = HDC100X_TEMP;
	HAL_I2C_write(HDC100X_I2CADDR , 1 ,data );
	vTaskDelay(100);
	if(HAL_I2C_read(HDC100X_I2CADDR , 2 , data) != STATUS_OK){
		return false;
	}
	buffer = data[0] << 8 | data[1];
	*temp = (float) buffer;
	*temp /=65536;
	*temp *= 165;
	*temp -= 40;
	
	data[0] = HDC100X_HUMID;
	if(HAL_I2C_read(HDC100X_I2CADDR , 2 , data) != STATUS_OK){
		return false;
	}
	buffer = data[0] << 8 | data[1];
	*humi = (float) buffer;
	*humi /= 65536;
	*humi *= 100;
	
	return true;
}