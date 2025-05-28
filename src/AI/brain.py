from connection import Connection
from commands import *
import logging

class Brain:
    """main class of the AI client
    """
    def __init__(self, data: dict):
        """Brain class constructor

        Args:
            data (dict): dictionnary contains mandatroy values
        """
        self.co = Connection(data["-h"], data["-p"])
        self.team = data["-n"]
        
    def run(self):
        """main loop of the programm
        """
        print(self.co.receive())
        self.co.send(self.team)
        print(self.co.receive())
        
        while True:
            response = look(self.co)
            print(response)