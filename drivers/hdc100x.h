/*
 * hdc100x.h
 *
 * Created: 21/01/2016 20:32:30
 *  Author: GroundLayer
 */ 


#ifndef HDC100X_H_
#define HDC100X_H_

#include "asf.h"
#include "HAL/i2c.h"

#define HDC100X_I2CADDR       0x41
#define HDC100X_TEMP          0x00
#define HDC100X_HUMID         0x01
#define HDC100X_CONFIG        0x02
#define HDC100X_CONFIG_RST    (1 << 15)
#define HDC100X_CONFIG_HEAT   (1 << 13)
#define HDC100X_CONFIG_MODE   (1 << 12)
#define HDC100X_CONFIG_BATT   (1 << 11)
#define HDC100X_CONFIG_TRES_14  0
#define HDC100X_CONFIG_TRES_11  (1 << 10)
#define HDC100X_CONFIG_HRES_14  0
#define HDC100X_CONFIG_HRES_11  (1 << 8)
#define HDC100X_CONFIG_HRES_8   (1 << 9)

#define HDC100X_SERIAL1       0xFB
#define HDC100X_SERIAL2       0xFC
#define HDC100X_SERIAL3       0xFD
#define HDC100X_MANUFID       0xFE
#define HDC100X_DEVICEID      0xFF

bool HDC100x_init(void);
bool HD100x_read_temp_humi(float* temp , float* humi);




#endif /* HDC100X_H_ */