import logging
import socket

class Connection:
    """the following class handle all connection features with the socket library
    """
    def __init__(self, host: str, port: int):
        self.sock: socket = socket.create_connection((host, port))
        self.sock.setblocking(True)
        logging.info(f"successfully connected to the server {host} on port {port}")
        
    def send(self, message: str):
        self.sock.sendall((message.strip() + '\n').encode())
        logging.info(f"successfully send the following message on the server: {message}")
    
    def receive(self):
        logging.info("successfully receive a message from the server")
        return self.sock.recv(4096).decode()