import BTinterface
import graph

bt = BTinterface.interface()
graph = graph.Graph()
dirc = 'PX'

####### state changing part #######

# start with hault state
# adjust compass
bt.Arduino_Adjust_Compass()
# will come back to hault state

# start search state
bt.Arduino_Search()

####### main explore part #######

while True:
	bt.send_dir(dirc)
	msg = bt.get_Arduino_msg()
	if msg in 'LN':
		if msg == 'L':
			graph.move(dirc)
		elif msg == 'N':
			graph.noline(dirc)
		if graph.end_explore():
			   break
		dirc = graph.get_nextDir()
	graph.print_graph()

####### output graph #######

print("End explore!!!")
bt.end_process()
graph.print_graph()
graph.out_file()

####### end of programm #######
