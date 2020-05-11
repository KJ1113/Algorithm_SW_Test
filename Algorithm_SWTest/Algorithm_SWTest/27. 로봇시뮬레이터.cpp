#pragma warning (disable :4996)
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int MaxX, MaxY;
int N, M;
int Map[101][101];
struct robot {
	int y;
	int x;
	char dir;
};
vector <robot> v;
bool flag = true;
void move(int num, char move_D, int cnt) {
	if (move_D == 'L') {
		cnt = cnt % 4;
		for (int i = 0; i < cnt; i++) {
			if (v[num].dir == 'N') {
				v[num].dir = 'W';
			}
			else if (v[num].dir == 'W') {
				v[num].dir = 'S';
			}
			else if (v[num].dir == 'E') {
				v[num].dir = 'N';
			}
			else {
				v[num].dir = 'E';
			}
		}
	}
	else if (move_D == 'R') {
		cnt = cnt % 4;
		for (int i = 0; i < cnt; i++) {
			if (v[num].dir == 'N') {
				v[num].dir = 'E';
			}
			else if (v[num].dir == 'W') {
				v[num].dir = 'N';
			}
			else if (v[num].dir == 'E') {
				v[num].dir = 'S';
			}
			else {
				v[num].dir = 'W';
			}
		}
	}
	else {
		if (v[num].dir == 'N') {
			for (int i = 1; i <= cnt; i++) {
				if (v[num].y - i < 0) {
					cout << "Robot " << num + 1 << " crashes into the wall" << endl;
					exit(0);
				}
				if (Map[v[num].y - i][v[num].x] != 0) {
					cout << "Robot " << num + 1 << " crashes into robot " << Map[v[num].y - i][v[num].x] << endl;
					exit(0);
				}
			}
			Map[v[num].y][v[num].x] = 0;
			v[num].y -= cnt;
			Map[v[num].y][v[num].x] = num;
		}
		else if (v[num].dir == 'W') {
			for (int i = 1; i <= cnt; i++) {
				if (v[num].x - i < 0) {
					cout << "Robot " << num + 1 << " crashes into the wall" << endl;
					exit(0);
				}
				if (Map[v[num].y][v[num].x - i] != 0) {
					cout << "Robot " << num + 1 << " crashes into robot " << Map[v[num].y][v[num].x - i] << endl;
					exit(0);
				}
			}
			Map[v[num].y][v[num].x] = 0;
			v[num].x -= cnt;
			Map[v[num].y][v[num].x] = num;
		}
		else if (v[num].dir == 'E') {
			for (int i = 1; i <= cnt; i++) {
				if (v[num].x + i >= MaxX) {
					cout << "Robot " << num + 1 << " crashes into the wall" << endl;
					exit(0);
				}
				if (Map[v[num].y][v[num].x + i] != 0) {
					cout << "Robot " << num + 1 << " crashes into robot " << Map[v[num].y][v[num].x + i] << endl;
					exit(0);
				}
			}
			Map[v[num].y][v[num].x] = 0;
			v[num].x += cnt;
			Map[v[num].y][v[num].x] = num;
		}
		else {
			for (int i = 1; i <= cnt; i++) {
				if (v[num].y + i >= MaxY) {
					cout << "Robot " << num + 1 << " crashes into the wall" << endl;
					exit(0);
				}
				if (Map[v[num].y + i][v[num].x] != 0) {
					cout << "Robot " << num + 1 << " crashes into robot " << Map[v[num].y + i][v[num].x] << endl;
					exit(0);
				}
			}
			Map[v[num].y][v[num].x] = 0;
			v[num].y += cnt;
			Map[v[num].y][v[num].x] = num;
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	cin >> MaxX >> MaxY;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		robot r;
		cin >> r.x >> r.y >> r.dir;
		r.x = r.x - 1;
		r.y = MaxY - r.y;
		v.push_back(r);
		Map[r.y][r.x] = i + 1;
	}
	for (int i = 0; i < M; i++) {
		int index, cnt;
		char d;
		cin >> index >> d >> cnt;
		if (flag == true)move(index - 1, d, cnt);
	}
	if (flag == true) cout << "OK" << endl;
	return 0;
}