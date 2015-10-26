#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define FRONT 0
#define LEFT 1
#define BACK 2
#define RIGHT 3
#define TOP 4
#define BOTTOM 5

#define RED 0
#define BLUE 1
#define ORANGE 2
#define GREEN 3
#define YELLOW 4
#define WHITE 5

const char name[6][10] = { "FRONT", "LEFT", "BACK", "RIGHT", "TOP", "BOTTOM" };
const char color[6][10] = {"RED", "BLUE", "ORANGE", "GREEN", "YELLOW", "WHITE" };

int f[6][9];

void Init()
{
	puts("Colors:");
	for (int i=0; i<6; i++)
		printf("%d for %s\n", i, color[i]);
	for (int i=0; i<6; i++)
	{
		printf("Input %s\n", name[i]);
		for (int j=0; j<3; j++)
			for (int k=0; k<3; k++)
				scanf("%d", &f[i][j][k]);
	}
}

int main()
{
	Init();
	return 0;
}

