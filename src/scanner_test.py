# AccelRanger
# TESTING CODE

import serial

com_port = '/dev/ttyACM0'
baud_rate = 9600

ser = serial.Serial(com_port, baud_rate, timeout=1)

ser.write(b'\x16T\r') # TURNS ON SCANNER

print("Scanning... Press Ctrl+C to stop.")

try:
    while True:
        if ser.in_waiting > 0:
            barcode_data = ser.readline().decode('utf-8').strip()
            print("Scanned Data:", barcode_data)

except KeyboardInterrupt:
    print("\nStopping...")

ser.write(b'\x16U\r') # TURNS OFF SCANNER
ser.close()
