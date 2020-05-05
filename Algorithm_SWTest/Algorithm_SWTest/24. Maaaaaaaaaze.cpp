#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<cstring>
#include<queue>
#include <vector>
#include<algorithm>
using namespace std;
int firstMap[5][5][5];
int solveMap[5][5][5];
int spoint[4][4] = { {0,0,4,4} ,{0,4,4,0}, {4,0,0,4}, {4,4,0,0 } };
int dir[6][3] = { {0,1,0}, {0,-1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
vector<int> hIndex;
int result = 999999;
struct point{
	int y, x, h;
};
void move(int h, int cnt) {
	int hMap[5][5];
	for (int c = 0; c < cnt; c++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				hMap[i][j] = solveMap[h][i][j];
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				solveMap[h][i][j] = hMap[4 - j][i];

			}
		}
	}
}
void bfs() {
	for (int K = 0; K < 4; K++) {
		int startY = spoint[K][0];
		int startX = spoint[K][1];
		int startH = 0;
		int endH = 4;
		int endY = spoint[K][2];
		int endX = spoint[K][3];
		if (solveMap[startH][startY][startX] == 0 || solveMap[endH][endY][endX] == 0) continue;
		bool vistMap[5][5][5];
		memset(vistMap, false, sizeof(vistMap));

		queue <point>q;
		point p;
		p.y = startY;
		p.x = startX;
		p.h = startH;
		q.push(p);
		vistMap[startH][startY][startX] = true;
		int cnt = 0;
		int ans = 0;

		while (!q.empty()) {
			int qsize = q.size();
			cnt++;
			if (cnt > result) { return; };
			for (int n = 0; n < qsize; n++) {
				int cunY = q.front().y;
				int cunX = q.front().x;
				int cunH = q.front().h;
				q.pop();

				for (int i = 0; i < 6; i++) {
					int nextY = cunY + dir[i][0];
					int nextX = cunX + dir[i][1];
					int nextH = cunH + dir[i][2];
					if (nextY < 0 || nextY >= 5 || nextX < 0 || nextX >= 5 || nextH < 0 || nextH >= 5) continue;
					if (vistMap[nextH][nextY][nextX] == true) continue;
					if (solveMap[nextH][nextY][nextX] == 0) continue;

					point p;
					p.y = nextY;
					p.x = nextX;
					p.h = nextH;
					q.push(p);
					vistMap[nextH][nextY][nextX] = true;
					if (nextY == endY && endX == nextX && nextH == endH) {
						ans = cnt;
						result = min(result, ans);
					};
				}
			}
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	for (int h = 0; h < 5; h++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				scanf("%d",&firstMap[h][i][j]);
			}
		}
	}
	for (int h = 0; h < 5; h++) {
		hIndex.push_back(h);
	}
	do {
		for (int h = 0; h < 5; h++) {
			memcpy(solveMap[hIndex[h]], firstMap[h], sizeof(solveMap[hIndex[h]]));
		}
		for (int one = 0; one < 4; one++) {
			for (int two = 0; two < 4; two++) {
				for (int three = 0; three < 4; three++) {
					for (int four = 0; four < 4; four++) {
						int tmpMap[5][5][5];
						memcpy(tmpMap, solveMap, sizeof(solveMap));
						move(1, one);
						move(2, two);
						move(3, three);
						move(4, four);
						bfs();
						memcpy(solveMap, tmpMap, sizeof(solveMap));
					}
				}
			}
		}
		if (result == 12) { // 12보다 짧은 최단 거리는 없음
			printf("%d", result);
			return 0;
		}
	} while (next_permutation(hIndex.begin(), hIndex.end()));
	if (result==999999) {
		printf("%d",-1);
	}
	else {
		printf("%d", result);
	}
	return 0;
}