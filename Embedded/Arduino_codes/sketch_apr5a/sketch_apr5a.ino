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
  while(Serial.available()>0)
  {
    // c = Serial.read();
    // count = count + 1;
    // RFid += c;
    digitalWrite(8, LOW);
    RFid = Serial.readString();
    // length of digit is 10
    
      lcd.clear(); // Clear the LCD display
      lcd.setCursor(0, 0); // Set cursor to the first row
      lcd.print("RFID: " + RFid); // Display RFID tag

      if(RFid == "010D429BBA")
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
 
  //reset
  count = 0;
  RFid = "";
  delay(500);
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
