#include "emergency.h"
#include "fake_mcu.h" 

int EmergencyStatus(void) {
    return MCU_ReadStatusRegister();
}