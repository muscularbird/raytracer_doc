#!/usr/bin/env python3

import logging
from sys import argv, exit


# -------------------- logging configuration --------------------
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[logging.FileHandler("src/AI/zappy_ai.log")]
)

args = {
    "-p": None,
    "-n": None,
    "-h": "localhost"
}

# -------------------- usage function --------------------
def usage():
    print("USAGE: ./zappy_gui -p port -h machine")
    logging.warning("Invalid execution, read the usage guide on the standard output")
    logging.info("----------- AI ENDS -----------")    
    return 1


def main():
    
    try:
        logging.info("----------- AI STARTS -----------")
        if len(argv) <= 1 or (len(argv) == 2 and argv[1] == "--help"):
            return usage()
        
        if (len(argv) > 2 and (len(argv) - 1) % 2 != 0) or len(argv) > 7:
            raise Exception("invalid args numbers")
        logging.info("----------- AI ENDS SUCCESSFULLY -----------")
        
        for i in range(len(argv)):
            if argv[i] == "-p":
                n = int(argv[i + 1])
                args["-p"] = n
                continue
            if argv[i] == "-n":
                s = str(argv[i + 1])
                args["-n"] = s
                continue
            if argv[i] == "-h":
                m = str(argv[i + 1])
                args["-h"] = m
                continue
        
        for x, y in args.items():
            print(x, y)   
        return 0
    except Exception as e:
        logging.error(f"Exception raised: {e}")
        logging.critical("----------- AI ENDS WITH ERRORS -----------")
        return 84

if __name__ == "__main__":
    exit(main())
