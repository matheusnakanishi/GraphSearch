#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Graph Structure
typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct graph {
    Node **vet; //List vector
    int vertex; //Number of vertex
    int edges;  //Number of edges
} *Graph;

//Colors
#define WHITE 0
#define GRAY 1
#define BLACK 2

//Functions

void print_distance(int *distance, int *end, int size) {
    printf("Vertex Time:\n");

    for (int i = 0; i < size; i++)
        printf("[%d]: %d | %d\n", i, distance[i], end[i]);
    
}

void visit(Graph G, int u, int *color, int *distance, int *parent, int *end, int *time) {
    color[u] = GRAY;
    (*time)++;
    distance[u] = time;

    Node *adj = G->vet[u];

    while (adj) {
        int v = adj->value;

        if (color[v] == WHITE) {
            parent[v] = u;
            visit(G, v, color, distance, parent, end, time);
        }
        adj = adj->next;
    }
    
    color[u] = BLACK;
    (*time)++;
    end[u] = *time;
}


void dfs(Graph G) {
    int *color = (int*)malloc(G->vertex * sizeof(int));
    int *distance = (int*)malloc(G->vertex * sizeof(int));
    int *parent = (int*)malloc(G->vertex * sizeof(int));
    int *end = (int*)malloc(G->vertex * sizeof(int));

    for (int i = 0; i < G->vertex; i++) {
        color[i] = WHITE;
        distance[i] = INT_MAX/2;
        parent[i] = -1;
    }

    int time = 0;

    for (int u = 0; u < G->vertex; u++) {
        if (color[u] == WHITE)
            visit(G, u, color, distance, parent, end, &time);
    }
    
    print_distance(distance, end, G->vertex);

    free(color);
    free(distance);
    free(parent);
}

Graph graph_boot(int num_vertex) {
    Graph G = malloc(sizeof (*G));
    G->vertex = num_vertex;
    G->edges = 0;

    G->vet = malloc(num_vertex * sizeof(Node*));
    for (int i = 0; i < num_vertex; i++) 
        G->vet[i] = NULL;
    
    return G;
}

void edge_insert(Graph G, int i, int j) {
    Node *newI = malloc(sizeof(Node));
    newI->value = j;
    newI->next = G->vet[i];
    G->vet[i] = newI;
    G->edges++;
}

void print_graph(Graph G) {
    printf("\n");
    for (int i = 0; i < G->vertex; i++) {
        Node *aux = G->vet[i];
        
        printf("[%d]->",i);
        while (aux) {
            printf("(%d)->",aux->value);
            aux = aux->next;
        }
        printf("NULL\n");
    }
}


void release_graph(Graph G) {
    for (int i = 0; i < G->vertex; i++) {
        Node *aux = G->vet[i];
        while (aux) {
            Node *del = aux;
            aux = aux->next;
            free(del);
        }
        G->vet[i] = NULL;
    }
    free(G->vet);
    G->vet = NULL;
    free(G);
}



int main() {
    Graph G = graph_boot(5);

    edge_insert(G, 0, 1);
    edge_insert(G, 0, 2);
    edge_insert(G, 1, 3);
    edge_insert(G, 1, 4);
    edge_insert(G, 2, 3);

    dfs(G);

    print_graph(G);
    
    release_graph(G);

    return 0;
}