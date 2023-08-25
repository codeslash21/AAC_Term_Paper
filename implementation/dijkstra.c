#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_DIST 9999

// define structure node
typedef struct node {
    int distance;
    int predecessor;
    int visited;
} Node;

//global variables
static Node * nodes[101]={NULL};
static int weights[101][101]={0};
static int u1=0,v1=0, count=0;

//initialize all the nodes in the graph
void Initialize_Sigle_Source(int start, int end) {
    int i;
    for(i=1;i<=100;i++) {
        nodes[i] = (Node *)malloc(sizeof(Node));
        nodes[i]->distance = MAX_DIST;
        nodes[i]->predecessor = 0;
        nodes[i]->visited = 0;
    }
    nodes[start]->distance = 0;
}

//relax the edge
void relaxEdge(int u, int v, int w) {
    if(nodes[v]->distance > (nodes[u]->distance + w)) {
        nodes[v]->distance = nodes[u]->distance + w;
        nodes[v]->predecessor = u;
    }
}

//get the node with minimum cost from the unvisited nodes
int findMinCost(int source, int destination) {
    int min = MAX_DIST, min_index, i;
    for(i=1;i<=100;i++) {
        if(nodes[i]->distance < min && nodes[i]->visited==0) {
            min=nodes[i]->distance;
            min_index = i;
        }
    }
    return min_index;
}

//dijkstra algorithm
void Dijkstra(int source, int destination) {
    int i;
    Initialize_Sigle_Source(source, destination);
    //printf("Initialization done\n");
    for(i=1;i<=100;i++) {
        u1 = findMinCost(source, destination);
        nodes[u1]->visited = 1;
        if(u1==destination)
            break;
        for(v1=1;v1<=100; v1++) {
            if(weights[u1][v1]!=0) {
                relaxEdge(u1, v1, weights[u1][v1]);
                count++;
            }
        }
    }
}

//print the shortest path
void printPath(Node **nodes, int source, int destination) {
    int i=destination-source, cur=destination;
    printf("%d",destination);
    while(nodes[nodes[cur]->predecessor]) {
        printf(" - %d", nodes[cur]->predecessor);
        cur = nodes[cur]->predecessor;
    }
}

int main() {
    int i, j, source, destination;
    clock_t start, end;
    FILE *fp = fopen("input.txt", "r");
    printf("Give source index: ");
    scanf("%d", &source);
    printf("Give destination index: ");
    scanf("%d", &destination);
    //create weights matrix
    for(i=1;i<101;i++) {
        for(j=1;j<101;j++) {
            fscanf(fp, "%d", &weights[i][j]);
        }
    }
    //close the file pointer
    fclose(fp);
    //printf("Matrx created\n");
    start = clock();
    Dijkstra(source, destination);
    end = clock();
    if(nodes[destination]->distance==9999) {
        printf("Path not found\n");
    }
    else {
        printf("\nMinimum Cost is: %d\n", nodes[destination]->distance);
        printf("Shortest path is: \n");
        printPath(nodes, source, destination);
    }
    
    printf("\nNo of nodes counted is: %d\n", count);
    printf("Time taken is %f:", ((double)(end-start))/CLOCKS_PER_SEC);
}