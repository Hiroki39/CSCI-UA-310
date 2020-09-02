weight_limit = int(input())

values = [int(num) for num in input().split()]
weights = [int(num) for num in input().split()]

num_of_weights = len(weights)

DP = [[0 for i in range(num_of_weights + 1)] for j in range(weight_limit + 1)]

for k in range(num_of_weights):
    # iterate through different weight limit
    for curr_weight_limit in range(weight_limit + 1):
        solution1 = 0

        # if the weight limit is greater than the kth weight
        if curr_weight_limit >= weights[k]:
            solution1 = DP[curr_weight_limit - weights[k]][k] + values[k]

        solution2 = DP[curr_weight_limit][k]  # discard the kth item
        DP[curr_weight_limit][k + 1] = max(solution1, solution2)

print(DP[weight_limit][num_of_weights])
