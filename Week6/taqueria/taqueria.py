def main():

    # Implement a dictionary and store all food items
    menu =  {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
    }

    new_menu = dict()
    #print out menu & append the new_menu
    for k,v in menu.items():
        new_menu[k.lower()] = v
        print(k,v)

    # Get use input and store it in a list
    foods = []
    sum = 0
    print("Please add new items.")
    print("Press enter when done.\n")

    while True:
        try:
            food = input("Item: ").lower()
            #if food in new_menu:
                #foods.append(food)
            #calculate the total cost of food
            #for key in new_menu:
            if food in new_menu:
                #print(key)
                sum += new_menu[food]
                #print out the total
                format_sum = "{0:.2f}".format(sum)
                print(f"Total: ${format_sum}")
        #if len(food) == 0:
            #break
        except EOFError:
            print("\n")
            break


main()