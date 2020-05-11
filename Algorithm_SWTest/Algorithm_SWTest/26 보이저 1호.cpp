#pragma warning (disable :4996)
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char Map[500][500];
int N, M;
int PR, PC;
int maxnum;
int maxdir;
int dir[4][2] = { {-1,0}, {1,0}, {0,-1} ,{0,1} };
char Dir[4] = { 'U','D','L','R' };
void go(int y, int x , int d) {
	int cundir = d;
	int cuny = y;
	int cunx = x;
	int cnt = 1;
	while (true){
		int nextY = cuny + dir[cundir][0];
		int nextX = cunx + dir[cundir][1];
		if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) {
			break;
		}
		if (x == nextX && y == nextY && d == cundir) {
			cout << Dir[d] << endl;
			cout << "Voyager" ;
			exit(0);
		}
		if (Map[nextY][nextX] =='C') {
			break;
		}
		if (Map[nextY][nextX] == '/') {
			if (cundir ==0) {
				cundir = 3;
			}
			else if (cundir == 1) {
				cundir = 2;
			}
			else if (cundir == 2) {
				cundir = 1;
			}
			else {
				cundir = 0;
			}
		}
		if (Map[nextY][nextX] == '\\') {
			if (cundir == 0) {
				cundir = 2;
			}
			else if (cundir == 1) {
				cundir = 3;
			}
			else if (cundir == 2) {
				cundir = 0;
			}
			else {
				cundir = 1;
			}
		}
		cuny = nextY;
		cunx = nextX;
		cnt++;
	}
	if (maxnum < cnt) {
		maxnum = cnt;
		maxdir = d;
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
		}
	}
	cin >> PR >> PC;
	PR = PR - 1;
	PC = PC - 1;
	go(PR, PC, 0);
	go(PR, PC, 3);
	go(PR, PC, 1);
	go(PR, PC, 2);
	cout << Dir[maxdir] << endl;
	cout << maxnum ;
	return 0;
}