#include "stdio.h"
#include "conio.h"
#include "iostream"

using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2

int n,e;
int capacity[100][100], // Матрица пропускных способнотей
 flow[100][100],  // Матрица потока
 color[100],      // Цвета для вершин
 pred[100];       // Массив пути
 int head, tail;  // Начало, Конец
 int q[102];      // Очередь, хранящая номера вершин входящих в неё
//Сравнение двух целых значений
int min(int x, int y)
{
  if (x < y)
    return x;
  else
    return y;
}
//Добавить в очередь (мы ступили на вершину)
void enque(int x)
{
  q[tail] = x;     // записать х в хвост
  tail++;          // хвостом становиться следующий элемент
  color[x] = GREY; // Цвет серый (из алгоритма поиска)
}
//Убрать из очереди (Вершина чёрная, на неё не ходить)
int deque()
{
  int x = q[head];  // Записать в х значение головы
  head++;           // Соответственно номер начала очереди увеличивается
  color[x] = BLACK; // Вершина х - отмечается как прочитанная
  return x;         // Возвращается номер х прочитанной вершины
}
//Поиск в ширину
int bfs(int start, int end)
{
  int u,v;
  for( u = 0; u < n; u++ ) // Сначала отмечаем все вершины не пройденными
    color[u]=WHITE;

  head=0;   // Начало очереди 0
  tail=0;   // Хвост 0
  enque(start);      // Вступили на первую вершину
  pred[start]= -1;   // Специальная метка для начала пути
  while(head!=tail)  // Пока хвост не совпадёт с головой
  {
    u=deque();       // вершина u пройдена
    for( v = 0; v < n; v++ ) // Смотрим смежные вершины
    {
     // Если не пройдена и не заполнена
     if(color[v] == WHITE && (capacity[u][v]-flow[u][v]) > 0) {
       enque(v);  // Вступаем на вершину v
       pred[v]=u; // Путь обновляем
     }
    }
  }
  if(color[end] == BLACK) // Если конечная вершина, дошли - возвращаем 0
    return 0;
  else return 1;
}
//Максимальный поток из истока в сток
int max_flow(int source, int stock)
{
  int i,j,u;
  int maxflow=0;            // Изначально нулевой
  for( i = 0; i < n; i++ )  // Зануляем матрицу потока
    {
      for( j = 0; j < n; j++)
	  flow[i][j]=0;
    }
  while(bfs(source,stock) == 0)             // Пока сеществует путь
    {
      int delta=10000;
      for(u = n-1; pred[u] >= 0; u=pred[u]) // Найти минимальный поток в сети
	  {
	    delta=min(delta, ( capacity[pred[u]][u] - flow[pred[u]][u] ) );
      }
      for(u = n-1; pred[u] >= 0; u=pred[u]) // По алгоритму Форда-Фалкерсона
	  {
	    flow[pred[u]][u] += delta; // для каждого ребра увеличиваем поток
	    flow[u][pred[u]] -= delta; // для каждого ребра уменьшаем пропускную способность на минимальный поток
	  }
      maxflow+=delta;                       // Повышаем максимальный поток
    }
  return maxflow;
}
//Описав все эти предварительные функции, можем кратко оформить функцию main().
//Данные считаем из файла.
int main()
{
  setlocale(LC_ALL, "Russian");       // установка вывода (не ввода) русского языка в консоли (только Visual Studio)

  // Чтение из файла
  freopen ("data.txt", "r", stdin);  // аргумент 1 - путь к файлу, 2 - режим ("r" || "w"), 3 - stdin || stdout
  cin >> n;
  cout << "Количество вершин: " << n << endl;
  int i,j;
  for( i = 0; i < n; i++ )
    {
      for( j = 0; j < n; j++ )
        cin >> capacity[i][j];
    }

  cout << "Максимальный поток: " << max_flow(0,n-1) << endl;
  cout << "Матрица чего-то там: " << endl;
    for( i = 0; i < n; i++ )
    {
      for( j = 0; j < n; j++ )
        cout << flow[i][j] << " ";
	  cout << endl;
    }

  _getche();
  return 0;
}
