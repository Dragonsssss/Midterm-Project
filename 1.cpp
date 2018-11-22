#include <iostream>
using namespace std;

int main()
{
	int n = 0, m = 0, w = 0, d = 0;
	cin >> n >> m >> w >> d;
	
	const int MAX_n = 1000;
	
	int X[MAX_n] = {0}, Y[MAX_n] = {0}, R[MAX_n] = {0}, P[MAX_n] = {0};
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(i == 0)
				cin >> X[j];
			else if(i == 1)
				cin >> Y[j];
			else if(i == 2)
				cin >> R[j];
			else
				cin >> P[j];
		}
	}
	
	int sx = 0, sy = 0, ex = 0, ey = 0;
	cin >> sx >> sy >> ex >> ey;
	
	return 0;
}

