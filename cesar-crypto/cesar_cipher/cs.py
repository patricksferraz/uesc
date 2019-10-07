import sys
from datetime import datetime
from io import open
from itertools import repeat

_ALPHABET = (
    ("a", "A"),
    ("b", "B"),
    ("c", "C"),
    ("d", "D"),
    ("e", "E"),
    ("f", "F"),
    ("g", "G"),
    ("h", "H"),
    ("i", "I"),
    ("j", "J"),
    ("k", "K"),
    ("l", "L"),
    ("m", "M"),
    ("n", "N"),
    ("o", "O"),
    ("p", "P"),
    ("q", "Q"),
    ("r", "R"),
    ("s", "S"),
    ("t", "T"),
    ("u", "U"),
    ("v", "V"),
    ("w", "W"),
    ("x", "X"),
    ("y", "Y"),
    ("z", "Z"),
)
_key = 3


def _encrypt(char: str, key: int = _key) -> str:
    """Encrypt character using Cesar cipher with the key.
    By default, the key is 3

    Parameters
    ----------
    char : str
        Character to encrypt.
    key : int
        Key to encrypt.

    Returns
    -------
    str
        Character encrypted.

    """
    try:
        lw = char.lower()
        up = char.upper()

        pos_e = _ALPHABET.index((lw, up))
        pos_i = _ALPHABET[pos_e].index(char)

    except ValueError:
        return char
    else:
        n_pos = (pos_e + key) % len(_ALPHABET)
        return _ALPHABET[n_pos][pos_i]


def _decrypt(char: str, key: int = _key) -> str:
    """Decrypt character using Cesar cipher with the key.
    By default, the key is 3

    Parameters
    ----------
    char : str
        Character to decrypt.
    key : int
        Key to decrypt.

    Returns
    -------
    str
        Character decrypted.

    """
    try:
        lw = char.lower()
        up = char.upper()

        pos_e = _ALPHABET.index((lw, up))
        pos_i = _ALPHABET[pos_e].index(char)

    except ValueError:
        return char
    else:
        aux = pos_e - key
        n_pos = aux if aux >= 0 else aux + len(_ALPHABET)
        return _ALPHABET[n_pos][pos_i]


def _use_msg() -> None:
    """Show use message.
    """
    print(
        "{name} version 1.0.dev1\n"
        "Use:\n"
        "\t{name} -e file key:\t encrypts the file\n"
        "\t{name} -d file key:\t decrypts the file\n"
        "\t{name} ...:\t\t this information\n"
        "Where:\n"
        "\tarq:\t file name\n"
        "\tkey:\t key to en/decrypt between 1 and 26\n"
        "\t...:\t is anything".format(name=sys.argv[0])
    )


def cesar(msg: str, cmd: str, key: int = _key):
    """Function to use Cesar cipher.

    Parameters
    ----------
    msg : str
        Message/Char to be encrypted or decrypted.
    cmd : str
        'e' to encrypt or 'd' to decrypt.
    key : int
        Optional key to be used during the process (the default is 3).

    Returns
    -------
    str
        Message/Char after apply the operation the en/decrypt
        or None if error occurred.

    """
    out = []
    text = ""
    cmds = {"e": _encrypt, "d": _decrypt}

    try:
        cmd = cmds[cmd]

        for i in msg:
            out = list(map(cmd, i, repeat(key)))
            text += "".join(out)
    except Exception:
        return
    else:
        return text


if __name__ == "__main__":
    cmd_size = len(sys.argv)

    if cmd_size == 4:
        try:
            cmd = sys.argv[1]
            file_i = sys.argv[2]
            _key = int(sys.argv[3])

            if (cmd != "-e") and (cmd != "-d"):
                _use_msg()
            else:
                with open(file_i, "r") as f:
                    text = cesar(f, cmd[1:], _key)

                date = datetime.now()
                date = date.strftime("%y_%m_%d_%H_%M_%S")
                file_o = "out_{}.txt".format(date)
                with open(file_o, "w") as f:
                    f.write(text)

                print("Operation realized with success")

        except TypeError as err:
            print(err)

    else:
        a = _use_msg()
