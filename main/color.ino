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

void color_setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

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
