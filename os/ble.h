
#ifndef BLE_H_
#define BLE_H_

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino_JSON.h>

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

extern bool deviceConnected;
extern JSONVar weatherObj;
extern bool weatherDataReceived;
extern bool newWeatherData;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("connected");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("disconnected");
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      Serial.println("HELLO");
      newWeatherData = true;
      weatherDataReceived = false;
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++){
          Serial.print(rxValue[i]);
        }
        char weather[rxValue.length() + 1];
        strcpy(weather, rxValue.c_str());
        Serial.println();
        Serial.println(weather);
        weatherObj = JSON.parse(weather);
        Serial.println("*********");
        if (JSON.typeof(weatherObj) == "undefined") {
          Serial.println("Parsing input failed!");
          return;
        }
        weatherDataReceived = true;
      }
    }
};


void initBLE(BLEServer **pServer, BLECharacteristic **pTxCharacteristic);

#endif
