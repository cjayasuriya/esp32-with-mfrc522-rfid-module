#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 4
#define SS_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN);

void initRFID(){
  SPI.begin();
  rfid.PCD_Init();
}

//Read tag if available
boolean isRFIDDetected()
{

  tagID = "";

  if (rfid.PICC_IsNewCardPresent()) { // Check new tag is available

    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed

      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      for (int i = 0; i < rfid.uid.size; i++) {
        tagID.concat(String(rfid.uid.uidByte[i], HEX));
      }

      tagID.toUpperCase();

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }

  }

  if (tagID.length() > 6) {
    buzzerBeep(100);
    return true;
  } else {
    return false;
  }

}
