/-----------rfid настройки и настройки светодиода------------
#include <SPI.h> // Библиотека для работы с SPI интерфейсом
#include <MFRC522.h> // Библиотека для работы с модулем RC522

int s;
#define SS_PIN 10   // Пин для подключения модуля (SS)
#define RST_PIN 9   // Пин для сброса модуля
#define LED_PIN 7   // Пин для подключения светодиода
#define LOCK_PIN 8  // Пин для замка
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Создаем объект MFRC522
bool isCorrectCard = false;
/------------------------------------------------------------

/-------------------------способности:
//  проверить в данных карт
void checkcart(){
  if (!mfrc522.PICC_IsNewCardPresent()) {  // Проверяем наличие новой карты
    return;
  }
  
  if (!mfrc522.PICC_ReadCardSerial()) {     // Читаем данные карты
    return;
  }
  Serial.print("UID tag :");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  // Пример правильного UID карты: замените этот массив на ваш UID
  byte correctUID[] = {0x12, 0x34, 0x56, 0x78};
  for (int i = 0; i < mfrc522.uid.size; i++) {
    if (correctUID[i] != mfrc522.uid.uidByte[i]) {
      isCorrectCard = false;
      break;
    }
    if (correctUID[i] == mfrc522.uid.uidByte[i]) {
      isCorrectCard = true;
      break;
    }
  }
}

//    вкл светодиод
void vklsvet(){
  if(isCorrectCard == true){
    digitalWrite(LED_PIN, HIGH);  // Включаем светодиод
    Serial.println("Правильная карта! Светодиод включен.");
  }
}

//	открыть дверь
void open(){
  if(isCorrectCard == true){
    digitalWrite(LOCK_PIN, HIGH);
  }
}
//	закрыть дверь
void close(){
  if(isCorrectCard == true){
    digitalWrite(LOCK_PIN, LOW);
  }
}
//    выкл светодиод
void vuklsvet(){
  if(isCorrectCard != true){
    digitalWrite(LED_PIN, LOW);   // Выключаем светодиод
    Serial.println("Неправильная карта! Светодиод выключен.");
}
/-----------------------------------
/---------------setup----------------------------------------
void setup() {
  int s = 0;
  Serial.begin(9600);         // Инициализация последовательного порта
  SPI.begin();                // Инициализация SPI интерфейса
  mfrc522.PCD_Init();         // Инициализация MFRC522

  pinMode(LED_PIN, OUTPUT);   // Настраиваем пин светодиода как выход
  pinMode(LOCK_PIN, OUTPUT);

}


/------------------------------главный код--------------
void loop() {
  //триггеры

  
  //-------

  //состояния


  //------
}
/-------------------------------------------------------
