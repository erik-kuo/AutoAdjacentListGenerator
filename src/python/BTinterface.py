import BT
import maze

class interface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
        self.ser = BT.bluetooth()
        port = input("PC bluetooth port name: ")
        while(not self.ser.do_connect(port)):
            if(port == "quit"):
                self.ser.disconnect()
                quit()
            port = input("PC bluetooth port name: ")
        input("Press enter to start.")
        self.ser.SerialWrite('s')

    def wait_for_Arduino(self):
        return self.ser.SerialReadByte()

    def send_action(self,dirc):
        #if(dirc == maze.Action.ADVANCE):
        if(dirc==1):
            self.ser.SerialWrite('f')
                #elif(dirc == maze.Action.U_TURN):
        elif(dirc==2):
            self.ser.SerialWrite('b')
                #elif(dirc == maze.Action.TURN_RIGHT):
        elif(dirc==3):
            self.ser.SerialWrite('r')
                #elif(dirc == maze.Action.TURN_LEFT):
        elif(dirc==4):
            self.ser.SerialWrite('l')
                #elif(dirc == maze.Action.HALT):
        elif(dirc==5):
            self.ser.SerialWrite('h')
        else:
            print ('Error: An invalid input for action.')

    def end_process(self):
        self.ser.SerialWrite('e')
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