#define LED_RED 2
#define LED_YELLOW 3
#define LED_GREEN 4
#define BUTTON 8


//Roda uma vez no início e geralmente é pra configurar as entradas:
void setup()
{
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(BUTTON, INPUT);

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
}

int mode=0;

int td = 200;
unsigned long t=0;

//Roda em loop infinito e executa as tarefas desejadas:
void loop()
{
    switch(mode%3)
    {
        case 0:
            digitalWrite(LED_RED, HIGH);
            digitalWrite(LED_YELLOW, LOW);
            digitalWrite(LED_GREEN, LOW);
        break;
        case 1:
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_YELLOW, HIGH);
            digitalWrite(LED_GREEN, LOW);
        break;
        case 2:
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_YELLOW, LOW);
            digitalWrite(LED_GREEN, HIGH);
        break;
    }

    if(((millis() - t) >= td) && (digitalRead(BUTTON) == HIGH))
    {
        t = millis();
        mode++;
    }
}