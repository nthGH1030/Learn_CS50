#promt input(:Height: ")
#if input != integer, re-prompt
# i = 1
#for row in rows
    #print " " * (Height - i)
    #print "#" * i
    #print " "
    #print "#" * i
Height = input("Height: ")
while (Height.isdigit() != True or int(Height) < 1 or int(Height) > 8):
    Height = input("Height: ")

Height = int(Height)
if Height == 1:
    print("#  #")
else:
    for i in range(1, (Height + 1), 1):
        print(" " *(Height - i) + "#" * i + "  " + "#" * i)




