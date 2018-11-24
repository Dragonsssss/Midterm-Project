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
	
	Point start, end;
	cin >> start.x >> start.y >> end.x >> end.y;
	
	const int NUMBER_choice = 5; // 目前有5個choice 
	const int MAX_cp = 2; // 而其中最多有2個changing point
	double lowest_routeCost = 0;
	Point best_route[2*MAX_n] = {0};
	int Cnt3 = 0;
	for(int i = 1; i <= NUMBER_choice; i++)
	{
		// 轉折點 
		Point changingpoint[MAX_cp] = {0};
		int Cnt1 = generate_changingpoint(i, changingpoint, X, Y, R, P, d); // Cnt1為轉折點數量(ps. 如果該路線不可行則回傳Cnt為0)
		if(i != 1 and Cnt1 == 0) // 該路線不可行 
		{
			continue;
		}
		
		// 路徑(需計算風險的點) 
		Point route[2*MAX_n] = {0};
		int Cnt2 = generate_route(start, end, changingpoint, route, Cnt1); // Cnt2為需計算風險的點的數量  
		
		// 路徑風險 
		double routeCost = calculate_routeCost(route, X, Y, R, P, Cnt2, w);
		
		// 找出最佳路徑並儲存其轉折點 
		if(i == 1 or routeCost < lowest_routeCost)
		{
			lowest_routeCost = routeCost;
			for(int j = 0; j < Cnt1; j++)
			{
				best_route[j].x = route[j].x;
				best_route[j].y = route[j].x;
				Cnt3 = Cnt1; // Cnt3為"最佳路線"的轉折點數量
			}	
		}
	}
	
	// 輸出答案 
	if(Cnt3 == 0) //從起點飛到終點 
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
	
	return Cnt1; // Cnt1為轉折點數量(ps. 如果該路線不可行則回傳Cnt為0)
}
int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1)
{
	int Cnt2 = 0;
	
	return Cnt2; // Cnt2為需計算風險的點的數量 
}
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt2, int w)
{
	
}
