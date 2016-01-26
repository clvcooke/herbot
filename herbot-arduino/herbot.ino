#include <EtherCard.h>

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "herb0t.herokuapp.com";

/**
 * Sets up the ethernet controller
 * @returns false if the setup fails, true if it is succesful
 */
static bool setupEther(){

    Serial.println(F("\n[webClient]"));

    //setup the ethernet controller
    if (ether.begin(sizeof Ethernet::buffer, mymac) == 0){ 
      Serial.println(F("Failed to access Ethernet controller"));
      return false;
    }
    if (!ether.dhcpSetup()){
      Serial.println(F("DHCP failed"));
      return false;
    }

    //try out the DNS
    if (!ether.dnsLookup(website)){
      Serial.println("DNS failed");
      return false;
    }
    
     //if we reach this point the ethernet card is working
     return true;
}

/**
 *  @param level the current water level of the plant 
 */
static void postLevel(int level){


      //Note that this isn't the fastest way to convert an int to a string, its just the easiest
      const String l = String(level);
  
      ether.browseUrl(PSTR("/"), l.c_str(), website, my_callback);

}

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
}

void setup () {
  //setting the baud rate
  Serial.begin(57600);
  if (!setupEther()){
    Serial.println("Ethernet setup has failed, exiting program");
    exit(0);
  }


}

void loop () {

  //parse any received data (necessary to process any response to the level postings
  ether.packetLoop(ether.packetReceive());
  
  if (millis() > timer) {
    timer = millis() + 5000;
    Serial.println();
    Serial.print("<<< REQ ");
    postLevel(19);
  }
}
