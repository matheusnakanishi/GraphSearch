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

//Queue Structure
typedef struct queue {
    Node *start;
} Queue;

//Colors
#define WHITE 0
#define GRAY 1
#define BLACK 2

//Functions
Queue *create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->start = NULL;
    return queue;
}

void enqueue(Queue *queue, int item) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = item;
    node->next = NULL;

    if (queue->start == NULL) {
        queue->start = node;
    } else {
        Node *aux = queue->start;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = node;
    }
}

int dequeue(Queue *queue) {
    int item = queue->start->value;
    Node *deleteNode = queue->start;
    queue->start = deleteNode->next;
    free(deleteNode);

    return item;
}

void print_distance(int *distance, int size) {
    printf("Distance from the start vertex:\n");

    for (int i = 0; i < size; i++)
        printf("[%d]: %d\n", i, distance[i]);
    
}

void bfs(Graph G, int s) {
    int *color = (int*)malloc(G->vertex * sizeof(int));
    int *distance = (int*)malloc(G->vertex * sizeof(int));
    int *parent = (int*)malloc(G->vertex * sizeof(int));

    for (int i = 0; i < G->vertex; i++) {
        color[i] = WHITE;
        distance[i] = INT_MAX/2;
        parent[i] = -1;
    }

    Queue *queue = create_queue();
    color[s] = GRAY;
    distance[s] = 0;
    parent[s] = -1;
    enqueue(queue, s);

    while (queue->start) {
        int u = dequeue(queue);
        Node *adj = G->vet[u];

        while (adj) {

            if (color[adj->value] == WHITE) {
                distance[adj->value] = distance[u] + 1;
                parent[adj->value] = u;
                enqueue(queue, adj->value);
            }
            adj = adj->next;
        }
        color[u] = BLACK;
    }

    print_distance(distance, G->vertex);

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
    Graph G = graph_boot(8);

    edge_insert(G, 0, 1);
    edge_insert(G, 1, 2);
    edge_insert(G, 0, 3);
    edge_insert(G, 3, 4);
    edge_insert(G, 3, 5);
    edge_insert(G, 4, 5);
    edge_insert(G, 4, 6);
    edge_insert(G, 6, 7);
    edge_insert(G, 7, 5);
    
    bfs(G, 0);

    //print_graph(G);
    
    release_graph(G);

    return 0;
}