Direction = ["PX", "PY", "NX", "NY"]

class Node():
	## Data member for Node: 
	## coord 	: a tuple, 		represent the coordinate of the node.
	## dirc 	: a string, 	represent which direction the car entered the node. (dirc == None for starting node.)
	## explore 	: a dictionary,	represent which direction the car has explored.

	def __init__(self, coord = None, dirc = "PX", idx = 0):
		if coord == None:
			self.init_start()
		else:
			self.coord = coord
			self.dirc = dirc
			self.init_explore()
		self.idx = idx

	def init_start(self):
		self.coord = (0, 0)
		self.dirc = None
		self.explored = {"PX": False, "PY": False, "NX": False, "NY": False}

	def init_explore(self):
		self.explored = {"PX": False, "PY": False, "NX": False, "NY": False}
		self.explored[self.dirc] = True

	def explore(self, dirc):
		self.explored[dirc] = True

	def is_explored(self, dirc):
		return self.explored[dirc]

	def all_check(self):
		return all(self.explore)

	def is_start(self):
		return (self.dirc == None)

	def get_coord(self):
		return self.coord

	def get_dirc(self):
		return self.dirc

	def get_idx(self):
		return self.idx

class Graph():
	def __init__(self):
		self.car_coord = (0,0)
		self.car_dir = "PX"
		self.NodeList = {(0,0): Node()}
		self.idx_count = 1
		## self.Adj = 

	def get_next(self, dirc):
		new_coord = list(self.car_coord)
		if dirc == "PX":
			new_coord[0] += 1
			new_dirc = "NX"
		elif dirc == "PY":
			new_coord[1] += 1
			new_dirc = "NY"
		elif dirc == "NX":
			new_coord[0] -= 1
			new_dirc = "PX"
		elif dirc == "NY":
			new_coord[1] -= 1
			new_dirc = "PY"
		else:
			return False
		new_coord = tuple(new_coord)
		return new_coord, new_dirc

	def move(self, dirc):
		## change car_coord to the next coordinate.
		new_coord, new_dirc = self.get_next(dirc)
		
		if new_coord not in NodeList:
			self.NodeList[new_coord] = Node(new_coord, new_dirc, self.idx_count)
			self.idx_count += 1
		## TODO: link two nodes in csv

		self.car_coord = new_coord
		return True

	def change_dir(self, dirc):
		## Change car_dir to current car direction.
		## Call this function whenever main.py gets the checkline output from car.
		## dirc : PX, PY, NX, or NY
		assert (dirc in Direction)
		self.car_dir = dirc

	def get_nextDir(self):
		node = self.NodeList[self.car_coord]
		if node.all_check():
			dirc = node.get_dirc()
			new_coord, new_dirc = self.get_next(dirc)
			self.NodeList[new_coord].explore(new_dirc)
		else:
			for d in Direction:
				if !node.is_explored(dirc):
					dirc = d
					break
		self.change_dir(dirc)
		return dirc

	def noline(self, dirc):
		self.NodeList[self.car_coord].explore(dirc)

	def end_explore(self):
		return self.NodeList[(0,0)].all_check()
