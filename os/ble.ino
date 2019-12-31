
#include "ble.h"

void initBLE(BLEServer **pServer, BLECharacteristic **pTxCharacteristic) {

  // Create the BLE Device
  BLEDevice::init("Valeriy's DumbWatch");


  // TODO figure out it this is necessary
  BLEDevice::setMTU(512);
  Serial.println(BLEDevice::getMTU());

  // Create the BLE Server
  *pServer = BLEDevice::createServer();

  if (*pServer == NULL) {
    perror("failed to correctly initialize server");
  }

  (*pServer)->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = (*pServer)->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  *pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );

  if (*pTxCharacteristic == NULL) {
    perror("failed to correctly initialize transmit characteristic");
  }


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
