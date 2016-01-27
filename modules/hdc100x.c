/*
 * hdc100x.c
 *
 * Created: 21/01/2016 20:46:35
 *  Author: GroundLayer
 */ 

#include "../drivers/hdc100x.h"
#include "./hdc100x.h"

#include "registrar/registrar.h"
#include "tasks/modules.h"

#define MODULE_NAME "HDC100X_TEMP_HUMI"
#define MODULE_DATA_SIZE 2
#define MODULE_TEMP "temperature"
#define MODULE_HUMIDITY "humidity"

data_name HDC100X_names[MODULE_DATA_SIZE] = { MODULE_TEMP , MODULE_HUMIDITY };
data_type HDC100X_types[] = { FLOAT , FLOAT };

void HDC100X_tick(void);
definition *HDC100X_def;

void HDC100X_module_init(void) {
	HDC100x_init();
	HDC100X_def = register_definition(EVENT , MODULE_NAME , HDC100X_names , HDC100X_types , MODULE_DATA_SIZE , NULL, HDC100X_tick , 1000);
}

void HDC100X_tick(void) {
	float temp , humi;
	
	if(HD100x_read_temp_humi(&temp , &humi)) {
		instance inst = create_instance(MODULE_NAME);
		if(inst.def != NULL && inst.values != NULL){
			(*(float*) inst.values[0]) = temp;
			(*(float*) inst.values[1]) = humi;
			portBASE_TYPE xStatus = xQueueSendToBack(module_out, &inst , 10 / portTICK_RATE_MS );
			if(xStatus != pdPASS){
				release_instance(inst);
			}
		}
	}
}