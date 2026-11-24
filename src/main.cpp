/***************************************************************************************

                            a v r _ u a r t

                                                                        қuran nov 2026
**************************************************************************************/
#include <avr/interrupt.h>
#include <avr/io.h>

#define TRUE 1
#define FALSE 0
#define ON_BOARD_LED 0x20
#define KEY 0x01
#define BOUD_RATE_9600 103

volatile int flag;
volatile char recChar;

/******************************************************************
 * PURPOSE: Sends one character via the serial interface.
 * IN: character - Character to be sent.
 * OUT: The character is transmitted via UART.
 * POST: The character has been written to the UART data register.
 ******************************************************************/
static void serial_send(char character)
{
    while ((UCSR0A & (1 << UDRE0)) == 0)
    {
        // Wait until the UART data register is ready.
    }

    UDR0 = character;
}

/******************************************************************
 * PURPOSE: Initializes the ports and the serial interface and
 *          processes received characters.
 * OUT: Start message and received characters via UART.
 * POST: UART communication and LED control are active.
 ******************************************************************/
int main(void)
{
    DDRB = 0xff;
    DDRB &= ~KEY;
    PORTB |= KEY;
    DDRD = 0xfe;
    flag = FALSE;

    UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UBRR0H = 0;
    UBRR0L = BOUD_RATE_9600;

    serial_send('s');
    serial_send('t');
    serial_send('a');
    serial_send('r');
    serial_send('t');
    serial_send('!');

    sei();

    for (;;)
    {
        if (flag)
        {
            flag = FALSE;

            if (recChar == 'x')
            {
                PORTB ^= ON_BOARD_LED;
            }

            serial_send(recChar);
        }
    }
}

/******************************************************************
 * PURPOSE: Handles the completion of a UART transmission.
 ******************************************************************/
ISR(USART_TX_vect)
{
    // do nothing
}

/******************************************************************
 * PURPOSE: Receives one character via UART.
 * IN: Received character from the UART data register UDR0.
 * OUT: The character is stored in recChar.
 * POST: recChar contains the received character and flag is TRUE.
 ******************************************************************/
ISR(USART_RX_vect)
{
    recChar = UDR0;
    flag = TRUE;
}

/*
 * The same program using the Arduino framework:
 *
 * #include <Arduino.h>
 *
 * bool ledState = LOW;
 *
 * void setup()
 * {
 *     pinMode(LED_BUILTIN, OUTPUT);
 *     Serial.begin(9600);
 *     Serial.print("start!");
 * }
 *
 * void loop()
 * {
 *     if (Serial.available() > 0)
 *     {
 *         const char receivedCharacter = Serial.read();
 *
 *         if (receivedCharacter == 'x')
 *         {
 *             ledState = !ledState;
 *             digitalWrite(LED_BUILTIN, ledState);
 *         }
 *
 *         Serial.write(receivedCharacter);
 *     }
 * }
 */
