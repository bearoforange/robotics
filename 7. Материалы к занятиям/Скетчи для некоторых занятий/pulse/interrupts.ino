volatile int rate[10];                    // Хранит значение последних 10 временных промежутков IBI
volatile unsigned long sampleCounter = 0;          // определяет время пульса
volatile unsigned long lastBeatTime = 0;           // находит значение интервала времени между пульсациями
volatile int P = 512;                      // находит пик волны пульса
volatile int T = 512;                     // находит дно волны пульса
volatile int thresh = 512;                // мгновенное значение пульса
volatile int amp = 100;                   // хранит значение амплитуды волны пульса
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = true;       // used to seed rate array so we startup with reasonable BPM

void interruptSetup(){    
 // Инициализируем таймер 2 через задержку каждые 2 мс 
 TCCR2A = 0x02;     // Деактивуруем ШИМ на цифровых пинах 3 и 11, и вводим их в режим CTC
 TCCR2B = 0x06;     // выставляем предделитель 256
 OCR2A = 0X7C;      // ограничиваем предел счета 124 для 500Hz простого счета
 TIMSK2 = 0x02;     // Прерывание по совпадению TIMER2 и OCR2A
 sei();             // разрешаем глобальные прерывания    
}

// Настройка прерываний TIMER 2
// Timer 2 проверяет, что мы считываем показания каждые 2мс
ISR(TIMER2_COMPA_vect){                         // переключается при достижении Timer2 значения 124
   cli();                                      // в этот момент отключаем прерывания
   Signal = analogRead(pulsePin);              // считываем значения сенсора
   sampleCounter += 2;                         // в этой переменной отслеживаем время в мс
   int N = sampleCounter - lastBeatTime;       // мониторим время с последнего пульса для избегания шума

//  находим максимальное и минимальное значение волны пульса
   if(Signal < thresh && N > (IBI/5)*3){       // избегаем дихроичного шума ожидая 3/5 последнего IBI
       if (Signal < T){                        // T — дно волны пульса
           T = Signal;                         // отслеживает дно волны пульса
        }
      }

   if(Signal > thresh && Signal > P){          // помогает избежать шума
       P = Signal;                             // P — пик полны пульса
      }                                        // отслеживает пик волны пульса

 // Пора отслеживать пульс!
 // сигнал скачет при каждом пульсе
if (N > 250){                                   // защита от высокочастотного шума
 if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){       
   Pulse = true;                               // выставляет флаг пульса когда мы подозреваем, что сейчас есть пульс
   digitalWrite(blinkPin,HIGH);                // включает LED на 13 пине
   IBI = sampleCounter - lastBeatTime;         // измеряем время между пульсами в мс
   lastBeatTime = sampleCounter;               // хранит значение времени для следующего пульса

        if(firstBeat){                         // if it’s the first time we found a beat, if firstBeat == TRUE
            firstBeat = false;                 // clear firstBeat flag
            return;                            // IBI value is unreliable so discard it
           }  
        if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
           secondBeat = false;                 // clear secondBeat flag
              for(int i=0; i<=9; i++){         // seed the running total to get a realisitic BPM at startup
                   rate[i] = IBI;                      
                   }
           }

   // keep a running total of the last 10 IBI values
   word runningTotal = 0;                   // clear the runningTotal variable   

   for(int i=0; i<=8; i++){                // shift data in the rate array
         rate[i] = rate[i+1];              // and drop the oldest IBI value
         runningTotal += rate[i];          // add up the 9 oldest IBI values
       }

   rate[9] = IBI;                          // add the latest IBI to the rate array
   runningTotal += rate[9];                // add the latest IBI to runningTotal
   runningTotal /= 10;                     // average the last 10 IBI values
   BPM = 60000/runningTotal;               // how many beats can fit into a minute? that’s BPM!
   QS = true;                              // set Quantified Self flag
   // QS FLAG IS NOT CLEARED INSIDE THIS ISR
   }                      
}

 if (Signal < thresh && Pulse == true){     // when the values are going down, the beat is over
     digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
     Pulse = false;                         // reset the Pulse flag so we can do it again
     amp = P - T;                           // get amplitude of the pulse wave
     thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
     P = thresh;                            // reset these for next time
     T = thresh;
    }

 if (N > 2500){                             // if 2.5 seconds go by without a beat
     thresh = 512;                          // set thresh default
     P = 512;                               // set P default
     T = 512;                               // set T default
     lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date       
     firstBeat = true;                      // set these to avoid noise
     secondBeat = true;                     // when we get the heartbeat back
    }

 sei();                                     // enable interrupts when youre done!
}// end isr
