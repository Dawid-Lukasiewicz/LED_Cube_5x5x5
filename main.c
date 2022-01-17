#include "Numbers.h"
#include "Functions.h"

#define TIME 20
// PIN 7 (PD7), 13 (PB5) and A5 (PC5) are for buttons
// X is on register B, to turn X on bit must be set PB0-PB4(on Arduino 8-12 pins)
// Y is on register D, to turn Y on bit must be clear PD2-PD6 (on Arduino 2-6 pins)
// Z is on register C, to turn C on bit must be clear PC0-PC4(on Arduino AC0-AC4 pins)

void InitalValues()
{
    PORTB = X_CLEAR;
    PORTD = Y_CLEAR;
    PORTC = Z_CLEAR;
}

void test()
{
    InitalValues();
    if (bit_is_clear(PINC, PC5))
    {
        _delay_ms(1000);
        CubeExpanding(60);
        _delay_ms(1000);
    }
}
int main()
{
//    time_tt tt;
//    srand(time(NULL));
    srand(1);
    // Initialazing pins
    DDRC = 0b00011111;
    PORTC = 0b00111111;
    // Z is on register C(analog pins)

    DDRD = 0b01111100;
    PORTD = 0b11111100;
    // Y is on register D
    // The last bit is INPUT_PULLUP for button
    DDRB = 0b00011111;
    PORTB = 0b00100000;
    // X is on register B
    // The last bit is INPUT_PULLUP for button
    
    int8_t button = 0;
    uint8_t i = 0;
    while (1)
    {
        switch (button)
        {
        case 0:
            for (; i < 5; i++)
            {
                InitalValues();
                Number0(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;

                if (bit_is_clear(PINC, PC5))
                {
                    InitalValues();
                    _delay_ms(1000);
                    RandomLedOn(20);

                    _delay_ms(1000);
                }
            }
            break;
        case 1:
            for (; i < 5; i++)
            {
                InitalValues();
                Number1(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;

                if (bit_is_clear(PINC, PC5))
                {
                    InitalValues();
                    _delay_ms(1000);
                    Rain();
                    _delay_ms(1000);
                }
            }
            break;
        case 2:
            for (; i < 5; i++)
            {
                InitalValues();
                Number2(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;

                if (bit_is_clear(PINC, PC5))
                {
                    InitalValues();
                    _delay_ms(1000);
                    HeavyRain(3);
                    _delay_ms(1000);
                }
            }
            break;
        case 3:
            for (; i < 5; i++)
            {
                InitalValues();
                Number3(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;

                if (bit_is_clear(PINC, PC5))
                {
                    InitalValues();
                    _delay_ms(1000);
                    RunningPoints(20);
                    _delay_ms(1000);
                }
            }
            break;
        case 4:
            for (; i < 5; i++)
            {
                InitalValues();
                Number4(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;

                if (bit_is_clear(PINC, PC5))
                {
                    InitalValues();
                    _delay_ms(1000);
                    CubeExpanding(20);
                    _delay_ms(1000);
                }
            }
            break;
        case 5:
            for (; i < 5; i++)
            {
                InitalValues();
                Number5(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;

                if (bit_is_clear(PINC, PC5))
                {
                    InitalValues();
                    _delay_ms(1000);
                    Crusher(25);
                    _delay_ms(1000);
                }
            }
            break;
        case 6:
            for (; i < 5; i++)
            {
                InitalValues();
                Number6(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;
            }
            break;
        case 7:
            for (; i < 5; i++)
            {
                InitalValues();
                Number7(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;
            }
            break;
        case 8:
            for (; i < 5; i++)
            {
                InitalValues();
                Number8(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;
            }
            break;
        case 9:
            for (; i < 5; i++)
            {
                InitalValues();
                Number9(i, TIME);
                if (bit_is_clear(PINB, PB5) || bit_is_clear(PIND, PD7))
                    break;
            }
            break;
        default:
            break;
        }
        if (bit_is_clear(PINB, PB5))
        {
            button++;
            i++;
            while (bit_is_clear(PINB, PB5))
                _delay_ms(50);
        }
        else if (bit_is_clear(PIND, PD7))
        {
            button--;
            i++;
            while (bit_is_clear(PIND, PD7))
                _delay_ms(50);
        }
        if (button > 9)
        {
            button = 0;
        }
        else if (button < 0)
        {
            button = 9;
        }
        if (i >= 5)
            i = 0;
    }
}