#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 10;
int N, M, K;
int Map[MAX][MAX];
int foodMap[MAX][MAX];
int ans = 0;
int dir[8][2] = { {1,0} ,{-1,0} ,{0,1} ,{0,-1} ,{1,1} ,{1,-1} ,{-1,1} ,{-1,-1} }; 
struct plant{
	int y, x;
	int lifecnt = 1;
	bool life = true;
};
vector<plant> plist[2];
void push(plant inputP,int index) {
	plist[index].push_back(inputP);
}
void oneYear(){

	for (int index = 0; index < plist[0].size(); index++) {
		int conY = plist[0][index].y;
		int conX = plist[0][index].x;
		if (Map[conY][conX] < plist[0][index].lifecnt) {
			plist[0][index].life = false;
		}
		else {
			Map[conY][conX] -= plist[0][index].lifecnt;
			plist[0][index].lifecnt++;
		}
	}
	for (int index = 0; index < plist[0].size(); index++) {
		int conY = plist[0][index].y;
		int conX = plist[0][index].x;

		if (plist[0][index].life == false) {
			int sumfood = plist[0][index].lifecnt/2;
			Map[conY][conX] += sumfood;
		}
		else {
			if (plist[0][index].lifecnt % 5 == 0) {
				for (int i = 0; i < 8; i++) {
					int nextY = conY + dir[i][0];
					int nextX = conX + dir[i][1];
					if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N) continue;
					plant p;
					p.y = nextY;
					p.x = nextX;
					push(p,1);
				}
			}
		}
	}
	for (int index = 0; index < plist[0].size(); index++) {
		if (plist[0][index].life == true) {
			push(plist[0][index], 1);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Map[i][j] += foodMap[i][j];
		}
	}
	plist[0] = plist[1];
	plist[1].clear();
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N,&M,&K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d",&foodMap[i][j]);
			Map[i][j]=5;
		}
	}
	for (int i = 0; i < M; i++) {
		plant p;
		scanf("%d %d %d", &p.y,&p.x,&p.lifecnt);
		p.y--;
		p.x--;
		push(p,0);
	}
	for (int year = 0; year < K; year++) {
		oneYear();
	}
	printf("%d", plist[0].size()); // size == 살아있는 나무수
	return 0;
}