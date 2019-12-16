Direction = ["PX", "PY", "NX", "NY"]

class Node():
	## Data member for Node: 
	## coord 	: a tuple, 		represent the coordinate of the node.
	## dirc 	: a string, 	represent which direction the car entered the node. (dirc == None for starting node.)
	## explore 	: a dictionary,	represent which direction the car has explored.

	def __init__(self, coord = None, dirc = "PX"):
		if last_coord == None:
			self.init_start()
		else:
			self.coord = coord
			self.dirc = dirc
			self.init_explore()

	def init_start(self):
		self.coord = (0, 0)
		self.dirc = None
		self.explore = {"PX": False, "PY": False, "NX": False, "NY": False}

	def init_explore(self):
		self.explore = {"PX": False, "PY": False, "NX": False, "NY": False}
		self.explore[self.dirc] = True

	def explore(self, dirc):
		self.explore[dirc] = True

	def is_explored(self, dirc):
		return self.explore[dirc]

	def all_check(self):
		return all(self.explore)

	def is_start(self):
		return (self.dirc == None)

	def get_coord(self):
		return self.coord

	def get_dirc(self):
		return self.dirc

class Graph():
	def __init__(self):
		self.car_coord = (0,0)
		self.car_dir = "PX"
		self.NodeList = {(0,0): Node()}

	def add_nextNode(self):
		## add a node to the graph.
		new_coord = list(self.car_coord)
		if self.car_dir == "PX":
			new_coord[0] += 1
			new_dirc = "NX"
		elif self.car_dir == "PY":
			new_coord[1] += 1
			new_dirc = "NY"
		elif self.car_dir == "NX":
			new_coord[0] -= 1
			new_dirc = "PX"
		elif self.car_dir == "NY":
			new_coord[1] -= 1
			new_dirc = "PY"
			return False

		new_coord = tuple(new_coord)

		if new_coord in self.NodeList:
			print("ERROR: Node already exist!")
			return False

		self.NodeList[new_coord] = Node(new_coord, new_dirc)
		self.car_coord = new_coord
		return True

	def change_dir(self, dirc):
		## Change car_dir to current car direction.
		## Call this function whenever main.py gets the checkline output from car.
		## dirc : PX, PY, NX, or NY
		assert (dirc in Direction)
		self.car_dir = dirc

	def get_nextDir(self):
		node = self.NodeList[self.coord]
		if node.all_check():
			return node.get_dirc()
		
		for dirc in Direction:
			if !node.is_explored(dirc):
				node.explored(dirc)
				return dirc