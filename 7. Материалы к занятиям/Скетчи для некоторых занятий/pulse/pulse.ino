int pulsePin = 0;           // Датчик подключен к analog pin 0
int blinkPin = 13;         // Пин индиктора ударов
int fadePin = 5;             // Пин притухающего индикаторв на каждый удар
int fadeRate = 0;          //  Значение ШИМ для управления индикатором

volatile int BPM;        // Хранит значение пульса
volatile int Signal;      // Хранит сырые входные данные
volatile int IBI = 600; // Хранит значение промежутка времени между пиками пульса (Inter-Beat Interval)
volatile boolean Pulse = false;     // Выражение истинно при высоком значении волны пульса и ложно при низком
volatile boolean QS = false;       // Становится истинным при наличия пульса

void setup(){
 pinMode(blinkPin,OUTPUT);         // пин «мигает» синхронно с пульсом
 pinMode(fadePin,OUTPUT);          // пин «мигает» в противофазе с пульсом
 Serial.begin(115200);             // битрейт порта
 interruptSetup();                 // устанавливает считывание показаний сенсора каждые 2 мс
  // РАЗКОММЕНТИРУЙТЕ СЛЕДУЮЩУЮ СТРОКУ, ЕСЛИ ВЫ ПИТАЕТЕ СЕНСОР НИЗКИМ НАПРЯЖЕНИЕМ И ОСТАВЬТЕ ЗАКОММЕНТИРОВАННОЙ, ЕСЛИ ПИТАНИЕ ПОДАЕТСЯ ЧЕРЕЗ ОПОРНОЕ НАПРЯЖЕНИЕ
  //analogReference(EXTERNAL);  
}

void loop(){
 sendDataToProcessing('S', Signal);     // отправка сырых входных данных на обработку
 if (QS == true){                       // истинно, если ардуино «видит» пульс
       fadeRate = 255;                  // задает значение переменной ‘fadeRate’ изменяемой в пределах до 255 для потухания светодиода с пульсом
       sendDataToProcessing('B',BPM);   // передает значение пульса с префиксом «В»
       sendDataToProcessing('Q',IBI);   // передает значение временного промежутка между пиками пульса с префиксом «Q» 
       QS = false;              // Сбрасывает флаг Quantified Self для следующего измерения
    }

 ledFadeToBeat();

 delay(20);                             //  задержка
}

void ledFadeToBeat(){
   fadeRate -= 15;  
   fadeRate = constrain(fadeRate,0,255);  
   analogWrite(fadePin,fadeRate);    
 }

void sendDataToProcessing(char symbol, int data ){
   Serial.print(symbol);          
   Serial.println(data);            
 }

