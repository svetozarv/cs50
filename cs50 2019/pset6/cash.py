from cs50 import get_float

while True:
    cash = get_float("Change owed: ")
    if cash > 0:
        break

coins = 0
cash = int(cash * 100)
while cash != 0:
    if cash >= 25:
        cash -= 25
        coins += 1
    elif 10 <= cash < 25:
        cash -= 10
        coins += 1
    elif 5 <= cash < 10:
        cash -= 5
        coins += 1
    elif 1 <= cash < 5:
        cash -= 1
        coins += 1

print(coins)
