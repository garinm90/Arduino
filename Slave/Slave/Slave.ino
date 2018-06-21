#include <RFM69.h>         //get it here: https://github.com/lowpowerlab/rfm69
#include <RFM69_ATC.h>     //get it here: https://github.com/lowpowerlab/RFM69
#include <RFM69_OTA.h>     //get it here: https://github.com/lowpowerlab/RFM69
#include <SPIFlash.h>      //get it here: https://github.com/lowpowerlab/spiflash
#include <SPI.h>           //included with Arduino IDE (www.arduino.cc)

//****************************************************************************************************************
//**** IMPORTANT RADIO SETTINGS - YOU MUST CHANGE/CONFIGURE TO MATCH YOUR HARDWARE TRANSCEIVER CONFIGURATION! ****
//****************************************************************************************************************
#define NODEID          2 //the ID of this node
#define NETWORKID     102 //the network ID of all nodes this node listens/talks to
#define FREQUENCY     RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define ENCRYPTKEY    "sampleEncryptKey" //identical 16 characters/bytes on all nodes, not more not less!
#define IS_RFM69HW_HCW  //uncomment only for RFM69HW/HCW! Leave out if you have RFM69W/CW!
#define SERIAL_BAUD  115200
//*****************************************************************************************************************************

#ifdef __AVR_ATmega1284P__                   
#define LED           15 // Moteino MEGAs have LEDs on D15
#define FLASH_SS      23 // and FLASH SS on D23
#else
#define LED           9 // Moteinos have LEDs on D9
#define FLASH_SS      8 // and FLASH SS on D8
#endif



#ifdef ENABLE_ATC
RFM69_ATC radio;
#else
RFM69 radio;
#endif



void setup() {
  Serial.begin(SERIAL_BAUD);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
#ifdef IS_RFM69HW_HCW
  radio.setHighPower(); //must include this only for RFM69HW/HCW!
#endif
  radio.encrypt(ENCRYPTKEY);

  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", radio.getFrequency() / 1000000);
  Serial.println(buff);


}
void Blink(byte PIN, int DELAY_MS)
{
  for (int i = 0; i < 10; i++) {
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN, LOW);
    delay(DELAY_MS);
  }
}

void sendData() {
  if (radio.receiveDone()) {
    for (byte i = 0; i < radio.DATALEN; i++) {
      Serial.print((char)radio.DATA[i]);
      Blink(LED, 3);
    }
    Serial.println("");
  }
}
void loop() {
  sendData();
  //Blink(LED, 80);

}


