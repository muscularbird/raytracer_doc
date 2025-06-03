from navigator import Navigator
from commands import *
from statics import CRITICAL_FOOD_AMOUNT
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
        self.nav = Navigator(self.co)
        self.state = "explore"
        
    def act(self, state, pos):
        if state == "survive":
            logging.info("critical food amount, seeking food")
            
        
    def tiles_with_food(self, response):
        for i, tile in enumerate(response):
            if "food" in tile:
                return i
        return -1
    
    def food_amount(self, inv):
        for item in inv.strip()[1:-1].split(','):
            if "food" in item:
                return int(item.split()[1])
        return 0
        
    def run(self):
        """main loop of the programm
        """
        print(self.co.receive())
        self.co.send(self.team)
        print(self.co.receive())
        
        self.co.send("Inventory")
        print(self.co.receive())
        while True:
            # ----- look cmd -----
            
            response = look(self.co)
            inv = inventory(self.co)
            logging.info("------ look response ------")
            logging.info(response)
            logging.info("------ inventory content ------")
            logging.info(inv)
            
            if response is None or inv is None:
                break
            
            food_nb = self.food_amount(inv)
            food_pos = self.tiles_with_food(response)
            
            if food_nb < CRITICAL_FOOD_AMOUNT:
                self.state = "survive"
            elif food_pos == 0:
                self.state = "take_food"
            elif food_pos > 0:
                self.state = "go_to_food"
            else:
                self.state = "explore"
            
            print(food_nb)
            print(self.nav.get_tile_map(response))