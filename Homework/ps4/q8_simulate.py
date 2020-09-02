import random

n = int(input())
flower_field = [[None for i in range(n)] for i in range(n)]
max_num_of_edge_visit = 0

for count in range(100000):

    m = random.randint(3, n**2)  # types of flowers

    for i in range(n):
        for j in range(n):
            flower_field[i][j] = random.randint(1, m)

    num_of_edge_visit = 0  # counter of #visits

    edges = set()  # all unexplored edges connecting two different type of flowers

    for i in range(n):
        for j in range(n):
            if i < n - 1:
                if flower_field[i][j] != flower_field[i + 1][j]:
                    edges.add(((i, j), (i + 1, j)))
            if j < n - 1:
                if flower_field[i][j] != flower_field[i][j + 1]:
                    edges.add(((i, j), (i, j + 1)))

    while len(edges) > 0:
        # select an unexplored edge connecting two different types of flowers  to start dfs
        start = edges.pop()
        flower_type1 = flower_field[start[0][0]][start[0][1]]
        flower_type2 = flower_field[start[1][0]][start[1][1]]
        frontier = [start]
        explored_edges = set([start])
        # DFS with respect to edge
        while len(frontier) > 0:
            curr_edge = frontier.pop()
            num_of_edge_visit += 1
            # adjacent edges
            for edge in [
                ((curr_edge[0][0] - 1, curr_edge[0][1]), curr_edge[0]),
                (curr_edge[0], (curr_edge[0][0] + 1, curr_edge[0][1])),
                ((curr_edge[0][0], curr_edge[0][1] - 1), curr_edge[0]),
                (curr_edge[0], (curr_edge[0][0], curr_edge[0][1] + 1)),
                ((curr_edge[1][0] - 1, curr_edge[1][1]), curr_edge[1]),
                (curr_edge[1], (curr_edge[1][0] + 1, curr_edge[1][1])),
                ((curr_edge[1][0], curr_edge[1][1] - 1), curr_edge[1]),
                (curr_edge[1], (curr_edge[1][0], curr_edge[1][1] + 1))
            ]:
                if edge == curr_edge:
                    continue
                # if edge doesn't exist
                if (edge[0][0] < 0 or edge[0][1] < 0 or edge[1][0] > n - 1 or edge[1][1] > n - 1):
                    continue
                # if edge is connecting current two types of flowers
                if flower_field[edge[0][0]][edge[0][1]] in (flower_type1, flower_type2) and flower_field[edge[1][0]][edge[1][1]] in (flower_type1, flower_type2) and edge not in explored_edges:
                    explored_edges.add(edge)
                    frontier.append(edge)
                    # if this edge connects two different types of flowers
                    if flower_field[edge[0][0]][edge[0][1]] != flower_field[edge[1][0]][edge[1][1]]:
                        edges.remove(edge)

    # store the largest possible number of visits
    if num_of_edge_visit > max_num_of_edge_visit:
        max_num_of_edge_visit = num_of_edge_visit

print(num_of_edge_visit)
