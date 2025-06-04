from connection import Connection

def look(conn: Connection):
    """send look command to the server
    Args:
        conn (_type_): connection socket to the server
    """
    
    conn.send("Look")
    raw: str = conn.receive().strip()
    
    if "dead" in raw:
        return None
        
    if raw.startswith("[") and raw.endswith("]"):
        raw = raw[1:-1]
    else:
        return []
    
    tiles = [tile.strip() for tile in raw.split(',')]
    parsed = [tile.split() if tile else [] for tile in tiles]
    
    index = 0
    result = []
    
    for tile in parsed:
        result.append({index: tile})
        index += 1
    
    return result
    
    
def inventory(conn: Connection):
    """send inventory command to the server

    Args:
        conn (Connection): connection class

    Returns:
        None: if the command deosn't work
        raw: the content of the inventory
    """
    conn.send("Inventory")
    raw: str = conn.receive().strip()
    
    if "ko" in raw:
        return None
    return raw

def forward(conn: Connection):
    """_summary_

    Args:
        conn (Connection): _description_
    """
    conn.send("Forward")
    raw: str = conn.receive().strip()
    
    return raw