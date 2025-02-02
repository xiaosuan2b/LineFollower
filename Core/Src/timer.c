
unsigned long long currentMillis = 0;



void update10ms(void)
{
    currentMillis += 10;
}

unsigned long long millis(void)
{
    return currentMillis;

}

