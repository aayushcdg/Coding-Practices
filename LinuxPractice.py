#!/usr/bin/python3


from gpiozero import PWMLED, Button
from signal import pause, signal, SIGTERM, SIGHUP
from time import sleep
from threading import Thread
from rpi_lcd import LCD
from smbus import SMBus
from math import log10

delay = 1
steps = 255
display = 0.2
active = True
running = True
message = " "
fading_factor = (steps * log10(2))/(log10(steps))
leds = (PWMLED(13), PWMLED(19), PWMLED(26), PWMLED(20), PWMLED(21))
button = Button(16)

lcd = LCD()
bus = SMBus(1)


def cleanup(signum, frame):
    exit(1)

ads7830_commands = [0x84, 0xc4, 0x94, 0xa4, 0xe4, 0xb4, 0xf4]

def read_ads7830(input):
    bus.write_byte(0x4b, ads7830_commands[input])
    return bus.read_byte(0x4b)


def change_speed():
    global delay, display
    global message

    if delay >= 0.2 and display<=0.8:
        delay = delay - 0.2
        display = display + 0.2

    elif delay < 0.8:
        delay = 1
        display = 0.2


def show_pattern():
    global delay
    try:
         while active:
            for num in (0, 1, 2, 3, 4, 3, 2, 1):
                brightness = read_ads7830(0)
                leds[num].value = (pow(2, (brightness/fading_factor))-1)/steps
                sleep(delay)
                leds[num].off()
    except AttributeError:
        pass


def lcd_Output_display():
    try:
        while running:
            brightness = read_ads7830(0)
            message = f"Speed :{display*100:0.1f} %"
            lcd.text(message, 1)
            brightness = (brightness*100)/255
            message1 = f"Brightness:{brightness:0.1f}%"
            lcd.text(message1, 2)
            sleep(0.1)

    except AttributeError:
        pass

try:
    signal(SIGTERM, cleanup)
    signal(SIGHUP, cleanup)

    button.when_pressed = change_speed
    reader = Thread(target=show_pattern, daemon=True)
    bright = Thread(target=lcd_Output_display, daemon=True)
    bright.start()
    reader.start()
    pause()

except KeyboardInterrupt:
    pass

finally:
    running = False
    active = False
    lcd.clear()
    bright.join()
    reader.join()
    sleep(0.25)
    leds[0].close()
    leds[1].close()
    leds[2].close()
    leds[3].close()
    leds[4].close()
