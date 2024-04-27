#include <Servo.h> // servo motor
#include <LiquidCrystal.h> // LCD display
#include <EtherCard.h>

// Static IP configuration
static byte myip[] = { 169, 254, 65, 30 }; // Arduino's static IP address
static byte gwip[] = { 169, 254, 65, 29 }; // Gateway IP address

// MAC address of the Arduino
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2d, 0x30, 0x31 };

#define REQUEST_RATE 5000 // milliseconds

// ethernet interface ip address
// static byte myip[] = { 192,168,1,203 };
// // gateway ip address
// static byte gwip[] = { 192,168,1,1 };
// remote website ip address and port
static byte hisip[] = { 127,0,0,1 };
// remote website name
const char website[] PROGMEM = "localhost:80";
static long timer;

// Ethernet buffer size
byte Ethernet::buffer[700];

const char welcomePage[] PROGMEM =
  "<!DOCTYPE html>"
  "<html lang='en'>"
  "<head>"
  "<meta charset='UTF-8'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "<title>Electronics Tree</title>"
  "<style>"
  "body {"
  "font-family: Arial, sans-serif;"
  "background-color: #f0f0f0;"
  "text-align: center;"
  "padding: 20px;"
  "}"
  "h1 {"
  "color: #333333;"
  "}"
  "p {"
  "color: #666666;"
  "}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Electronics Tree's Hands-On Journey</h1>"
  "<p>Welcome to Electronics Tree, where our name isn’t just a title—it’s a "
  "commitment to practical growth in your knowledge and skills."
  "Think of it like planting a seed.</p>"
  "</body>"
  "</html>";

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LCD pins

String RFid;
Servo myservo;

static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
  pinMode(8, OUTPUT); // GREEN LED
  Serial.println("Scan your RFid TAG");
  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.print("Scan your RFid");

  // Change 'SS' to your Slave Select pin, if you arn't using the default pin
  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println( "Failed to access Ethernet controller");

  ether.staticSetup(myip, gwip);

  ether.copyIp(ether.hisip, hisip);
  ether.printIp("Server: ", ether.hisip);

  while (ether.clientWaitingGw())
    ether.packetLoop(ether.packetReceive());
  Serial.println("Gateway found");
}

void loop() {
  word pos = ether.packetLoop(ether.packetReceive());
  if (pos) {
     // Extract data from Ethernet buffer
    char *data = (char *)Ethernet::buffer + pos;



    // Copy the welcome page content to the Ethernet buffer
    memcpy_P(ether.tcpOffset(), welcomePage, sizeof welcomePage);

    // Send HTTP response with the welcome page to the client
    ether.httpServerReply(sizeof welcomePage - 1);
  }

  while(Serial.available() > 0)
  {
    digitalWrite(8, LOW);
    RFid = Serial.readString();
    
    sendReq(RFid);

    lcd.clear(); // Clear the LCD display
    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("RFID: " + RFid); // Display RFID tag
  }
}

void sendReq(String rfid){

}

void onRecvRfid(char* data){
  if(data[0]==1)
  {
    lcd.setCursor(0, 1); // Set cursor to the second row
    Serial.println("Valid TAG, Access Allowed!");
    digitalWrite(8, HIGH);
    myservo.write(180);
    delay(3000); // door is open
    myservo.write(0);  
    digitalWrite(8, LOW);
    // print time of entrance
    lcd.print("Time: ");
    printTime();
  }
  else
  {
    lcd.setCursor(0, 1); // Set cursor to the second row
    lcd.print("Access Denied"); // Display access status
    Serial.println("Invalid TAG, Access Denied");
    delay(3000);        
    myservo.write(0); // door is closed ASAP
  }
}

void printTime() {
  unsigned long currentMillis = millis(); // Get the current time since Arduino started
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes % 60);
  lcd.print(":");
  lcd.print(seconds % 60);
}
