#############################################################################
## File			[BTinterface.py]
## Author		[Erik Kuo]
## Synopsis		[bluetooth interface with Arduino]
## Modify		[2019/12/16 Erik Kuo]
#############################################################################

import BT

class interface:
	def __init__(self):
		print("")
		print("Arduino Bluetooth Connect Program.")
		print("")
		# input the COM port from keyboard
		port = input("PC bluetooth port name: ")
		self.ser = BT.bluetooth(port)
		while(not self.ser.do_connect(port)):
			if(port == "quit"):
				self.ser.disconnect()
				quit()
			port = input("PC bluetooth port name: ")
		print('Bluetooth connected!')
		print('')
	
	# sending change state cmd    
	def Arduino_Search(self):
		input("Press enter to start SERACH().")
		self.ser.write('S')

	def Arduino_Adjust_Compass(self):
		input("Press enter to start COMPASS().")
		self.ser.write('A')
		print('Auto change to HAULT() when finished')

	def Arduino_Hault(self):
		input("Press enter to start HAULT().")
		self.ser.write('H')

	# get msg from Arduino::checkLine()
	def get_Arduino_msg(self):
		while True:
			if self.ser.waiting():
				msg = self.ser.readString()
				msg = msg[:-1]
				print('Get msg: ', msg, 'from Arduino.')
				return msg
		
	# sending dirction 
	def send_dir(self,dirc):
		#PY
		if(dirc=="PY"):
			input("Press enter to send PY.")
			self.ser.write('n')
		#PX
		elif(dirc=="PX"):
			input("Press enter to send PX.")
			self.ser.write('e')
		#NX
		elif(dirc=="NX"):
			input("Press enter to send NX.")
			self.ser.write('w')
		#NY
		elif(dirc=="NY"):
			input("Press enter to send NY.")
			self.ser.write('s')
		#error
		else:
			print ('Error: An invalid input for action.')

	# end process and let Arduino stay Hault
	def end_process(self):
		self.ser.write('H')
		self.ser.disconnect()