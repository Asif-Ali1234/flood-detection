#include "DHT.h"      // download dhtlib from Manage Libraries and include in into this
#define DHTTYPE DHT11
#include <SPI.h>
#include <Wire.h>  //Download Adafruit ssd1306 library and also its dependencies from arduino
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define dht_data_pin D2 // connect data pin of DHT to D2 pin

#define buzzer_pin D1 // connect input pin to D0 of nodemcu

Adafruit_SSD1306 display(-1);

const char* ssid = "***************";
const char* password = "************";

unsigned long channel_number = *************;
const char* writeapikey = "*********************";

WiFiClient client;

DHT dht(dht_data_pin,DHTTYPE);

const int trigP = D5;  
const int echoP = D6;  

long duration;
int water_level;
int msgval;

void display_data(float h,float t,int w){
  display.clearDisplay();
  delay(1000);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Humidity : ");
  display.print(h);
  display.setCursor(1,0);
  display.println("Temperature : ");
  display.print(t);
  display.setCursor(2,0);
  display.println("Water Level : ");
  display.print(w);
  delay(1000);
}

void setup() {
  //Initializing OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  //Initializing Ultrasonic sensor
  pinMode(trigP, OUTPUT);
  pinMode(echoP, INPUT); 

  //Initializing DHT sensor
  dht.begin();
  delay(700);

  //Initializing Buzzer
  pinMode(buzzer_pin,OUTPUT);
  Serial.begin(115200);
  connect_to_wifi();
  ThingSpeak.begin(client);
}

void loop() {

  //start the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  delay(1000);
  digitalWrite(trigP, LOW);
  delayMicroseconds(2);

  digitalWrite(trigP, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigP, LOW);

  duration = pulseIn(echoP, HIGH);
  water_level= duration*0.034/2;
  Serial.println("Humidity is :");
  Serial.print(humidity);
  Serial.println("Temperature is :");
  Serial.print(temperature);
  Serial.println("Water level is :");
  Serial.print(water_level);
  display_data(humidity,temperature,water_level);
  if(water_level < 5 && humidity < 30 && temperature < 25){
    digitalWrite(buzzer_pin,LOW);
    msgval = 2;
    Serial.println("Flood Alert");
  }
  else if(water_level < 5 && humidity > 30 && temperature > 25){
    digitalWrite(buzzer_pin,LOW);//buzzer is on
    msgval = 4;
    Serial.println("Water is high but humidity and temperature is constant");
  }
  else if(water_level > 90 && humidity > 30 && temperature > 25){
    digitalWrite(buzzer_pin,LOW);
    msgval = 3;
    Serial.println("Water level is very low ");
  }
  else if(humidity < 30 && temperature < 25 && water_level > 90 && water_level < 5){
    msgval = 5;
    Serial.println("Temperature and humidity are low but water level is constant");
  }
  else{
    digitalWrite(buzzer_pin,HIGH);//buzzer is off
    msgval = 1;
    Serial.println("Everything looks safe");
  } 
  upload_to_cloud(humidity,temperature,water_level,msgval);
}

void connect_to_wifi(){
  delay(2000);
  Serial.print("Connecting to ");Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected , IP Address: ");
  Serial.println(WiFi.localIP());
}

void upload_to_cloud(float h,float t,int w,int val){
  ThingSpeak.setField(1,h);
  ThingSpeak.setField(2,t);
  ThingSpeak.setField(3,w);
  ThingSpeak.setField(4,val);
  ThingSpeak.writeFields(channel_number,writeapikey);
}
