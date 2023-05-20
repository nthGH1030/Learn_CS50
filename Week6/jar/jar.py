class Jar:
    def __init__(self, capacity=12):
        #if capacity is not a non-negative int, raise valueError
        self.capacity = capacity
        self.size = 0
        if self.capacity < 1:
            raise ValueError

    def __str__(self):
        #return a str that represent the number of cookies
        for cookie in self.size:
            print('\N{cookie}')
            cookie += 1

    def deposit(self, n):
        # add n to the jar
        # if the n > jar.capacity, raise valueError
        self.size += n
        if self.size > self.capacity:
            raise ValueError
        else:
            self.size += n

    def withdraw(self, n):
        # Remove n cookies from the jar
        # if n > capacity, raise valueError
        self.size -= n
        if self.size < 0:
            raise ValueError
        else:
            self.size -= n

    @property
    def capacity(self):
        #return a jar capacity
        return self.capacity

    @property
    def size(self):
        #return the number of cookies in the jar
        return self.size

def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))

    jar.deposit(2)
    print(str(jar))

    jar.withdraw(1)
    print(str(jar))

main()

