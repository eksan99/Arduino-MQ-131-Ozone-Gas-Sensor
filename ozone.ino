#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MQ131.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  Serial.begin(115200);
  display.clearDisplay();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    }
//MQ131 
   MQ131.begin(2,A0, LOW_CONCENTRATION, 1000000);
   Serial.println("Calibration in progress...");
   MQ131.calibrate();
   Serial.println("Calibration done!");
   Serial.print("R0 = ");
   Serial.print(MQ131.getR0());
   Serial.println(" Ohms");
   Serial.print("Time to heat = ");
   Serial.print(MQ131.getTimeToRead());
   Serial.println(" s");
  
}
  
void loop() {
  
  Serial.println("Sampling...");
  MQ131.sample();
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(UG_M3));
  Serial.println(" ug/m3");
  //Display
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
  // Display static text
  display.print("Ozone: ");
  display.print(MQ131.getO3(UG_M3));
  display.println("  ug/m3");
  display.display(); 
  delay(10000);

}



 

