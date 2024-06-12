# Arduino-MQ-131-Ozone-Gas-Sensor

This is Arduino library to detect ozone concentration in the air with the MQ-131 sensor. The library supports low concentration, the calibration, the control of the heater, and the output of values in µg/m3.

## Library
Go to the Library manager of the Arduino IDE and install the library "MQ131 gas sensor" by Olivier Staquet.

## Wiring
![image](https://github.com/eksan99/Arduino-MQ-131-Ozone-Gas-Sensor/assets/156219322/45273eb2-8cd6-418d-8237-2dd4021e8ce9)

## Code
```
#include <MQ131.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(1000);
  display.clearDisplay();
  
  MQ131.begin(2,A0, LOW_CONCENTRATION, 1000); 
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
  delay(1000);
  Serial.print("Concentration Ozone : ");
  Serial.print(MQ131.getO3(UG_M3));
  Serial.println(" ug/m3");
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(0, 0);
  display.print("Ozone: ");
  display.print(MQ131.getO3(UG_M3));
  display.print("  ug/m3");
  display.display(); 

  delay(2000);
}
```
## Output and Display


