import sys


def shortest_path(n, edges, source=1):
    INF = float("inf")

    def format_val(val):
        return "INF" if val == INF else str(val)

    # Stage 1: Construct weighted adjacency matrix M
    M = [[INF] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        M[i][i] = 0

    for u, v, w in edges:
        M[u][v] = w

    # Print Matrix M with formatting
    header = "     " + "".join(f"X{j:<4}" for j in range(1, n + 1))
    print(header)
    print("   -" + "-" * (n * 5))
    for i in range(1, n + 1):
        row_str = "".join(f"{format_val(M[i][j]):<5}" for j in range(1, n + 1))
        print(f"X{i} | {row_str}")

    # Stage 2: Construct vector V0
    V_prev = [INF] * (n + 1)
    for i in range(1, n + 1):
        if i == n:
            V_prev[i] = 0
        else:
            V_prev[i] = M[i][n]

    row_str = "".join(f"{format_val(V_prev[i]):<5}" for i in range(1, n + 1))
    print(f"V0 | {row_str}")

    # Stage 3: Iterative construction of vector Vk
    k = 1
    while True:
        V_curr = [INF] * (n + 1)
        V_curr[n] = 0

        for i in range(1, n):
            min_val = INF
            for j in range(1, n + 1):
                if i != j:
                    val = V_prev[j] + M[i][j]
                    if val < min_val:
                        min_val = val
            V_curr[i] = min_val

        row_str = "".join(f"{format_val(V_curr[i]):<5}" for i in range(1, n + 1))
        print(f"V{k} | {row_str}")

        # The iterations stop when we get a vector equal to the previous one
        if V_curr == V_prev:
            print("\nNo changes => done\n")
            break

        V_prev = V_curr[:]
        k += 1

    # Path Reconstruction
    shortest_len = V_curr[source]
    all_paths = []

    if shortest_len != INF:

        def backtrack(u, current_path):
            if u == n:
                all_paths.append(list(current_path))
                return

            for v in range(1, n + 1):
                # Ensure edge exists, avoids looping back, and maintains the optimal path equation
                if u != v and M[u][v] != INF and v not in current_path:
                    if V_curr[u] == M[u][v] + V_curr[v]:
                        current_path.append(v)
                        backtrack(v, current_path)
                        current_path.pop()

        backtrack(source, [source])

    # Return the minimum path length and the list of paths
    return shortest_len, all_paths


edges = []
print("Enter edges (format: from to weight), or empty line to finish:")

for line in sys.stdin:
    line = line.strip()
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

    shortest, paths = shortest_path(n, edges, source=1)

    if shortest == float("inf"):
        print(f"No path found from 1 to {n}.")
    else:
        print(f"The shortest path length from 1 to {n} is: {shortest}")
        print("All shortest paths:")
        for path in paths:
            print(" -> ".join(map(str, path)))
