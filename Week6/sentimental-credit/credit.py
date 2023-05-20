
def main():
# promt user for input, reject invalid input
    card = input("Number: ")
    while card.isdigit() != True:
        card = input("Number: ")

    #checkValid(card)

    if (checkValid(card) == True) and (checkCardType(card) == 'VISA' or checkCardType(card) == 'MASTERCARD' or checkCardType(card) == 'AMEX'):
        print(f'{checkCardType(card)}')
    else:
        print('INVALID')

# implement luhn's algorithm to check if the card number is valid
# return a bool valid or invalid
def checkValid(input):
    sum1 = 0
    sum2 = 0
    for i in range(len(input)-1, 0, -2):
        if int(input[i-1]) * 2 > 9:
            s = int(input[i-1]) * 2
            sum1 = sum1 + int(str(s)[0]) + int(str(s)[1])
        else:
            sum1 = sum1 + (int(input[i-1]) * 2)

        print(sum1)
    for j in range(len(input), 0, -2):
        sum2 = sum2 + int(input[j-1])

    total = sum1 + sum2
    #print(total)
    if (total % 10 == 0):
        return True
    else:
        return False

# Check the type of card
# return string of card type
def checkCardType(input):
    # case: Visa
    if input.startswith('4') and (len(input) == 13 or len(input) == 16):
        return 'VISA'

    # case: American Express
    AMEX = ['34','37']
    if input.startswith(tuple(AMEX)) and len(input) == 15:
        return 'AMEX'

    # case: MasterCard
    MASTERCARD = ['51', '52', '53', '54', '55']
    if input.startswith(tuple(MASTERCARD)) and len(input) == 16:
        return 'MASTERCARD'


main()