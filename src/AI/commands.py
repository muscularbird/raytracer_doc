from connection import Connection

def look(conn: Connection):
    """send look command to the server
    Args:
        conn (_type_): connection socket to the server
    """
    
    conn.send("Look")
    raw: str = conn.receive().strip()
    
    if raw.startswith("[") and raw.endswith("]"):
        raw = raw[1:-1]
    else:
        return []
    
    tiles = [tile.strip() for tile in raw.split(',')]
    parsed = [tile.split() if tile else [] for tile in tiles]
    
    return parsed
    