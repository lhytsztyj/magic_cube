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

int f[6][16], *_f[6][3][3];

void Init()
{
	fputs("Colors:", stderr);
	for (int i=0; i<6; i++)
		fprintf(stderr, "%d for %s\n", i, color[i]);
	for (int i=0; i<6; i++)
	{
		fprintf(stderr, "Input %s\n", name[i]);
		scanf("%d%d%d%d%d%d%d%d%d",
				&f[i][LL|UU],	&f[i][UU],	&f[i][RR|UU],
				&f[i][LL],		&f[i][0],	&f[i][RR],
				&f[i][LL|DD],	&f[i][DD],	&f[i][RR|DD]
			 );
		_f[i][0][0] = &f[i][LL|UU],		_f[i][0][1] = &f[i][UU],	_f[i][0][2] = &f[i][RR|UU];
		_f[i][1][0] = &f[i][LL],		_f[i][1][1] = &f[i][0],		_f[i][1][2] = &f[i][RR];
		_f[i][2][0] = &f[i][LL|DD],		_f[i][2][1] = &f[i][DD],	_f[i][2][2] = &f[i][RR|DD];
	}
}

void Output()
{
	for (int i=0; i<6; i++)
	{
		fprintf(stderr, "Face %s:", name[i]);
		for (int j=0; j<2; j++)
			fprintf(stderr, "%d %d %d\n", *_f[i][j][0], *_f[i][j][1], *_f[i][j][2]);
	}
}

int near(int face, int tow)
{
	switch (face)
	{
		case FRONT : return tow==UU ? TOP   : tow==LL ? LEFT  : tow==RR ? RIGHT : BOTTOM;
		case LEFT  : return tow==UU ? TOP   : tow==LL ? BACK  : tow==RR ? FRONT : BOTTOM;
		case BACK  : return tow==UU ? TOP   : tow==LL ? RIGHT : tow==RR ? LEFT  : BOTTOM;
		case RIGHT : return tow==UU ? TOP   : tow==LL ? FRONT : tow==RR ? BACK  : BOTTOM;
		case TOP   : return tow==UU ? BACK  : tow==LL ? LEFT  : tow==RR ? RIGHT : FRONT;
		case BOTTOM: return tow==UU ? FRONT : tow==LL ? LEFT  : tow==RR ? RIGHT : BACK;
	}
}

int diff(int p1, int p2)
{
	p1 = p1==UU ? 0 : p1==RR ? 1 : p1==DD ? 2 : 3;
	p2 = p2==UU ? 0 : p2==RR ? 1 : p2==DD ? 2 : 3;
	return p2-p1;
}

void SpinCW(int f) // used by Spin
{
	int tmp[3][3];
	memcpy(tmp, *_f[f], sizeof tmp);
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			*_f[f][j][2-i] = tmp[i][j];
}

void Circle(int **data1, int offset1, int **data2, int offset2, int **data3, int offset3, int **data4, int offset4) // used by Spin
{
	int tmp1[3], tmp2[3], tmp3[3], tmp4[3];
	for (int *i=tmp1, **j=data1; i<tmp1+3; i++, j+=offset1)
		*i = **j;
	for (int *i=tmp2, **j=data2; i<tmp2+3; i++, j+=offset2)
		*i = **j;
	for (int *i=tmp3, **j=data3; i<tmp3+3; i++, j+=offset3)
		*i = **j;
	for (int *i=tmp4, **j=data4; i<tmp4+3; i++, j+=offset4)
		*i = **j;
	for (int *i=tmp1, **j=data2; i<tmp1+3; i++, j+=offset2)
		**j = *i;
	for (int *i=tmp2, **j=data3; i<tmp2+3; i++, j+=offset3)
		**j = *i;
	for (int *i=tmp3, **j=data4; i<tmp3+3; i++, j+=offset4)
		**j = *i;
	for (int *i=tmp4, **j=data1; i<tmp4+3; i++, j+=offset1)
		**j = *i;
}

// Spin(face, t) : Spin `face` clock-wise `t` times
void Spin(int face, int t)
{
	while (t--)
	{
		SpinCW(face);
		switch (face)
		{
			case RIGHT:
				Circle(&_f[FRONT][0][2], 3, &_f[TOP][0][2], 3, &_f[BACK][2][0], -3, &_f[BOTTOM][0][2], 3);
				break;
			case LEFT:
				Circle(&_f[FRONT][0][0], 3, &_f[BOTTOM][0][0], 3, &_f[BACK][2][2], -3, &_f[TOP][0][0], 3);
				break;
			case BACK:
				Circle(&_f[TOP][0][0], 1, &_f[LEFT][2][0], -3, &_f[BOTTOM][2][2], -1, &_f[RIGHT][0][2], 3);
				break;
			case BOTTOM:
				Circle(&_f[FRONT][2][0], 1, &_f[RIGHT][2][0], 1, &_f[BACK][2][0], 1, &_f[LEFT][2][0], 1);
				break;
			case FRONT:
				Circle(&_f[TOP][2][0], 1, &_f[RIGHT][0][0], 3, &_f[BOTTOM][0][2], -1, &_f[LEFT][2][2], -3);
				break;
			case TOP:
				Circle(&_f[FRONT][0][0], 1, &_f[LEFT][0][0], 1, &_f[BACK][0][0], 1, &_f[RIGHT][0][0], 1);
		}
	}
	printf("\nSpin %s %d times:\n", name[face], t);
	Output();
}

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

PI bottom_find_edge(int dir)
{
	int bc=f[BOTTOM][0], sc=f[near(BOTTOM,dir)][0];

	if (f[TOP][UU]==bc && f[BACK][UU]==sc) return PI(TOP,UU);
	if (f[TOP][LL]==bc && f[LEFT][UU]==sc) return PI(TOP,LL);
	if (f[TOP][RR]==bc && f[RIGHT][UU]==sc) return PI(TOP,RR);
	if (f[TOP][DD]==bc && f[FRONT][UU]==sc) return PI(TOP,DD);

	// TODO: lhy
}

void bottom_fetch_edge(const PI &from, int to)
{
	int face = from.fi, pos = from.se;
	if (face==BOTTOM && pos==to) return;
	if (face==BOTTOM)
	{
		Spin(near(BOTTOM, pos), 1);
		bottom_fetch_edge(bottom_find_edge(to), to);
	} else
	if (face!=TOP && pos==DD)
	{
		Spin(face, 1);
		bottom_fetch_edge(bottom_find_edge(to), to);
	} else
	if (face!=TOP && pos==UU)
	{
		int avoided = bottom_avoid(face, to);
		Spin(face, 1);
		Spin(BOTTOM, -avoided);
		bottom_fetch_edge(bottom_find_edge(to), to);
	} else
	if (face!=TOP)
	{
		int avoided = bottom_avoid(face, to);
		if (pos==LL)
			Spin(near(face,LL), 1);
		else
			Spin(near(face,RR), -1);
		Spin(BOTTOM, -avoided);
	} else
	{
		int avoided = bottom_avoid(near(TOP, pos), to);
		Spin(near(TOP, pos), 2);
		Spin(BOTTOM, -avoided);
	}
}

PI bottom_find_corner(int dir1, int dir2)
{
	int bc=f[BOTTOM][0], sc1=f[near(BOTTOM,dir1)][0], sc2=f[near(BOTTOM,dir2)][0];

	if (f[TOP][RR|UU]==bc && f[BACK][LL|UU]==sc1 && f[RIGHT][RR|UU]==sc2) return PI(TOP,RR|UU);
	if (f[TOP][RR|DD]==bc && f[RIGHT][LL|UU]==sc1 && f[FRONT][RR|UU]==sc2) return PI(TOP,RR|DD);
	if (f[TOP][LL|DD]==bc && f[FRONT][LL|UU]==sc1 && f[LEFT][RR|UU]==sc2) return PI(TOP,LL|DD);
	if (f[TOP][LL|UU]==bc && f[RIGHT][LL|UU]==sc1 && f[BACK][RR|UU]==sc2) return PI(TOP,LL|UU);

	// TODO: lhy
}

void bottom_fetch_corner(const PI &from, int to)
{
	int face = from.fi, pos = from.se;
	
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

