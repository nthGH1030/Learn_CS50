from pyfiglet import Figlet
import sys
import random


def main():
    figlet = Figlet()
    if len(sys.argv) == 1:
        #user woudld like to output text in random font
        randomFont = random.choice(figlet.getFonts())
        figlet.setFont(font = randomFont)
        print(figlet.renderText(get_text()))

    elif len(sys.argv) == 3 and (sys.argv[1] == '-f' or sys.argv[1] == '--font'):
        #user would like to output text in a specific font
        figlet.setFont(font = sys.argv[2])
        print(figlet.renderText(get_text()))

    else:
        sys.exit('Invalid usage')


#declare a function
#prompt the user to enter a string as input
def get_text() -> str:
    output = input("Please enter a text: ")
    return output

#call main
main()