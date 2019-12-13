
#include "ble.h"

void initBLE(BLEServer **pServer, BLECharacteristic **pTxCharacteristic) {
 
  // Create the BLE Device
  BLEDevice::init("Valeriy's DumbWatch");

  // Create the BLE Server
  *pServer = BLEDevice::createServer();
  (*pServer)->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = (*pServer)->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  *pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  (*pTxCharacteristic)->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  (*pServer)->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}
