#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int N;
int tmpMap[20][20];
int ans = 0;
queue <int > q;
queue <int> tmpq;
bool cursh = false;
void update(int y, int x) {
	if (!tmpq.empty()) {
		tmpMap[y][x] = tmpq.front();
		tmpq.pop();
	}
	else {
		tmpMap[y][x] = 0;
	}
}
void merge() {
	if (!q.empty()) {
		while (!q.empty()) {
			int cunTmp = q.front();
			q.pop();
			if (!q.empty()) {
				int nexttmp = q.front();
				if (cunTmp == nexttmp) {
					tmpq.push(nexttmp * 2);
					q.pop();
				}
				else {
					tmpq.push(cunTmp);
				}

			}
			else {
				tmpq.push(cunTmp);
			}
		}
	}
}
void move(int cnt, int dir) {
	if (cnt == 6) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ans = max(ans, tmpMap[i][j]);

			}
		}
	}
	else {
		int Map[20][20];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				Map[i][j] = tmpMap[i][j];
			}
		}

		if (dir == 1) {
			for (int j = 0; j < N; j++) {
				for (int i = 0; i < N; i++) {
					if (tmpMap[i][j] != 0) {
						q.push(tmpMap[i][j]);
					}
				}
				merge();
				for (int i = 0; i < N; i++) {
					update(i, j);
				}
			}
		}
		else if (dir == 2) {
			for (int j = 0; j < N; j++) {
				for (int i = N - 1; i >= 0; i--) {
					if (tmpMap[i][j] != 0) {
						q.push(tmpMap[i][j]);
					}
				}
				merge();
				for (int i = N - 1; i >= 0; i--) {
					update(i, j);
				}
			}
		}
		else if (dir == 3) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (tmpMap[i][j] != 0) {
						q.push(tmpMap[i][j]);
					}
				}
				merge();
				for (int j = 0; j < N; j++) {
					update(i, j);
				}
			}
		}
		else if (dir == 4) {
			for (int i = 0; i < N; i++) {
				for (int j = N - 1; j >= 0; j--) {
					if (tmpMap[i][j] != 0) {
						q.push(tmpMap[i][j]);
					}
				}
				merge();
				for (int j = N - 1; j >= 0; j--) {
					update(i, j);
				}
			}
		}
		for (int D = 1; D <= 4;D++) {
			move(cnt + 1, D);
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				tmpMap[i][j] = Map[i][j];
			}
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &tmpMap[i][j]);
		}
	}
	move(0, 0);
	printf("%d", ans);
	return 0;
}