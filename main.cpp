#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

// face
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

//direction
#define UU 1
#define LL 2
#define DD 4
#define RR 8

const char name[6][10] = { "FRONT", "LEFT", "BACK", "RIGHT", "TOP", "BOTTOM" };
const char color[6][10] = {"RED", "BLUE", "ORANGE", "GREEN", "YELLOW", "WHITE" };

typedef pair<int,int> PI;
#define fi first
#define se second
const PI PI_NULL(-1,-1);

int f[6][16];

void Init()
{
	puts("Colors:");
	for (int i=0; i<6; i++)
		printf("%d for %s\n", i, color[i]);
	for (int i=0; i<6; i++)
	{
		printf("Input %s\n", name[i]);
		scanf("%d%d%d%d%d%d%d%d%d",
				&f[i][LL|UU],	&f[i][UU],	&f[i][RR|UU],
				&f[i][LL],		&f[i][0],	&f[i][RR],
				&f[i][LL|DD],	&f[i][DD],	&f[i][RR|DD]
			 );

	}
}

void bottom_fetch(const PI &from, int to)
{
}

void bottom_find_edge(int dir)
{
	int bc=f[BOTTOM][0], sc=f[near(BOTTOM,dir)][0];

	if (f[UP][UU]==bc && f[BACK][UU]==sc) return PI(UP,UU);
	if (f[UP][LL]==bc && f[LEFT][UU]==sc) return PI(UP,LL);
	if (f[UP][RR]==bc && f[RIGHT][UU]==sc) return PI(UP,RR);
	if (f[UP][DD]==bc && f[FRONT][UU]==sc) return PI(UP,DD);

	// TODO: lhy
}

void bottom_find_corner(int dir1, int dir2)
{
	int bc=f[BOTTOM][0], sc1=f[near(BOTTOM,dir1)][0], sc2=f[near(BOTTOM,dir2)][0];

	if (f[UP][RR|UU]==bc && f[BACK][LL|UU]==sc1 && f[RIGHT][RR|UU]==sc2) return PI(UP,RR|UU);
	if (f[UP][RR|DD]==bc && f[RIGHT][LL|UU]==sc1 && f[FRONT][RR|UU]==sc2) return PI(UP,RR|DD);
	if (f[UP][LL|DD]==bc && f[FRONT][LL|UU]==sc1 && f[LEFT][RR|UU]==sc2) return PI(UP,LL|DD);
	if (f[UP][LL|UU]==bc && f[RIGHT][LL|UU]==sc1 && f[BACK][RR|UU]==sc2) return PI(UP,LL|UU);

	// TODO: lhy
}

void SolveFloor()
{
	bottom_fetch(bottom_find_edge(UU), UU);
	bottom_fetch(bottom_find_edge(LL), LL);
	bottom_fetch(bottom_find_edge(DD), DD);
	bottom_fetch(bottom_find_edge(RR), RR);

	bottom_fetch(bottom_find_corner(UU,RR), UU|RR);
	bottom_fetch(bottom_find_corner(RR,DD), RR|DD);
	bottom_fetch(bottom_find_corner(DD,LL), DD|LL);
	bottom_fetch(bottom_find_corner(LL,UU), LL|UU);
}

void Solve()
{
	SolveFloor();

}

int main()
{
	Init();
	Solve();
	return 0;
}

