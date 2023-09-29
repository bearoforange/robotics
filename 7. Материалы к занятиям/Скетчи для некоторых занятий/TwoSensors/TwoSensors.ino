/*****************************************************/
// - Данный скетч демонстрирует работу одновременно двух модулей
// - Ко входу А0 Ардуино нужно подключить датчик ЭМГ(EMG)
// - Ко входу А1 Ардуино нужно подключить датчик КГР(GSR)
/*****************************************************/
#include <TimerOne.h>

void sendData();

void setup() {
  Serial.begin(115200); // Включаем асинхронный порт на скорости обмена 115200
  
  Timer1.initialize(30000);  // Запускаем таймер с перидом 300мс для оцифровки КГР
  Timer1.attachInterrupt(sendData);  // По таймеру вызываем функцию отправки данных

}

void loop() {

  
 // delay(5); // Задержка 5мс 
}

void sendData(){
  
  Serial.write("A1");  // Отправка имени порта, к которому подключен КГР
  Serial.write(map(analogRead(A1),0,1024,0,255)); // Отправка значения сигнала КГР 

  Serial.write("A0");  // Отправка имени порта, к которому подключен ЭМГ
  Serial.write(map(analogRead(A0),0,1024,0,255)); // Отправка значения ЭМГ сигнала
}
