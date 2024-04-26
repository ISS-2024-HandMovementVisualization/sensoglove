import serial
import requests
from timeit import default_timer as timer
import random

ser = serial.Serial(
    port='COM6',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

count=1

line = ""
sensor_line = None
last_send = timer()

def send(data):
    requests.post("http://192.168.0.145:8080", data=data)

class SerialParser:
    def __init__(self):
        self.line = ""
        self.sensor_line = ""
        self.last_send = timer()
        self.interval_s = 0.1
        self.dry = False

    def advance(self, char):
        self.line += char
        if char == "\n":
            print(self.line)
            if self.line.strip().startswith(">"):
                self.got_sensor_line(self.line)
            self.line = ""

    def got_sensor_line(self, line):
        self.sensor_line = self.process_sensor_line(line)
        print(self.sensor_line)
        elapsed = timer() - self.last_send
        print(elapsed)
        if elapsed >= self.interval_s and self.sensor_line:
            if not self.dry:
                print("sending")
                send(self.sensor_line)
            self.last_send = timer()

    def process_sensor_line(self, line):
        readings =  line.strip().partition(":")[2].strip().split(" ")
        while len(readings) > 4:
            readings += "0"
        return " ".join(readings)


def dummy():
    x1 = random.randint(-10, 90)
    x2 = random.randint(-10, 90)
    x3 = random.randint(-10, 90)
    x4 = random.randint(-10, 90)
    send(f"{x1} {x2} {x3} {x4}")

def main():
    reader = SerialParser()
    try:
        while True:
            for chint in ser.read():
                reader.advance(chr(chint))
    finally:
        ser.close()
if __name__ == "__main__":
    main()