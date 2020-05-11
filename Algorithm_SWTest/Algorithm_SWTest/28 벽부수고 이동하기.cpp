#pragma warning (disable :4996)
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
struct point {
	int y, x, d;
};
queue <point> q;
char Map[51][51];
int N ,fy,fx;
int ans = 999999;
int vist[51][51][4];
int dir[4][2] = { {-1,0} ,{1,0}, {0,-1}, {0,1} };
void move() {
	while (!q.empty()){
		int cunY = q.front().y;
		int cunX = q.front().x;
		int cund = q.front().d;
		q.pop();
		int nextY = cunY + dir[cund][0];
		int nextX = cunX + dir[cund][1];
		if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N) continue;
		if ( Map[nextY][nextX] == '*') continue;
		if (Map[nextY][nextX] == '.') {
			if (vist[nextY][nextX][cund] > vist[cunY][cunX][cund]) {
				vist[nextY][nextX][cund] = vist[cunY][cunX][cund];
				point p;
				p.y = nextY;
				p.x = nextX;
				p.d = cund;
				q.push(p);
			}
		}
		if (Map[nextY][nextX] == '!') {
			
			if (vist[nextY][nextX][cund] > vist[cunY][cunX][cund]) {
				vist[nextY][nextX][cund] = vist[cunY][cunX][cund];
				point p;
				p.y = nextY;
				p.x = nextX;
				p.d = cund;
				q.push(p);
			}
			if (cund == 0 || cund ==1 ) {
				if (vist[nextY][nextX][2] > vist[cunY][cunX][cund] + 1) {
					vist[nextY][nextX][2] = vist[cunY][cunX][cund] + 1;
					point p;
					p.y = nextY;
					p.x = nextX;
					p.d = 2;
					q.push(p);
				}
				if (vist[nextY][nextX][3] > vist[cunY][cunX][cund] + 1) {
					vist[nextY][nextX][3] = vist[cunY][cunX][cund] + 1;
					point p;
					p.y = nextY;
					p.x = nextX;
					p.d = 3;
					q.push(p);
				}
			}
			else {
				if (vist[nextY][nextX][0] > vist[cunY][cunX][cund] + 1) {
					vist[nextY][nextX][0] = vist[cunY][cunX][cund] + 1;
					point p;
					p.y = nextY;
					p.x = nextX;
					p.d = 0;
					q.push(p);
				}
				if (vist[nextY][nextX][1] > vist[cunY][cunX][cund] + 1) {
					vist[nextY][nextX][1] = vist[cunY][cunX][cund] + 1;
					point p;
					p.y = nextY;
					p.x = nextX;
					p.d = 1;
					q.push(p);
				}
			}
		}
		if (Map[nextY][nextX] == '#'&& fy == nextY && fx == nextX) {
			vist[nextY][nextX][cund] = vist[cunY][cunX][cund];
			ans = min(ans, vist[nextY][nextX][cund]);
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d",&N );
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1s", &Map[i][j]);
			for (int d = 0; d < 4; d++) {
				vist[i][j][d] = 999999;
			}
			if (Map[i][j] == '#') {
				if (q.empty()) {
					for (int d = 0; d < 4; d++) {
						point p;
						p.y = i;
						p.x = j;
						p.d = d;
						q.push(p);
						vist[i][j][d] = 0;
					}
				}
				else {
					fy = i;
					fx = j;
				}
			}
		}
	}
	move();
	printf("%d", ans);
	return 0;
}