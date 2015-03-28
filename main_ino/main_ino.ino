#include <ChainableLED.h>
#include "DHT.h"
#include"AirQuality.h"
#include"Arduino.h"

// Chainable LED
#define NUM_LEDS  5

// Sensors
#define DHTPIN 8      // Digital pin for DHT sensor
#define DHTTYPE DHT11  // DHT 11 sensor type
#define LUX_PIN A3    // Analog pin for luminosity sensor
#define AIR_PIN A0    // Analog pin for air quality sensor

// Temperature defines
#define T_VERY_LOW 65
#define T_LOW 66
#define T_NORMAL 67
#define T_HIGH 68

// Humidity defines
#define H_VERY_LOW 69
#define H_LOW 70
#define H_NORMAL 71
#define H_HIGH 72

// Polution defines
#define VERY_POLUTED 73
#define POLUTED 74
#define LOW_PLUTION 75
#define NO_POLUTION 76

// Interior air quality defines
#define IAQ_VERY_BAD 77
#define IAQ_BAD 78
#define IAQ_GOOD 79
#define IAQ_VERY_GOOD 80

// Lumonisity
#define L_VERY_LOW 81
#define L_LOW 82
#define L_NORMAL 83
#define L_HIGH 84

// Ventilation
#define VENTILATION_ON 85
#define VENTILATION_OFF 86

// Heater
#define HEATER_ON 87
#define HEATER_OFF 88

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// Air quality sensor object
AirQuality airqualitysensor;

// Chainable LED config
ChainableLED leds(4, 5, NUM_LEDS);

// Global variables for colors
int colorMaison[4][3] = {{0,0,255},{245,238,10},{255,146,3},{255,0,0}};
int colorUsine[4][3] = {{131,165,30},{246,255,3},{51,216,26},{0,0,255}};
int colorNuage[4][3] = {{255,0,0},{246,255,3},{130,130,255},{51,216,26}};
int colorMan[4][3] = {{131,165,30},{246,255,3},{51,216,26},{0,0,255}};
int colorSoleil[4][3] = {{110,110,7},{154,157,63},{197,201,103},{248,252,125}};

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
  // attente active
  delay(3000);
  temperature = dht.readTemperature();
  humidite = dht.readHumidity();
  luminosite = analogRead(LUX_PIN);
  qualiteAir = airqualitysensor.slope();
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    
    switch (incomingByte)
    {
      // Temperature less than 16 degrees celsius
      case T_VERY_LOW:
      leds.setColorRGB(0, colorMaison[0][0], colorMaison[0][1], colorMaison[0][2]);
      break;
      
      case T_LOW;
      break;
      
      case T_NORMAL;
      break;
      
      case T_HIGH:
      break;
      
      case H_VERY_LOW:
      break;
      
      case H_LOW:
      break;
      
      case H_NORMAL:
      break;
      
      case H_HIGH:
      break;
      
      case VERY_POLUTED:
      break;
      
      case POLUTED:
      break;
      
      case LOW_PLUTION:
      break;
      
      case NO_POLUTION:
      break;
      
      case IAQ_VERY_BAD:
      break;
      
      case IAQ_BAD:
      break;
      
      case IAQ_GOOD:
      break;
      
      case IAQ_VERY_GOOD:
      break;
      
      case L_VERY_LOW:
      break;
      
      case L_LOW:
      break;
      
      case L_NORMAL:
      break;
      
      case L_HIGH:
      break;
      
      case VENTILATION_ON:
      break;
      
      case VENTILATION_OFF:
      break;
      
      case HEATER_ON:
      break;
      
      case HEATER_OFF:
      break;

      default:
      break;
      
    }
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
