import serial
import requests
from timeit import default_timer as timer

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

# requests.post("http://192.168.0.145:8080", data="aaaa")
# exit()

class Sender:
    def __init__(self):
        self.line = ""
        self.sensor_line = ""
        self.last_send = timer()
        self.interval_s = 5
        self.dry = True

    def advance(self, char):
        self.line += char
        if char == "\n":
            if self.line.strip().startswith("R"):
                self.got_sensor_line(self.line)
            self.line = ""

    def got_sensor_line(self, line):
        self.sensor_line = self.process_sensor_line(line)
        print(self.sensor_line)
        elapsed = timer() - self.last_send
        if elapsed >= self.interval_s and sensor_line:
            if not self.dry:
                requests.post("http://192.168.0.145:8080", data=sensor_line)
            self.last_send = timer()

    def process_sensor_line(self, line):
        line =  line.strip().partition(":")[2].strip()
        return f"{line} 0 0 0"

sender = Sender()

try:
    while True:
        for chint in ser.read():
            sender.advance(chr(chint))
except KeyboardInterrupt:
    ser.close()
