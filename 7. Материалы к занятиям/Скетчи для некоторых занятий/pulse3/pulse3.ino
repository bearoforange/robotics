#include <SPI.h>
#include <SD.h>

const int chipSelect = 2;

unsigned long dataj, i = 0, prevtime = 0;;
int mind = 1023, maxd = 0, j = -2; //-2 - чтобы отсеить первые пару значений
bool isPeak = false;
int data[10];
unsigned long dataj1, i1 = 0, prevtime1 = 0;;
int mind1 = 1023, maxd1 = 0, j1 = -2;
bool isPeak1 = false;
int data1[10];
unsigned long dataj2, i2 = 0, prevtime2 = 0;;
int mind2 = 1023, maxd2 = 0, j2 = -2;
bool isPeak2 = false;
int data2[10];

void checkPulse()
{
    // определение минимального и максимального аналогово значения. Переодическое обуление сигнала.
  if (analogRead(A0) > maxd) maxd = analogRead(A0);
  if (analogRead(A0) < mind) mind = analogRead(A0);
  i++;
  if (i > 50000)
  {
    i = 0;
    mind = 1023;
    maxd = 0;
  }

  if (analogRead(A1) > maxd1) maxd1 = analogRead(A1);
  if (analogRead(A1) < mind1) mind1 = analogRead(A1);
  i1++;
  if (i1 > 50000)
  {
    i1 = 0;
    mind1 = 1023;
    maxd1 = 0;
  }

  if (analogRead(A2) > maxd2) maxd2 = analogRead(A2);
  if (analogRead(A2) < mind2) mind2 = analogRead(A2);
  i2++;
  if (i2 > 50000)
  {
    i2 = 0;
    mind2 = 1023;
    maxd2 = 0;
  }
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111


  //обработка сигнала пульса
  if ((!isPeak) && (analogRead(A0) > (maxd - (maxd / 10))))
  {
    isPeak = true;
    dataj = 60000 / (millis() - prevtime);
    prevtime = millis();
    j++;

    Serial.print("A0:");
    Serial.print(dataj);
    Serial.print(" ");
    
    if (j >= 0)
    {
      data[j] = dataj;
    }
    if (j >= 9)
    {
      j = -2; //-2 - чтобы отсеить первые пару значений
      dataj = 0;
      for (int k = 0; k < 5; k++)
      {
        dataj += data[k];
      }
      Serial.print("A0 ");
      Serial.print(dataj / 5);
      Serial.print("; ");

       File dataFile = SD.open("a0.txt", FILE_WRITE);
       // if the file is available, write to it:
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(" ");
          dataFile.println(dataj / 5);
          dataFile.close();
          // print to the serial port too:
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening A1.txt");
        }

      if ((dataj / 5 < 250) && (dataj / 5 > 20))
      {
        File dataFile = SD.open("data.txt", FILE_WRITE);
       // if the file is available, write to it:
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(" ");
          dataFile.println(dataj / 5);
          dataFile.close();
          // print to the serial port too:
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening data.txt");
        }
      }
    }
  }
  if (analogRead(A0) < (maxd - (maxd / 10)))
  {
    isPeak = false;
  }

  if ((!isPeak1) && (analogRead(A1) > (maxd1 - (maxd1 / 10))))
  {
    isPeak1 = true;
    dataj1 = 60000 / (millis() - prevtime1);
    prevtime1 = millis();
    j1++;

    Serial.print("A1:");
    Serial.print(dataj1);
    Serial.print(" ");
    
    if (j1 >= 0)
    {
      data1[j1] = dataj1;
    }
    if (j1 >= 9)
    {
      j1 = -2; //-2 - чтобы отсеить первые пару значений
      dataj1 = 0;
      for (int k = 0; k < 5; k++)
      {
        dataj1 += data1[k];
      }
      Serial.print("A1 ");
      Serial.print(dataj1 / 5);
      Serial.print("; ");

       File dataFile = SD.open("a1.txt", FILE_WRITE);
       // if the file is available, write to it:
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(" ");
          dataFile.println(dataj1 / 5);
          dataFile.close();
          // print to the serial port too:
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening A1.txt");
        }
      if ((dataj1 / 5 < 250) && (dataj1 / 5 > 20))
      {
        File dataFile = SD.open("data.txt", FILE_WRITE);
       // if the file is available, write to it:
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(" ");
          dataFile.println(dataj1 / 5);
          dataFile.close();
          // print to the serial port too:
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening data.txt");
        }
      }
    }
  }
  if (analogRead(A1) < (maxd1 - (maxd1 / 10)))
  {
    isPeak1 = false;
  }

  if ((!isPeak2) && (analogRead(A2) > (maxd2 - (maxd2 / 10))))
  {
    isPeak2 = true;
    dataj2 = 60000 / (millis() - prevtime2);
    prevtime2 = millis();
    j2++;
    
    Serial.print("A2:");
    Serial.print(dataj2);
    Serial.print(" ");
    
    if (j2 >= 0)
    {
      data2[j2] = dataj2;
    }
    if (j2 >= 9)
    {
      j2 = -2; //-2 - чтобы отсеить первые пару значений
      dataj2 = 0;
      for (int k = 0; k < 5; k++)
      {
        dataj2 += data2[k];
      }
      Serial.print("A2 ");
      Serial.print(dataj2 / 5);
      Serial.println("; ");
      
      File dataFile = SD.open("a2.txt", FILE_WRITE);
       // if the file is available, write to it:
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(" ");
          dataFile.println(dataj2 / 5);
          dataFile.close();
          // print to the serial port too:
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening A2.txt");
        }
      if ((dataj2 / 5 < 250) && (dataj2 / 5 > 20))
      {
        File dataFile = SD.open("data.txt", FILE_WRITE);
       // if the file is available, write to it:
        if (dataFile) {
          dataFile.print(millis());
          dataFile.print(" ");
          dataFile.println(dataj2 / 5);
          dataFile.close();
          // print to the serial port too:
        }
        // if the file isn't open, pop up an error:
        else {
          Serial.println("error opening data.txt");
        }
      }
    }
  }
  if (analogRead(A2) < (maxd2 - (maxd2 / 10)))
  {
    isPeak2 = false;
  }
}

void setup() 
{
  Serial.begin(115200);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  prevtime = prevtime1 = prevtime2 = millis();
  
  File dataFile = SD.open("start.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(prevtime);
    dataFile.close();
    // print to the serial port too:
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening start.txt");
  }
}

void loop() 
{
  checkPulse();
}
