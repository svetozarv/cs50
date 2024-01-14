from cs50 import get_string

card_num = get_string("Number: ")
sum = 0

for index, digit in enumerate(card_num[::-1]):
    digit = int(digit)
    if index % 2 == 1:
        sum += digit*2 % 10
        sum += digit*2 // 10
    else:
        sum += digit

if sum % 10 != 0:
    print("INVALID")
else:
    two_digits = int(card_num[:2])
    if two_digits == 37 or two_digits == 34 and len(card_num) == 15:
        print('AMEX')
    elif 51 <= two_digits <= 55 and len(card_num) == 16:
        print('MASTERCARD')
    elif two_digits // 10 == 4 and len(card_num) == 13 or len(card_num) == 16:
        print('VISA')
    else:
        print("INVALID")
