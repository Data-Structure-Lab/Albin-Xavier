#include <stdio.h>
#include <stdlib.h>

struct node 
{
  int vertex;
  struct node* next;
};

struct node* createNode(int v);

struct Graph 
{
  int numVertices;
  int* visited;

  struct node** adjLists;
};

void DFS(struct Graph* graph, int vertex) 
{
  struct node* adjList = graph->adjLists[vertex];
  struct node* temp = adjList;

  graph->visited[vertex] = 1;
  printf("Visited %d \n", vertex);

  while (temp != NULL) 
  {
    int connected_Vertex = temp->vertex;

    if (graph->visited[connected_Vertex] == 0) 
    {
      DFS(graph, connected_Vertex);
    }
    temp = temp->next;
  }
}

struct node* createNode(int vert) 
{
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = vert;
  newNode->next = NULL;
  return newNode;
}

struct Graph* createGraph(int vertices) 
{
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  graph->visited = malloc(vertices * sizeof(int));

  int i;
  
  for (i = 0; i < vertices; i++) 
  {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

void addEdge(struct Graph* graph, int src, int dest) 
{
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

void printDFS(struct Graph* graph) 
{
  int v;
  for (v = 0; v < graph->numVertices; v++) 
  {
    struct node* temp = graph->adjLists[v];
    printf("\nvertex %d\ : ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}

int main() 
{
  struct Graph* graph = createGraph(5);
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 1, 3);
  addEdge(graph, 1, 4);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);
  addEdge(graph, 3, 4);

  printDFS(graph);

  DFS(graph, 0);

  return 0;

