/*
 * Sketch2.ino
 *
 * Created: 9/15/2015 2:44:03 AM
 * Author: Алексей
 */
 
int pin = 13;
int time = 500;

void setup()
{

	  //инициализируем диод
	  pinMode(pin, OUTPUT);

}

void loop()
{
	//генерируем букву "S" азбукой Морзе.
	//точка
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
	//точка
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
	//точка
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
	
	//генерируем букву "O" азбукой Морзе.
	//тире
	digitalWrite(pin, HIGH);
	delay(3*time);
	digitalWrite(pin, LOW);
	delay(time);
	//тире
	digitalWrite(pin, HIGH);
	delay(3*time);
	digitalWrite(pin, LOW);
	delay(time);
	//тире
	digitalWrite(pin, HIGH);
	delay(3*time);
	digitalWrite(pin, LOW);
	delay(time);
	
	//генерируем букву "S" азбукой Морзе.
	//точка
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
	//точка
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
	//точка
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	delay(time);
	
	//пауза между повторами
	delay(4*time);
}
