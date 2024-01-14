from sys import argv, exit
from cs50 import get_string

k = int(argv[1])
if k < 0 or len(argv) != 2:
    exit(1)

plaintext = get_string("plaintext: ")
print("ciphertext: ", end='')

for i in plaintext:
    if i.isupper():
        print(chr(((ord(i) - 65 + k) % 26) + 65), end='')
    elif i.islower():
        print(chr(((ord(i) - 97 + k) % 26) + 97), end='')
    else:
        print(i, end='')
print()
