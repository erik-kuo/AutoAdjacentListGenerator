#############################################################################
## File			[graph.py]
## Author		[Joshua Lin]
## Synopsis		[Classes Node and Graph for AALG]
## Modify		[2020/01/02 Joshua Lin]
#############################################################################
import pandas as pd
Direction = ["PX", "PY", "NX", "NY"]

class Node():
    # Data member for Node:
    # coord 	: a tuple, 		represent the coordinate of the node.
    # dirc 	    : a string, 	represent which direction the car entered the node. (dirc == None for starting node.)
    # explore 	: a dictionary,	represent which direction the car has explored.

    def __init__(self, coord=None, dirc="PX", idx=0):
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
        # Set Node's dirc to explored.
        # A direction of a node is explored when all its successor is explored.
        self.explored[dirc] = True

    def is_explored(self, dirc):
        # Return True if a direction of a node is explored.
        return self.explored[dirc]

    def all_check(self):
        # Retrun if all the direction of a node is explored.
        return all(self.explored.values())

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
        self.car_coord = (0, 0)
        self.car_dir = "PX"
        self.NodeList = {(0, 0): Node()}
        self.idx_count = 1
        self.Adj = pd.DataFrame({}, columns=["PY", "NY", "NX", "PX"])

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
        # change car_coord to the next coordinate.
        new_coord, new_dirc = self.get_next(dirc)

        if new_coord not in self.NodeList:
            self.NodeList[new_coord] = Node(new_coord, new_dirc, self.idx_count)
            self.idx_count += 1

        self.Adj.loc[self.NodeList[self.car_coord].get_idx(), dirc] = self.NodeList[new_coord].get_idx()

        self.car_coord = new_coord
        return True

    def change_dir(self, dirc):
        # Change car_dir to current car direction.
        # Call this function whenever main.py gets the checkline output from car.
        # dirc : PX, PY, NX, or NY
        assert (dirc in Direction)
        self.car_dir = dirc

    def get_nextDir(self):
        # get the next direction the car is going to explore.
        node = self.NodeList[self.car_coord]
        dirc = ''
        if node.all_check():
            dirc = node.get_dirc()
            new_coord, new_dirc = self.get_next(dirc)
            self.NodeList[new_coord].explore(new_dirc)
        else:
            for d in Direction:
                if not node.is_explored(d):
                    dirc = d
                    break
        self.change_dir(dirc)
        return dirc

    def noline(self, dirc):
        # Marked the direction of car_coord as noline. 
        self.NodeList[self.car_coord].explore(dirc)

    def end_explore(self):
        # Return True if explore end.
        return self.NodeList[(0, 0)].all_check()

    def out_file(self):
        # Output adjacent list file. (filename: adj_list.csv)
        DF = self.Adj.rename(columns={"PX": "East", "PY": "North", "NX": "West", "NY": "South"})
        DF.index.name = "index"
        DF.to_csv("../../adj_list.csv")
    
    def print_graph(self):
        # Print the current graph on the terminal.
        print("Car pos: {}:{}, Car dir: {}".format(self.NodeList[self.car_coord].get_idx(), self.car_coord, self.car_dir))
        print(self.Adj)
        print()


if __name__ == "__main__":
    # For debbuging: Explore a imaginary graph by typing if the given direction has a line.
    graph = Graph()
    dirc = 'PX'
    
    graph.print_graph()
    while True:
        msg = input("Line or No line? (y/n): ")
        if msg in 'yn':
            if msg == 'y':
                graph.move(dirc)
            else:
                graph.noline(dirc)
            if graph.end_explore():
                break
            dirc = graph.get_nextDir()
        print("send to car: {}".format(dirc))
        graph.print_graph()
    
    print("End explore!!!")
    graph.print_graph()
    graph.out_file()