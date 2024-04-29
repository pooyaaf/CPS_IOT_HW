#include <Servo.h> // servo motor
#include <LiquidCrystal.h> // LCD display


LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // LCD pins

char c;
String RFid;
int count = 0;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
  pinMode(8, OUTPUT); // GREEN LED
  Serial.println("Scan your RFid TAG");
  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.print("Scan your RFid"); // Display initial message
}

void loop() {
  // put your main code here, to run repeatedly:
  
 
  //reset
  count = 0;
  RFid = "";
  delay(500);
}
