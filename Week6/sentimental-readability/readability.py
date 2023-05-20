# TODO


def main():
#promt user for input
    text = input('Text: ')
    counts = Count(text)
    Coleman(counts)


def Count(text):
#Get number of letters
#Get number of words
#Get number of sentence
    letterCount = 0
    wordCount= 1
    sentenceCount = 0
    sentence = ('.', '!', '?')
    for letters in text:
        if letters.isalpha() == True:
            letterCount += 1
        if letters == ' ':
            wordCount += 1
        if letters in sentence:
            sentenceCount += 1

    count = [letterCount, wordCount, sentenceCount]
    print(count)

    return count

#Apply Coleman-Laiu index
def Coleman(count):
    #0.0588 * L - 0.296 * S - 15.8

    l = count[0]/count[1] * 100
    s = count[2]/count[1] * 100
    print(l)
    print(s)
    index = round(0.0588 * l - 0.296 * s - 15.8)

    if index < 1:
        grade = "1"
    elif index >= 16:
        grade = "16+"
    else:
        grade = index

#print grade
    if index < 1:
        print('Before Grade 1')
    else:
        print(f'Grade {grade}')


main()