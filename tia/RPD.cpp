#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    5  
#define RST_PIN   22  
#define LED_STATUS  2  
#define LED_DETECT  4 

MFRC522 rfid(SS_PIN, RST_PIN);

unsigned long lastStatusToggle = 0;
unsigned long lastDetectToggle = 0;
bool statusState = LOW;
bool detectState = LOW;

bool cardDetected = false;

void setup() {
  Serial.begin(115200);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_STATUS, OUTPUT);
  pinMode(LED_DETECT, OUTPUT);

  Serial.println("Place card near the reader...");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastStatusToggle >= 1000) {
    statusState = !statusState;
    digitalWrite(LED_STATUS, statusState);
    lastStatusToggle = currentMillis;
  }

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    cardDetected = true;
  } else {
    cardDetected = false;
  }

  if (cardDetected) {
    if (currentMillis - lastDetectToggle >= 500) {
      detectState = !detectState;
      digitalWrite(LED_DETECT, detectState);
      lastDetectToggle = currentMillis;
    }
  } else {
    digitalWrite(LED_DETECT, LOW);
  }
}