from machine import lightsleep, deepsleep, Pin
import time

led = Pin(25, Pin.OUT)

led.value(1)
time.sleep(5)
led.value(0)
time.sleep(15)

def blink():
    led.toggle()
    time.sleep(0.5)
    
for _ in range(6):
    blink()

lightsleep(15000)
led.value(1)

time.sleep(5)

for _ in range(5):
    blink()
    
deepsleep(15000)
led.value(1)


