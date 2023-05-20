import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    for line in reader:
        state = line['state']
        date = line['date']
        cases = int (line['cases'])

        #implement a second dictionary called previous_case in order to ge the everyday value for new_cases
        # if the state is not in previous_cases
            #add the item to the previous cases list
            # add a blank item in new_cases
        # if the state is already in previous_cases
            # Get the case number for new_cases to append
            # cases = Previous_cases[state] - cases

        # after certain amount of cycles, only the 2nd if statement will be executed as all the cases are in previous cases

        #logic to calculate the each day cases
        # add the first cases to previous_cases
        if state not in previous_cases:
            previous_cases[state] = cases
        else:
            #update value of cases for new_cases to append
            new_case = cases - previous_cases[state]
            #update value of previous cases for next loop cycle
            previous_cases[state] = cases

            #declare a new empty list to append to, but only once for each state
            if state not in new_cases:
                new_cases[state] = []
            #Remove first index when list size exceed 14,
            if len(new_cases[state]) >= 14:
                new_cases[state].pop(0)
            #append new value at the end
            new_cases[state].append(new_case)

    return new_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    # sum up and get the average of 7 day by getting the last 7 elements
    # calculate the percent increase or decrease by comparing the 2 7 daysaverages
    for state in states:
        #slice the dict to get the 8-14 day value
        recentCase = new_cases[state][7:14]
        #slice the dictionary to get the 0-7 day value
        oldCase = new_cases[state][0:7]
        averageRecent = round(sum(recentCase) / 7)
        averageOld = round(sum(oldCase) / 7)
        #try:
            # the % change = (recent - previous)previous
            #numerator / denominator
        #except ZeroDivisionError:
        try:
            percentageChange = round((averageRecent-averageOld)/averageOld * 100)
        except ZeroDivisionError:
            return 0
        if recentCase > oldCase:
            # it is a increase
            # print increase & %
            # print using ,
            print(state, "had a 7-day average of",averageRecent, " and an increase of " , percentageChange ," %")
        elif recentCase < oldCase:
            # it is a decrease
            # print using format
            print(f"{state} had a 7-day average of {averageRecent} and a decrease of {percentageChange} %")
        else:
            print(f"{state} had a 7-day average of {averageRecent} and there is no change of cases")



main()
