#include <TimerOne.h>

#define arrSize 32  // Размер массива для анализа
#define noise 50  // Шумовой уровень

double sData = 0;  // Амплитуда размаха сигнала

int val[arrSize]; //массив для анализа ЭМГ сигнала

int i = 0; // Глобальный счетчик

void sendData();

void setup() {
  Serial.begin(115200);

  Timer1.initialize(3000);  // Запускаем таймер с периодом 3мс
  Timer1.attachInterrupt(sendData);  // Выполняем функцию sendData каждую 3мс

  pinMode(13, OUTPUT); // Определим 13 ножу как вывод
  digitalWrite(13, LOW); // Установим "низкое" состояние на ножке

  // Заполняем массив для изучения нулями
  for (int k = 0; k < arrSize; k++) {
    val[k] = 0;
  }

}

void loop() {

}

void sendData() {
  Serial.write("A0");    // Отправляем имя порта, к которому подключен
  val[i] = map(analogRead(A0), 0, 1023, 0, 255); // Конвертируем из 10битного вида к 8 битному
  Serial.write(val[i++]); // Отправляем результат оцифровки

  if (i == arrSize) {  // Если полностью заполнили массив
    i = 0;  //не выходим индексом i за размер массива
    double maxV = val[0], minV = val[0];  // Инициализируем максимальное и минимальное значение

    // Ищем максимальное и минимальное значение в массиве
    for (int k = 0; k < arrSize; k++) {
      if ( val[k] > maxV)
        maxV = val[k];
      if ( val[k] < minV)
        minV = val[k];
    }

    //sData =  0.4*sData + 0.6*(maxV - minV); // Что бы применить комплиментарный фильтр, расскомментируйте строку
    sData = maxV - minV; // Определяем максимальный размах сигнала

  }

  if (sData > noise) // Если размах сигнала больше уровня шума
    digitalWrite(13, HIGH); // Подаем логическую 1 на ногу 13
  else
    digitalWrite(13, LOW); // Иначе подаем логический 0 на ногу 13
}

