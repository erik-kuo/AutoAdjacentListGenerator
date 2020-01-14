#############################################################################
## File			[graph.py]
## Author		[Joshua Lin]
## Synopsis		[Example code for Classes Node and Graph for AALG]
## Modify		[2020/01/14 Joshua Lin]
#############################################################################

class Node():
    # Data member for Node:
    # coord 	: a tuple, 		represent the coordinate of the node.
    # dirc 	    : a string, 	represent which direction the car entered the node. (dirc == None for starting node.)
    # explore 	: a dictionary,	represent which direction the car has explored.

    def __init__(self, coord, dirc, idx):
        ...
        ...

    def explore(self, dirc):
        # Set Node's dirc to explored.
        ...

    def is_explored(self, dirc):
        # Return True if a direction of a node is explored.
        return ...

    def all_check(self):
        # Retrun if all the direction of a node is explored.
        return ...


class Graph():
    def __init__(self):
        self.NodeList = {(0, 0): Node()}  # initially there's a starting node in the NodeList
        ...
        ...

    def move(self, dirc):
        # move the car to the next coordinate.
        new_dirc = ...
        ...
        ...
        if new_coord not in self.NodeList:
            self.NodeList[new_coord] = Node(new_coord, ...)  # Create a new node in the NodeList
        
        self.car_coord = new_coord

    def get_nextDir(self):
        # get the next direction the car is going to explore.
        dirc = ''
        ...
        ...

        return dirc

    def noline(self, dirc):
        # Mark the direction of current car coordinate as noline.
        ...

    def end_explore(self):
        # Return True if explore ends.
        return ...

    def out_file(self):
        # Output adjacent list file.
        ...
        ...