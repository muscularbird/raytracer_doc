import pytest
from src.AI.parsing import parse_args

def test_valid_args():
    argv = ["zappy_ai", "-p", "8080", "-n", "team"]
    expected = {"-p": 8080, "-n": "team", "-h": "localhost"}
    assert parse_args(argv) == expected

def test_valid_args_with_host():
    argv = ["zappy_ai", "-p", "8080", "-n", "team", "-h", "127.0.0.1"]
    expected = {"-p": 8080, "-n": "team", "-h": "127.0.0.1"}
    assert parse_args(argv) == expected

def test_missing_port():
    argv = ["zappy_ai", "-n", "team"]
    with pytest.raises(Exception, match="mandatory values is missing"):
        parse_args(argv)

def test_invalid_arg_count():
    argv = ["zappy_ai", "-p", "8080", "-n"]
    with pytest.raises(Exception, match="invalid args numbers"):
        parse_args(argv)
