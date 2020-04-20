#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 101;
int N, K, L;
int Map[MAX][MAX];
int ConDir = 4; //1상 2하 3좌 4우
int time = 1;
int index = 0;
queue <pair<int, int>> dummy;
vector <pair<int, char>> timeDir;
void dirchange() {
	if (ConDir == 1) {
		if (timeDir[index].second == 'L') {
			ConDir = 3;
		}
		else {
			ConDir = 4;
		}
	}
	else if (ConDir == 2) {
		if (timeDir[index].second == 'L') {
			ConDir = 4;
		}
		else {
			ConDir = 3;
		}
	}
	else if (ConDir == 3) {
		if (timeDir[index].second == 'L') {
			ConDir = 2;
		}
		else {
			ConDir = 1;
		}
	}
	else {
		if (timeDir[index].second == 'L') {
			ConDir = 1;
		}
		else {
			ConDir = 2;
		}
	}
}
int main() {
	dummy.push(pair<int, int>(0, 0));
	Map[0][0] = 2;
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &K);
	for (int k = 0; k < K; k++) {
		int y, x;
		scanf("%d %d", &y, &x);
		Map[y-1][x-1] = 1;
	}
	scanf("%d", &L);
	for (int l = 0; l < L; l++) {
		int time;
		char c;
		scanf("%d %c", &time, &c);
		timeDir.push_back(pair<int, char>(time, c));
	}

	int T = timeDir[0].first;
	char Dir = timeDir[0].second;
	while (true) {
		int conY = dummy.back().first;
		int conX = dummy.back().second;
		int nextY = conY;
		int nextX = conX;
		// 이동 위치 설정
		if (ConDir == 1) {
			nextY--;
		}
		else if (ConDir == 2) {
			nextY++;
		}
		else if (ConDir == 3) {
			nextX--;
		}
		else {
			nextX++;
		} 
		// 종료조건 탐색
		if (Map[nextY][nextX] == 2 || nextY < 0 || nextY >= N || nextX < 0 || nextX >= N) {
			printf("%d",time);
			return 0;
		}
		else {
			dummy.push(pair<int, int>(nextY, nextX));
			if (Map[nextY][nextX] == 0) {
				Map[dummy.front().first][dummy.front().second] = 0;
				dummy.pop();
			}
			Map[nextY][nextX] = 2;
		}

		//초가끝난뒤 머리 방향변경	
		if (time == T) {
			dirchange();
			index++;
			if (index != timeDir.size()) {
				T = timeDir[index].first;
				Dir = timeDir[index].second;
			}
		}
		time++;
	};
	return 0;
}