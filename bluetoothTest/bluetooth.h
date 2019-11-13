#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h> //Library to use BLE as server
#include <BLE2902.h>

// SERVICES
#define BatteryService BLEUUID((uint16_t)0x180F)

// CHARACTERISTICS
BLECharacteristic BatteryLevelCharacteristic(BLEUUID((uint16_t)0x2A19), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

// DESCRIPTORS
BLEDescriptor BatteryLevelDescriptor(BLEUUID((uint16_t)0x2901));
