#include <iostream>
#include <cmath> 
using namespace std;

struct Point
{
	int x;
	int y;
};

double distance(Point a, Point b);
int generate_changingpoint(int i, Point changingpoint[], int X[], int Y[], int R[], int P[], int d, int m);
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
	
	const int NUMBER_choice = 5; //we have 5 choices now 
	const int MAX_cp = 2; //most changing point
	double lowest_routeCost = 0;
	Point best_route[2*MAX_n] = {0};
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
		
		// route risk
		double routeCost = calculate_routeCost(route, X, Y, R, P, Cnt2, w);
		
		// find best route and save the changing point
		if(i == 1 or routeCost < lowest_routeCost)
		{
			lowest_routeCost = routeCost;
			for(int j = 0; j < Cnt1; j++)
			{
				best_route[j].x = route[j].x;
				best_route[j].y = route[j].x;
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

int generate_changingpoint(int i, Point changingpoint[], int X[], int Y[], int R[], int P[], int d, int m)
{
	int Cnt1 = 0;
	if(i == 1)
	{
		return 0;
	}
	else if(i == 2)
	{
		int sum_x=0;
		for(int j=0;j<m;j++)
			sum_x+=X[j];
		changingpoint[0].x=sum_x/m;
		
		int sum_y=0;
		for(int j=0;j<m;j++)
			sum_y+=Y[j];
		changingpoint[0].y=sum_y/m;	
		
		return 1;
	}
	else if(i == 3)
	{
		int sum_p=0;
		for(int j=0;j<m;j++)
			sum_p+=P[j];
		
		int sum_x=0;
		for(int j=0;j<m;j++)
			sum_x+=X[j]*(sum_p-P[j])/((m-1)*sum_p);
		changingpoint[0].x=sum_x;
		
		int sum_y=0;
		for(int j=0;j<m;j++)
			sum_y+=Y[j]*(sum_p-P[j])/((m-1)*sum_p);
		changingpoint[0].y=sum_y;	
		
		return 1;
	}
	else if(i == 4)
	{
		int sum_x=0;
		for(int j=0;j<m;j++)
			sum_x+=X[j];
		changingpoint[0].x=sum_x/m;
		
		int sum_y=0;
		for(int j=0;j<m;j++)
			sum_y+=Y[j];
		changingpoint[0].y=sum_y/m;
		
		int sum_p=0;
		for(int j=0;j<m;j++)
			sum_p+=P[j];
		
		sum_x=0;
		for(int j=0;j<m;j++)
			sum_x+=X[j]*(sum_p-P[j])/((m-1)*sum_p);
		changingpoint[1].x=sum_x;
		
		sum_y=0;
		for(int j=0;j<m;j++)
			sum_y+=Y[j]*(sum_p-P[j])/((m-1)*sum_p);
		changingpoint[1].y=sum_y;
	
		return 2;	
	}
	else if(i == 5)
	{
		int sum_p=0;
		for(int j=0;j<m;j++)
			sum_p+=P[j];
		
		int sum_x=0;
		for(int j=0;j<m;j++)
			sum_x+=X[j]*(sum_p-P[j])/((m-1)*sum_p);
		changingpoint[0].x=sum_x;
		
		int sum_y=0;
		for(int j=0;j<m;j++)
			sum_y+=Y[j]*(sum_p-P[j])/((m-1)*sum_p);
		changingpoint[0].y=sum_y;
		
		sum_x=0;
		for(int j=0;j<m;j++)
			sum_x+=X[j];
		changingpoint[0].x=sum_x/m;
		
		sum_y=0;
		for(int j=0;j<m;j++)
			sum_y+=Y[j];
		changingpoint[0].y=sum_y/m;	
		
		return 2;
	}
	
	return Cnt1;
	// Cnt1 is the number of changing point if it is unavailable then return 0
}
int generate_route(Point start, Point end, Point changingpoint[], Point route[], int Cnt1)
{
	int Cnt2 = 0;
	
	return Cnt2; // Cnt2 is the changing point quantity that need to be calculate risk
}
double calculate_routeCost(Point route[], int X[], int Y[], int R[], int P[], int Cnt2, int w)
{
	
}
