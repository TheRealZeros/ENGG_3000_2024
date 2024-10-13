import socket
import queue
import threading
import json

MCP = socket.create_connection(("127.0.0.1", 25565))
ESP = socket.create_connection(("localhost", 25566))

MCPQ = queue.Queue()
ESPQ = queue.Queue()

def MCPread():
    while True:
        y = MCP.recv(250)
        if y != '':
            MCPQ.put(y)
            MCPQ.task_done()
            print("rec from MCP")

#def MCPsend():
    
#def ESPread():
    
def ESPsend():
    while True:
        if ESPQ.empty() == False:
            ESP.send(ESPQ.get())
            print("sent to ESP")
        
        
    
threading.Thread(target = MCPread).start()
threading.Thread(target = ESPsend).start()

while(True):
    ESPQ.put(MCPQ.get())
    ESPQ.task_done()
