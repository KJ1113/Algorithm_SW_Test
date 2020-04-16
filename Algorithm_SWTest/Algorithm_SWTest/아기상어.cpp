#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 20;
int N;
int Map[MAX][MAX];
int dir[4][2] = { {-1,0}, {0,-1}, {0, 1}, {1,0} };
int ans = 0;
int startY, startX;
int fishSize = 2;
int fish_EatNum = 0;
bool flag = false;
bool visted[MAX][MAX];
void bfs(int y, int x) {
	queue<pair<int, int>>q;
	q.push(pair<int, int>(y,x));
	visted[y][x] = true;

	int time = 0;
	while (!q.empty()){
		int qSize = q.size();
		int eatY;
		int eatX;
		time++;
		for (int s = 0; s < qSize; s++) {
			int conY = q.front().first;
			int conX = q.front().second;
			q.pop();
			
			for (int i = 0; i < 4;i++) {
				int nextY = conY + dir[i][0];
				int nextX = conX + dir[i][1];
				if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N) continue;
				if (visted[nextY][nextX]==true || Map[nextY][nextX] > fishSize) continue;

				if (Map[nextY][nextX] <= fishSize) {
					visted[nextY][nextX] = true;
					q.push(pair<int, int>(nextY, nextX));

					if (Map[nextY][nextX] < fishSize && Map[nextY][nextX]!=0) {
						if (flag== false) {
							eatY = nextY;
							eatX = nextX;
							flag = true;
						}
						else {
							if (nextY < eatY || (nextY==eatY && nextX < eatX)) {
								eatY = nextY;
								eatX = nextX;
							}
						}
					}
				}
			}
		}
		if (flag == true) {
			fish_EatNum++;
			startY = eatY;
			startX = eatX;
			ans += time;
			Map[eatY][eatX] = 0;
			if (fish_EatNum == fishSize) {
				fishSize++;
				fish_EatNum = 0;
			}
			return;
		}
	}
}
int main() {
	//freopen("input.txt","r",stdin);
	scanf("%d",&N);
	
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N;j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] == 9) {
				Map[i][j] = 0;
				startY=i;
				startX=j;
			}
		}
	}
	while (true) {
		bfs(startY, startX);
		if (flag == false) {
			break;
		}
		else {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					visted[i][j] = false;
				}
			}
			flag = false;
		}
	}
	printf("%d", ans);
	return 0;
}