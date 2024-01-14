from cs50 import get_string
from sys import argv, exit


def main():
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    file_name = argv[1]

    file = open(file_name, "r")

    words_set = set()
    for i in file:
        i = i.strip("\n")
        words_set.add(i)

    user_input = get_string("What message would you like to censor?\n").split()

    for i, val in enumerate(user_input):
        for j in words_set:
            if val.lower() == j:
                user_input[i] = len(val) * '*'

    print(" ".join(user_input))


if __name__ == "__main__":
    main()
