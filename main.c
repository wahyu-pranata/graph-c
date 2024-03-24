#include <stdio.h>
#include <stdlib.h>

int getVertex()
{
  int vertex = 0;
  printf("Masukkan jumlah vertex: ");
  scanf("%d", &vertex);
  return vertex;
}

int **createGraph(int vertex)
{
  int **graph = (int **)malloc((vertex * vertex) * sizeof(int));
  if (graph == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < vertex; i++)
  {
    graph[i] = (int *)malloc(vertex * sizeof(int));

    if (graph[i] == NULL)
    {
      return NULL;
    }
  }
  return graph;
}

void connectGraph(int vertexA, int vertexB, int **graph)
{
  char userInput = '\0';
  int isFirstAttempt = 1;

  while (userInput != 'y' && userInput != 'n')
  {
    scanf("%*c");
    if (isFirstAttempt == 0)
    {
      printf("Masukkan nilai yang benar [y/n]\n");
    }
    printf("Apakah vertex %d dan vertex %d terhubung?\n", vertexA, vertexB);
    scanf("%c", &userInput);

    if (userInput == 'y')
    {
      graph[vertexA][vertexB] = 1;
    }
    else if (userInput == 'n')
    {
      graph[vertexA][vertexB] = 0;
    }
    isFirstAttempt = 0;
  };
}

void getDegree(int **graph, int vertex, int vertexNo)
{
  int count = 0;
  for (int i = 0; i < vertex; i++)
  {
    if (graph[vertexNo][i] == 1)
    {
      count++;
    }
  }
  printf("Derajat vertek %d adalah: %d\n", vertexNo, count);
}

int main()
{
  int vertex = getVertex();
  int **graph = createGraph(vertex);

  if (graph == NULL)
  {
    printf("Memory allocation failed!\n");
    return 1;
  }

  // Banyak vertex berarti sama dengan banyak baris dan kolom
  for (int i = 0; i < vertex; i++)
  {
    for (int j = i + 1; j < vertex; j++)
    {
      if (i == j)
      {
        graph[i][j] = 0;
      }
      else
      {
        connectGraph(i, j, graph);
        graph[j][i] = graph[i][j];
      }
    }
  }

  for (int i = 0; i < vertex; i++)
  {
    for (int j = 0; j < vertex; j++)
    {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }

  getDegree(graph, vertex, 1);

  free(graph);

  return 0;
}