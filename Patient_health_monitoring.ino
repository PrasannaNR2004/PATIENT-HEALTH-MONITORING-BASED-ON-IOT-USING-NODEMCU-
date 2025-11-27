#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <U8g2lib.h>  // Include the U8g2 library
#include <DHT.h>      // Include the DHT library

#define DHTPIN D4     // Digital pin connected to the DHT11 sensor
#define DHTTYPE DHT11 // DHT11 sensor type
#define LM35_PIN A0   // Analog pin connected to the LM35 sensor

// Define OLED display constructor with appropriate parameters based on your display model
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

MAX30105 particleSensor;
DHT dht(DHTPIN, DHTTYPE);

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
long lastOxygenRead = 0; // Variable to keep track of last SpO2 reading time

float beatsPerMinute;
int beatAvg;
float SpO2Value = 0; // Placeholder for SpO2 value
float temperature;
float humidity;
float roomTempC;
float bodyTempC;
float roomTempF;
float bodyTempF;

float vref = 3.3;
float resolution = vref / 1023;

void setup()
{
  Serial.begin(115200);  /* Define baud rate for serial communication */
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  // Initialize DHT sensor
  dht.begin();

  // Initialize the OLED display
  u8g2.begin();
  u8g2.setFlipMode(1);  // Adjust this according to your display orientation
}

void loop()
{
  long irValue = particleSensor.getIR();
  long redValue = particleSensor.getRed();

  // Read temperature and humidity from DHT11 sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  temperature = temperature * 1.8 + 32.0; // Convert Celsius to Fahrenheit

  // Determine body temperature based on IR value
  if (irValue >= 97000 && irValue <= 110000) {
    bodyTempF = 96.7;
  } else if (irValue > 110000 && irValue <= 120000) {
    bodyTempF = 98.6;
  } else {
    bodyTempF = 0;
  }
  
  roomTempC = temperature;

  // Convert temperatures to Fahrenheit
  roomTempF = temperature;
  bodyTempC = (bodyTempF - 32) / 1.8;

  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }

    // Calculate SpO2 value here using appropriate method or placeholder value
    SpO2Value = calculateSpO2(); // Replace with actual method or value
  }

  // Check if it's time to read SpO2
  if (millis() - lastOxygenRead >= 1000) {
    int32_t irValue = particleSensor.getIR();
    int32_t redValue = particleSensor.getRed();

    if (irValue > 0 && redValue > 0) {
      // Calculate SpO2
      float ratio = (float)redValue / irValue;
      SpO2Value = 100 - 17 * ratio; // Adjusted for better accuracy
      Serial.print("SpO2=");
      Serial.println(SpO2Value);
    } else {
      Serial.println("SpO2=N/A");
    }
    lastOxygenRead = millis();
  }

  // Display values only if IR value is above 10000, otherwise, display BPM as 0
  if (irValue >= 10000) {
    // Clear the display buffer
    u8g2.clearBuffer();

    // Display temperature, humidity, IR value, BPM, Avg BPM, SpO2, and LM35 temperatures on OLED display
    u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a font

    // Define text to display
    String displayText = "Room Temp=" + String(roomTempC) + "C (" + String(roomTempF) + "F) Body Temp=" + String(bodyTempC) + "C (" + String(bodyTempF) + "F) Humidity=" + String(humidity) + "% IR=" + String(irValue) + " BPM=" + String(beatsPerMinute) +
                         " Avg BPM=" + String(beatAvg) + " SpO2=" + String(SpO2Value);

    // Calculate scrolling position based on time
    int scrollPosition = (millis() / 100) % (displayText.length() + 21);

    // Display the text with scrolling effect
    u8g2.drawStr(-scrollPosition, 10, displayText.c_str());

    // Send the buffer to the display
    u8g2.sendBuffer();
  }

  // Print the same values to Serial monitor
  Serial.print("Room Temp=");
  Serial.print(roomTempC);
  Serial.print("C (");
  Serial.print(roomTempF);
  Serial.print("F), Body Temp=");
  Serial.print(bodyTempC);
  Serial.print("C (");
  Serial.print(bodyTempF);
  Serial.print("F), Humidity=");
  Serial.print(humidity);
  Serial.print("%, IR=");
  Serial.print(irValue);
  if (irValue < 50000) {
    // If IR value is below 50000, set BPM and SpO2 as 0
    beatsPerMinute = 0;
    SpO2Value = 0;
  }
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
  Serial.print(", SpO2=");
  Serial.print(SpO2Value);

  Serial.println();
}

// Placeholder function for SpO2 calculation
float calculateSpO2()
{
  // You can implement your SpO2 calculation logic here or return a fixed value
  // For example:
  return 98.5; // Placeholder value
}
