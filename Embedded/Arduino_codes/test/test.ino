#include <EtherCard.h>

#define REQUEST_RATE 5000 // milliseconds

// ethernet interface mac address
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
// ethernet interface ip address
static byte myip[] = { 169,254,88,42 };
// gateway ip address
static byte gwip[] = {169,254,88,41 };
// remote website ip address and port
static byte hisip[] = { 169,254,88,41 };
// remote website name
const char website[] PROGMEM = "169.254.88.41";

// Ethernet buffer size
byte Ethernet::buffer[700];

static long timer;

// called when the client request is complete
static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  Serial.print(millis() - timer);
  Serial.println(" ms");
  Serial.println((const char*) Ethernet::buffer + off);
}


void setup() {
  Serial.begin(9600);
  Serial.println("\n[getStaticIP]");
  // Begin Ethernet communication with buffer size and MAC address
  ether.begin(sizeof Ethernet::buffer, mymac, SS);

  // Configure static IP and gateway IP
  ether.staticSetup(myip, gwip);

  ether.copyIp(ether.hisip, hisip);
  ether.printIp("Server: ", ether.hisip);

  while (ether.clientWaitingGw())
    ether.packetLoop(ether.packetReceive());
  Serial.println("Gateway found");

  timer = - REQUEST_RATE; // start timing out right away
}

void loop () {
  ether.packetLoop(ether.packetReceive());

  if (millis() > timer + REQUEST_RATE) {
    timer = millis();
    Serial.println("\n>>> REQ");
    ether.browseUrl(PSTR("/enter_door?rfid=1234567890"), "", website, my_result_cb);
  }
}

