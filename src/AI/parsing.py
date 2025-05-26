# -------- parsing function --------------
def parse_args(argv):
    """parse args passed in the execution

    Args:
        argv (tab): all args in the command line 

    Raises:
        Exception: invalid args numbers
        Exception: mandatory values is missing

    Returns:
        args: dictionnary contains all values parsed
    """
    args = {
        "-p": None,
        "-n": None,
        "-h": "localhost"
    }

    if (len(argv) > 2 and (len(argv) - 1) % 2 != 0) or len(argv) > 7:
        raise Exception("invalid args numbers")


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

    if args["-p"] is None or args["-n"] is None:
        raise Exception("mandatory values is missing")
    
    return args