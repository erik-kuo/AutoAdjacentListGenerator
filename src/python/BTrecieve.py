import student

arduino= student.interface()
while True:
	print('get',arduino.wait_for_node())