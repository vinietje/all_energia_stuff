#include <RemoteReceiver.h>
//#include <RemoteSwitch.h>


/*
* Demo for RF remote switch receiver.
* For details, see RemoteReceiver.h!
*
* This sketch demonstrates how to use the static version of
* RemoteReceiver::sendTelegram, which can be used in low-memory
* situations.
*
* Connect the transmitter to digital pin 11, and the receiver to digital pin 2.
*
* When run, this sketch waits for a valid code from the receiver, decodes it,
* and retransmits it after 5 seconds.
*/
#define interruptPin P1_4

void setup() {
 //  Serial.begin(9600);

  //blink led
  pinMode(RED_LED, OUTPUT);
  pinMode(interruptPin, INPUT);
  
  //See example Show_received_code for info on this
  RemoteReceiver::init(interruptPin, 3, showCode);
  digitalWrite(RED_LED,HIGH);
  delay(200);
  digitalWrite(RED_LED,LOW);
  
//  attachInterrupt(interruptPin, blink, RISING);
  
  
}

void loop() {
  while(1)
    delay(1000);
    
}

void blink(){
   digitalWrite(RED_LED,HIGH);
  delay(5);
  digitalWrite(RED_LED,LOW);
 
} 


void showCode(unsigned long receivedCode, unsigned int period) {  
  //Disable the receiver; otherwise it might pick up the retransmit as well.
  RemoteReceiver::disable();
  
  //Need interrupts for delay
  interrupts();
  
  unsigned long code;
  
  //Copy the received code. 
  code = receivedCode & 0xFFFFF; //truncate to 20 bits for show; receivedCode is never more than 20 bits..
  
  //Add the period duration to the code. Range: [0..511] (9 bit)
  code |= (unsigned long)period << 23;
  
  //Add the number of repeats to the code. Range: [0..7] (3 bit). The actual number of repeats will be 2^(repeats), 
  //in this case 8
  code |= 3L << 20;
  
  //Wait 5 seconds before sending.
  digitalWrite(RED_LED,HIGH);
  delay(2000);
  digitalWrite(RED_LED, LOW);
  
  //Retransmit the signal on pin 11. Note: no object was created!
  //RemoteSwitch::sendTelegram(code,11);
  
  RemoteReceiver::enable();
}

