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

int diff(int p1, int p2)
{
	p1 = p1==UU ? 0 : p1==RR ? 1 : p1==DD ? 2 : p1==LL : 3;
	p2 = p2==UU ? 0 : p2==RR ? 1 : p2==DD ? 2 : p2==LL : 3;
	return p2-p1;
}

// Spin(face, t) : Spin `face` clock-wise `t` times

int bottom_avoid(int face, int to)
{
	int from = 
		near(BOTTOM, UU)==face ? UU :
		near(BOTTOM, RR)==face ? RR :
		near(BOTTOM, DD)==face ? DD :
			LL;
	int d = diff(to, from);
	Spin(BOTTOM, d);
	return d;
}

void bottom_fetch_edge(const PI &from, int to)
{
	int face = from.fi, pos = from.se;
	if (face==BOTTOM && pos==to) return;
	if (face==BOTTOM)
	{
		Spin(near(BOTTOM,_pos), 1);
		bottom_fetch_edge(bottom_find_edge(to), to);
	} else
	if (face!=UP && pos==DD)
	{
		Spin(face, 1);
		bottom_fetch_edge(bottom_find_edge(to), to);
	} else
	if (face!=UP && pos==UU)
	{
		int avoided = bottom_avoid(face, to);
		Spin(face, 1);
		Spin(BOTTOM, -avoided);
		bottom_fetch_edge(bottom_find_edge(to), to);
	} else
	if (face!=UP)
	{
		int avoided = bottom_avoid(face, to);
		if (pos==LL)
			Spin(near(face,LL), 1);
		else
			Spin(near(face,RR), -1);
		Spin(BOTTOM, -avoided);
	} else
	{
		int avoided = bottom_avoid(near(UP, pos), to);
		Spin(near(UP, pos), 2);
		Spin(BOTTOM, -avoided);
	}
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

void bottom_fetch_corner(const &PI from, int to)
{
	int face = from.fi, pos = from.se;
	
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
	bottom_fetch_edge(bottom_find_edge(UU), UU);
	bottom_fetch_edge(bottom_find_edge(LL), LL);
	bottom_fetch_edge(bottom_find_edge(DD), DD);
	bottom_fetch_edge(bottom_find_edge(RR), RR);

	bottom_fetch_corner(bottom_find_corner(UU,RR), UU|RR);
	bottom_fetch_corner(bottom_find_corner(RR,DD), RR|DD);
	bottom_fetch_corner(bottom_find_corner(DD,LL), DD|LL);
	bottom_fetch_corner(bottom_find_corner(LL,UU), LL|UU);
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

