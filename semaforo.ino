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

//Roda em loop infinito e executa as tarefas desejadas:
void loop()
{

}