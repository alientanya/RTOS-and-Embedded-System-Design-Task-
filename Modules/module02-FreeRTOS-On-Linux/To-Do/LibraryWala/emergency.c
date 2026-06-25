#include "emergency.h"
#include "fake_mcu.h" 

uint8_t EmergencyStatus(void) {
    return MCU_ReadStatusRegister();
}