import logging
from connection import Connection

class Navigator:
    """A helper class to compute directions to a target tile in the
    field of vision and move the same target properly
    """
    
    def __init__(self, conn, level=1):
        self.conn: Connection = conn
        self.level: int = level
        
    def find_object(self, vision: list, object: str="food"):
        for tile in vision:
            if object in tile:
                print("oui")
    
    def choose_direction(self, vision):
        self.find_object(vision)