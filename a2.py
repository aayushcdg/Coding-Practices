#!/usr/bin/python3
"""
# Program: LNX255 Assignment 2
# Student: : Aayush Jain
#    Date: April, 2022
"""
from gpiozero import PWMLED, Button
from signal import pause, signal, SIGTERM, SIGHUP
from time import sleep
from threading import Thread
from rpi_lcd import LCD

active = True

leds = [PWMLED(16), PWMLED(20), PWMLED(19), PWMLED(26), PWMLED(21)]

button = Button(13)

lcd = LCD()


def cleanup(signum, frame):
    exit(1)


delay = 0.1


def change_speed():
    global delay
    global message

    if delay < 0.5:
        delay = delay - 0.02
    elif delay >= 0.51:
        delay = 0.1
    speed_message = f"Speed = {100-(delay*1000):.1f} %"
    lcd.text(speed_message, 1)
    brightness_message = f"Brightness = "
    lcd.text(brightness_message, 2)


def show_pattern():
    try:
        while active:
            for num in (0, 1, 2, 3, 4, 3, 2, 1):
                leds[num].on()
                sleep(delay)
                leds[num].off()

    except AttributeError:
        pass


try:
    signal(SIGTERM, cleanup)
    signal(SIGHUP, cleanup)

    button.when_pressed = change_speed
    pattern = Thread(target=show_pattern, daemon=True)
    pattern.start()

    pause()

except KeyboardInterrupt:
    pass

finally:
    active = False
    pattern.join()
    lcd.clear()
    PWMLED.close
    sleep(0.25)
