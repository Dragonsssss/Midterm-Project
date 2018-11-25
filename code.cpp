#include <iostream>
#include <cmath> 
using namespace std;

struct Point
{
	double x;
	double y;
};

const int NUMBER_choice = 3; //we have 3 choices now 
const int MAX_cp = 2; //most changing point

double Distance(Point a, Point b);
int generate_changingpoint(int i, Point changingpoint[], int X[], int Y[], int R[], int P[], int d, int m);
int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1);
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt1, int Cnt2, int w, int m);
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
	
	double lowest_routeCost = 0;
	Point best_changingpoint[MAX_cp] = {0};
	int Cnt3 = 0;
	for(int i = 1; i <= NUMBER_choice; i++)
	{
		// changing point
		Point changingpoint[MAX_cp] = {0};
		int Cnt1 = generate_changingpoint(i, changingpoint, X, Y, R, P, d, m); 
		// Cnt1 is the quantity of changing points(if the point is unavailable, return 0)
		if(i != 1 and Cnt1 == 0) // unavailable route
		{
			continue;
		}
		
		// route(need to calculate risk)
		Point route[2*MAX_n] = {0};
		int Cnt2 = generate_route(start, end, changingpoint, route, Cnt1); 
		// Cnt2 is the quantity that need to calculate risk 

		// route cost
		double routeCost = calculate_routeCost(route, X, Y, R, P, Cnt1, Cnt2, w, m);
		
		// find best route and save the changing point
		if(i == 1 or routeCost < lowest_routeCost)
		{
			lowest_routeCost = routeCost;
			for(int j = 0; j < Cnt1; j++)
			{
				best_changingpoint[j].x = changingpoint[j].x;
				best_changingpoint[j].y = changingpoint[j].y;
				Cnt3 = Cnt1; // Cnt3 is the best number of changing point
			}	
		}
	}
	
	// print answer
	if(Cnt3 == 0) //from beg to end
	{
		cout << 0;
	}	
	else
	{
		cout << Cnt3 << " ";
		for(int i = 0; i < Cnt3 - 1; i++)
		{
			cout << best_changingpoint[i].x << " " << best_changingpoint[i].y << " ";
		}
		cout << best_changingpoint[Cnt3 - 1].x << " " << best_changingpoint[Cnt3 - 1].y;
	}

	return 0;
}

double Distance(Point a, Point b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)); 
}

int generate_changingpoint(int i, Point changingpoint[], int X[], int Y[], int R[], int P[], int d, int m)
{
	if(i == 1)
	{
		changingpoint[0].x = 0;
		changingpoint[0].y = 0;
		
		return 0;
	}
	else if(i == 2)
	{
		changingpoint[0].x = 5;
		changingpoint[0].y = 1;
		
		return 1;
	}
	else if(i == 3)
	{
		changingpoint[0].x = 2;
		changingpoint[0].y = 3;
		changingpoint[1].x = 4;
		changingpoint[1].y = 4;
		
		return 2;
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
				Cnt2 += 1;
			}
			tmp = Dst - static_cast<int>(Dst);			
		}
		else
		{
			for(int j = 1; j < Dst + tmp; j++)
			{
				route[Cnt2].x = totalpoint[i].x + (j - tmp) * xdif/ Dst;
				route[Cnt2].y = totalpoint[i].y + (j - tmp) * ydif/ Dst;
				Cnt2 += 1;
			}
			tmp = Dst + tmp - static_cast<int>(Dst+tmp);
		}
	}
	return Cnt2; // Cnt2 is the changing point quantity that need to be calculate risk
}
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt1, int Cnt2, int w, int m)
{
	//routecost = route risk + w(k - 1) 
	//calculate routerisk
	double routeRisk = 0, dist = 0;
	for (int i = 0; i < m; i ++)
	{
		for (int j = 0; j < Cnt2; j ++)
		{
			dist = sqrt(pow((route[j].x - X[i]), 2) + pow((route[j].y - Y[i]), 2));
			if (R[i] - dist > 0)
				routeRisk += P[i] * (R[i] - dist)/ R[i];
		}
	}
	double routeCost = 0;
	routeCost = routeRisk + w * Cnt1; 
	return routeCost;
}
