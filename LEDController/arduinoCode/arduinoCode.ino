/*
  LED Controller

 This sketch connects to a a web server and makes request values to 
 control an LED using a WiFi equipped Arduino board
 
 by Nurudeen Agbonoga

 connections
  A0 --> Red LED
  A1 --> Green LED
  A2 --> Blue LED
 */

#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
// LED pins
int red = A0;
int green = A1;
int blue = A2;
int valueR;
int valueG;
int valueB;
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// server address:
//char server[] = "192.168.1.177";
IPAddress server(192,168,1,4);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1L * 1000L; // delay between updates, in milliseconds

void setup() {
  //set up analog pin modes
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status and turn on LED's
  printWifiStatus();
  analogWrite(red,50);
  analogWrite(green,50);
  analogWrite(blue,50);
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  /*while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }*/

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the Nina module
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 5000)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    //client.println("GET /arduino/Something");
    String json = "{\"action\":\"0\"}";

    // Build the request
    String request = "POST / HTTP/1.1\r\n";
    request += "Content-Type: application/json\r\n";
    request += "Content-Length: " + String(json.length()) + "\r\n";
    request += "\r\n";
    request += json;
    
    client.println(request);
    //client.println("Connection: close");
    client.println();

    // Wait for the server response
    while (!client.available()) {
      // Wait until data is available
      delay(4);
    }
    
    String responseString; // should only contain RGB values
    boolean responseStarted = false;
    while (client.available()) {
      char c = client.read();
      if (responseStarted)
        responseString += c;
      if (c == '*')
        responseStarted = true;
    }

    Serial.println("Response: ");
    Serial.println(responseString);
    Serial.println("******Response end");

    // note the time that the connection was made:
    lastConnectionTime = millis();
    // Convert hex code string to a long integer
    long hexValue = strtol(responseString.c_str(), NULL, 16);
    
    // Extract the individual color components (R, G, and B)
    if (responseString.length() == 6){
      valueR = (hexValue >> 16) & 0xFF;
      valueG = (hexValue >> 8) & 0xFF;
      valueB = hexValue & 0xFF;
      
      // Use the color values to drive the LEDs
      analogWrite(red, valueR);   
      analogWrite(green, valueG); 
      analogWrite(blue, valueB);
      }
    
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
