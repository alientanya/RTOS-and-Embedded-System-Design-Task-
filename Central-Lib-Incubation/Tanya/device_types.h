#ifndef DEVICE_TYPES_H
#define DEVICE_TYPES_H

typedef enum
{
    DEVICE_OK,
    DEVICE_BUSY,
    DEVICE_ERROR,
    DEVICE_DISCONNECTED,
    DEVICE_NOT_INITIALIZED
} device_status_t;

#endif /* DEVICE_TYPES_H */