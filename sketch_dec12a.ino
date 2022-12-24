//Keypad working button = 6,8,A,* 
#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;
int buzzer =1;

char* password = "1234"; // change the password here, just pick any 3 numbers
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
int count=0;


char keys[ROWS][COLS] = {
{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'*','0','=','+'}
};



byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock = 11;
int GreenpinUnlock = 10;
void setup()
{
ServoMotor.attach(13);
LockedPosition(true);
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);

}
  
void loop()
{

  char key= keypad.getKey();
  
  
  if(key=='A' || key=='B' || key=='C' || key=='D' || key=='#' || key=='*' || key=='0' | key=='1' | key=='2' | key=='3' | key=='4' | key=='5' | key=='6' | key=='7' | key=='8' | key=='9'){
  
    if (key == '5')
    {
    position = 0;
      count=0;
    LockedPosition(true);
    }

    if (key == password[position])
    {
    position ++;

    }
    if(count<12){
    	if (position == 4)
    	{
		count=0;
    	LockedPosition(false);
    	}
  	}
    if(key != password[position])
    {
    	count++;
    }
    if(count>12){
      for(int i=0;i<6;i++){
        tone(buzzer, 250);
        delay(100);
        digitalWrite(RedpinLock, HIGH);
        delay(500);
        digitalWrite(RedpinLock, LOW);
        delay(500);
        noTone(buzzer);
      }
    }
  }
  
    delay(100);
}

void LockedPosition(int locked)
{
  if (locked)
  {
  digitalWrite(GreenpinUnlock, LOW);
  ServoMotor.write(0);
  }
  else
  {

  digitalWrite(GreenpinUnlock, HIGH);
  ServoMotor.write(150);

  }
  
} 
