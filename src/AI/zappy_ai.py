#!/usr/bin/env python3

import logging
from sys import argv, exit
from parsing import parse_args



logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[logging.FileHandler("src/AI/zappy_ai.log")]
)


# -------------------- usage function --------------------
def usage():
    """print the usage guide of the binary

    Returns:
        1: return value if the user execute the binary badly
    """
    print("USAGE: ./zappy_gui -p port -h machine")
    logging.warning("Invalid execution, read the usage guide on the standard output")
    logging.info("----------- AI ENDS -----------")    
    return 1


# ------------------- main function -------------------------
def main():
    """main function

    Returns:
        0: successfull execution
        1: usage displaying
        84: exception raised among the code
    """
    try:
        logging.info("----------- AI STARTS -----------")
        if len(argv) <= 1 or (len(argv) == 2 and argv[1] == "--help"):
            return usage()
        
        values = parse_args(argv)
        print(values)
        logging.info("----------- AI ENDS SUCCESSFULLY -----------")
        return 0
    except Exception as e:
        logging.error(f"Exception raised: {e}")
        logging.critical("----------- AI ENDS WITH ERRORS -----------")
        return 84


# ----------------------- entrypoint ---------------------
if __name__ == "__main__":
    exit(main())
