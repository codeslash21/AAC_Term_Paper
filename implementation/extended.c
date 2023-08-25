#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_DIST 9999

//define the structure node
typedef struct node {
    int distance;
    int predecessor;
    int visited;
    int family;
} Node;

//global variables
Node * nodes[101]={NULL};
int weights[101][101]={0};
static int flag=0, cost=0, count=0, u=0, v=0;

//initialize all the nodes
void Initialize_Sigle_Source(int source, int destination) {
    int i;
    for(i=1;i<=100;i++) {
        nodes[i] = (Node *)malloc(sizeof(Node));
        nodes[i]->distance = MAX_DIST;
        nodes[i]->predecessor = 0;
        nodes[i]->visited = 0;
        nodes[i]->family = 0;
    }
    nodes[source]->distance = 0;
    nodes[source]->family = source;
    nodes[destination]->distance = 0;
    nodes[destination]->family = destination;
}

// relax the edge
void relaxEdge(int u, int v, int w) {
    if(nodes[v]->distance > (nodes[u]->distance + w)) {
        nodes[v]->distance = nodes[u]->distance + w;
        nodes[v]->predecessor = u;
        nodes[v]->family = nodes[u]->family;
    }
}
int findMinCost() {
    int min = MAX_DIST, min_index, i;
    for(i=1;i<=100;i++) {
        if(nodes[i]->distance < min && nodes[i]->visited==0) {
            min=nodes[i]->distance;
            min_index = i;
        }
    }
    return min_index;
}

void extendedDijkstra(int source, int destination) {
    int i;
    Initialize_Sigle_Source(source, destination);
    //printf("Initialization done\n");
    for(i=1;i<=100;i++) {
        u = findMinCost();
        nodes[u]->visited = 1;
        for(v=1;v<=100; v++) {
            if(weights[u][v]!=0) {
                if((nodes[u]->family==source && nodes[v]->family==destination && nodes[v]->visited==1) || 
                (nodes[u]->family==destination && nodes[v]->family==source && nodes[v]->visited==1)) {
                    flag=1;
                    cost = nodes[u]->distance + nodes[v]->distance + weights[u][v];
                    break;
                }
                else {
                    relaxEdge(u, v, weights[u][v]);
                    count++;
                }
            }
        }
        if(flag)
            break;
    }
    
}

void printPath(int u, int v) {
    int path1[100]={0}, path2[100]={0}, cur=0, i=99, j=0;
    path1[i--]=v;
    path1[i--]=u;
    cur=u;
    //printf("%d %d",path1[i+1], path1[i+2]);
    while(nodes[nodes[cur]->predecessor]) {
        path1[i--]=nodes[cur]->predecessor;
        cur=nodes[cur]->predecessor;
    }
    for(j=i+1;j>=99;j++) {
        printf("%d - ", path1[j]);
    }
    cur=v;
    i=0;
    while(nodes[nodes[cur]->predecessor]) {
        path2[i++]=nodes[cur]->predecessor;
        cur=nodes[cur]->predecessor;
    }
    for(j=0;j<i;j++) {
        printf("%d - ", path2[j]);
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
    for(i=1;i<101;i++) {
        for(j=1;j<101;j++) {
            fscanf(fp, "%d", &weights[i][j]);
        }
    }
    //printf("Matrx created\n");
    start = clock();
    extendedDijkstra(source, destination);
    end = clock();
    if(cost==0) {
        printf("Path not found\n");
    }
    else {
        printf("Minimum cost is: %d\n", cost);
        //printf("Shortest path is: \n");
        printPath(u, v);
    }
    
    printf("No of nodes counted: %d\n", count);
    printf("Time taken is %f", ((double)end-start)/CLOCKS_PER_SEC);
}