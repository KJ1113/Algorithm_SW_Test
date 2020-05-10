#pragma warning (disable :4996)
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
int N;
int vist[51][51][2];
char Map[51][51];
struct Point {
	int y, x;
	int move = 0;
	int upndown ;
};
Point s_p;
Point e_p;
queue <Point> q;
int Dir[8][2] = { {-1,0} ,{1,0}, {0,-1}, {0,1},{1,1},{1,-1},{-1,1},{-1,-1} };
bool same(Point ip) {
	if (ip.upndown ==0) {
		if (ip.y == e_p.y && e_p.x == ip.x && Map[ip.y][ip.x-1] == 'E' && Map[ip.y][ip.x + 1] == 'E') {
			return true;
		}
	}
	else {
		if (Map[ip.y-1][ip.x] == 'E' && Map[ip.y +1][ip.x] == 'E' &&ip.y == e_p.y && e_p.x == ip.x) {
			return true;
		}
	}
	return false;
}
void BFS() {
	while (!q.empty()){
		Point cp = q.front();
		int cunY = q.front().y;
		int cunX = q.front().x;
		int move = q.front().move;
		int upd = q.front().upndown;
		q.pop();
		if (same(cp)) {
			cout << move;
			exit(0);
			return;
		}
		for (int dir = 0; dir < 5; dir++) {
			Point np;
			int falg = true;
			if (dir ==4) {
				for (int i = 0; i < 8;i++) {
					if (cunY + Dir[i][0] < 0 || cunY + Dir[i][0] >= N || cunX + Dir[i][1] < 0 || cunX + Dir[i][1] >= N || Map[cunY + Dir[i][0]][cunX + Dir[i][1]] == '1') {
						falg = false;
						break;
					}
				}
				if (falg == true) {
					np.y = cunY;
					np.x = cunX;
					np.move = move + 1;
					if (cp.upndown == 0) { // 가로
						if (vist[cunY][cunX][1] != 0) continue;
						vist[cunY][cunX][1] = move + 1;
						np.upndown = 1;
						q.push(np);
					}
					else { // 가로
						if (vist[cunY][cunX][0] != 0) continue;
						vist[cunY][cunX][0] = move + 1;
						np.upndown = 0;
						q.push(np);
					}
				}
			}
			else {
				int nextY = cunY + Dir[dir][0];
				int nextX = cunX + Dir[dir][1];
				if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N || Map[nextY][nextX]=='1') continue;
				if (vist[nextY][nextX][upd] != 0 ) continue;
				if (cp.upndown ==0) { // 가로
					if (nextY < 0 || nextY >= N || nextX - 1 < 0 || nextX - 1 >= N || Map[nextY][nextX - 1] == '1') continue;
					if (nextY < 0 || nextY >= N || nextX + 1 < 0 || nextX + 1 >= N || Map[nextY][nextX + 1] == '1') continue;
					vist[nextY][nextX][upd] = move + 1;
					np.y = nextY;
					np.x = nextX;
					np.move = move + 1;
					np.upndown = 0;
					q.push(np);
				}
				else { // 세로
					if (nextY-1 < 0 || nextY-1 >= N || nextX  < 0 || nextX  >= N || Map[nextY - 1][nextX] == '1') continue;
					if (nextY+1 < 0 || nextY+1 >= N || nextX  < 0 || nextX  >= N || Map[nextY + 1][nextX] == '1') continue;
					vist[nextY][nextX][upd] = move + 1;
					np.y = nextY;
					np.x = nextX;
					np.move = move + 1;
					np.upndown = 1;
					q.push(np);
				}
				
			}
			
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> N;
	int spc = 0;
	int epc = 0;
	int zy = -1;
	int ty = -1; 
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 'B') {
				if (spc == 0) { zy = i; }
				if (spc == 1){
					s_p.y = i;
					s_p.x = j;
				}
				if (spc == 2) { ty = i; }
				spc++;
			}
			if (Map[i][j] == 'E') {
				if (epc == 1) {
					e_p.y = i;
					e_p.x = j;
				}
				epc++;
			}
		}
	}
	if (zy == ty) {
		s_p.upndown = 0;
	}
	else {
		s_p.upndown = 1;
	}
	q.push(s_p);
	BFS();
	cout << 0 ;
	return 0;
}
