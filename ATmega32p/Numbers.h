#ifndef NUMBERS
#define NUMBERS

#include <avr/io.h>
#include <util/delay.h>

#define X_PIN 0b00000001
#define Y_PIN 0b00000100
#define Z_PIN 0b00000001

void Number0(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11101100;
        PORTC = 0b00101110;

        _delay_ms(3);

        PORTD = 0b11010100;
        PORTC = 0b00110101;

        _delay_ms(3);

        PORTD = 0b11010100;
        PORTC = 0b00111011;

        _delay_ms(3);

        PORTB &= ~(X_PIN << X);
    }
}

void Number1(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X;    //X
        PORTC = 0b00100000;     //Z
        PORTD &= ~(Y_PIN << 3); //Y

        _delay_ms(5);

        PORTD = 0b11100111;
        PORTC = 0b00110111;

        _delay_ms(5);

        PORTD = 0b11111111;
        PORTC = 0b00111111;
        PORTB &= ~(X_PIN << X);
    }
}

void Number2(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11000100;
        PORTC = 0b00111110;

        _delay_ms(2);

        PORTD = 0b11110100;
        PORTC = 0b00111101;

        _delay_ms(2);

        PORTD = 0b11101100;
        PORTC = 0b00111011;

        _delay_ms(2);

        PORTD = 0b11010100;
        PORTC = 0b00110111;

        _delay_ms(2);

        PORTD = 0b11001100;
        PORTC = 0b00101111;

        _delay_ms(2);

        PORTB &= ~(X_PIN << X);
    }
}

void Number3(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11000100;
        PORTC = 0b00101110;

        _delay_ms(3);

        PORTD = 0b11011100;
        PORTC = 0b00110101;

        _delay_ms(3);

        PORTD = 0b11001100;
        PORTC = 0b00111011;

        _delay_ms(3);

        PORTB &= ~(X_PIN << X);
    }
}

void Number4(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11011100;
        PORTC = 0b00111110;

        _delay_ms(2);

        PORTD = 0b11011100;
        PORTC = 0b00111101;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00111011;

        _delay_ms(2);

        PORTD = 0b11001100;
        PORTC = 0b00110111;

        _delay_ms(2);

        PORTD = 0b11011100;
        PORTC = 0b00101111;

        _delay_ms(2);

        PORTB &= ~X_PIN << X;
    }
}

void Number5(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11100100;
        PORTC = 0b00111110;

        _delay_ms(2);

        PORTD = 0b11011100;
        PORTC = 0b00111101;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00111011;

        _delay_ms(2);

        PORTD = 0b11110100;
        PORTC = 0b00110111;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00101111;

        _delay_ms(2);

        PORTB &= ~(X_PIN << X);
    }
}

void Number6(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11101100;
        PORTC = 0b00111110;

        _delay_ms(2);

        PORTD = 0b11010100;
        PORTC = 0b00111101;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00111011;

        _delay_ms(2);

        PORTD = 0b11110100;
        PORTC = 0b00110111;

        _delay_ms(2);

        PORTD = 0b11001100;
        PORTC = 0b00101111;

        _delay_ms(2);

        PORTB &= ~(X_PIN << X);
    }
}

void Number7(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11110100;
        PORTC = 0b00111110;

        _delay_ms(2);

        PORTD = 0b11110100;
        PORTC = 0b00111101;

        _delay_ms(2);

        PORTD = 0b11101100;
        PORTC = 0b00111011;

        _delay_ms(2);

        PORTD = 0b11011100;
        PORTC = 0b00110111;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00101111;

        _delay_ms(2);

        PORTB &= ~(X_PIN << X);
    }
}

void Number8(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11000100;
        PORTC = 0b00101110;

        _delay_ms(3);

        PORTD = 0b11010100;
        PORTC = 0b00110101;

        _delay_ms(3);

        PORTD = 0b11000100;
        PORTC = 0b00111011;

        _delay_ms(3);

        PORTB &= ~(X_PIN << X);
    }
}

void Number9(uint8_t X, int time)
{
    int i;
    for (i = 0; i < time; i++)
    {
        PORTB |= X_PIN << X; //X
        PORTD = 0b11000100;
        PORTC = 0b00111110;

        _delay_ms(2);

        PORTD = 0b11011100;
        PORTC = 0b00111101;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00111011;

        _delay_ms(2);

        PORTD = 0b11010100;
        PORTC = 0b00110111;

        _delay_ms(2);

        PORTD = 0b11000100;
        PORTC = 0b00101111;

        _delay_ms(2);

        PORTB &= ~(X_PIN << X);
    }
}

#endif