#Get input from user
#if it is exactly equal to 'hello'
    #return $0
#elif it starts with 'h' && not 'hello'
    #return $20
#else
    #return $100
#print result

input = input(f'Greetings: ')
input = input.strip()
input = input.split()
input = input[0].lower()
if 'hello' in input:
    print('$0')
elif input.startswith('h') == True:
    print('$20')
else:
    print('$100')


