#include <SoftwareSerial.h>
#include <TMCStepper.h>

#define STEPPER_CURRENT 900        // mA, do not exceed 800
#define STEP_TIME 500              // microseconds per half step (lower is faster)
#define HIGH_STEPPER_CURRENT 1000  // mA when trying to overcome jam, do not exceed 800
#define SLOW_STEP_TIME 800         // microseconds per half step when trying to overcome jam

#define NUMBER_4BYTE_UIDS 6  //amount of 4b tags
#define NUMBER_7BYTE_UIDS 3  //ammount of 7b tags

uint8_t uids4B[NUMBER_4BYTE_UIDS][4] = {
  { 0x00, 0x00, 0x00, 0x00 },  // MAM
  { 0x00, 0x00, 0x00, 0x00 },  // ME
  { 0x00, 0x00, 0x00, 0x00 },  // MIKE
  { 0x00, 0x00, 0x00, 0x00 }, // HAYLEY
  { 0x00, 0x00, 0x00, 0x00 },  // ELSIE
  { 0x00, 0x00, 0x00, 0x00 },  // MY GLOVE
};

uint8_t uids7B[NUMBER_7BYTE_UIDS][7] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // MY HAND
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // JEN THUMB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // ELISE THUMB
};


#define BZ_PIN 2    // BUZZER pin PA6
#define EN_PIN 3    // Enable pin PB5
#define DIR_PIN 4   // Direction PA7
#define STEP_PIN 5  // Step pin PB5
#define TOFF 5
#define MICROSTEPS 8      // Options are 0,2,4,8,16,32,64,128,256
#define SPREADCYCLE true  // Options are true or false
#define R_SENSE 0.11f    // shunt resistor value 
#define SERIAL_PORT Serial                     // Hardware Serial Port
TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);  // Hardware Serial (TX / RX pins)
SoftwareSerial mySerial(PIN_PB1, PIN_PB0); // RX, TX for software Serial printing

#define MAX_STEPS_NORMAL 1920
#define MAX_STEPS_SLOW 1630

#define LOCKED_SWITCH 11    //  left pogo gpio-PC1 
#define UNLOCKED_SWITCH 12  // right pogo gpio-PC2 
bool checkLocked;          // Limit switch value for locked position
bool checkUnlocked;        // Limit switch value for unlocked position

#include <SPI.h>
#include <Adafruit_PN532.h>

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK (16)   //PIN PA3
#define PN532_MOSI (14)  //PIN PA1
#define PN532_SS (13)    //PIN PC3 OR PA4(0)
#define PN532_MISO (15)  //PIN PA2

Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

#define MAXIMUM_INVALID_ATTEMPTS 13
uint8_t invalidAttempts = 0;
const uint8_t invalidDelays[MAXIMUM_INVALID_ATTEMPTS] = { 1, 1, 1, 1, 1, 2, 3, 5, 8, 13, 21, 33, 54 };

void beep(int number, long time) {
  for (int i = 0; i < number; i++) {
    tone(BZ_PIN, 440);
    delay(time);
    noTone(BZ_PIN);
    delay(time);
  }
}


void moveLock(bool dir) {
  driver.toff(TOFF);
  digitalWrite(DIR_PIN, dir);

  checkLocked = digitalRead(LOCKED_SWITCH);
  checkUnlocked = digitalRead(UNLOCKED_SWITCH);

  digitalWrite(EN_PIN, LOW);

  long stepCount = 0;
  while (((!dir && checkLocked) || (dir && checkUnlocked)) && stepCount < MAX_STEPS_NORMAL) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(STEP_TIME);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(STEP_TIME);

    checkLocked = digitalRead(LOCKED_SWITCH);
    checkUnlocked = digitalRead(UNLOCKED_SWITCH);
    stepCount++;
  }
  if ((checkLocked && checkUnlocked) || (dir && checkLocked) || (!dir && checkUnlocked)) {
    stepCount = 0;
    driver.rms_current(HIGH_STEPPER_CURRENT);
    while (((!dir && checkLocked) || (dir && checkUnlocked)) && stepCount < MAX_STEPS_SLOW) {
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(SLOW_STEP_TIME);
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(SLOW_STEP_TIME);

      checkLocked = digitalRead(LOCKED_SWITCH);
      checkUnlocked = digitalRead(UNLOCKED_SWITCH);
      stepCount++;
    }
    driver.rms_current(STEPPER_CURRENT);
  }
  driver.toff(0);
  digitalWrite(EN_PIN, HIGH);
}

void changeState() {
  checkLocked = digitalRead(LOCKED_SWITCH);
  checkUnlocked = digitalRead(UNLOCKED_SWITCH);

  if (!checkUnlocked) {  // checks if door is open or locked.
    beep(2, 200);
    // Clockwise
    moveLock(false);
    mySerial.println("Door unlocked");  // Print to Software Serial
 
  } else {
    beep(1, 200);
    // Anti-clockwise
    moveLock(true);
    mySerial.println("Door locked");  // Print to Software Serial
         }
}

void setup() {
  Serial.begin(115200);  // Setup Hardware Serial
  mySerial.begin(9600);  // Setup Software Serial
 
  delay(500);
  mySerial.print(F("Start of program"));  // Print to Software Serial
 

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
  
  driver.begin();
  driver.rms_current(STEPPER_CURRENT);
  driver.microsteps(MICROSTEPS);
  driver.en_spreadCycle(SPREADCYCLE);
  driver.pwm_autoscale(true);
  driver.toff(0);

  pinMode(LOCKED_SWITCH, INPUT_PULLUP);
  pinMode(UNLOCKED_SWITCH, INPUT_PULLUP);
  checkLocked = digitalRead(LOCKED_SWITCH);
  checkUnlocked = digitalRead(UNLOCKED_SWITCH);

  nfc.begin();

  delay(1000);
  mySerial.println(F("Starting up!"));  // Print to Software Serial
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    mySerial.print(F("Didn't find PN53x board"));  // Print to Software Serial
      while (1);  // halt
  }

  mySerial.print(F("Found chip PN5"));  // Print to Software Serial
  mySerial.println((versiondata >> 24) & 0xFF, HEX);
  mySerial.print(F("Firmware ver. "));  // Print to Software Serial
  mySerial.print((versiondata >> 16) & 0xFF, DEC);
  mySerial.print('.');
  mySerial.println((versiondata >> 8) & 0xFF, DEC);

  nfc.SAMConfig();
  mySerial.println(F("Waiting for an ISO14443A card"));  // Print to Software Serial
}

void loop() {
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  // Awaiting an UID to be Presented
  if (!success) {
    return;
  }

  bool validUID = false;
  if (uidLength == 4) {
    mySerial.println("4B UID");  // Print to Software Serial
    for (int i = 0; i < NUMBER_4BYTE_UIDS; i++) {
      bool same = true;
      for (int j = 0; j < 4; j++) {
        if (uids4B[i][j] != uid[j]) {
          same = false;
        }
      }
      if (same) {
        validUID = true;
      }
    }
  } else if (uidLength == 7) {
    mySerial.println("7B UID");  // Print to Software Serial
    for (int i = 0; i < NUMBER_7BYTE_UIDS; i++) {
      bool same = true;
      for (int j = 0; j < 7; j++) {
        if (uids7B[i][j] != uid[j]) {
          same = false;
        }
      }
      if (same) {
        validUID = true;
      }
    }
  } else {
    mySerial.print("Unknown UID type / length");  // Print to Software Serial
  }

  if (validUID) {
    mySerial.println("Valid UID");  // Print to Software Serial
    changeState();
    invalidAttempts = 0;
  } else {
    mySerial.println(" Access denied");  // Print to Software Serial
    beep(3, 150);
    delay(invalidDelays[invalidAttempts] * 1000);
    if (invalidAttempts < MAXIMUM_INVALID_ATTEMPTS - 1) {
      invalidAttempts++;
    }
  }
}