#include<SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

SoftwareSerial fp(2,3); //지문 인식 모듈 TX/RX 설정

int relayPin = 4;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fp);
void setup() {
  pinMode(relayPin, OUTPUT); //릴레이 핀을 OUTPUT으로 설정
  finger.begin(57600); //지문 인식 모듈 통신 시작
  finger.verifyPassword(); 
  finger.getTemplateCount();
}

void loop() {
  digitalWrite(relayPin,HIGH);
  int num = 0; //지문 인식 번호의 초기값을 0으로 설정
  while((num=getFingerprintIDez())<=0); //값이 -1(오류) 또는 0(기본값)에서 벗어날 때까지 인식 요청
  if(num==1 or num==2 or num==3){
    digitalWrite(relayPin,LOW);
    delay(3000);
  }
  delay(100);
}
int getFingerprintIDez() { //지문 인식하는 함수
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  return finger.fingerID; //지문 인식 결과 리턴
}
