#include <ChainableLED.h>

#include "DHT.h"
#include"AirQuality.h"
#include"Arduino.h"

// DHT
#define DHTPIN 8      // Digital pin for DHT sensor
#define DHTTYPE DHT11  // DHT 11 sensor type
#define LUX_PIN A3    // Analog pin for luminosity sensor
#define AIR_PIN A0    // Analog pin for air quality sensor

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// Air quality sensor object
AirQuality airqualitysensor;

// Global variables for sensors
int qualiteAir =-1;
float temperature = 0;
float humidite = 0;
int luminosite = 0;

// Data count
int count = 0;

// Incoming data for actions
int incomingByte;


void setup() 
{
  // Serial output at 9600 baud
  Serial.begin(9600);
  // Initialize dht sensor
  dht.begin();
  airqualitysensor.init(14);  
}



void loop()
{
  
    delay(3000);

  
  temperature = dht.readTemperature();
  humidite = dht.readHumidity();
  luminosite = analogRead(LUX_PIN);
  qualiteAir = airqualitysensor.slope();      

   if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();



                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }
   printInfo(temperature, humidite, luminosite, qualiteAir);

   count ++;

}



ISR(TIMER2_OVF_vect)
{
    
	if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
	{
			airqualitysensor.last_vol=airqualitysensor.first_vol;
			airqualitysensor.first_vol=analogRead(AIR_PIN);
			airqualitysensor.counter=0;
			airqualitysensor.timer_index=1;
			PORTB=PORTB^0x20;
	}
	else
	{
		airqualitysensor.counter++;
	}
}


void printInfo(float temp, float hum, int lux, int air){
 Serial.println("{");
 
 Serial.print("\"count\" : ");
 Serial.print(count);
 Serial.println(",");

 Serial.print("\"temp\" : ");
 Serial.print(temp);
 Serial.println(",");
 
 Serial.print("\"hum\" : ");
 Serial.print(hum);
 Serial.println(",");
 
 Serial.print("\"lux\" : ");
 Serial.print(lux);
 Serial.println(",");
 
 Serial.print("\"air\" : ");
 Serial.println(air);

 Serial.println("}");
  
}
