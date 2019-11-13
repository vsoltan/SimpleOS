
#include "bluetooth.h"

BLEServer *watchServer = NULL;

bool deviceConnected = false;

class serverCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *server) {
      deviceConnected = true;
    }

    void onDisconnect(BLEServer *server) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);
  initBLE();
}

void initBLE() {
  BLEDevice::init("Valeriy's DumbSmart Watch");

  // create the server
  watchServer = BLEDevice::createServer();
  watchServer->setCallbacks(new serverCallbacks());

  // battery life
  BLEService *watchService = watchServer->createService(BatteryService);

  watchService->addCharacteristic(&BatteryLevelCharacteristic);

  BatteryLevelCharacteristic.addDescriptor(&BatteryLevelDescriptor);
  BatteryLevelCharacteristic.addDescriptor(new BLE2902());

  BatteryLevelDescriptor.setValue("Percentage 0 - 100");

  // advertising

  watchServer->getAdvertising()->addServiceUUID(BatteryService);
  watchService->start();
  watchServer->getAdvertising()->start();

}

void initBatteryLife(BLEServer *server) {

}

uint8_t level = 57;

void loop() {

  BatteryLevelCharacteristic.setValue(&level, 1);
  BatteryLevelCharacteristic.notify();
  delay(5000);

  level++;
  Serial.println(int(level));

  if (int(level) == 100)
    level = 0;

}
