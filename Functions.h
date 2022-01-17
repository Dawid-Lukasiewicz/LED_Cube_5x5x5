#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <time.h> // I am afraid i can't use this for MCU

#define X_PIN 0b00000001
#define Y_PIN 0b00000100
#define Z_PIN 0b00000001

#define X_SHIFT 0
#define Y_SHIFT 2
#define Z_SHIFT 0

#define X_CLEAR 0b00100000
#define Y_CLEAR 0b11111100
#define Z_CLEAR 0b00111111

#define SET_5_BITS 0b11111
#define CLEAR_5_BITS 0b00000

#define TIMETAKEN 300
#define TIMETAKEN_LOW 500
#define TIMETAKEN_MEDIUM 1000
#define TIMETAKEN_HIGH 1500

#define EDGE 5

void LightOne(uint8_t X, uint8_t Y, uint8_t Z)
{
    if (X >= 0 && X < 5 && Y >= 0 && Y < 5 && Z >= 0 && Z < 5)
    {
        PORTB |= X_PIN << X;    //Set X-pin to 1(turn on)
        PORTD &= ~(Y_PIN << Y); //Set Y-pin to 0(turn on)
        PORTC &= ~(Z_PIN << Z); //Set Z-pin to 0(turn on)
    }
}

void OffOne(uint8_t X, uint8_t Y, uint8_t Z)
{
    if (X >= 0 && X < 5 && Y >= 0 && Y < 5 && Z >= 0 && Z < 5)
    {
        PORTB &= ~(X_PIN << X); //Set X-pin to 0(turn off)
        PORTD |= Y_PIN << Y;    //Set Y-pin to 1(turn off)
        PORTC |= Z_PIN << Z;    //Set Z-pin to 1(turn off)
    }
}

void LightRowX(uint8_t X, uint8_t Z)
{
    if (X >= 0 && X < 5 && Z >= 0 && Z < 5)
    {
        PORTB |= X_PIN << X;              //Set X-pin to 1 (turn on)
        PORTD &= CLEAR_5_BITS << Y_SHIFT; //Set all Y-pins to 0 (turn on)
        PORTC &= ~(Z_PIN << Z);           //Set Z-pin to 0 (turn on)
    }
}

void OffRowX(uint8_t X, uint8_t Z)
{
    if (X >= 0 && X < 5 && Z >= 0 && Z < 5)
    {
        PORTB &= ~(X_PIN << X);         //Set X-pin to 0 (turn off)
        PORTD |= SET_5_BITS << Y_SHIFT; //Set all Y-pins to 1 (turn off)
        PORTC |= Z_PIN << Z;            //Set Z-pin to 1 (turn off)
    }
}

void RandomLedOn(uint8_t Repeats)
{
    while (bit_is_set(PINC, PC5))
    {
        uint8_t RandomNumber[3];
        RandomNumber[0] = rand() % 5;
        RandomNumber[1] = rand() % 5;
        RandomNumber[2] = rand() % 5;
        uint8_t count = 0;
        while (count < Repeats)
        {
            count++;
            LightOne(RandomNumber[0], RandomNumber[1], RandomNumber[2]);
            _delay_ms(10);
            OffOne(RandomNumber[0], RandomNumber[1], RandomNumber[2]);
        }
    }
}

void Rain()
{
    while (bit_is_set(PINC, PC5))
    {
        uint8_t tmp_randomX = rand() % EDGE, tmp_randomY = rand() % EDGE;
        PORTB |= X_PIN << tmp_randomX;
        PORTD &= ~(Y_PIN << tmp_randomY);
        int8_t i;
        for (i = EDGE - 1; i >= 0; i--)
        {
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
            PORTC &= ~(Z_PIN << i);
            _delay_ms(55);
            PORTC |= Z_PIN << i;
        }
        PORTB &= ~(X_PIN << tmp_randomX);
        PORTD |= Y_PIN << tmp_randomY;
    }
}

void HeavyRain(uint8_t MinDropsNumber)
{
    uint8_t Number = (rand() % 4) + MinDropsNumber;
    int8_t Drops[Number][3];
    int8_t i;
    for (i = 0; i < Number; i++)
    {
        int8_t k;
        for (k = 0; k < 3; k++)
        {
            Drops[i][k] = rand() % EDGE;
        }
    }

    while (bit_is_set(PINC, PC5))
    {
        int8_t i;
        for (i = 0; i < Number; i++)
        {

            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
            LightOne(Drops[i][0], Drops[i][1], Drops[i][2]);
            _delay_ms(12);
            OffOne(Drops[i][0], Drops[i][1], Drops[i][2]--);
            if (Drops[i][2] < 0)
            {
                Drops[i][0] = rand() % EDGE;
                Drops[i][1] = rand() % EDGE;
                Drops[i][2] = 4;
            }
            _delay_us((100));
        }
    }
}

void Crusher(uint8_t Repeats)
{
    uint8_t Step = 0, Count = 0;
    bool Crush = true, ToggleBit = true;
    while (bit_is_set(PINC, PC5))
    {
        if (Crush && !ToggleBit)
            Crush = false;
        else if (!Crush && ToggleBit)
            Crush = true;

        switch (Step)
        {
        case 0:
            Count = 0;
            while (Count < Repeats)
            {
                if (bit_is_clear(PINC, PC5))
                    break;

                Count++;
                uint8_t i;
                for (i = 0; i < EDGE; i++)
                {
                    LightRowX(i, Step);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffRowX(i, Step);

                    LightRowX(i, 4 - Step);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffRowX(i, 4 - Step);
                }
            }
            ToggleBit = true;
            Step++;
            break;

        case 1:
            Count = 0;
            while (Count < Repeats)
            {
                if (bit_is_clear(PINC, PC5))
                    break;

                Count++;
                uint8_t i;
                for (i = 0; i < EDGE; i++)
                {
                    LightRowX(i, Step);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffRowX(i, Step);

                    LightRowX(i, 4 - Step);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffRowX(i, 4 - Step);
                }
            }
            if (Crush)
                Step++;
            else
                Step--;
            break;

        case 2:
            Count = 0;
            while (Count < Repeats)
            {
                if (bit_is_clear(PINC, PC5))
                    break;

                Count++;
                uint8_t i;
                for (i = 0; i < EDGE; i++)
                {
                    LightRowX(i, Step);
                    _delay_us(2 * TIMETAKEN_MEDIUM);
                    OffRowX(i, Step);
                }
            }
            ToggleBit = false;
            Step--;
            break;

        default:
            break;
        }
    }
}

void RunningPoints(uint8_t Repeats) //Messy code
{
    while (bit_is_set(PINC, PC5))
    {
        // Point starts in middle on top
        PORTB = 0b00100100; //X set middle
        PORTD = 0b11101100; //Y set middle
        PORTC = 0b00101111; //Z set middle
        int8_t i;
        for (i = 4; i >= 0; i--)
        {
            PORTC &= ~(Z_PIN << i); //Turn on
            _delay_ms(200);
            PORTC |= Z_PIN << i; //Turn off
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
        }
        if (bit_is_clear(PINC, PC5))
        {
            break;
        }
        
        // Split to 4 points at bottom and go seperately into 4 directions
        PORTC &= ~(Z_PIN << 0); //Turn on Z0
        for (i = 3; i < 5; i++)
        {
            uint8_t count = 0;
            while (count < Repeats)
            {
                count++;
                
//                LightOne(k, 3, 0);
//                LightOne(4 - k, 3, 0);
                PORTD = 0b11101100;      //Y set middle
                PORTB |= X_PIN << i;     //Turn on beginning from middle +
                PORTB |= X_PIN << 4 - i; //Turn on beginning from middle -
                _delay_ms(5);
                PORTD = 0b11111100;         //Y turn off middle
                PORTB &= ~(X_PIN << i);     //Turn off
                PORTB &= ~(X_PIN << 4 - i); //Turn off
//                OffOne(k, 3, 0);
//                OffOne(4 - k, 3, 0);

//                LightOne(3, k, 0);
//                LightOne(3, 4 - k, 0);
                PORTB = 0b00100100;         //X set middle
                PORTD &= ~(Y_PIN << i);     //Turn on begginig from +
                PORTD &= ~(Y_PIN << 4 - i); //Turn on begginig from -
                _delay_ms(5);
                PORTB = 0b00100000;      //X turn off middle
                PORTD |= Y_PIN << i;     //Turn off begginig from +
                PORTD |= Y_PIN << 4 - i; //Turn off begginig from -
//                OffOne(3, k, 0);
//                OffOne(3, 4 - k, 0);

                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
            }
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
        }
        if (bit_is_clear(PINC, PC5))
        {
            break;
        }
        // Points run counterclockwise
        //Half rotations
        for (i = 2; i < 5; i++)
        {
            uint8_t count = 0;
            while (count < Repeats)
            {
                count++;

                PORTB = 0b00110000; //X0
                PORTD &= ~(Y_PIN << i);
                _delay_ms(3);
                PORTD |= Y_PIN << i;

                PORTB = 0b00100001; //X4
                PORTD &= ~(Y_PIN << 4 - i);
                _delay_ms(3);
                PORTD |= Y_PIN << 4 - i;
                PORTB = 0b00100000; //Turn off X

                PORTD = 0b11111000; //Y0
                PORTB |= X_PIN << i;
                _delay_ms(3);
                PORTB &= ~(X_PIN << i);

                PORTD = 0b10111100; //Y4
                PORTB |= X_PIN << 4 - i;
                _delay_ms(3);
                PORTB &= ~(X_PIN << 4 - i);
                PORTD = 0b11111100; //Turn off Y

                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
            }
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
        }
        if (bit_is_clear(PINC, PC5))
        {
            break;
        }
        // 3 full counterclockwise rotations
        int8_t j;
        for (j = 0; j < 3; j++)
        {
            int8_t i;
            for (i = 4; i >= 0; i--)
            {
                uint8_t count = 0;
                while (count < Repeats)
                {
                    count++;

                    PORTD = 0b10111100;
                    PORTB |= X_PIN << i;
                    _delay_ms(3);
                    PORTB &= ~(X_PIN << i);

                    PORTD = 0b11111000;
                    PORTB |= X_PIN << 4 - i;
                    _delay_ms(3);
                    PORTB &= ~(X_PIN << 4 - i);

                    PORTD = 0b11111100;

                    PORTB = 0b00110000;
                    PORTD &= ~(Y_PIN << 4 - i);
                    _delay_ms(3);
                    PORTD |= Y_PIN << 4 - i;

                    PORTB = 0b00100001;
                    PORTD &= ~(Y_PIN << i);
                    _delay_ms(3);
                    PORTD |= Y_PIN << i;

                    PORTB = 0b00100000;

                    if (bit_is_clear(PINC, PC5))
                    {
                        break;
                    }
                }
                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
            }
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
        }
        if (bit_is_clear(PINC, PC5))
        {
            break;
        }
        // Points go up
        for (i = 0; i < 5; i++)
        {
            uint8_t count = 0;
            while (count < Repeats)
            {
                count++;

                PORTC &= ~(Z_PIN << i);

                PORTB = 0b00110000;
                PORTD = 0b10111100;
                _delay_ms(3);

                PORTB = 0b00100001;
                PORTD = 0b10111100;
                _delay_ms(3);

                PORTB = 0b00100001;
                PORTD = 0b11111000;
                _delay_ms(3);

                PORTB = 0b00110000;
                PORTD = 0b11111000;
                _delay_ms(3);

                PORTC |= Z_PIN << i;

                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
            }
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
        }
        if (bit_is_clear(PINC, PC5))
        {
            break;
        }
        PORTB = 0b00100000;
        PORTD = 0b11111100;
        PORTC &= ~(Z_PIN << 4);
        for (i = 1; i < 3; i++)
        {
            uint8_t count = 0;
            while (count < 2 * Repeats)
            {
                count++;

                PORTB |= X_PIN << i;
                PORTB |= X_PIN << 4 - i;
                PORTD &= ~(Y_PIN << i);
                PORTD &= ~(Y_PIN << 4 - i);
                _delay_ms(5);
                PORTB &= ~(X_PIN << i);
                PORTB &= ~(X_PIN << 4 - i);
                PORTD |= Y_PIN << 4 - i;
                PORTD |= Y_PIN << i;

                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
            }
            if (bit_is_clear(PINC, PC5))
            {
                break;
            }
        }
    }
}

void CubeExpanding(uint8_t Repeats)
{

    uint8_t CubeSize = 0;
    uint8_t TimeCount = 0;
    uint8_t X = 2, Y = 2, Z = 2; // Middle of Cube
    bool Expands = true, ToggleBit = true;

    while (bit_is_set(PINC, PC5))
    {
        if (Expands && !ToggleBit)
        {
            Expands = false;
        }
        else if (!Expands && ToggleBit)
        {
            Expands = true;
        }
        switch (CubeSize)
        {
        // First expand
        case 0:
            TimeCount = 0;
            PORTB = X_CLEAR;
            PORTD = Y_CLEAR;
            PORTC = Z_CLEAR;
            while (TimeCount < Repeats)
            {
                TimeCount++;
                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }

                LightOne(X, Y, Z);
                _delay_ms(10);
                OffOne(X, Y, Z);
            }
            CubeSize++;
            ToggleBit = true;
            break;
        // Second expand
        case 1:
            TimeCount = 0;
            PORTB = X_CLEAR;
            PORTD = Y_CLEAR;
            PORTC = Z_CLEAR;
            while (TimeCount < Repeats)
            {
                TimeCount++;
                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
                uint8_t i;
                for (i = 1; i < 4; i++)
                {
                    if (bit_is_clear(PINC, PC5))
                    {
                        break;
                    }

                    LightOne(1, 2, 1);
                    LightOne(3, 2, 1);
                    LightOne(1, 2, 3);
                    LightOne(3, 2, 3);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffOne(1, 2, 1);
                    OffOne(3, 2, 1);
                    OffOne(1, 2, 3);
                    OffOne(3, 2, 3);

                    LightOne(i, 1, 1);
                    LightOne(i, 3, 1);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffOne(i, 1, 1);
                    OffOne(i, 3, 1);

                    LightOne(i, 1, 3);
                    LightOne(i, 3, 3);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffOne(i, 1, 3);
                    OffOne(i, 3, 3);

                    LightOne(1, 1, 2);
                    LightOne(1, 3, 2);
                    LightOne(3, 1, 2);
                    LightOne(3, 3, 2);
                    _delay_us(TIMETAKEN_MEDIUM);
                    OffOne(1, 1, 2);
                    OffOne(1, 3, 2);
                    OffOne(3, 1, 2);
                    OffOne(3, 3, 2);
                }
            }
            if (Expands)
                CubeSize++;
            else
                CubeSize--;
            break;
        // Third expand
        case 2:
            TimeCount = 0;
            PORTB = X_CLEAR;
            PORTD = Y_CLEAR;
            PORTC = Z_CLEAR;
            while (TimeCount < Repeats)
            {
                TimeCount++;
                if (bit_is_clear(PINC, PC5))
                {
                    break;
                }
                uint8_t i;
                for (i = 0; i < EDGE; i++)
                {
                    if (bit_is_clear(PINC, PC5))
                    {
                        break;
                    }
                    LightOne(0, i, 0);
                    LightOne(4, i, 0);
                    LightOne(0, i, 4);
                    LightOne(4, i, 4);
                    _delay_us(TIMETAKEN_LOW);
                    OffOne(0, i, 0);
                    OffOne(4, i, 0);
                    OffOne(0, i, 4);
                    OffOne(4, i, 4);

                    LightOne(i, 0, 0);
                    LightOne(i, 4, 0);
                    LightOne(i, 0, 4);
                    LightOne(i, 4, 4);
                    _delay_us(TIMETAKEN_LOW);
                    OffOne(i, 0, 0);
                    OffOne(i, 4, 0);
                    OffOne(i, 0, 4);
                    OffOne(i, 4, 4);

                    LightOne(4, 0, i);
                    _delay_us(1000);
                    OffOne(4, 0, i);

                    LightOne(4, 4, i);
                    _delay_us(TIMETAKEN_LOW);
                    OffOne(4, 4, i);

                    LightOne(0, 0, i);
                    _delay_us(TIMETAKEN_LOW);
                    OffOne(0, 0, i);

                    LightOne(0, 4, i);
                    _delay_us(TIMETAKEN_LOW);
                    OffOne(0, 4, i);
                }
                PORTB = X_CLEAR;
                PORTD = Y_CLEAR;
                PORTC = Z_CLEAR;
            }
            CubeSize--;
            ToggleBit = false;
            break;
        default:
            break;
        }
    }
}