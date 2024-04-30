#include <EtherCard.h>
#include <Servo.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

char c;
String RFid;
int count = 0;
Servo myservo;

static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

static byte myip[] = { 169,254,88,42 };

static byte gwip[] = {169,254,88,41 };

static byte hisip[] = { 169,254,88,41 };

const char website[] PROGMEM = "169.254.88.41";

byte Ethernet::buffer[700];


static void my_result_cb (byte status, word off, word len) {
  String res = (const char*) Ethernet::buffer + off;
  Serial.println(res);
  if(res.charAt(res.length() - 1) == 'k')
  {
    lcd.setCursor(0, 1);
    Serial.println("Valid TAG, Access Allowed!");
    lcd.print("Time: ");
    for (int i = 0; i < 5; i++) 
      lcd.print(res.charAt(res.length() - 7 + i));
    digitalWrite(8, HIGH);
    myservo.write(180);
    delay(3000);
    myservo.write(0);  
    digitalWrite(8, LOW);
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Access Denied"); 
    Serial.println("Invalid TAG, Access Denied");
    delay(3000);        
    myservo.write(0);
  }
}


void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
  pinMode(8, OUTPUT); 
  Serial.println("Scan your RFid TAG");
  lcd.begin(16, 2);
  lcd.print("Scan your RFid"); 
  ether.begin(sizeof Ethernet::buffer, mymac, SS);
  ether.staticSetup(myip, gwip);
  ether.copyIp(ether.hisip, hisip);

  while (ether.clientWaitingGw())
    ether.packetLoop(ether.packetReceive());
}

void loop () {
  ether.packetLoop(ether.packetReceive());

  handleInput();
}

void handleInput(){
  while(Serial.available()>0)
  {
    digitalWrite(8, LOW);
    RFid = Serial.readString();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("RFID: " + RFid);

    ether.browseUrl(PSTR("/enter_door?rfid="), RFid.c_str(), website, my_result_cb);    
  }
}

void printTime() {
  unsigned long currentMillis = millis(); 
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  lcd.print(hours);
  lcd.print(":");
  lcd.print(minutes % 60);
  lcd.print(":");
  lcd.print(seconds % 60);
}

