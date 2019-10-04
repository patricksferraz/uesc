# cesar_cipher

## Installing

```sh
$ pip install cesar_cipher
```

## Usage

```py
from cesar_cipher import cs

cs.cesar(msg, cmd, key=3)
# where:
#   * 'msg' is the message/char to be encrypt/decrypt
#   (special digits are ignored)
#   * 'cmd' is the command to define the operation
#   ('e' to encrypt and 'd' to decrypt)
#   * 'key' is optional (default 3) key to encrypt/decrypt
```

## Example

```sh

>>>from cesar_cipher import cs
>>># Encrypting the letter 'a' with default key (3)
>>>print(cs.cesar('a', 'e'))
'd'
>>># Decrypting the letter 'd' with default key (3)
>>>print(cs.cesar('d', 'd'))
'a'
>>># Encrypting the string 'abc' with default key (3)
>>>print(cs.cesar('ABC', 'e'))
'DEF'
```
