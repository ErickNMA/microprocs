#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
#include <RF24.h>

RF24 radio(9, 10);
byte enderecos[][6] = {"1node", "2node"};

class Button
{
    private:
        int p;
        short deb_time = 100;
        unsigned long t;

    public:
        Button(int pin)
        {
            p = pin;
        }
        bool click(bool hold_count)
        {
            if(hold_count)
            {
                if(!digitalRead(p))
                {
                    if((millis() - t) >= deb_time)
                    {
                        t = millis();
                        return true;
                    }
                }
            }else
            {
                if(!digitalRead(p))
                {
                    if((millis() - t) >= deb_time)
                    {
                        t = millis();
                        return true;
                    }
                    t = millis();
                }
            }
            return false;
        }

};

/*struct estruturaDadosRF
{
  int dimmer=0;
  int strobe=0;
  int red=0;
  int green=0;
  int blue=0;
  int pan=0;
  int tilt=0;
  int velocity=0;
  int acceleration=0;
  int smoothness=0;
};
typedef struct estruturaDadosRF tipoDadosRF;
tipoDadosRF current, target;*/
int current[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int target[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int last[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CLK 3
#define DT 2
#define SW 4

RotaryEncoder encoder(CLK, DT);

long add=0, last_pos=-1;
int mode = 1, i=0, v0;

void enc_check()
{
  encoder.tick();
}

bool change()
{
  for(int j=0; j<10; j++)
  {
    if(target[j] != last[j])
    {
      return true;
    }
  }
  return false;
}

void att()
{
  for(int j=0; j<10; j++)
  {
    last[j] = target[j];
  }
}

void setup() 
{
  Serial.begin(9600);
  
  //RF:
  radio.begin();
  radio.openWritingPipe(enderecos[0]);
  radio.openReadingPipe(1, enderecos[1]);
  radio.stopListening();

  //LCD:
  lcd.init();
  lcd.backlight();
  lcd.clear();

  //Pins:
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  //Interrupções:
  attachInterrupt(digitalPinToInterrupt(CLK), enc_check, RISING);
  attachInterrupt(digitalPinToInterrupt(DT), enc_check, RISING);

  encoder.setPosition(0);
  mode = 1;
  lcd.setCursor(0, 0);
  lcd.print("      MENU      ");
}

String menu[10] = {"     Dimmer     ", "     Strobe     ", "       RED      ", "     GREEN     ", "      BLUE      ", "      PAN       ", "      TILT      ", "     SPEED      ", "  ACCELERATION  ", "   SMOOTHNESS   "};
//Botão:
Button bot(SW);
char text[18];

void loop() 
{
  //radio.stopListening();     
  if(change())
  {                              
    while(radio.write(&target, 10*sizeof(int)));
    att();
  }
  //radio.startListening();
  /*if(radio.available())
  {
    radio.read(current, 10*sizeof(int));
  }*/

  switch(mode)
  {
    case 1:
      //Menu principal:
      if(encoder.getPosition()<0)
      {
        i = ((encoder.getPosition()+1000001)%10);
      }else
      {
        i = (encoder.getPosition()%10);
      }
      if(i != last_pos)
      {
        lcd.setCursor(0, 1);
        lcd.print(menu[i]);
        last_pos = i;
      }
      if(bot.click(false))
      {
        v0 = target[i];
        encoder.setPosition(0);
        mode = 2;
        lcd.setCursor(0, 0);
        lcd.print(menu[i]);
      }
    break;
    case 2:
      if(encoder.getPosition()<0)
      {
        add = (encoder.getPosition()+1000001);
      }else
      {
        add = encoder.getPosition();
      }
      target[i] = ((v0+add)%101);
      sprintf(text, "      %.3d%%      ", target[i]);
      lcd.setCursor(0, 1);
      lcd.print(text);
      if(bot.click(false))
      {
        mode = 1;
        encoder.setPosition(0);
        lcd.setCursor(0, 0);
        lcd.print("      MENU      ");
        last_pos = -1;
      }
    break;
  }

  
  
}
