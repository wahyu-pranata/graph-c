#include <stdio.h>
#include <stdlib.h>

int getVertex()
{
  int vertex = 0;
  printf("Masukkan jumlah vertex: ");
  scanf("%d", &vertex);
  return vertex;
}

void connectGraph(int vertexA, int vertexB, int *graph)
{
  int value;
  do
  {
    printf("%d", value);
    printf("Apakah vertex %d dan vertex %d terhubung? [Iya (0)/Tidak (1)]", vertexA, vertexB);

  } while (value != 0 || value != 1);
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
    for (int j = 0; j < vertex; j++)
    {
      if (i == j)
      {
        graph[i][j] = 0;
      }
      graph[i][j] = i + j;
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

  return 0;
}