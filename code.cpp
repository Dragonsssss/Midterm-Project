#include <iostream>
#include <cmath> 
using namespace std;

struct Point
{
	double x;
	double y;
};

const int MAX_cp = 2000; // max quantity of the changing points

double Distance(Point a, Point b);
bool generate_changingpoint(int i, int j, int Cnt1, Point start, Point end, Point changingpoint[], int d);
int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1);
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt1, int Cnt2, int w, int m);
int main()
{
	int n = 0, m = 0, w = 0, d = 0;
	cin >> n >> m >> w >> d;
	
	const int MAX_n = 1000;
	const int MAX_m = 10000;
	
	int X[MAX_m] = {0}, Y[MAX_m] = {0}, R[MAX_m] = {0}, P[MAX_m] = {0};
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
	
	Point changingpoint[MAX_cp] = {0};
	Point best_changingpoint[MAX_cp] = {0};
	double lowest_routeCost = 50000000;
	int Cnt1 = 0; // Cnt1 is the quantity of changing points
	double Dst = Distance(start, end);
	double radius = Dst / 100 + 1;
	while(true)
	{	
		Cnt1 += 1;
		bool flag = 0;	
		for(int i = 0; i < radius; i++)
		{
			for(int j = 0; j < radius; j++)
			{
				
				if((i*i + j*j) >= Dst or (i == 0 and j == 0))
				{
					continue;
				}
				
				// changing point
				bool available = generate_changingpoint(i, j, Cnt1, start, end, changingpoint, d);
				if(available == 0) // it is not available
				{
					continue;
				}
				
				// route
				Point route[2*MAX_n] = {0};
				int Cnt2 = generate_route(start, end, changingpoint, route, Cnt1); 
				// Cnt2 is the quantity of points on the route				
				
				// route cost
				double routeCost = calculate_routeCost(route, X, Y, R, P, Cnt1, Cnt2, w, m);				
				if(routeCost < lowest_routeCost)
				{
					flag = 1;
					lowest_routeCost = routeCost;
					best_changingpoint[Cnt1-1].x = changingpoint[Cnt1-1].x;
					best_changingpoint[Cnt1-1].y = changingpoint[Cnt1-1].y;												
				}
			}
		}
		
		if(flag == 1)
		{
			changingpoint[Cnt1-1].x = best_changingpoint[Cnt1-1].x;
			changingpoint[Cnt1-1].y = best_changingpoint[Cnt1-1].y;				
		}
		else
		{
			Cnt1 -= 1;
			break;
		}		
		
		if(changingpoint[Cnt1-1].x == end.x or changingpoint[Cnt1-1].y == end.y)
		{
			break;
		}  
	}
	

	// print answer
	cout << Cnt1 << " ";
	for(int i = 0; i < Cnt1 - 1; i++)
	{
		cout << best_changingpoint[i].x << " " << best_changingpoint[i].y << " ";
	}
	cout << best_changingpoint[Cnt1 - 1].x << " " << best_changingpoint[Cnt1 - 1].y;
	
	return 0;
}

double Distance(Point a, Point b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)); 
}

bool generate_changingpoint(int i, int j, int Cnt1, Point start, Point end, Point changingpoint[], int d)
{
	int x_sign = (end.x - start.x) / abs(end.x - start.x);
	int y_sign = (end.y - start.y) / abs(end.y - start.y);
	if(Cnt1 == 1)
	{
		changingpoint[Cnt1-1].x = start.x;
		changingpoint[Cnt1-1].y = start.y;
	}
	else
	{
		changingpoint[Cnt1-1].x = changingpoint[Cnt1-2].x;
		changingpoint[Cnt1-1].y = changingpoint[Cnt1-2].y;
	}	
	
	changingpoint[Cnt1-1].x += i * x_sign;
	changingpoint[Cnt1-1].y += j * y_sign;
	
	if(x_sign > 0 and y_sign > 0)
	{
		if(changingpoint[Cnt1-1].x > end.x or changingpoint[Cnt1-1].y > end.y)
		{
			return 0;
		}			
	}
	else if(x_sign > 0 and y_sign < 0)
	{
		if(changingpoint[Cnt1-1].x > end.x or changingpoint[Cnt1-1].y < end.y)
		{
			return 0;
		}			
	}
	else if(x_sign < 0 and y_sign > 0)
	{
		if(changingpoint[Cnt1-1].x < end.x or changingpoint[Cnt1-1].y > end.y)
		{
			return 0;
		}			
	}
	else if(x_sign < 0 and y_sign < 0)
	{
		if(changingpoint[Cnt1-1].x < end.x or changingpoint[Cnt1-1].y < end.y)
		{
			return 0;
		}			
	}
		
	double sum_d = 0;
	sum_d += Distance(start, changingpoint[0]);
	for(int i = 1; i < Cnt1 - 1; i++)
	{
		sum_d += Distance(changingpoint[i], changingpoint[i+1]);
	}
	sum_d += Distance(changingpoint[Cnt1 - 1], end);
	
	if(sum_d > d)
	{
		return 0;
	}	
	else
	{
		return 1;
	}	
}

int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1)
{
	Point totalpoint[MAX_cp + 2] = {0};
	totalpoint[0] = start;
	totalpoint[Cnt1+1] = end;
	for(int i = 1; i <= Cnt1; i++)
	{
		totalpoint[i] = changingpoint[i-1];
	}
	Cnt1 += 2; // length of total point
	
	int Cnt2 = 0;
	double Dst = 0, tmp = 0;
	for(int i = 0; i < Cnt1 - 1; i++)
	{
		Dst = Distance(totalpoint[i], totalpoint[i+1]);
		int xdif = totalpoint[i+1].x - totalpoint[i].x;
		int ydif = totalpoint[i+1].y - totalpoint[i].y;
		if(tmp == 0)
		{
			for(int j = 1; j <= Dst; j++)
			{
				route[Cnt2].x = totalpoint[i].x + j * xdif / Dst;
				route[Cnt2].y = totalpoint[i].y + j * ydif / Dst;
				if(route[Cnt2].x != end.x or route[Cnt2].y != end.y)
				{
					Cnt2 += 1;
				}		
			}
			tmp = Dst - static_cast<int>(Dst);			
		}
		else
		{
			for(int j = 1; j <= Dst + tmp; j++)
			{
				route[Cnt2].x = totalpoint[i].x + (j - tmp) * xdif/ Dst;
				route[Cnt2].y = totalpoint[i].y + (j - tmp) * ydif/ Dst;
				if(route[Cnt2].x != end.x or route[Cnt2].y != end.y)
				{
					Cnt2 += 1;
				}
			}
			tmp = Dst + tmp - static_cast<int>(Dst+tmp);
		}
	}
	return Cnt2; 
}

double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt1, int Cnt2, int w, int m)
{
	double routeRisk = 0, dist = 0;
	for (int i = 0; i < m; i ++)
	{
		for (int j = 0; j < Cnt2; j++)
		{
			dist = sqrt(pow((route[j].x - X[i]), 2) + pow((route[j].y - Y[i]), 2));
			if(R[i] - dist > 0)
				routeRisk += P[i] * (R[i] - dist)/ R[i];
		}
	}
	
	double routeCost = 0;
	routeCost = routeRisk + w * Cnt1;
	
	return routeCost;
}		
		
