import serial.tools.list_ports as portlist
import serial
import tkinter as tk
from tkinter import *
from tkinter import ttk
from threading import Thread
import time

serialPort = None
condition = False
stop_threads = False

blink = False
blinkSpeed = 500
ledOn = False
ledLit = True

def display_selection(text, thread):
    # Get the selected value.
    global serialPort, condition, stop_threads
    print(combo.current())
    selection = ports[combo.current()]
    serialPort = serial.Serial(port = ports[combo.current()].device, baudrate=38400, bytesize=8, timeout=1, stopbits=serial.STOPBITS_ONE)
    print("Selected port")
    text.insert(INSERT, "-------------------------------------------------------------\n")
    text.insert(INSERT, f"Connected to {selection} \n")
    text.insert(INSERT, "-------------------------------------------------------------\n")
    text.see("end")
    if not thread.is_alive():
        thread.start()
    stop_threads = False
    
def communication(text):
    global serialPort, stop_threads, blink, blinkSpeed, ledOn, ledLit
    while True:
        if not stop_threads:
            msg = serialPort.readline().decode('utf-8')
            try:
                if int(msg) == 1001:
                    text.insert(INSERT, "Heartbeat Received\n")
                    if blink:
                        command = bytes(f"2001\t{blinkSpeed}\n", 'utf-8')
                        serialPort.write(command)
                        text.insert(INSERT, f"Blinking {blinkSpeed} ms\n")
                        blink = False
                    if ledOn:
                        if ledLit:
                            serialPort.write(b'2002\t0\n')
                            text.insert(INSERT, "Led off\n")
                            ledOn = False
                        else:                        
                            serialPort.write(b'2002\t1\n')
                            text.insert(INSERT, "Led on\n")
                            ledOn = False
                else:
                    text.insert(INSERT, "No hearbeat\n")
            except:
                text.insert(INSERT, "No hearbeat\n")
            text.see("end")

def disconnect(text, thread):
    global serialPort, stop_threads
    stop_threads = True
    serialPort.close()
    text.insert(INSERT, "Disconnected\n")

def blinkLed(speed):
    global blink, blinkSpeed
    blink = True
    blinkSpeed = speed

def toggle_led():
    global ledOn, ledLit
    ledOn = True
    ledLit = not ledLit

# create the root window
root = tk.Tk()
root.title('LedComMaster')
root.resizable(True, True)
root.geometry('800x300')



ports = list(portlist.comports())


text = Text(root, height=10, width=100)
text.pack()

combo = ttk.Combobox(root, values=ports, state = "readonly")
combo.pack()

thread2 = Thread(target = communication, args=(text,))
thread2.daemon = True

button = ttk.Button(root, text="Connect", command=lambda: display_selection(text, thread2))
button.pack()

button2 = ttk.Button(root, text="Disconnect", command=lambda: disconnect(text, thread2))
button2.pack()

inputText = tk.Entry(root)
inputText.insert(0, "500")

button3 = ttk.Button(root, text="Blink", command=lambda: blinkLed(inputText.get()))
button3.pack()

inputText.pack()

button4 = ttk.Button(root, text="Toggle led", command=toggle_led)
button4.pack()

port = ports[combo.current()]

root.mainloop()
