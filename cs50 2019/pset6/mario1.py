from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

smbl_space = " "
smbl_hash = "#"

for i in range(1, height+1):
    line = smbl_space*(height - i) + smbl_hash*i
    print(line, end='  ')
    reversed_line = smbl_hash*i + smbl_space*(height - i)
    print(reversed_line.strip())
