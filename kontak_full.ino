#define SS_PIN D4
#define RST_PIN D3


#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SPI.h>
boolean izin;
boolean relayStatus= false;
int relay=5;
MFRC522 nfckart(SS_PIN, RST_PIN);
void setup() {
  // put your setup code here, to run once:
pinMode(relay,OUTPUT);
Serial.begin(9600);
SPI.begin();
nfckart.PCD_Init();

}

void loop() {
  if ( ! nfckart.PICC_IsNewCardPresent()) 
    {
     return ;
   }
  // Kart okundu ise
  if ( ! nfckart.PICC_ReadCardSerial()) 
  {
    return ;
  }
  Serial.println();
  Serial.print(" UID etiketi :");
  String content= "";
  byte letter;
  for (byte i = 0; i < nfckart.uid.size; i++) 
  {
     Serial.print(nfckart.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(nfckart.uid.uidByte[i], HEX);
     content.concat(String(nfckart.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(nfckart.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "6A 77 0C 85"  ) // Bu UID degerini tanimlamak istediginiz kartin degeri ile degistirin.
  {
    if ( relayStatus != true ) // Bu UID degerini tanimlamak istediginiz kartin degeri ile degistirin.
  {
 
   relayStatus=true;
    Serial.println(" Kontak Acildi ");
    
     digitalWrite(relay, LOW);    
    Serial.println();
   delay(4000);
  }
 else if ( relayStatus == true )
  {
    relayStatus=false;
    Serial.println(" Kontak Kapatildi ! ");
   
     digitalWrite(relay, HIGH);    
    
    Serial.println();
   delay(4000);
  }
  }

  else {
    Serial.println("kart taninmadi");
    digitalWrite(relay, HIGH);
    
    }
    
  }
  
//  nfckart.PICC_HaltA();
