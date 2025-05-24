// ПОДКЛЮЧЕНИЯ ПИНОВ
#define SS_PIN 10
#define RST_PIN 9
#define LED_RED_PIN 2
#define LED_GREEN_PIN 3
#define SERVO_PIN 6

// ВКЛЮЧЕНИЯ И БИБЛИОТЕКИ
#include <SPI.h>
#include <MFRC522.h>

// СОЗДАЕМ RFID ЧИТАЛКУ
MFRC522 rfidReader(SS_PIN, RST_PIN);

// SETUP ФУНКЦИЯ
void setup() {
  Serial.begin(9600);              // Запускаем последовательный порт для отладочной печати
  SPI.begin();                     // Инициализируем SPI-интерфейс
  rfidReader.PCD_Init();           // Инициализируем RFID-чип

  pinMode(LED_RED_PIN, OUTPUT);     // Конфигурируем вывод красного светодиода
  pinMode(LED_GREEN_PIN, OUTPUT);   // Конфигурируем вывод зеленого светодиода
}

// ОСНОВНОЙ ЦИКЛ ПРОГРАММЫ
void loop() {
  // Проверяем наличие новой карты рядом с устройством
  if (rfidReader.PICC_IsNewCardPresent()) {
    // Если новая карта обнаружена, читаем её серийный номер (UID)
    if (rfidReader.PICC_ReadCardSerial()) {
      // Выведем UID карты в консоль
      Serial.print("Карточка обнаружена с номером: ");
      printHex(rfidReader.uid.uidByte, rfidReader.uid.size); // Используем нашу собственную функцию для красивого отображения hex-значений
    }
  }

  // Пауза между сканированиями (чтобы избежать излишнего опроса датчика)
  delay(500);
}

// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ДЛЯ ПЕЧАТИ HEX-ЗНАЧЕНИЙ
void printHex(byte* buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {                      // Правильно сформированный цикл
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");              // Добавляем лидирующий ноль, если значение меньше 16
    Serial.print(buffer[i], HEX);                              // Выводим каждую позицию массива буфера в виде шестнадцатеричного числа
  }
  Serial.println();                                            // Перевод строки после завершения вывода
}