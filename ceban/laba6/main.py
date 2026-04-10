def read_adj():
    adj_list = {}

    n = 0
    while n <= 0:
        print("Enter the number of vertices: ", end="")
        try:
            n = int(input())
            if n <= 0:
                print("Enter num >= 1")
        except ValueError:
            print("Enter num >= 1")

    print("Enter the adjacency list, non digit to exit, 0 to next:")

    for i in range(1, n + 1):
        neighbors = []
        print(f"{i} : ", end="")

        try:
            line = input().strip()
            vertices = line.split()

            for vertex in vertices:
                try:
                    num = int(vertex)
                    if num == 0:
                        break
                    elif 1 <= num <= n:
                        neighbors.append(num)
                    else:
                        print(f"\nno vertex {num}, skipping...")
                except ValueError:
                    break
        except EOFError:
            break

        adj_list[i] = neighbors

    return adj_list


def print_adj(adj_list):
    if not adj_list:
        print("Adjacency list is empty.")
        return

    print("\nAdj list:")
    for vertex in sorted(adj_list.keys()):
        neighbors = adj_list[vertex]
        neighbors_str = " ".join(map(str, neighbors))
        if neighbors_str:
            print(f"{vertex:2d}: {neighbors_str} 0")
        else:
            print(f"{vertex:2d}: 0")


def edit_graph(adj_list):
    """
    Edit graph by removing certain edges based on traversal algorithm.
    
    Algorithm:
    1) Create empty M (queue), T (queue), V (set)
    2) Push vertex with lowest number not in V to M
    3) Pop vertex S from M, add S to V
    4) Push all children of S not in V to T
    5) Pop C from T
    6) Delete C->t and t->C for all t in T
    7) Delete C->m and m->C for all m in M where m != S
    8) Push C to M
    9) If T not empty, go to step 5
    10) If M not empty, go to step 3
    11) If len(V) != number of vertices, go to step 2
    """
    total_vertices = len(adj_list)
    
    if total_vertices == 0:
        return
    
    n = max(adj_list.keys())
    
    M = []  # Queue (maintains order of visit)
    T = []  # Queue (maintains order)
    V = set()  # Set of visited vertices
    
    while len(V) != total_vertices:
        # Step 2: Push vertex with lowest number not in V to M
        min_vertex = None
        for v in range(1, n + 1):
            if v not in V and v in adj_list:
                min_vertex = v
                break
        
        if min_vertex is not None:
            M.append(min_vertex)
        
        # Step 10: If M not empty
        while M:
            # Step 3: Pop vertex S from M, add S to V
            S = M.pop(0)
            V.add(S)
            
            # Step 4: Push all children of S not in V to T
            if S in adj_list:
                for child in adj_list[S][:]:
                    if child not in V:
                        T.append(child)
            
            # Step 9: If T not empty
            while T:
                # Step 5: Pop C from T
                C = T.pop(0)
                
                # Step 6: Delete C->t and t->C for all t in T
                for t in T:
                    if C in adj_list and t in adj_list[C]:
                        adj_list[C].remove(t)
                    if t in adj_list and C in adj_list[t]:
                        adj_list[t].remove(C)
                
                # Step 7: Delete C->m and m->C for all m in M where m != S
                for m in M:
                    if m != S:
                        if C in adj_list and m in adj_list[C]:
                            adj_list[C].remove(m)
                        if m in adj_list and C in adj_list[m]:
                            adj_list[m].remove(C)
                
                # Step 8: Push C to M
                M.append(C)


def main():
    adj_list = read_adj()
    #print_adj(adj_list)
    edit_graph(adj_list)
    print_adj(adj_list)


if __name__ == "__main__":
    main()