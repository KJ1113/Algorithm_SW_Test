#pragma warning (disable :4996)
#include<iostream>
#include<cstdio>
using namespace std;
int N, M;
int Map[501][501];
bool boolMap[501][501];
int ens = 0;
int dir[4][2] = { {1,0} ,{-1,0} ,{0,1}, {0,-1} };
int upY, downY;
int leftX, rightX;
void fuckYoudir(int y ,int x) {
	int sum = 0;
	upY = y - 1;
	downY = y + 1;
	leftX = x - 1;
	rightX = x + 1;
	//  け
	//けけけ
	if (upY >= 0 && leftX >= 0 && rightX < M) {
		sum = Map[upY][x] + Map[y][leftX] + Map[y][rightX] + Map[y][x];
		if (sum > ens) {
			ens = sum;
		}
	}
	// けけけ
	//   け
	if (downY < N && leftX >= 0 && rightX < M) {
		sum = Map[downY][x] + Map[y][leftX] + Map[y][rightX] + Map[y][x];
		if (sum > ens) {
			ens = sum;
		}
	}
	// け
	// けけ
	// け
	if (upY >= 0 && downY < N && rightX < M) {
		sum = Map[upY][x] + Map[downY][x] + Map[y][rightX] + Map[y][x];
		if (sum > ens) {
			ens = sum;
		}
	}
	//   け
	// けけ
	//   け
	if (upY >= 0 && downY < N && leftX >= 0) {
		sum = Map[upY][x] + Map[downY][x] + Map[y][leftX] + Map[y][x];
		if (sum > ens) {
			ens = sum;
		}
	}
}
void dfs(int y , int x, int cnt ,int sum) {

	if (cnt >= 4) {
		if (sum > ens) {
			ens = sum;
		}
		return;
	}
	else {

		for (int i = 0; i < 4; i++) {
			int nextY = y + dir[i][0];
			int nextX = x + dir[i][1];

			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) continue;
			if (boolMap[nextY][nextX] == true) continue;

			boolMap[nextY][nextX] = true;
			dfs(nextY, nextX, cnt + 1, sum + Map[nextY][nextX]);
			boolMap[nextY][nextX] = false;

		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d",&N,&M);
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M;j++) {
			scanf("%d", &Map[i][j]);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			boolMap[i][j] = true;
			dfs(i, j, 1, Map[i][j]);
			fuckYoudir(i,j);
			boolMap[i][j] = false;
		}
	}
	printf("%d", ens);
	return 0;
}