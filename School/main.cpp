#include "stdio.h"
#include "conio.h"
#include "iostream"

using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2

int n,e;
int capacity[100][100], // ������� ���������� �����������
 flow[100][100],  // ������� ������
 color[100],      // ����� ��� ������
 pred[100];       // ������ ����
 int head, tail;  // ������, �����
 int q[102];      // �������, �������� ������ ������ �������� � ��
//��������� ���� ����� ��������
int min(int x, int y)
{
  if (x < y)
    return x;
  else
    return y;
}
//�������� � ������� (�� ������� �� �������)
void enque(int x)
{
  q[tail] = x;     // �������� � � �����
  tail++;          // ������� ����������� ��������� �������
  color[x] = GREY; // ���� ����� (�� ��������� ������)
}
//������ �� ������� (������� ������, �� �� �� ������)
int deque()
{
  int x = q[head];  // �������� � � �������� ������
  head++;           // �������������� ����� ������ ������� �������������
  color[x] = BLACK; // ������� � - ���������� ��� �����������
  return x;         // ������������ ����� � ����������� �������
}
//����� � ������
int bfs(int start, int end)
{
  int u,v;
  for( u = 0; u < n; u++ ) // ������� �������� ��� ������� �� �����������
    color[u]=WHITE;

  head=0;   // ������ ������� 0
  tail=0;   // ����� 0
  enque(start);      // �������� �� ������ �������
  pred[start]= -1;   // ����������� ����� ��� ������ ����
  while(head!=tail)  // ���� ����� �� ������� � �������
  {
    u=deque();       // ������� u ��������
    for( v = 0; v < n; v++ ) // ������� ������� �������
    {
     // ���� �� �������� � �� ���������
     if(color[v] == WHITE && (capacity[u][v]-flow[u][v]) > 0) {
       enque(v);  // �������� �� ������� v
       pred[v]=u; // ���� ���������
     }
    }
  }
  if(color[end] == BLACK) // ���� �������� �������, ����� - ���������� 0
    return 0;
  else return 1;
}
//������������ ����� �� ������ � ����
int max_flow(int source, int stock)
{
  int i,j,u;
  int maxflow=0;            // ���������� �������
  for( i = 0; i < n; i++ )  // �������� ������� ������
    {
      for( j = 0; j < n; j++)
	  flow[i][j]=0;
    }
  while(bfs(source,stock) == 0)             // ���� ���������� ����
    {
      int delta=10000;
      for(u = n-1; pred[u] >= 0; u=pred[u]) // ����� ����������� ����� � ����
	  {
	    delta=min(delta, ( capacity[pred[u]][u] - flow[pred[u]][u] ) );
      }
      for(u = n-1; pred[u] >= 0; u=pred[u]) // �� ��������� �����-����������
	  {
	    flow[pred[u]][u] += delta; // ��� ������� ����� ����������� �����
	    flow[u][pred[u]] -= delta; // ��� ������� ����� ��������� ���������� ����������� �� ����������� �����
	  }
      maxflow+=delta;                       // �������� ������������ �����
    }
  return maxflow;
}
//������ ��� ��� ��������������� �������, ����� ������ �������� ������� main().
//������ ������� �� �����.
int main()
{
  setlocale(LC_ALL, "Russian");       // ��������� ������ (�� �����) �������� ����� � ������� (������ Visual Studio)

  // ������ �� �����
  freopen ("data.txt", "r", stdin);  // �������� 1 - ���� � �����, 2 - ����� ("r" || "w"), 3 - stdin || stdout
  cin >> n;
  cout << "���������� ������: " << n << endl;
  int i,j;
  for( i = 0; i < n; i++ )
    {
      for( j = 0; j < n; j++ )
        cin >> capacity[i][j];
    }

  cout << "������������ �����: " << max_flow(0,n-1) << endl;
  cout << "������� ����-�� ���: " << endl;
    for( i = 0; i < n; i++ )
    {
      for( j = 0; j < n; j++ )
        cout << flow[i][j] << " ";
	  cout << endl;
    }

  _getche();
  return 0;
}
