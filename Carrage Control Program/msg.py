import socket
import queue
import threading
import json
import time
#testing ip: 10.126.124.75

MCP = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ESP = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ESP.bind(('', 3009))
#ESP.settimeout(2);
MCPadd = ("localhost", 2001)
##MCP.connect(MCPadd)

ESPadd = ''
MCPQ = queue.Queue()
ESPQ = queue.Queue()

ESPdict = {"speed": 50, "doors": 1, "message": ""}

def MCPread():
    while True:
        y = MCP.recv(1024)
        if y != '':
            MCPQ.put(y)
            MCPQ.task_done()
            print("rec from MCP")

def MCPsend():
    while True:
        obj = {"client_type" "ccp", "message": "CCIN", "client_id": 1}
        jsonobj = json.dumps(obj)
        MCP.sendto(jsonobj.encode(), MCPadd)
        time.sleep(2)
    
            
def ESPread():
    global ESPadd
    msg = "nothing"
    if ESPadd == '':
        msg, ESPadd = ESP.recvfrom(1024)
    else:
        msg, ESPadd = ESP.recvfrom(1024)
    print(msg)
    
    
def ESPsend():
    while True:
        if ESPQ.empty() == False:
            if ESPadd != '':
                ESP.sendto(json.dumps(ESPQ.get()).encode(), ESPadd)
                print("sent to ESP", ESPadd)

    
##threading.Thread(target = MCPread).start()
##threading.Thread(target = MCPsend).start()
threading.Thread(target = ESPsend).start()
threading.Thread(target = ESPread).start()


while(True):
    x = input("to ESP")
    y = x.split()
    print(y)
    if len(y) == 2: ## Verify that input is valid
        if y[0] == "speed":
            ESPdict["speed"] = int(y[1])

        if y[0] == "doors":
            ESPdict["doors"] = int(y[1])

    ESPQ.put(ESPdict)
    ESPQ.task_done()
    continue
