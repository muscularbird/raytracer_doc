import logging
from connection import Connection

class Navigator:
    """A helper class to compute directions to a target tile in the
    field of vision and move the same target properly
    """
    
    def __init__(self, conn, level=1):
        self.conn: Connection = conn
        self.level: int = level
        
    def get_tile_map(self, look):
        vision = []
        index = 0
        
        for tile in look:
            vision.append({index: tile})
            index += 1
        return vision