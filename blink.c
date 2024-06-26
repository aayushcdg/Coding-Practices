/*
    Program: wiringPi Basics (blink.c)

    Original Author:  M. Heidenreich, (c) 2021-2022
   Adapted Author : Sabhay Midha , March 2022

    Description: This code is provided in support of the following YouTube tutorial:
                 https://youtu.be/RDAOxX6vqqs

    How to compile: 			gcc -Wall blink.c -lwiringPi -o blink
    How to run compiled program: 	./blink

    This tutorial is an introduction to how to use wiringPi library
	with Raspberry Pi to control LEDs.

    THIS SOFTWARE AND LINKED VIDEO TOTORIAL ARE PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
    ALL WARRANTIES INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
    OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
    NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <wiringPi.h>
#include <signal.h>

#define GREEN 13
#define RED 19
#define BLUE 26
int blink = 1;

void cleanup(int signo) {
    blink = 0;
}

int main(void) {
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);
    signal(SIGHUP, cleanup);

    wiringPiSetupGpio();
    pinMode(GREEN, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);

    while (blink) {
        digitalWrite(GREEN, HIGH);
        delay(500);
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, HIGH);
        delay(500);
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, HIGH);
        delay(500);
        digitalWrite(BLUE, LOW);

    }

    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE,LOW);

    pinMode(GREEN, INPUT);
    pinMode(RED, INPUT);
    pinMode(BLUE, INPUT);

    return 0;
}

