#include <Servo.h> // servo motor
char c;
String RFid;
int count = 0;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
  pinMode(13, OUTPUT);
  Serial.println("Scan your RFid TAG");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
    c = Serial.read();
    count = count + 1;
    RFid += c;
    // length of digit is 10
    if(count == 10)
    {
      Serial.print(RFid);
      if(RFid == "010D429BBA")
      {
        Serial.println("Valid TAG, Access Allowed!");
        digitalWrite(13, HIGH);
        myservo.write(180);
        delay(3000); // door is open
        myservo.write(0);  
      }
      else
      {
        Serial.println("Invalid TAG, Access Denied");
        digitalWrite(13, LOW);
        myservo.write(0); // door is closed ASAP
      }
    }
  }
  //reset
  count = 0;
  RFid = "";
  delay(500);
}
