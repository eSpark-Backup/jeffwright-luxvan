#include "DHT.h"
#include "HX711.h"
#include <Wire.h>
#include <BLE2902.h>
#include <BLEUtils.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>



/***** BLE-Protocol Declaration *****/
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // Random 128-bit UniqueID for BLE Service
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // Random 128-bit UniqueID for BLE Characteristic


/***** Inclinometer Definition *****/
#define SDA 21
#define SCL 22
Adafruit_MPU6050 mpu;

/***** DHT11 Sensor Definition *****/
#define DHTPIN 15
#define DHTTYPE DHT11

/***** Ultrasonic Sensor Definition *****/
const int trigPin = 5;
const int echoPin = 2;
#define RXD2 16
#define TXD2 17

/***** HX711 Sensor Definition *****/
const int LOADCELL_DOUT_PIN = 25;
const int LOADCELL_SCK_PIN = 26;
HX711 scale;


/***** Constructor for Sensors *****/
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;


/***** Custom User Variables *****/
float h_dht = 0;
float t_dht = 0;
float t_bmp = 0;
float a_bmp = 0;
float weight = 0;
float aX=0, aY=0, aZ=0, gX=0, gY=0, gZ=0;
long duration;
int distance;
String mydata = "";
char payload[80];
int test1 = 0, test2 = 1, test3 = 2, test4 = 3;   // Variables to test logic without Sensors


/***** BLE-Callback Function for BLE-Stack *****/
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void setup() {

  pinMode(trigPin, OUTPUT); // Pin Initializ
  pinMode(echoPin, INPUT); 
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  dht.begin();    // Validate and Initialize the DHT11 Sensor
  
  if (!bmp.begin())   // Validate and Initialize the BMP180 Sensor
    Serial.println("Could not find a valid BMP085 sensor, check wiring!"); // Prints the message and continues with the code


/***** Inclinometer Sensor Initialization *****/
  if (!mpu.begin()) { 
    Serial.println("Failed to find MPU6050 chip");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);


/***** Wieght Sensor Initialization *****
  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
  // by the SCALE parameter (not set yet)

  scale.set_scale(233.82);    // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided

  
/***** BLE-Stack Definitions *****/
  BLEDevice::init("Slave_2");   // Give a custom name to the device
  
  pServer = BLEDevice::createServer();    // Create a BLE-Server Application for Slave Functionality
  pServer->setCallbacks(new MyServerCallbacks());   // Attach callback function declared above to BLE-Stack
  
  BLEService *pService = pServer->createService(SERVICE_UUID);    // Create a custom Service to hold the BLE Characteristics
  
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );                                        // Create and define the properties of the BLE Characteristic
                    
  pCharacteristic->addDescriptor(new BLE2902());
  
  pService->start();    // Start the BLE-Server

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  Serial.println("Waiting for a client connection to notify...");

}

void loop() {

    if (deviceConnected) {    //Variable automatically true when a device connects via the Callback function
        sens_data();
        pCharacteristic->setValue(payload);
        pCharacteristic->notify();
        delay(3); 
    }   
    
    if (!deviceConnected && oldDeviceConnected) {   // If a previous connected device disconnects, BLE-Callback automatically satisfies this condition
        delay(500); 
        pServer->startAdvertising(); 
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    
    if (deviceConnected && !oldDeviceConnected) {   // Overwrite the oldDeviceConnected variable with newly connected device.
    
        oldDeviceConnected = deviceConnected;
    }
}
