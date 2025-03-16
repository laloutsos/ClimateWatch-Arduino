//www.elegoo.com
//2023.05.05
#include <Wire.h>
#include <DS3231.h>
#include "IRremote.h"
#include <dht_nonblocking.h>
#include <LiquidCrystal.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define RED 13
#define BLUE 6

DS3231 clock;
RTCDateTime dt;

float tempC ;
float temperature;
float humidity;

int receiver = 2; // Signal Pin of IR receiver to Arduino Digital Pin 2

static const int DHT_SENSOR_PIN = 4;

DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

int tempPin = 0;
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
// Variable used to store the last decodedRawData
uint32_t last_decodedRawData = 0;

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
{
  // Check if it is a repeat IR code 
  if (irrecv.decodedIRData.flags)
  {
    // Set the current decodedRawData to the last decodedRawData 
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    lcd.setCursor(0, 0);
    lcd.print("REPEAT!");
  } else
  {
    // Output the IR code on the LCD
    lcd.setCursor(0, 0);
    lcd.print("IR c0de:0x");
   // lcd.setCursor(0, 1);
    //lcd.print(irrecv.decodedIRData.decodedRawData, HEX);
  }
  
  // Map the IR code to the remote key
  switch (irrecv.decodedIRData.decodedRawData)
  {
    case 0xF807FF00:lcd.setCursor(0, 0); lcd.print("HUMIDITY:2     "); lcd.setCursor(0, 1); lcd.print("R00M TEMP:3     "); break;
    
    case 0xF609FF00: lcd.setCursor(0, 0); lcd.print("DATE AND TIME:0 "); lcd.setCursor(0, 1); lcd.print("THERMIST0R T:1   "); break;
    
    case 0xE619FF00: lcd.setCursor(0, 0); lcd.print("   UP    D0WN   "); lcd.setCursor(0, 1); lcd.print("L0CK SCREEN:P0W "); break;
    
    case 0xBA45FF00:  lcd.setCursor(0, 0); lcd.print(" CLIMATE WATCH  ");  lcd.setCursor(0, 1); lcd.print(" MENU :PRESS EQ "); break;
    
    case 0xF30CFF00: lcd.setCursor(0, 0); lcd.print("THERMIST0R TEMP "); lcd.setCursor(0, 1); lcd.print(tempC); lcd.setCursor(5, 1); lcd.print("  Celcius  ");  break;
    
    case 0xE718FF00: lcd.setCursor(0, 0); lcd.print("    HUMIDITY    ");lcd.setCursor(0, 1);lcd.print("     "); lcd.setCursor(5, 1); lcd.print(humidity); lcd.setCursor(10, 1); lcd.print("%     ");  break;

    case 0xA15EFF00: lcd.setCursor(0, 0); lcd.print("R00M TEMPERATURE"); lcd.setCursor(0, 1); lcd.print(temperature); lcd.setCursor(5, 1); lcd.print("   Celcius ");  break;

    case 0xE916FF00: lcd.setCursor(0, 0); lcd.print(" DATE AND TIME  ");  lcd.setCursor(0, 1); lcd.print(dt.year);  lcd.setCursor(4, 1); lcd.print("-"); lcd.setCursor(5, 1); lcd.print(dt.day);  
     
    lcd.setCursor(6 , 1); lcd.print("-"); lcd.setCursor(7, 1);  lcd.print(dt.month); lcd.setCursor(8, 1); lcd.print("  ");lcd.setCursor(10, 1); lcd.print(dt.hour); 
    
    lcd.setCursor(12 , 1); lcd.print(":"); lcd.setCursor(13, 1); lcd.print(dt.minute); lcd.setCursor(15, 1); lcd.print(" "); 
  } // End Case

  // Store the last decodedRawData
  last_decodedRawData = irrecv.decodedIRData.decodedRawData;
  delay(500); // Do not get immediate repeat
} // END translateIR
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); lcd.print(" CLIMATE WATCH  ");  lcd.setCursor(0, 1); lcd.print(" MENU :PRESS EQ "); 
  irrecv.enableIRIn(); // Start the receiver
} /*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  dt = clock.getDateTime();
  measure_environment( &temperature, &humidity );
  int tempReading = analogRead(tempPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  if (irrecv.decode()) // Have we received an IR signal?
  {
   
    translateIR();
    irrecv.resume(); // Receive the next value
  }
  if (tempC > 45) {
                digitalWrite(RED, HIGH);
                digitalWrite(BLUE, LOW);
                
    } else {
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, HIGH);
       
    }
} /* --(end main loop )-- */
