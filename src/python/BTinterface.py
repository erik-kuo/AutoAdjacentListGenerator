import BT
import maze

class interface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
        port = input("PC bluetooth port name: ")
        self.ser = BT.bluetooth(port)
        while(not self.ser.do_connect(port)):
            if(port == "quit"):
                self.ser.disconnect()
                quit()
            port = input("PC bluetooth port name: ")
        
    def Arduino_Search(self):
        input("Press enter to start SERACH().")
        self.ser.write('S')

    def Arduino_Adjust_Compass(self):
        input("Press enter to start COMPASS().")
        self.ser.write('A')    

    def Arduino_Hault(self):
        input("Press enter to start HAULT().")
        self.ser.write('H')

    def get_Arduino_msg(self):
        return self.ser.readString()

    def send_dir(self,dirc):
        #PY
        if(dirc==1):
            self.ser.write('n')
        #PX
        elif(dirc==2):
            self.ser.write('e')
        #NX
        elif(dirc==3):
            self.ser.write('w')
        #NY
        elif(dirc==4):
            self.ser.write('s')
        #error
        else:
            print ('Error: An invalid input for action.')

    def end_process(self):
        self.ser.write('H')
        self.ser.disconnect()

'''
if __name__ == "__main__":
    # Please modify the port name.
    arduino = interface()
    bt = BT.bluetooth("COM4")
    while not bt.is_open(): pass
    print("BT Connected!")

    readThread = threading.Thread(target=read)
    readThread.setDaemon(True)
    readThread.start()

    while True:
        msgWrite = input()
        if msgWrite == "exit": sys.exit()
        bt.write(msgWrite)
'''