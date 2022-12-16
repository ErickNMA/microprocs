#include <Arduino.h>
 
 #include <RF24.h>

RF24 radio(9, 10);
byte enderecos[][6] = {"1node", "2node"};

int current[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int target[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() 
{
  Serial.begin(9600);
  
  //RF:
  radio.begin();
  radio.openWritingPipe(enderecos[1]);
  radio.openReadingPipe(1, enderecos[0]);
  radio.startListening();

  //Pins:
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

double ref=0;
unsigned long long mode=0;

void loop() 
{
  /*radio.stopListening();                                   
  while(radio.write(current, 10*sizeof(int)));
  radio.startListening();*/
  if(radio.available())
  {
    radio.read(&target, 10*sizeof(int));
    Serial.println("ENTROU!");
  }

  if(target[1] != 0)
  {
    if((millis()-ref)>(1000.0/float(target[1])))
    {
      mode++;
      ref = millis();
    }
  }else
  {
    mode = 0;
  }

  switch(mode%2)
  {
    case 0:
      analogWrite(3, (40*(target[0]/100.0)*(target[2]/100.0)));
      analogWrite(5, (120*(target[0]/100.0)*(target[3]/100.0)));
      analogWrite(6, (255*(target[0]/100.0)*(target[4]/100.0)));
    break;
    case 1:
      analogWrite(3, LOW);
      analogWrite(5, LOW);
      analogWrite(6, LOW);
    break;
  }
    
}
