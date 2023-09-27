/**************************************************************************
   Tests the getTemperature and getHumidity functions of the aht20 library
 **************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

void setup() {
  Serial.begin(115200);
  Serial.println("Humidity AHT20 examples");

  Wire.begin();  //Join I2C bus
  //Check if the AHT20 will acknowledge
  if (aht20.begin() == false) {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1)
      ;
  }
  Serial.println("AHT20 acknowledged.");

  Serial.println("128x64 OLED FeatherWing test");
  delay(250);                 // wait for the OLED to power up
  display.begin(0x3C, true);  // Address 0x3C default

  Serial.println("OLED begun");
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Connecting to AHT-20':");
  display.println("connected!");
  display.println("Getting temp...");
  display.println("Getting humidity...");
  display.display();  // actually display all of the above
}

void loop() {



  if (aht20.available() == true) {
    //Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.print("% RH");

    Serial.println();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("\n");
    display.print("\n");
    display.print("Temperature: ");
    display.print(int(temperature));
    display.print("C");
    display.print("\n");
    display.print("\n");
    display.println("Relative");
    display.print("Humidity: ");
    display.print(int(humidity));
    display.print("%");
    display.print("\n");
    yield();
    display.display();
  }

  //The AHT20 can respond with a reading every ~50ms. However, increased read time can cause the IC to heat around 1.0C above ambient.
  //The datasheet recommends reading every 2 seconds.
  delay(2000);
}