import BTinterface

arduino= BTinterface.interface()
while True:
	print('get',arduino.get_Arduino_msg())