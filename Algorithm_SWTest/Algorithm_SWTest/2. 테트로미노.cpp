#pragma warning (disable :4996)
#include<iostream>
#include<cstdio>
using namespace std;
int N, M;
int Map[501][501];
int ens = 0;
int dir[4][2] = { {1,0} ,{-1,0} ,{0,1}, {0,-1} };
bool sizeCheck(int nextY,int nextX) {

	if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) {
		return false;
	}
	else {
		return true;
	}
}
void dfs(int y , int x, int cnt ,int sum) {

	if (cnt ==4) {
		if (sum > ens) {
			ens == sum;
		}
	}
	else {


		for (int i = 0; i < 4; i++) {
			int nextY = y + dir[i][0];
			int nextX = x + dir[i][1];

			if (sizeCheck(nextY, nextX)==false ) continue;
			if (Map[nextY][nextX] == 0) continue;

			int tmp = Map[nextY][nextX];
			Map[nextY][nextX] = 0;
			dfs(nextY, nextX, cnt + 1, sum + tmp);
			Map[nextY][nextX] = tmp;

		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d",&N,&M);

	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M;j++) {
			scanf("%d", &Map[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d", Map[i][j]);
		}
		printf("\n");
	}

	return 0;
}