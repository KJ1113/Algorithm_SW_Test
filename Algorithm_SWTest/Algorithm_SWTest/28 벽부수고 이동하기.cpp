#pragma warning (disable :4996)
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int Map[1000][1000];
int solMap[1000][1000];
int markMap[1000][1000];
bool vist[1000][1000];
int N, M;
int dir[4][2] = { {1,0} ,{-1,0}, {0,1}, {0,-1} };
vector<pair<int, int>> v;
vector<pair<int, int>> vone;
void bfs(int y,int x,int mark) {
	queue <pair<int,int>> q;
	queue <pair<int, int>> qtwo;
	q.push(pair<int, int>(y,x));
	qtwo.push(pair<int, int>(y, x));
	vist[y][x] = true;
	int cnt = 1;
	while (!q.empty()){
		int cunY =q.front().first;
		int cunX =q.front().second;
		q.pop();
		for (int i = 0; i < 4;i++) {
			int nextY = cunY + dir[i][0];
			int nextX = cunX + dir[i][1];
			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M || vist[nextY][nextX] == true) continue;
			if (Map[nextY][nextX] == 0) {
				q.push(pair<int, int>(nextY, nextX));
				qtwo.push(pair<int, int>(nextY, nextX));
				vist[nextY][nextX] = true;
				cnt++;
			}
		}
	}
	while (!qtwo.empty()){
		solMap[qtwo.front().first][qtwo.front().second] = cnt;
		markMap[qtwo.front().first][qtwo.front().second] = mark;
		qtwo.pop();
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d",&N ,&M);
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &Map[i][j]);
			if (Map[i][j] == 0) { v.push_back(pair<int, int>(i, j)); }
			else { vone.push_back(pair<int, int>(i, j)); }
		}
	}
	int num = 1;
	for (int index = 0; index < v.size();index++) {
		if (vist[v[index].first][v[index].second] == false) {
			bfs(v[index].first, v[index].second, num++);
		}
	}
	for (int index = 0; index < vone.size(); index++) {
		int cunY = vone[index].first;
		int cunX = vone[index].second;
		int marks[4] = { -1,-1,-1,-1 };
		int sum =1;
		for (int i = 0; i < 4; i++) {
			bool falg = false;
			int nextY = cunY + dir[i][0];
			int nextX = cunX + dir[i][1];
			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M ) continue;
			if (solMap[nextY][nextX] == 0) continue;
			for (int j = 0;j<4;j++) {
				if (marks[j] == markMap[nextY][nextX]) {
					falg = true;
					break;
				}
			}
			if (falg == true) continue;
			sum = sum + solMap[nextY][nextX];
			marks[i] = markMap[nextY][nextX];
		}
		Map[cunY][cunX] = sum;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d", Map[i][j]%10);
		}
		printf("\n");
	}
	return 0;
}