from copy import deepcopy
import random 
from random import randint
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

# Ilość wierzchołków
SIZE = 19

G = nx.Graph()
G.add_nodes_from(list(range(SIZE)))
myedges = [
(0,1),(14,2),(1,3),(0,19),
(2,4),(3,6),(3,7),(1,18),
(4,7),(4,8),(5,8),(5,9),
(5,19),(6,0),(7,11),(18,12),
(8,10),(9,13),(17,15),
(10,14),(10,15),(11,15),(11,16),
(12,16),(12,17),(13,17),(13,18),
(19,2),(6,16)
]

G.add_edges_from(myedges)

graph = nx.Graph()
# matryca natężeń

# mymatrix = np.random.randint(0,200,size = (19,19))
# mymatrix[np.diag_indices_from(mymatrix)] = 0
# mymatrix2 = np.random.randint(0,200,size = (19,19))
# mymatrix2[np.diag_indices_from(mymatrix2)] = 0
# mymatrix3 = np.random.randint(0,200,size = (19,19))
# mymatrix3[np.diag_indices_from(mymatrix3)] = 0
# mymatrix4 = np.random.randint(0,200,size = (19,19))
# mymatrix4[np.diag_indices_from(mymatrix4)] = 0
# mymatrix = (mymatrix1 + mymatrix2 + mymatrix3 + mymatrix4) / 4

mymatrix = np.loadtxt('matrix.txt', dtype=int, usecols=range(SIZE))


# "nowa" matryca natężeń
def newmatrix(mymatrix, x):
    mymatrix =  mymatrix + x
    mymatrix[np.diag_indices_from(mymatrix)] = 0
    return mymatrix
#-------------------------------------    


# Tablica przechowująca usunięte krawędzie
removed_edges = []
#--------------------------------------------------------


# Wszystkie krawędzie mają czarny kolor
for edge in G.edges():
    G[edge[0]][edge[1]]["color"] = "black"
#---------------------------------------------------------

#tablicowanie najkrótszych sciezek na grafie
def create_list_of_all_paths(Graph):
    paths=[]
    for i in range(len(Graph)-1):
        for j in range(len(Graph)-1):
            try:
                for path in nx.all_shortest_paths(Graph, i, j):
                    paths.append(path)
            except nx.exception.NetworkXNoPath:
                print("dupa")        
    return paths
#---------------------------------------------------

# usuwanie krawędzi w grafie z zadanym pp
def delete_edges(p, copy_graph):

    for edge in copy_graph.edges():
        los = random.randint(0, 100)
        if los > p:
            #removed_edges.append(edge)
            copy_graph.remove_edge(edge[0], edge[1])
    return copy_graph        
#---------------------------------------------------------------

# dodawanie bazowych przepływów--------------------------------------
def a(v1, v2, new_matrix, paths):
    sum = 0
    try:
        for path in paths:
            if (v1 in path) and (v2 in path):
                sum = sum + new_matrix[path[0]][path[-1]]  
    except nx.exception.NetworkXNoPath:
            sum = sum            
    return sum      
#----------------------------------------------------------

# dodawanie bazowej przepostowości-----------------------------------------
def c(v1, v2, paths):
    sum = 0
    try:
        for path in paths:
            if (v1 in path) and (v2 in path):
                sum = sum + 1000
    except nx.exception.NetworkXNoPath:
            sum = sum            
    return sum     
#-------------------------------------------------------------------

#licz sredni przepust
def średni_przepust(graph):
    sum = 0
    for i,j in graph.edges:
        sum += graph[i][j]["weight2"] 
    return sum/graph.number_of_edges()
#------------------------------------------------------------------

#     
#dodawanie krawendzi-------------------------------------------
def dodaj_krawędź(graph, średni):
    non_edges = list(nx.non_edges(graph))
    i,j = random.sample(non_edges,1)[0]
    non_edges.remove((i,j))
    graph.add_edge(i,j)
    graph[i][j]["weight2"] = średni
#---------------------------------------------------------------

#dodawanie wag przepływu
def przeplyw(new_matrix, copy_graph):
    paths = create_list_of_all_paths(copy_graph)
    for edge in copy_graph.edges():
        v1 = edge[0]
        v2 = edge[1]
        copy_graph[v1][v2]["weight"] =  a(v1, v2, new_matrix, paths)
    return
#---------------------------------------------------------

#dodawanie wag przepustu
def przepust(copy_graph):
    paths = create_list_of_all_paths(copy_graph)
    for edge in copy_graph.edges():
        v1 = edge[0]
        v2 = edge[1]
        copy_graph[v1][v2]["weight2"] = c(v1, v2, paths) + 9000
    return
#----------------------------------------------------------------

# 
# zwiększanie przepustowości    
def podnies_przepust(copy_graph, incrementator):
    for edge in copy_graph.edges():
        v1 = edge[0]
        v2 = edge[1]
        copy_graph[v1][v2]["weight2"] += incrementator
    return
#-----------------------------------------------------------


#liczenie średniego T
def T(copy_graph,matrix, m):
    SUM=0
    smallsum=0
    for edge in copy_graph.edges():
        A = copy_graph[edge[0]][edge[1]]["weight"]
        C = copy_graph[edge[0]][edge[1]]["weight2"]
        if(A >= C/m ):
            return 2
        SUM = SUM + A/(C/m - A)
    for i in matrix:
        for j in range(len(i)):
            smallsum = smallsum + i[j]
    T= 1/smallsum*SUM
    
    return T   
#----------------------------------------------------------

przepust(G) #nadanie bazowej przepustowości


# print(T(G, newmatrix(mymatrix, 2), 4))

# badanie opóźnienia na danych parametrach: 
# m-wielkosc pakietu, grower_nat-zwiększenie natężeń, grower_przep - zwiększenie przepustowści, 
# pp - szansa wycięcia krawędzi, edge_adding - ile nowych krawedi
# print(mymatrix)

# TODO przepust nadać przed mainem na graph = deepcopy Graph
# potem w mainie graphik = deepcopy graph

def main1(m, grower_nat, old_matrix, pp, T_max):
    old_matrix = newmatrix(old_matrix, grower_nat)
    graph = deepcopy (G)

    graph = delete_edges(pp, graph)

    if(not (nx.is_connected(graph))):
        print("przerwano most")
        return 0
        
    #old_matrix = old_matrix + grower_nat
    przeplyw(old_matrix, graph)
    
    myT = (T(graph, mymatrix, m))
    

    if(myT <= T_max):
        return 1
    else:
        return 0
#-----------------------------------------------------


def main2(m, grower_przep, old_matrix, pp, T_max):
    
    graph = deepcopy (G)
    
    graph = delete_edges(pp, graph)

    if(not (nx.is_connected(graph))):
        print("przerwano most")
        return 0
        
    podnies_przepust(graph, grower_przep) # w każdej iteracji podnoszę przepustowość
    #old_matrix = old_matrix + grower_nat
    przeplyw(old_matrix, graph)
    
    # # printing ---------------------------
    # for edge in graph.edges():
    #     graph[edge[0]][edge[1]]["layout"] = "a(e): "+str(graph[edge[0]][edge[1]]["weight"])+"/c(e): "+str(graph[edge[0]][edge[1]]["weight2"])

    # print("opóźnienie: ")
    myT = (T(graph, mymatrix, m))
    # print(f"myT:  {myT}")

    if(myT <= T_max):
        return 1
    else:
        return 0
#-----------------------------------------------------

def main3(m, old_matrix, pp, T_max, edge_adding, średni):
    
    graph = deepcopy (G)
    
    for _ in range (0, edge_adding):
        dodaj_krawędź(graph, średni)

    graph = delete_edges(pp, graph)

    if(not (nx.is_connected(graph))):
        print("przerwano most")
        return 0
        
    
    przeplyw(old_matrix, graph)
    
    # # printing ---------------------------
    # for edge in graph.edges():
    #     graph[edge[0]][edge[1]]["layout"] = "a(e): "+str(graph[edge[0]][edge[1]]["weight"])+"/c(e): "+str(graph[edge[0]][edge[1]]["weight2"])

    
    myT = (T(graph, mymatrix, m))

    if(myT <= T_max):
        return 1
    else:
        return 0
#-----------------------------------------------------






#test1----------------------------------------------------
def test1(graph, matrix):
    matrix += 476
    podnies_przepust(graph, 63600)
    licznik = 0
    for i in range(50):
        licznik = 0
        for j in range (200):
            licznik = licznik + main1(2, 10 * i, mymatrix, 96, 0.01)

        print (licznik/200)

    return    
#---------------------------------------------------------

#test2----------------------------------------------------
# print(mymatrix)
def test2(matrix):
    matrix += 476
    licznik = 0
    for i in range(1, 70):
        licznik = 0
        for j in range (200):
            licznik = licznik + main2(2, (900*i), mymatrix, 96, 0.01)

        print (licznik/200)
   
    return    
#-----------------------------------------------------------


#test3----------------------------------------------------------
def test3(graph, matrix):
    matrix += 555
    podnies_przepust(graph, 21370)
    średni = średni_przepust(graph)
    licznik = 0
    for i in range(1, 50):
        licznik = 0
        for j in range (200):
            licznik = licznik + main3(2, mymatrix, 95, 0.01, i, średni)

        print (licznik/200)

    return
#-------------------------------------------------------------------------

    
test1(G, mymatrix)
# test2(mymatrix) 
# test3(G, mymatrix)
