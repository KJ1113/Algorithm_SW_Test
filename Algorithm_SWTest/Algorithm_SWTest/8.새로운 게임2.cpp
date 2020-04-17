#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
#include <vector>
using namespace std;
int N, K;

struct Words {
	int y;
	int x;
	int Myk;
	int dir;
};
 
struct pos
{
	int color=0;
};
pos Map[12][12];
vector <Words> Wlist;
void move(int index) {
	int conY= Wlist[index].y;
	int conX= Wlist[index].x;
	int nextY = conY;
	int nextX = conX;

	if (Wlist[index].dir == 1) {
		if (Wlist[index].y == 0) {
			nextY++;
		}
		else {
			nextY--;
		}
	}
	else if (Wlist[index].dir == 2) {
		if (Wlist[index].y == N-1) {
			nextY--;
		}
		else {
			nextY++;
		}
	}
	else if (Wlist[index].dir == 3) {
		if (Wlist[index].x == 0) {
			nextX++;
		}
		else {
			nextX--;
		}
	}
	else if(Wlist[index].dir == 4){
		if (Wlist[index].x == N - 1) {
			nextX--;
		}
		else {
			nextX++;
		}
	}

	if (Map[conY][conX].color == 1) {
	}
	else if (Map[conY][conX].color == 2) {

	}
	else {
		Wlist[index].y = nextY;
		Wlist[index].x = nextX;
	}
}
int main() {
	freopen("input.txt","r",stdin);
	scanf("%d %d", &N,&K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int input;
			scanf("%d", &input);
			Map[i][j].color = input;
		}
	}
	for (int i = 0; i < K;i++) {
		int y, x, dir;
		scanf("%d %d %d", &y,&x ,&dir);
		Words w;
		w.y = y-1;
		w.x = x-1;
		w.dir = dir;
		Wlist.push_back(w);
		
	}
	int time = 0;
	for (int i = 0; i < K; i++) {
		Words w = Wlist[i];
		cout << w.y << w.x << endl;
	}
	while (true)
	{
		time++;
		if (time ==1001) {
			printf("%d",-1);
			break;
		}
		else {
			for (int index = 0; index < K; index++) {
				move(index);
			}
		}
	}

	return 0;
}