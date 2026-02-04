import serial
from pymodbus.client.sync import ModbusTcpClient
import time

# --- Serial Setup ---
com_port = '/dev/ttyACM0'
baud_rate = 9600
ser = serial.Serial(com_port, baud_rate, timeout=1)
ser.write(b'\x16T\r')

# --- Modbus Setup ---
PLC_IP = '192.168.50.30'
PLC_PORT = 502
client = ModbusTcpClient(PLC_IP, port=PLC_PORT)
if not client.connect():
    print("Failed to connect to PLC")
    exit()

print("Scanning... Press Ctrl+C to stop.")

def string_to_registers(s):
    """
    Convert a string to a list of 16-bit integers (Modbus holding registers)
    Each register holds two ASCII characters.
    """
    if len(s) % 2 != 0:
        s += ' '
    registers = []
    for i in range(0, len(s), 2):
        reg = (ord(s[i]) << 8) + ord(s[i+1])
        registers.append(reg)
    return registers

try:
    while True:
        if ser.in_waiting > 0:
            barcode_data = ser.readline().decode('utf-8').strip()
            print("Scanned Data:", barcode_data)
          
            regs = string_to_registers(barcode_data)

            client.write_registers(0, regs)
            print(f"Sent to PLC Holding Registers: {regs}")

except KeyboardInterrupt:
    print("\nStopping...")

finally:
    ser.write(b'\x16U\r')
    ser.close()
    client.close()
