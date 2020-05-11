#pragma warning (disable :4996)
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
char cMap[100][100];
int N, M;
int ans = 999999;
int vMap[100][100][2];
int dir[4][2] = { {-1,0} ,{1,0}, {0,-1}, {0,1} };
struct point {
	int y, x;
	int condir = -1;
	int move = 0;
};
queue<point> q;
void BFS() {
	while (!q.empty()) {
		int cuny = q.front().y;
		int cunx = q.front().x;
		int cundir = q.front().condir; // 0 이면 가로 방향 // 1 이면 세로방향 // -1 이면 최초
		int cunmove = q.front().move;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nextY = cuny + dir[i][0];
			int nextX = cunx + dir[i][1];
			int nextdir;
			if (nextY == cuny) {
				nextdir = 0;
			}
			else {
				nextdir = 1;
			}
			if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M || cMap[nextY][nextX] == '*') continue;
			if (vMap[nextY][nextX][nextdir] <= cunmove) continue;
			point p;
			p.y = nextY;
			p.x = nextX;
			p.condir = nextdir;
			if (cundir == -1 || nextdir == cundir) {
				p.move = cunmove;
			}
			else {
				p.move = cunmove + 1;
			}
			q.push(p);
			vMap[nextY][nextX][nextdir] = p.move;
			if (cMap[nextY][nextX] == 'C') {
				ans = min(ans, p.move);
			}
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &M, &N);
	memset(vMap, 999999, sizeof(vMap));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1s", &cMap[i][j]);
			if (cMap[i][j] == 'C') {
				if (q.empty()) {
					point p;
					p.y = i;
					p.x = j;
					q.push(p);
					vMap[i][j][0] = 0;
					vMap[i][j][1] = 0;
				}
			}
		}
	}
	BFS();
	printf("%d", ans);
	return 0;
}