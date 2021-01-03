#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "DHT.h"




// BLE-Protocol Declaration //
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"



// DHT11 Sensor Definition //
#define DHTPIN 15
#define DHTTYPE DHT11

// Ultrasonic Sensor Definition //
const int trigPin = 5;
const int echoPin = 2;


// Constructor for DHT11 Sensor //
DHT dht(DHTPIN, DHTTYPE);

// Constructor for BMP180 Sensor //
Adafruit_BMP085 bmp;


// Variable Initialization //
float h_dht = 0;
float t_dht = 0;
float t_bmp = 0;
float a_bmp = 0;
long duration;
int distance;
String mydata = "";
char payload[80];
int test1 = 0, test2 = 1, test3 = 2, test4 = 3;



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void setup() {

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(115200);
//  Serial.println(F("DHTxx test!"));
//  dht.begin();
//
  if (!bmp.begin())
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");

  BLEDevice::init("ESP32_2");
  
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  
  BLEService *pService = pServer->createService(SERVICE_UUID);
  
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
                    
  pCharacteristic->addDescriptor(new BLE2902());
  
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  Serial.println("Waiting for a client connection to notify...");

}

void loop() {

    if (deviceConnected) {
        sens_data();
        pCharacteristic->setValue(payload);
        pCharacteristic->notify();
        delay(3); 
    }   
    
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); 
        pServer->startAdvertising(); 
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    
    if (deviceConnected && !oldDeviceConnected) {
    
        oldDeviceConnected = deviceConnected;
    }
}
