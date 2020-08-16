#include <ESP8266WiFi.h>

const char* ssid = "goMap24";
const char* password = "goMap@#1688";
WiFiClient client;
byte mac[6];                     // the MAC address of your Wifi shield


// address of the server machine e.g Xamp server with database
char server[] = "192.168.1.8"; // address of the computer running server running/hosting database
//char server[] = "gomap.tech"; // address of the computer running server running/hosting database

byte statusLed    = 13;

byte sensorInterrupt = 13;  // 0 = digital pin 2
byte sensorPin       = 13;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 6.2; // 7.5 is giving correct result with Sea water flow meter. (4.5 ia also value)

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long lastreading;
String macaddress; 
unsigned long oldTime;
String data;



void setup()
{
  
  // Initialize a serial connection for reporting values to the host
  Serial.begin(115200);
  connect2Wifi(); 
  
  // Set up the status LED line as an output
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
 
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  Serial.println("Setup Called");
  lastreading=0;
  macaddress=Get_Mac_Address();
  Serial.print("MAC ADDRESS-     ");
  Serial.println(macaddress);
}

/**
 * Main program loop
 */
void loop()
{   
    GetMeterReading();
    if (totalMilliLitres!=lastreading)
    {
      Send_Data_To_Server();
    } 
    lastreading=totalMilliLitres;
    delay(2000); // interval
}

/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}

//  Declare Function to setip WiFi Connection
void connect2Wifi()
{
   // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}



//  Calculate Water Meter Reading  
void GetMeterReading()
{
   if((millis() - oldTime) > 1000)    // Only process counters once per second
   { 
    detachInterrupt(sensorInterrupt);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
      
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
    Serial.print("\t");       // Print tab space
    Serial.print(totalMilliLitres/1000);
    Serial.print("L");
     // Reset the pulse counter so we can start incrementing again
     pulseCount = 0;
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
   }
}


void Send_Data_To_Server()   //CONNECTING WITH MYSQL via XAMP server /phpmyadmin
 {
    // this function requires SendData2DB.php file in XAMP server C:\xampp\htdocs\watermeter
    // file SendData2DB.php file has php script to send data to Mysql database using GET command and SQL
    // Make a HTTP request:
    Serial.println("trying to send data");
   // data = "totalvol=" + String(totalMilliLitres) + "&macIdval=" + macaddress;
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Serial.print("GET /watermeter/SendData2DB.php?totalvol=");
      client.print("GET /watermeter/SendData2DB.php?totalvol=");     //YOUR URL
      client.print(totalMilliLitres);
      client.print("&macIdval=");
      client.print(macaddress);
      client.print("&lastArdReading=");
      client.print(lastreading);
      client.print(" ");                //SPACE BEFORE HTTP/1.1
      client.print("HTTP/1.1");
        client.println();
        client.println("Host: 192.168.1.8");  //IP address host
      //client.println("Host: gomap.tech");  //IP address host
      //client.print("Host: ");
     // client.println(server);
     // client.println("Content-Type: application/x-www-form-urlencoded"); 
      //client.print("Content-Length: "); 
      //client.println(data.length()); 
      //Serial.println(data.length());
     // client.println();
     // client.print(data); 
      //Serial.println("Still Connected");
      client.println("Connection: close");
      client.println();
      
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }  
 }

 String Get_Mac_Address()
 {
  WiFi.macAddress(mac);
  String macadd=mac2String(mac);
  //macaddress=string(mac[0])+(mac[1])+(mac[2]);
  //Serial.println(macaddress);
  macadd.replace(" ","0");
  //Serial.println("New MAc Address");
//  Serial.println(macaddress);
//  Serial.print("MAC: ");
//  Serial.print(mac[0],HEX);
//  Serial.print(":");
//  Serial.print(mac[1],HEX);
//  Serial.print(":");
//  Serial.print(mac[2],HEX);
//  Serial.print(":");
//  Serial.print(mac[3],HEX);
//  Serial.print(":");
//  Serial.print(mac[4],HEX);
//  Serial.print(":");
//  Serial.println(mac[5],HEX);
  return macadd;
  }

String mac2String(byte ar[])
{
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    sprintf(buf, "%2X", ar[i]);
    s += buf;
    if (i < 5) s += ':';
  }
  return s;
}
