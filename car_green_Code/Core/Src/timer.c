
unsigned long long _currentMillis = 0;



void update10ms(void)
{
    _currentMillis += 10;
}

unsigned long long millis(void)
{
    return _currentMillis;

}

