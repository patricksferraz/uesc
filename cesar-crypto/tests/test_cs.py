from cesar_cipher.cs import cesar


def test_cesar():
    assert "d" == cesar("a", "e")
    assert "a" == cesar("d", "d")
    assert "def" == cesar("abc", "e")
    assert " " == cesar(" ", "d")
    assert "$" == cesar("$", "d")
    assert "123$&@" == cesar("123$&@", "e", 5)
