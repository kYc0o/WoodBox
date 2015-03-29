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
#define LOW_POLUTION 75
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
int colorSoleil[4][3] = {{10,10,7},{104,107,53},{197,201,103},{248,252,125}};

// Global variables for sensors
int qualiteAir =-1;
float temperature = 0;
float humidite = 0;
int luminosite = 0;

// Data count
int count = 0;

// Incoming data for actions
int incomingByte;
int hum = H_VERY_LOW;
int pol = VERY_POLUTED;
int iaq = IAQ_VERY_BAD;
int lux = L_VERY_LOW;


void setup() 
{
  // Serial output at 9600 baud
  Serial.begin(9600);

  //LEDS
  leds.init();
  leds.setColorRGB(0, 0, 0, 0);
  delay(100);
  leds.setColorRGB(1, 0, 0, 0);
  delay(100);
  leds.setColorRGB(2, 0, 0, 0);
  delay(100);
  leds.setColorRGB(3, 0, 0, 0);
  delay(100);
  leds.setColorRGB(4, 0, 0, 0);
  // Initialize dht sensor
  dht.begin();
  airqualitysensor.init(14);
  incomingByte = T_VERY_LOW;
}



void loop()
{
  // attente active
  delay(3000);
  temperature = dht.readTemperature();
  humidite = dht.readHumidity();
  luminosite = analogRead(LUX_PIN);
  qualiteAir = airqualitysensor.slope();
  
  //if (Serial.available() > 0) {
    // read the incoming byte:
    //incomingByte = Serial.read();
    //Serial.println(incomingByte);
          
    for (int i = 0; i < 6; i++) {
      
      if (temperature < 16)
        incomingByte = T_VERY_LOW;
        
      if (temperature > 16 && temperature < 21)
        incomingByte = T_LOW;
        
      if (temperature > 21 && temperature < 27)
        incomingByte = T_NORMAL;
        
      if (temperature > 27)
        incomingByte = T_HIGH;
        
      if (qualiteAir == 0)
        pol = VERY_POLUTED;
        
      if (qualiteAir == 1)
        pol = POLUTED;
        
      if (qualiteAir == 2)
        pol = LOW_POLUTION;
        
      if (qualiteAir == 3)
        pol = NO_POLUTION;
      
    if (luminosite < 200)
      lux = L_VERY_LOW;
      
    if (luminosite > 400 && luminosite < 600)
      lux = L_LOW;
      
    if (luminosite > 600 && luminosite < 800)
      lux = L_NORMAL;
      
    if (luminosite > 800)
      lux = L_HIGH;
      
      
    if (humidite < 40)
      hum = H_VERY_LOW;
      
    if (humidite > 50 && humidite < 60)
      hum = H_LOW;
      
    if (humidite > 60 && humidite < 80)
      hum = H_NORMAL;
      
    if (humidite > 80)
      hum = H_HIGH;     
    
    switch (incomingByte)
    {
      // Temperature less than 16 degrees celsius
      case T_VERY_LOW:
      leds.setColorRGB(0, colorMaison[0][0], colorMaison[0][1], colorMaison[0][2]);
      break;
      
      case T_LOW:
      leds.setColorRGB(0, colorMaison[1][0], colorMaison[1][1], colorMaison[1][2]);
      break;
      
      case T_NORMAL:
      leds.setColorRGB(0, colorMaison[2][0], colorMaison[2][1], colorMaison[2][2]);
      break;
      
      case T_HIGH:
      leds.setColorRGB(0, colorMaison[3][0], colorMaison[3][1], colorMaison[3][2]);
      break;
    }
    
    switch(hum)
    {      
      case H_VERY_LOW:
      leds.setColorRGB(2, colorNuage[0][0], colorNuage[0][1], colorNuage[0][2]);
      break;
      
      case H_LOW:
      leds.setColorRGB(2, colorNuage[1][0], colorNuage[1][1], colorNuage[1][2]);
      break;
      
      case H_NORMAL:
      leds.setColorRGB(2, colorNuage[2][0], colorNuage[2][1], colorNuage[2][2]);
      break;
      
      case H_HIGH:
      leds.setColorRGB(2, colorNuage[3][0], colorNuage[3][1], colorNuage[3][2]);
      break;
    }
    
    switch(pol)
    {      
      case VERY_POLUTED:
      leds.setColorRGB(1, colorUsine[0][0], colorUsine[0][1], colorUsine[0][2]);
      break;
      
      case POLUTED:
      leds.setColorRGB(1, colorUsine[1][0], colorUsine[1][1], colorUsine[1][2]);
      break;
      
      case LOW_POLUTION:
      leds.setColorRGB(1, colorUsine[2][0], colorUsine[2][1], colorUsine[2][2]);
      break;
      
      case NO_POLUTION:
      leds.setColorRGB(1, colorUsine[3][0], colorUsine[3][1], colorUsine[3][2]);
      break;
    }
    
    switch(iaq)
    {      
      case IAQ_VERY_BAD:
      leds.setColorRGB(3, colorMan[0][0], colorMan[0][1], colorMan[0][2]);
      break;
      
      case IAQ_BAD:
      leds.setColorRGB(3, colorMan[1][0], colorMan[1][1], colorMan[1][2]);
      break;
      
      case IAQ_GOOD:
      leds.setColorRGB(3, colorMan[2][0], colorMan[2][1], colorMan[2][2]);
      break;
      
      case IAQ_VERY_GOOD:
      leds.setColorRGB(3, colorMan[3][0], colorMan[3][1], colorMan[3][2]);
      break;
    }
    
    switch (lux)
    {      
      case L_VERY_LOW:
      leds.setColorRGB(4, colorSoleil[0][0], colorSoleil[0][1], colorSoleil[0][2]);
      break;
      
      case L_LOW:
      leds.setColorRGB(4, colorSoleil[1][0], colorSoleil[1][1], colorSoleil[1][2]);
      break;
      
      case L_NORMAL:
      leds.setColorRGB(4, colorSoleil[2][0], colorSoleil[2][1], colorSoleil[2][2]);
      break;
      
      case L_HIGH:
      leds.setColorRGB(4, colorSoleil[3][0], colorSoleil[3][1], colorSoleil[3][2]);
      break;
    }
      
     /* case VENTILATION_ON:
      break;
      
      case VENTILATION_OFF:
      break;
      
      case HEATER_ON:
      break;
      
      case HEATER_OFF:
      break;

      default:
      break;*/
    }
    
  printInfo(temperature, humidite, luminosite, qualiteAir);
  count ++;
  incomingByte++;
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
 //Serial.println("{");
 
 /*Serial.print("\"count\" : ");
 Serial.print(count);
 Serial.println(",");*/

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

 Serial.println("}]");
 Serial.println("[");  
}
