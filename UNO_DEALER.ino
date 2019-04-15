#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial  BT(2, 3);

/*=============================*/
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;


int color_read() {
        // считывание данных с фотодиодов с красным фильтром
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
     
      redFrequency = pulseIn(sensorOut, LOW);   // считываем выходную частоту
      redColor = map(redFrequency, 34, 120, 255,0);
//      redColor = redFrequency;
     
//      Serial.print("R = ");
//      Serial.print(redColor);
      delay(100);
     
      // считывание данных с фотодиодов с зеленым фильтром
      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
    
      greenFrequency = pulseIn(sensorOut, LOW); // считываем выходную частоту
      greenColor = map(greenFrequency, 35, 100, 255, 0);
//      greenColor = greenFrequency;
     
//      Serial.print(" G = ");
//      Serial.print(greenColor);
      delay(100);
     
      // считывание данных с фотодиодов с синим фильтром
      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
     
      blueFrequency = pulseIn(sensorOut, LOW);  // считываем выходную частоту
      blueColor = map(blueFrequency, 27, 84, 255, 0);
//      blueColor = blueFrequency;

//      Serial.print(" B = ");
//      Serial.print(blueColor);
      delay(100);
     
      // вывод на светодиод распознанный цвет
      // вывод в монитор порта сообщение, какой цвет распознан
      if (redColor < 0 || greenColor < 0 && blueColor < 0){
//          Serial.println(" - NO CARD detected!");
          return -1;
      }
      else if(redColor > greenColor && greenColor > 250){
//          Serial.println(" - YELLOW detected!");
          return 4;
      }
      else if(redColor > greenColor && redColor > blueColor){
          if (redColor < 200){ 
//            Serial.println(" - BLACK detected!");
            return 0;
          }
          else{
//            Serial.println(" - RED detected!");
            return 1;
          }
      }
      else if(greenColor > redColor && greenColor > blueColor){
//        Serial.println(" - GREEN detected!");
        return 2;  
      }
      else if(blueColor > redColor && blueColor > greenColor){
//        Serial.println(" - BLUE detected!");
        return 3; 
      }
}

int  color_check()
{
  int color = color_read();
  switch (color){
    case -1:
      BT.println("NO CARD DETECTED");
      break;
    case 0:
      BT.println("Black color??");
      break;
    case 1:
      BT.println("Red color??");
      break;
    case 2:
      BT.println("Green color??");
      break;
    case 3:
      BT.println("Blue color??");
      break;
    case 4:
      BT.println("Yellow maybe??");
      break;
    default:
      BT.println("No Card Detected");
      break;
  }
  return (180 / 4 * color);
}
/*=============================*/

const int servoPin = 9;
const int steprPin = 10;

Servo           servo;

int val = -1;
int ldeg = 0;

void  rotate_on(int deg)
{
  if (ldeg < deg)
  {
    for (int i = ldeg; i < deg; i++)
    {
      servo.write(i);
      delay(10);
    }
  }
  else
  {
    for (int i = ldeg; i > deg; i--)
    {
      servo.write(i);
      delay(10);
    }
  }
  ldeg = deg;
}

void  push_card()
{
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(steprPin, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(steprPin, LOW);
}
/*=============================*/
#include <stdlib.h>
#include <time.h>

int mode = 0;
int player_c = 0;
void setup() {
  pinMode(S0, OUTPUT);  pinMode(S1, OUTPUT);  pinMode(S2, OUTPUT);  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
  // put your setup code here, to run once:
  BT.begin(9600);
  servo.attach(servoPin);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(steprPin, OUTPUT);
label1:  
  BT.println("Please choose mode:\n1) Sort\n2) Shuffle");
  while (!(BT.available() > 0))
    delay(10);
    ;
  val = BT.read();
  if (val == '1')
    mode = 1;
  else if (val == '2')
    mode = 2;
  else 
    goto label1;
  BT.print("your choice - ");
  if (mode == 1)
  {
    BT.println("sort");
  }
  else
  {
    BT.println("shuffle");
players:
    BT.println("Please enter number of players (2-8): ");
    while (!(BT.available() > 0))
      delay(10);
      ;
    val = BT.read();
    if (!(val >= '2' && val <= '8'))
      goto players;      
    player_c = val - '0';    
  }
  srand(time(NULL));
}

int card = 180;

void shuffle(int player_count)
{
  int *deck;
  int r;

  deck = (int *)malloc(sizeof(int) * player_count);
  for (int i = 0; i < player_count; i++)
    deck[i] = 0;
  for (int c = 0; c < player_count * 7; c++)
  {
new_rand:
    r = rand() % player_count;
    if (deck[r] == 7)
      goto new_rand;
    rotate_on(180 / player_count * r);
    delay(10);
    push_card();
    deck[r] += 1;
  }
}

void loop() {
  if (mode == 1)
  {
  	while ((card = color_check()) > 0)
  	{
  		rotate_on(card);
  		delay(10);
  		push_card();
  	}
    mode = 3;
  }
  else if (mode == 2)
  {
    shuffle(player_c);
    mode = 3;
  }
  else if (mode == 3)
  {
    BT.println("Work has been done");
    mode = 0;
  }
/*============BLUETOOTH=========*/
/*
  if (BT.available())
  {
    val = BT.read();
    if (val == '1')
    {
      rotate_on(color_check());
      delay(10);
//      rotate_on(90);
      push_card();
    }
    else if (val == '0')
    {
      rotate_on(0);
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(steprPin, LOW);
    }
  }
*/
/*============COLOR_SENSOR=========*/


/* 
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(100);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(100);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(100);
*/
/*====================================*/
}
