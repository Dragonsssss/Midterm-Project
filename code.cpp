#include <iostream>
#include <cmath> 
using namespace std;

struct Point
{
	int x;
	int y;
};

double distance(Point a, Point b);
int generate_changingpoint(int i, Point changingpoint[], int X[], int Y[], int R[], int P[], int d);
int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1);
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt2, int w);
int main()
{
	int n = 0, m = 0, w = 0, d = 0;
	cin >> n >> m >> w >> d;
	
	const int MAX_n = 1000;
	
	int X[MAX_n] = {0}, Y[MAX_n] = {0}, R[MAX_n] = {0}, P[MAX_n] = {0};
	for(int i = 0; i < m; i++)
		cin >> X[i];
	for(int i = 0; i < m; i++)
		cin >> Y[i];
	for(int i = 0; i < m; i++)
		cin >> R[i];
	for(int i = 0; i < m; i++)
		cin >> P[i];
	
	int sx = 0, sy = 0, ex = 0, ey = 0;
	Point start, end;
	cin >> start.x >> start.y >> end.x >> end.y;
	
	const int NUMBER_choice = 5; // �ثe��5��choice 
	const int MAX_cp = 2; // �Ө䤤�̦h��2��changing point
	double lowest_routeCost = 0;
	Point best_route[2*MAX_n] = {0};
	int Cnt3 = 0;
	for(int i = 1; i <= NUMBER_choice; i++)
	{
		// ����I 
		Point changingpoint[MAX_cp] = {0};
		int Cnt1 = generate_changingpoint(i, changingpoint, X, Y, R, P, d); // Cnt1������I�ƶq(ps. �p�G�Ӹ�u���i��h�^��Cnt��0)
		if(i != 1 and Cnt1 == 0) // �Ӹ�u���i�� 
		{
			continue;
		}
		
		// ��|(�ݭp�⭷�I���I) 
		Point route[2*MAX_n] = {0};
		int Cnt2 = generate_route(start, end, changingpoint, route, Cnt1); // Cnt2���ݭp�⭷�I���I���ƶq  
		
		// ��|���I 
		double routeCost = calculate_routeCost(route, X, Y, R, P, Cnt2, w);
		
		// ��X�̨θ�|���x�s������I 
		if(i == 1 or routeCost < lowest_routeCost)
		{
			lowest_routeCost = routeCost;
			for(int j = 0; j < Cnt1; j++)
			{
				best_route[j].x = route[j].x;
				best_route[j].y = route[j].x;
				Cnt3 = Cnt1; // Cnt3��"�̨θ�u"������I�ƶq
			}	
		}
	}
	
	// ��X���� 
	if(Cnt3 == 0) //�q�_�I������I 
	{
		cout << 0;
	}	
	else
	{
		cout << Cnt3 << " ";
		for(int i = 0; i < Cnt3 - 1; i++)
		{
			cout << best_route[i].x << " " << best_route[i].y << " ";
		}
		cout << best_route[Cnt3 - 1].x << " " << best_route[Cnt3 - 1].y;
	}
	
	return 0;
}

double distance(Point a, Point b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)); 
}

int generate_changingpoint(int i, Point changingpoint[], int X[], int Y[], int R[], int P[], int d)
{
	int Cnt1 = 0;
	if(i == 1)
	{
		
	}
	else if(i == 2)
	{
		
	}
	else if(i == 3)
	{
		
	}
	else if(i == 4)
	{
		
	}
	else if(i == 5)
	{
		
	}
	
	return Cnt1; // Cnt1������I�ƶq(ps. �p�G�Ӹ�u���i��h�^��Cnt��0)
}
int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1)
{
	int Cnt2 = 0;
	
	return Cnt2; // Cnt2���ݭp�⭷�I���I���ƶq 
}
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt2, int w)
{
	
}
