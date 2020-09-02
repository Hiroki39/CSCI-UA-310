import random


def quote_generator():
    quote = ""
    length = random.randint(1, 4)
    for i in range(length):
        quote += chr(random.randint(65, 90))
    return quote


i = random.randint(1000, 10000)
print(i)

quotelist = []

for i in range(i):
    if len(quotelist) == 0:
        command = random.randint(1, 2)
    else:
        command = random.randint(1, 3)

    if command == 1:
        quote = quote_generator()
        price = random.randint(10, 10000)
        while quote in quotelist:
            quote = quote_generator()
        quotelist.append(quote)
        print(command, quote, price)
    if command == 2:
        high = quote_generator()
        low = quote_generator()
        print(command, low, high)
    if command == 3:
        quote = random.choice(quotelist)
        print(command, quote)
