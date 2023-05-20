import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Invalid usage')
    else:
        databaseCsv = sys.argv[1]
        sequenceTxt = sys.argv[2]

    # TODO: Read database file into a variable
    database = []
    with open(databaseCsv, newline='') as csvfile:
        readerCsv = csv.DictReader(csvfile)
        for row in readerCsv:
            database.append(row)


    # TODO: Read DNA sequence file into a variable
    with open(sequenceTxt, 'r') as txtfile:
        readerTxt = txtfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    runResult = []
    for i in database:
        for key in i.keys():
            if(key != 'name'):
                longest_run = longest_match(readerTxt, key)
                runResult.append(longest_run)

        break
    #print(runResult)
    #print(runResult[0])
    #print(runResult[1])
    #print(runResult[2])
    # TODO: Check database for matching profiles

    for row in database:
        i = 0
        for val in row.values():
            if(val.isdigit() == True):
                #print(val)
                if(int(val) == int(runResult[i])):
                    i = i + 1

        if i == len(runResult):
            break
                #print(runResult[i])
                #print(i)
        #print(len(runResult))
    if i == len(runResult):
        print(row['name'])
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
