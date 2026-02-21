def read_adj():
    adj_list = {}
    
    n = 0
    while n <= 0:
        print("Enter the number of vertices: ", end='')
        try:
            n = int(input())
            if n <= 0:
                print("Enter num >= 1")
        except ValueError:
            print("Enter num >= 1")
    
    print("Enter the adjacency list, non digit to exit, 0 to next vertex:")
    
    for i in range(1, n + 1):
        neighbors = []
        print(f"{i} : ", end='')
        
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
    
    print("\nThe adjacency list is:")
    for vertex in sorted(adj_list.keys()):
        neighbors = adj_list[vertex]
        neighbors_str = " ".join(map(str, neighbors))
        if neighbors_str:
            print(f"{vertex:2d}: {neighbors_str} 0")
        else:
            print(f"{vertex:2d}: 0")


def dfs_rec(adj_list, vertex, visited, result):
    visited.add(vertex)
    result.append(vertex)
    
    if vertex in adj_list:
        for neighbor in adj_list[vertex]:
            if neighbor not in visited:
                dfs_rec(adj_list, neighbor, visited, result)


def dfs(adj_list, start_vertex, visit_all=True):
    if not adj_list:
        return []
    
    if start_vertex not in adj_list:
        print(f"Vertex {start_vertex} not found in the graph.")
        return []
    
    visited = set()
    result = []
    
    dfs_rec(adj_list, start_vertex, visited, result)
    
    if visit_all:
        for vertex in sorted(adj_list.keys()):
            if vertex not in visited:
                dfs_rec(adj_list, vertex, visited, result)
    
    return result


def print_dfs(result):
    if not result:
        print("No vertices were visited.")
        return
    
    print(" -> ".join(map(str, result)))


def main():
    adj_list = read_adj()
    
    if adj_list:
        #print_adj(adj_list)
        
        print("\nEnter starting vertex for Depth-First Search: ", end='')
        try:
            start_vertex = int(input())
            
            dfs_result = dfs(adj_list, start_vertex)
            
            if dfs_result:
                print_dfs(dfs_result)
        except ValueError:
            print("Invalid vertex input.")
    else:
        print("No adjacency list was entered.")


if __name__ == "__main__":
    main()
