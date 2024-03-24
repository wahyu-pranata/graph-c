# Penjelasan Code
## Main Function
### Pembuatan Graph
```c
int vertex = getVertex();
int **graph = createGraph(vertex);
```
Baris pertama memanggil function `getVertex`, yang dimana akan meminta user untuk memasukkan jumlah vertex yang diinginkan.

Baris kedua memanggil function `createGraph` yang menerima argumen jumlah vertex yang ada. Fungsi tersebut mengembalikan nilai array 2 dimensi yang disimpan pada variabel `graph`

### Pengecekan Nilai Graph
```c
if (graph == NULL)
{
  printf("Memory allocation failed!\n");
  return 1;
}
```
Jika nilai graph yang dikembalikan function `createGraph` adalah `NULL`, maka hentikan proses dan tampilkan pesan gagal.

### Isi Nilai Graph/Matriks Ketetanggaan
```c
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
```
Pada bagian ini, terdapat dua kali looping dengan `for`. `for` yang pertama digunakan untuk mengulang baris yang ada pada matriks. Sedangkan `for` kedua digunakan untuk mengulang tiap kolom yang ada pada tiap baris.

Pada saat nilai kolom dan baris sama, maka tempatkan nilai 0. Jika tidak, maka tanya user –dengan function `connectGraph` yang menerima argumen vertex A, vertex B, dan graph yang dituju– nilai yang diinginkan.

Karena graph yang dibuat adalah graph tak berarah, maka untuk nilai `graph[i][j]` sama dengan `graph[j][i]`.

### Mencetak Isi Matriks Ketetanggaan
```c
for (int i = 0; i < vertex; i++)
{
  for (int j = 0; j < vertex; j++)
  {
    printf("%d ", graph[i][j]);
  }
  printf("\n");
}
```
Mirip seperti sebelumnya, terdapat dua buah `for` loop. Tiap perulangan pertama akan mencetak baris baru, dan setiap perulangan kedua akan mencetak nilai dari matriks.

### Mengecek Keterhubungan & Derajat
```c
checkConnectedGraph(0, graph, vertex);
getDegree(graph, vertex, 1);
```
Function `checkConnectedGraph` digunakan untuk mengecek keterhubungan dari setiap vertex yang ada pada graph. Sedangkan function `getDegree` digunakan untuk mencetak derajat dari vertex yang diinginkan. Untuk penjelasan lengkap tentang function tersebut akan dijelaskan di beberapa bagian berikutnya.

## Membuat Matriks Ketetanggaan
Terdapat 2 function utama yang digunakan untuk membuat matriks ketetanggaan. Yaitu `getVertex` dan `createGraph`.

### `getVertex()`
```c
int vertex = 0;

printf("Masukkan jumlah vertex: ");
scanf("%d", &vertex);

return vertex;
```
Function ini akan menerima input user terlebih dahulu, lalu akan mengembalikan nilai yang sudah user input-kan.
### `createGraph(int vertex)`
```c
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
```
Function `createGraph` berfungsi untuk membuat representasi graph dalam bentuk matriks ketetanggaan. Pada baris pertama, kita mengalokasikan memori yang dibutuhkan oleh variabel `graph`. Karena kita membutuhkan array 2 dimensi, maka kita bisa menggunakan *double pointer*. Memori yang dialokasikan berdasarkan banyak vertex yang sudah diterima pada argumen function.

Jika nilai graph ternyata `NULL`, maka kembalikan nilai `NULL` (yang dimana akan diterima oleh main function).

Setelah mengalokasikan memori ke variabel `graph`, karena kita membuat array 2 dimensi, kita juga harus mengalokasikan memori untuk setiap baris yang ada pada variabel tersebut. Dengan `for` loop, kita dapat mengalokasikan memori untuk setiap baris pada matriks yang sudah dibuat.

Sama seperti sebelumnya, jika alokasi memmori mengembalikan nilai `NULL`, maka kembalikan nilai `NULL`.

Setelah itu, kembalikan nilai `graph`.

## Membuat Koneksi Antar Vertex
Function `connectGraph` merupakan function utama untuk tugas ini.
### connectGraph(int vertexA, int vertexB, int **graph)
```c
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
```
Menerima 3 argumen, yaitu 2 vertex yang ingin dihubungkan serta graph yang dituju.

Variabel `userInput` berfungsi untuk menampung nilai user yang berupa char. Serta terdapat variabel `isFirstAttempt` yang digunakan untuk bantuan pada validasi.

Selama nilai dari input user bukan `y` atau `n`, maka tampilkan arahan untuk memasukkan input. Input yang diterima adalah `y` dan `n` saja. Selain itu, maka user harus mengulang lagi.

Jika nilai yang dimasukkan adalah `y`, maka nila 1 akan dimasukkan pada elemen matriks pada baris `vertexA` dan kolom `vertexB`. Sedangkan jika `n`, maka nilai 0 yang akan dimasukkan.

## Mendapatkan Derajat Vertex
Untuk mendapatkan derajat vertex, logikanya adalah tambahkan semua nilai 1 secara horizontal atau vertikal.
### getDegree(int **graph, int vertex, int vertexNo)
```c
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
```
Function ini menerima 3 buah argumen, yaitu graph yang dituju, banyak vertex yang ada, serta nomor vertex yang ingin dicari.

Terdapat variabel `count` yang digunakan menyimpan nilai derajat.

Seperti yang sudah dijelaskan sebelumnya, untuk mendapatkan derajat sebuah vertex, kita cukup menghitung nilai 1 secara horizontal atau vertikal. Disini dilakukan pengulangan untuk setiap baris yang ada, jika terapat nilai 1, maka tambahkan nilai 1 ke variabel `count`.

## Mengecek Graph Terhubung
Pada pengecekan graph terhubung, digunakan metode BFS. Untuk detail bagaimana algoritma ini bekerja, lihat pada link [berikut](https://www.geeksforgeeks.org/c-program-for-breadth-first-search-or-bfs-for-a-graph/)

### Variabel Global
Terdapat 2 variabel global yang digunakan, yaitu:
```c
int front = -1;
int rear = -1;
```
