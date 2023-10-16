//simulation sketch to simulate steps for testing ble with phone

// add this board under Arduino Preferences, additional boards: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

#include <ArduinoBLE.h>
#include <NewPing.h> //this library has built in interrupts, and median filtering

BLEService wallMountService("stedibalancev300bluetoothlenerg");
BLEUnsignedIntCharacteristic distanceSensorCharacteristic("1212", BLERead | BLENotify);

void setup() {
  Serial.begin(9600);

  //while(!Serial);
  if(!BLE.begin())
  {
    if (Serial){
      Serial.println("Starting BLE failed!");
      while(1);
    }
  }

  BLE.setLocalName("STEDIWallMountV3.00");
  BLE.setAdvertisedService(wallMountService);
  BLE.setDeviceName("SeanSTEDI");
  wallMountService.addCharacteristic(distanceSensorCharacteristic);
  BLE.addService(wallMountService);

  BLE.advertise();
  
  Serial.println("Bluetooth STEDI device active, waiting for connections ...");  

}

int distance = 45;

void loop() {
  BLEDevice central = BLE.central();

  if (central)
  {
    Serial.println("Connected to central: ");
    Serial.println(central.address());

    if (central.connected()) {
      Serial.println("Distance: "+distance);
      distanceSensorCharacteristic.writeValue(distance);
    }    
  }

  else{
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }

  if(distance==45){
    distance=39;
  } else if(distance==39){
    distance=45;
  }
  
  delay(50);  
}
