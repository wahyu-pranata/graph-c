#include <stdio.h>
#include <stdlib.h>

int front = -1;
int rear = -1;

typedef struct
{
  int index;
  int degree;
} vertex_t;

// all function

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
    printf("Apakah vertex %d dan vertex %d terhubung? [y/n]\n ", vertexA, vertexB);
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

void enqueue(int vertex, int *queue)
{
  if (front == -1)
  {
    front = 0;
  }
  rear++;
  queue[rear] = vertex;
}

int dequeue(int *queue)
{
  int vertex = queue[front];
  front++;
  return vertex;
}

void checkConnectedGraph(int start, int **graph, int vertex)
{
  int visited[vertex];
  int queue[vertex];
  for (int i = 0; i < vertex; i++)
  {
    visited[i] = 0;
  }

  visited[start] = 1;
  enqueue(start, queue);

  printf("Hubungan graf %d: ", start);

  while (!(front == -1 || front > rear))
  {
    int current = dequeue(queue);
    printf("%d->", current);

    for (int i = 0; i < vertex; i++)
    {
      if (graph[current][i] && !visited[i])
      {
        visited[i] = 1;
        enqueue(i, queue);
      }
    }
  }

  printf("\n");
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

void swapVertex(vertex_t *x, vertex_t *y)
{
  vertex_t temp = *x;
  *x = *y;
  *y = temp;
}

// Bubble sort
vertex_t *sortVertexDegree(vertex_t vertexDegree[], int vertex)
{
  int swapped;
  for (int i = 0; i < vertex - 1; i++)
  {
    swapped = 0;
    for (int j = 0; j < vertex - i - 1; j++)
    {
      if (vertexDegree[j].degree < vertexDegree[j + 1].degree)
      {
        swapVertex(&vertexDegree[j], &vertexDegree[j + 1]);
        swapped = 1;
      }
    }
    if (swapped == 0)
    {
      break;
    }
  }

  return vertexDegree;
}

void colorVertex(vertex_t vertexDegree[], int **graph, int vertex)
{
  int colors[vertex];

  // -1 artinya belum diwarnai
  for (int i = 0; i < vertex; i++)
  {
    colors[i] = -1;
  }
  int currentColor = 1;

  for (int i = 0; i < vertex; i++)
  {
    int currentVertex = vertexDegree[i].index;

    // Kalau warna dari vertex saat ini sama dengan -1, beri warna
    if (colors[currentVertex] == -1)
    {
      colors[currentVertex] = currentColor;

      // lakukan perulangan kembali untuk vertex setelah currentVertex
      for (int j = i + 1; j < vertex; j++)
      {
        int currentVertex2 = vertexDegree[j].index;

        // Cek apakah warna dari vertex currentVertex2
        if (colors[currentVertex2] == -1)
        {
          // cek apakah vertex dan vertex2 adjacent
          int isAdjacent = 0;
          for (int k = 0; k < vertex; k++)
          {
            if ((graph[currentVertex][k] == 1 || graph[currentVertex2][k] == 1) && colors[k] == currentColor)
            {
              isAdjacent = 1;
              break;
            }
          }
          if (!isAdjacent)
          {
            colors[currentVertex2] = currentColor;
          }
        }
      }
    }

    // Setelah selesai beri warna, tambah nilai warna
    currentColor++;
  }
  for (int i = 0; i < vertex; i++)
  {
    printf("Vertex %d berwarna %d\n", i, colors[i]);
  }
}

// MAIN FUNCTIONNNN

int main()
{
  int **graph; // entah kenapa klo ga ditaruh disini gajalan, katanya ga ke define, tapi coba dlu dah
  int ch;
  int isGraphCreated = 0;
  int vertex = getVertex();
  vertex_t vertexDegree[vertex];

  do
  {
    printf("1. create graph \t\t 2. Connect Graph \t\t 3. Print Adjacency Graph \t\t 4. Degree Information \t\t 5. Graph Coloring \t\t 6. Exit \n\n");
    printf("input menu services : ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
      graph = createGraph(vertex);

      if (graph == NULL)
      {
        printf("Memory allocation failed!\n");
        return 1;
      }
      isGraphCreated = 1;

      break;
    case 2:
      if (isGraphCreated == 0)
      {
        printf("Graph not created yet...\n");
        break;
      }

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

      break;
    case 3:
      if (isGraphCreated == 0)
      {
        printf("Graph not created yet...\n");
        break;
      }
      for (int i = 0; i < vertex; i++)
      {
        for (int j = 0; j < vertex; j++)
        {
          printf("%d ", graph[i][j]);
        }
        printf("\n");
      }

      break;
    case 4:
      if (isGraphCreated == 0)
      {
        printf("Graph not created yet...\n");
        break;
      }
      checkConnectedGraph(0, graph, vertex);
      getDegree(graph, vertex, 1);

      break;

    case 5:
      if (isGraphCreated == 0)
      {
        printf("Graph not created yet...\n");
        break;
      }
      for (int i = 0; i < vertex; i++)
      {
        vertexDegree[i].index = i;
        vertexDegree[i].degree = 0;
        for (int j = 0; j < vertex; j++)
        {
          vertexDegree[i].degree += graph[i][j];
        }
      }
      sortVertexDegree(vertexDegree, vertex);

      colorVertex(vertexDegree, graph, vertex);
      break;

    case 6:
      printf("Exiting Program.......");
      exit(0);

      break;
    default:
      printf("invalid input detected!");
    }

  } while (ch != 6);

  return 0;
}
