#include "battery.h"
#include "fake_mcu.h"
int BatteryVal(void)
{
  return MCU_ReadBatteryVoltage();
}
