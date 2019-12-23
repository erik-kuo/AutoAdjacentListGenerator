import BTinterface
import graph

bt = BTinterface()
graph = Graph()
dirc = 'PX'
############



##############
while True:
	msg = bt.get_Arduino_msg()
	if msg in 'LN':
		if msg == 'L':
			graph.move(dirc)
		else :
			graph.noline(dirc)
		dirc = graph.get_nextDir()
	bt.send_dir(dirc)