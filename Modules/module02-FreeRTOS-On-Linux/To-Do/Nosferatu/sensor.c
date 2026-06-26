#include "sensor.h"
#include "fake_mcu.h"

int SensorVal(void)
{
   return MCU_ReadADC();
}
