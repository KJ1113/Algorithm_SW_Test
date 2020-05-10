#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
using namespace std;
int MaxY, MaxX;
int goalY, goalX;
int dir[4][2] = { {0,1} ,{0,-1} ,{1,0}, {-1,0} };
char Map[50][50];
bool vist[50][50];
bool watervist[50][50];
int ans = 999999;
queue<pair<int, int>> waterq;
queue<pair<int, int>> sq;
void sol() {
	int cnt = 0;
	while (true){
		cnt++;
		if (!waterq.empty()) {
			int cunY = waterq.front().first;
			int cunX = waterq.front().second;
			watervist[cunY][cunX] = true;
			int qsize = waterq.size();
			for (int k = 0; k < qsize; k++) {
				cunY = waterq.front().first;
				cunX = waterq.front().second;
				waterq.pop();

				for (int d = 0; d < 4; d++) {
					int nextY = dir[d][0] + cunY;
					int nextX = dir[d][1] + cunX;
					if (nextY < 0 || nextX < 0 || nextY >= MaxY || nextX >= MaxX|| watervist[nextY][nextX] ==true) continue;
					if (Map[nextY][nextX] == 'X' || Map[nextY][nextX] == 'D' || Map[nextY][nextX] == '*')continue;
					Map[nextY][nextX] = '*';
					watervist[nextY][nextX] = true;
					waterq.push(pair<int, int>(nextY, nextX));
				}
			}
		}

		if (!sq.empty()) {
			int cunsY = sq.front().first;
			int cunsX = sq.front().second;
			vist[cunsY][cunsX] = true;
			int sqsize = sq.size();
			for (int k = 0; k < sqsize; k++) {
				cunsY = sq.front().first;
				cunsX = sq.front().second;
				sq.pop();
				for (int d = 0; d < 4; d++) {
					int nextY = dir[d][0] + cunsY;
					int nextX = dir[d][1] + cunsX;
					if (nextY < 0 || nextX < 0 || nextY >= MaxY || nextX >= MaxX) continue;
					if (Map[nextY][nextX] == 'X' || Map[nextY][nextX] == '*'|| vist[nextY][nextX]==true)continue;
					Map[nextY][nextX] = 'S';
					vist[nextY][nextX] = true;
					sq.push(pair<int, int>(nextY, nextX));
					if (nextY == goalY && goalX == nextX) {
						ans = cnt;
						return;
					}
				}
			}
		}
		if (sq.empty() && !waterq.empty()) break;
		if (cnt > MaxY * MaxX * 2) break;
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> MaxY >> MaxX;
	for (int i = 0; i < MaxY; i++) {
		for (int j = 0; j < MaxX; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'D') {
				goalY = i;
				goalX = j;
			}
			if (Map[i][j] == 'S') {
				sq.push(pair<int, int>(i, j));
			}
			if (Map[i][j] == '*') {
				waterq.push(pair<int, int>(i, j));
			}
		}
	}
	sol();
	if (ans == 999999) {
		cout << "KAKTUS";
	}
	else {
		cout << ans;
	}
	return 0;
}