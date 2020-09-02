p = int(input())

# coins of different denominations
coins = [int(num) for num in input().split()]

# an array storing soluion for every possible amount of money
DP = [None for i in range(p + 1)]
DP[0] = 0

for amount in range(1, p + 1):
    for denomination in coins:
        if amount >= denomination:
            recur_solution = DP[amount - denomination] + 1
            if not DP[amount] or recur_solution < DP[amount]:
                DP[amount] = recur_solution

print(DP)
