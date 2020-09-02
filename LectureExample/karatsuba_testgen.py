import random

logn = int(input())

n = 2 ** logn

print(n - 1)

a = [random.randint(100, 1000000) for i in range(n)]
b = [random.randint(100, 1000000) for i in range(n)]
print(' '.join(str(num) for num in a))
print(' '.join(str(num) for num in b))
