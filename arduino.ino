// DHT sensor library - Version: Latest 
// SparkFun APDS-9301 Lux Sensor - Version: Latest 
#include <Sparkfun_APDS9301_Library.h>
#include <Adafruit_Sensor.h> // import humidity sensor libraries
#include <Adafruit_AM2320.h>
#include <DHT.h>
#include <DHT_U.h>

// Arduino-Library-2.9.3 - Version: Latest 

#define DHTPIN 2 
#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
#define _DEBUG_
#define _DISABLE_TLS_
#define THINGER_USE_STATIC_MEMORY
#define THINGER_STATIC_MEMORY_SIZE 512

#include <WiFi.h> //import wifi access library for arduino
#include <ThingerWifi.h> //import thinger.io library for wifi connection

#define USERNAME "Corantin"// set a username 
#define DEVICE_ID "arduino"// set the device's name
#define DEVICE_CREDENTIAL "mrM15cvC9YKY" //device id

#define SSID "honor10" //set the network name/id
#define SSID_PASSWORD "connectedflowers" //set the password of the network

ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
APDS9301 apds; //import the lux sensor's library
Adafruit_AM2320 am2320 = Adafruit_AM2320();
#define INT_PIN 10
                     
    bool lightIntHappened = false;


int lightV = 0;
int temperatureV = 0;
int humidityV = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
 
  // configure wifi network
  thing.add_wifi(SSID, SSID_PASSWORD);

  delay(5);    // The CCS811 wants a brief delay after startup.
      Serial.begin(115200);
      Wire.begin();
      
      // APDS9301 (light sensor) sensor setup.
      apds.begin(0x39);  // We're assuming you haven't changed the I2C
                         //  address from the default by soldering the
                         //  jumper on the back of the board.
      apds.setGain(APDS9301::LOW_GAIN); // Set the gain to low. Strictly
                         //  speaking, this isn't necessary, as the gain
                         //  defaults to low.
      apds.setIntegrationTime(APDS9301::INT_TIME_13_7_MS); // Set the
                         //  integration time to the shortest interval.
                         //  Again, not strictly necessary, as this is
                         //  the default.
      apds.setLowThreshold(0); // Sets the low threshold to 0, effectively
                         //  disabling the low side interrupt.
      apds.setHighThreshold(50); // Sets the high threshold to 50. This
                         //  is an arbitrary number we pulled out of thin
                         //  air for purposes of the example. When the CH0
                         //  reading exceeds this level, an interrupt will
                         //  be issued on the INT pin.
      apds.setCyclesForInterrupt(1); // A single reading in the threshold
                         //  range will cause an interrupt to trigger.
      apds.enableInterrupt(APDS9301::INT_ON); // Enable the interrupt.
      apds.clearIntFlag();

      // Interrupt setup
      pinMode(INT_PIN, INPUT_PULLUP); // This pin must be a pullup or have
                         //  a pullup resistor on it as the interrupt is a
                         //  negative going open-collector type output.
      attachInterrupt(digitalPinToInterrupt(10), lightInt, FALLING);
      Serial.println(apds.getLowThreshold());
      Serial.println(apds.getHighThreshold());


  thing["light"] >> outputValue(lightV);
  thing["temperature"] >> outputValue(temperatureV);
  thing["humidity"] >> outputValue(humidityV);
  
}

void loop() {
  thing.handle();

static unsigned long outLoopTimer = 0;
      apds.clearIntFlag();                          

      // This is a timer that calculates and prints the current lux reading each second.
      if (millis() - outLoopTimer >= 5000)
      {
        outLoopTimer = millis(); // "reset" the timer
    
        Serial.print("Luminous flux: ");
        Serial.print(apds.readCH0Level(),6); //return the value of light
        Serial.println(" lux");
        lightV = apds.readCH0Level();
        
        delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println("C");
    temperatureV = event.temperature;
    
  dht.humidity().getEvent(&event);
  
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println("%");
    humidityV = event.relative_humidity;
    Serial.println("  ");
        if (lightIntHappened)
        {
          Serial.println("Interrupt");
          lightIntHappened = false;
        }
      }
    }
    
    void lightInt() //Interupt the programm to return the value, then reboot the pro
    {
      lightIntHappened = true;
    }