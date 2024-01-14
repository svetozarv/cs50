from sys import argv, exit
from cs50 import get_string


def main():
    key_word = argv[1]
    if len(argv) != 2:
        exit(1)
    for i in key_word:
        if not i.isalpha():
            exit(1)

    plaintext = get_string("plaintext: ")
    print("ciphertext: ", end='')

    i = j = key = 0
    while i < len(plaintext):
        value = plaintext[i]

        if value.isalpha():
            key = determine_shift(key_word[j % len(key_word)])
        else:
            j -= 1

        if value.isupper():
            print(chr(((ord(value) - 65 + key) % 26) + 65), end='')
        elif value.islower():
            print(chr(((ord(value) - 97 + key) % 26) + 97), end='')
        else:
            print(value, end='')

        i += 1
        j += 1
    print()


def determine_shift(char):
    if char.isupper():
        return ord(char) - 65
    elif char.islower():
        return ord(char) - 97
    return 0


if __name__ == "__main__":
    main()
