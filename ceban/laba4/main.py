def bellman_ford_shortest_path(n, edges, source=1):
    
    H = [float('inf')] * (n + 1)
    H[source] = 0
    
    print(f"H:\t{H[1:]}\n")
    
    iteration = 0
    
    while True:
        iteration += 1
        changed = False
        
        print(f"Iteration {iteration}:")
        
        for i, j, weight in edges:
            if H[i] != float('inf'):
                diff = H[j] - H[i]
                if diff > weight:
                    H[j] = H[i] + weight
                    changed = True
                    print(f"\t{i} -> {j}, {weight}: H[{j}] - H[{i}] = {H[j]} - {H[i]} = {diff} > {weight} => H[{j}] = {H[j]}")
                else:
                    print(f"\t{i} -> {j}, {weight}: H[{j}] - H[{i}] = {H[j]} - {H[i]} = {diff} =< {weight}")
        
        print(f"H = {H[1:]}\n")
        
        if not changed:
            print("No changes => done\n")
            break
    
    return H


def print_shortest_paths(H, edges, n, source=1):
    
    incoming = {}
    for i in range(1, n + 1):
        incoming[i] = []
    for i, j, weight in edges:
        incoming[j].append((i, weight))
    
    S = [[n]]
    O = []
    while S:
        g = S.pop()
        if g[0] == source:
            O.append(g)
        else:
            for i, weight in incoming[g[0]]:
                if H[g[0]] - H[i] == weight:
                    S.append([i] + g)
    
    i = 1
    for path in O:
        path_str = " -> ".join(map(str, path))
        print(f"{i}) {path_str}")
        i += 1

def print_adj_matrix(edges, n):
    adj_matrix = [[0] * n for _ in range(n)]
    for i, j, weight in edges:
        adj_matrix[i-1][j-1] = weight
    
    print("\n\n")
    for row in adj_matrix:
        print(",".join(map(str, row)))
    print("\n\n")
    


edges = []
print("Enter edges (format: from to weight), or empty line to finish:")

while True:
    line = input().strip()
    if not line:
        break
    try:
        parts = line.split()
        if len(parts) != 3:
            print("Invalid format. Please use: from to weight")
            continue
        
        i, j, weight = int(parts[0]), int(parts[1]), int(parts[2])
        edges.append((i, j, weight))
    except ValueError:
        print("Invalid input. Please enter three integers.")

if not edges:
    print("No edges entered.")
else:
    n = max(max(i, j) for i, j, w in edges)
    
    print_adj_matrix(edges, n)
    
    H = bellman_ford_shortest_path(n, edges, source=1)
    print("shortest paths:")
    print_shortest_paths(H, edges, n)
