#!/usr/bin/python3

"""
    Program: GPIO Programming Basics (blink.py)

    Original Author:  M. Heidenreich, (c) 2020-2022
    Adapted by: Aayush Jain, March 2022
    Description: This code is provided in support of the following YouTube tutorial:
                 https://youtu.be/7NzbZaX5MAA

    This tutorial is demonstrates how to how to control LEDs
	using Python3 and gpiozero on Raspberry Pi.

    THIS SOFTWARE AND LINKED VIDEO TOTORIAL ARE PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
    ALL WARRANTIES INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
    OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
    NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
"""

from gpiozero import LED
from signal import pause
from time import sleep

led1 = LED(16)
led2 = LED(20)
led3 = LED(21)

try:
    led1.blink(1,3)
    sleep(1)
    led2.blink(1,1)
    sleep(1)
    led3.blink(1,3)
    sleep(1)


    pause()

except KeyboardInterrupt:
    pass
