#include <DHT.h>
#include<Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25
#define Type DHT11
SoftwareSerial mySerial(10, 11);
void ReadBMP(void);
void ReadDHT(void);
void ReadRain(void);
void send_data(void);
int sensePin = 9;
DHT HT(sensePin,Type);
float humidity;
Adafruit_BMP085 bmp;

void setup(){
  mySerial.begin(115200);
  Serial.begin(9600);
  HT.begin();
  delay(2000);
}

void loop(){
  ReadRain();
  ReadDHT();
  ReadBMP();
  send_data();
}

void ReadDHT(void)
{
  humidity = HT.readHumidity();
  
  Serial.print("Humidity: ");
  Serial.println(humidity);
  delay(2000);
}

void ReadRain(void)
{
  int sensorValue = analogRead(A1);
  // print out the value you read:
  Serial.println(sensorValue);
  if (sensorValue<900&&sensorValue>600)
  {
      Serial.println("it is Drizzling!");
      
   }
   else if(sensorValue<600 && sensorValue>300)
   {
      Serial.println("It is Raining!");
   }
   else if(sensorValue<300)
   {
      Serial.println("It is Raining heavily!");
   }
   else
   {  
      Serial.println("it is not Raining");
       
   }
   delay(2000);
}

void ReadBMP(void)
{
 
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  else
  {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    Serial.println(" meters");
    
    Serial.println();
    delay(500);
  }
  delay(2000);
}

void send_data()
{
  if(mySerial.isListening()){
  mySerial.print('*'); // Starting char
  mySerial.print(bmp.readTemperature(), 0); //2 digit data
  mySerial.print(HT.readHumidity(), 0); //2 digit data
//  mySerial.print(myBMP.getPressure()); //5 digit data
//  mySerial.print(bmp.readAltitude(seaLevelPressure_hPa * 100) * 100); //5 digit data
//  mySerial.print(analogRead(A1)); //4 digit data
  mySerial.print('#'); // Ending char
  }
  else{
    Serial.print("no");
  }
}
