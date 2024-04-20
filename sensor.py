#!/usr/bin/python3

"""
    Program: HC-SR04 Sensor Demo (sensor.py)
    Author:  M. Heidenreich, (c) 2020
    Adapted by: Sabhay Midha, APRIL 2022
    Description:

    This code is provided in support of the following YouTube tutorial:
    https://youtu.be/JvQKZXCYMUM

    This example shows how to use the HC-SR04 sensor to activate a buzzer
    with Raspberry Pi.

    THIS SOFTWARE AND LINKED VIDEO TOTORIAL ARE PROVIDED "AS IS" AND THE
    AUTHOR DISCLAIMS ALL WARRANTIES INCLUDING ALL IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
"""

from signal import signal, SIGTERM, SIGHUP, pause
from time import sleep
from gpiozero import DistanceSensor, Buzzer, Device, RGBLED
from gpiozero.pins.pigpio import PiGPIOFactory
from threading import Thread

Device.pin_factory = PiGPIOFactory()

reading = True
sensor = DistanceSensor(echo=20, trigger=21)
buzzer = Buzzer(24)
led = RGBLED(13, 19, 26)


def safe_exit(signum, frame):
    exit(1)


def read_sensor():
    global message

    while reading:
        message = f"Distance: {sensor.value*100:.2f} cm"
        print(message)

        if sensor.value > 0.3:
            led.color = (1, 0, 0)
            buzzer.off()
        elif sensor.value > 0.08:
            led.color = (0, 1, 0)
            buzzer.beep(0.05, 0.05)
        else:
            led.color = (0, 0, 1)
            buzzer.on()
        sleep(0.1)


try:
    signal(SIGTERM, safe_exit)
    signal(SIGHUP, safe_exit)

    reader = Thread(target=read_sensor, daemon=True)
    reader.start()

    pause()

except KeyboardInterrupt:
    pass

finally:
    reading = False
    sensor.close()
    buzzer.close()
    led.close()
