//Sistema de debounce, sem delay:
class Button
    {
        private:
            uint8_t p;
            short deb_time = 100;
            unsigned long t;

        public:
            Button(int pin)
            {
                p = pin;
                t = -1;
            }
            bool click(bool hold_count)
            {
                if(hold_count)
                {
                    if(digitalRead(p))
                    {
                        if((millis() - t) >= deb_time)
                        {
                            this->t = millis();
                            return true;
                        }
                    }
                }else
                {
                    if(digitalRead(p))
                    {
                        if((millis() - t) >= deb_time)
                        {
                            this->t = millis();
                            return true;
                        }
                        t = millis();
                    }
                }
                return false;
            }

    };


#define sa 0
#define sb 1
#define sc 2
#define sd 3
#define se 4
#define sf 5
#define sg 6
#define d1 A0
#define d2 A1
#define d3 A2
#define d4 A3
#define sw1 8
#define sw2 9
#define sw3 10
#define buzz 12

int valores[10] = {64, 121, 36, 48, 25, 18, 2, 120, 0, 16};

void setup()
{
    pinMode(sa, OUTPUT);
    pinMode(sb, OUTPUT);
    pinMode(sc, OUTPUT);
    pinMode(sd, OUTPUT);
    pinMode(se, OUTPUT);
    pinMode(sf, OUTPUT);
    pinMode(sg, OUTPUT);
    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);
    pinMode(sw1, INPUT);
    pinMode(sw2, INPUT);
    pinMode(sw3, INPUT);
    pinMode(buzz, OUTPUT);

    digitalWrite(sa, HIGH);
    digitalWrite(sb, HIGH);
    digitalWrite(sc, HIGH);
    digitalWrite(sd, HIGH);
    digitalWrite(se, HIGH);
    digitalWrite(sf, HIGH);
    digitalWrite(sg, HIGH);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
    digitalWrite(buzz, LOW);
}

uint8_t display[4] = {d1, d2, d3, d4};
unsigned int mode=0, d_cont=0;
Button b1(sw1), b2(sw2), b3(sw3);

void loop()
{
    d_cont = millis();
    switch(mode%2)
    {
        case 0:
            digitalWrite(display[(d_cont-1)%4], LOW);
            digitalWrite(display[d_cont%4], HIGH);
            PORTD = valores[0];
            d_cont++;
            if(b2.click(false))
            {
                mode++;
            }
            /*while(true)
            {

            }*/
        break;
        case 1:
            if(b2.click(false))
            {
                mode++;
            }
        break;
    } 
}
