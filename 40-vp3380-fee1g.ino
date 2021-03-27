#include <TM1628.h>
#include <IRremote.h>

#define BEEP_UP 1
#define BEEP_DOWN 0

#define TM1628_STROBE 7
#define TM1628_DATA 8
#define TM1628_CLOCK 9
#define IR_SENSOR 10
#define SPEAKER 11

int counter;
int button;
// setup CLOCK, DATA and STROBE PINs for TM1628
TM1628 dvdLED(TM1628_CLOCK, TM1628_DATA, TM1628_STROBE);
// setup IR receiver PIN
IRrecv receiver(IR_SENSOR);

void setup() {
  counter = 0;
  
  dvdLED.begin(ON, 2);
  dvdLED.clear();
  dvdLED.print("HELLO");

  pinMode(SPEAKER, OUTPUT); //set the speaker as output
  pinMode(IR_SENSOR, OUTPUT); //set the IR sensor as input

  receiver.enableIRIn();
  
  //Serial.begin(9600);
  //Serial.print("HELLO"); 
}


void loop() {

  // check if buttons pressed
  button = dvdLED.getButtons();
  if (button != 0){
    if (0)
      counter = 0;
    else if (button & 0x02) { // K302 pressed
      counter++;
      LEDBlinkWithBeep(BEEP_UP);
    }
    else if (button & 0x04) { // K301 pressed
      counter--;
      LEDBlinkWithBeep(BEEP_DOWN);
    }
    else if (button & 0x16) { // K303 pressed   
      FailingBeep();
    }
    ClearPrint(counter);
  }

  // check received data on IR sensor
  if(receiver.decode()) {
    RandomMelody();
    receiver.resume();
  }
  
  delay(50);
}

void LEDBlinkWithBeep(int direction) {
  tone(SPEAKER,(direction ? 100 : 300));
  dvdLED.setLEDon(0);
  delay(100);
  tone(SPEAKER,(direction ? 300 : 100));
  dvdLED.setLEDoff(0);
  delay(150);
  noTone(SPEAKER);
}

void FailingBeep() {
  int i;
  for (i = 0; i < 10; i++) {
    tone(SPEAKER, i * 100);
    ClearPrint(i * 1111);
    delay(50);
  }
  for (i = 10; i > 0; i--) {
    tone(SPEAKER, i * 100);  
    ClearPrint(i * 1111);
    delay(50);
  }
  noTone(SPEAKER);
}

void RandomMelody() {
  int i;
  int direction = random(0,2);
  int _tone = direction ? 100 : 1500;
  for (i = 0; i < 10; i++) {
    tone(SPEAKER, _tone);
    ClearPrint(i * 1111);
    if (direction)
      _tone += random(1, 5) * 100;
    else
      _tone -= random(1, 5) * 100;
    if (_tone < 100)
      _tone = 100;
    delay(random(20,60));
  }
  noTone(SPEAKER);
}

void ClearPrint(unsigned int num) {
  dvdLED.clear();
  dvdLED.print(num);
}
