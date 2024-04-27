#include <SPI.h>
#include <Ethernet.h>

// Pin assignments for Arduino Uno in Proteus
const int ENC_CS_PIN = 10;   // Chip select pin for ENC28J60
const int ENC_SI_PIN = 11;   // SPI data input pin (MOSI)
const int ENC_SO_PIN = 12;   // SPI data output pin (MISO)
const int ENC_SCK_PIN = 13;  // SPI clock pin
const int ENC_RST_PIN = 9;   // Reset pin for ENC28J60

// MAC address for the ENC28J60 module
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IP address settings
IPAddress ip(192, 168, 1, 100);    // IP address for the Arduino
IPAddress gateway(192, 168, 1, 1); // Gateway IP address
IPAddress subnet(255, 255, 255, 0);// Subnet mask

// Initialize the Ethernet client library
EthernetClient client;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize Ethernet using ENC28J60 module
  Ethernet.begin(mac, ip, gateway, subnet);
  
  // Wait for Ethernet to be ready
  delay(1000);

  // Print local IP address
  Serial.print("Local IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Check if client is connected
  if (client.connected()) {
    // Make a HTTP request
    client.println("GET / HTTP/1.1");
    client.println("Host: localhost");
    client.println("Connection: close");
    client.println();
    
    // Wait for server response
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    
    // Close connection
    client.stop();
  } else {
    // If not connected, attempt to connect to server
    if (client.connect("127.0.0.1", 80)) { // Change IP address to your server's IP
      Serial.println("Connected to server");
    } else {
      Serial.println("Connection failed");
    }
  }

  // Wait before making another request
  delay(5000);
}