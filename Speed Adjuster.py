from signal import signal, SIGTERM, SIGHUP, pause
from time import sleep
from threading import Thread
from gpiozero import DistanceSensor, Buzzer
from rpi_lcd import LCD

reading = True
lcd = LCD()
sensor = DistanceSensor(echo=20, trigger=21)
buzzer = Buzzer(24)
breaking_distance = 0.05  # Set breaking distance to 5 cm

def safe_exit(signum, frame):
    exit(1)

def display_distance():
    while reading:
        lcd.text(message, 1)
        sleep(0.25)

def read_distance():
    global message

    while reading:
        distance = sensor.value
        if distance < breaking_distance:
            message = "Distance to next car:"
            lcd.color = [1, 0, 0]  # Set LCD color to red
            lcd.text("BREAKS!", 2)
            buzzer.on()  # Turn on the buzzer
        else:
            message = f"Distance to next car: {distance:1.2f} m"
            lcd.color = [0, 1, 0]  # Set LCD color to green
            lcd.text("", 2)
            buzzer.off()  # Turn off the buzzer

        sleep(0.1)

try:
    signal(SIGTERM, safe_exit)
    signal(SIGHUP, safe_exit)

    reader = Thread(target=read_distance, daemon=True)
    display = Thread(target=display_distance, daemon=True)

    reader.start()
    display.start()

    pause()

except KeyboardInterrupt:
    pass

finally:
    reading = False
    reader.join()
    display.join()
    lcd.clear()
    sensor.close()
    buzzer.close()
