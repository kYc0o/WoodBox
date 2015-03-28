
/* 
 * Example of using the ChainableRGB library for controlling a Grove RGB.
 * This code puts a red dot (led) moving along a strip of blue dots.
 */

#include <ChainableLED.h>

#define NUM_LEDS  5


ChainableLED leds(4, 5, NUM_LEDS);

int colorMaison[4][3] = {{0,0,255},{245,238,10},{255,146,3},{255,0,0}};
int colorUsine[4][3] = {{131,165,30},{246,255,3},{51,216,26},{0,0,255}};
int colorNuage[4][3] = {{255,0,0},{246,255,3},{130,130,255},{51,216,26}};
int colorMan[4][3] = {{131,165,30},{246,255,3},{51,216,26},{0,0,255}};
int colorSoleil[4][3] = {{110,110,7},{154,157,63},{197,201,103},{248,252,125}};






void setup()
{
  leds.init();
}

byte pos = 0;

void loop()
{
int i = 0;

  for(i=0 ; i< 4 ; i++){
      leds.setColorRGB(0, colorMaison[i][0], colorMaison[i][1], colorMaison[i][2]);  
      leds.setColorRGB(1, colorUsine[i][0], colorUsine[i][1], colorUsine[i][2]); 
      leds.setColorRGB(2, colorNuage[i][0], colorNuage[i][1], colorNuage[i][2]); 
      leds.setColorRGB(3, colorMan[i][0], colorMan[i][1], colorMan[i][2]); 
      leds.setColorRGB(4, colorSoleil[i][0], colorSoleil[i][1], colorSoleil[i][2]); 
      
  delay(1000);
}

delay(3000);
}
