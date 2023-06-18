#define BLYNK_TEMPLATE_ID "TMPLv7DXRjFu"
#define BLYNK_DEVICE_NAME "Micro"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
int flame_sensor = D6;
#include <DHT.h>;

//Constants
#define DHTPIN D2        //what pin we're connected to
#define DHTTYPE DHT21       //DHT 21  (AM2301)
DHT dht(DHTPIN, DHTTYPE);   //Initialize DHT sensor for normal 16mhz Arduino


//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value


// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
BLYNK_WRITE(V0)
{
int pinvalue=param.asInt();
digitalWrite(D0,pinvalue);
}
BLYNK_WRITE(V1)
{
int pinvalue=param.asInt();
digitalWrite(D1,!pinvalue);
}


void setup()
{
  Serial.begin(115200);
   pinMode(flame_sensor, INPUT);
   pinMode(D0,OUTPUT);
    pinMode(D1,OUTPUT);

   dht.begin();
  delay(100);

  BlynkEdgent.begin();
}

void loop() {                     
  BlynkEdgent.run();
    hum = dht.readHumidity();
  temp= dht.readTemperature();
  
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%,  Temperature: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  
  delay(2000); //Delay 2 sec.
  Blynk.virtualWrite(V2, hum);
  Blynk.virtualWrite(V3, temp);
int    flame_detected = digitalRead(flame_sensor);
  if (!flame_detected){
    Blynk.logEvent("warning", "fire detected!") ;}

}
