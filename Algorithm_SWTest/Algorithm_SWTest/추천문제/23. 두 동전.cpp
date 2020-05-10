#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
#include<cstring>
#include <vector>
using namespace std;
int N, M;
int dir[4][2] = { {-1,0} ,{1,0} ,{0,-1}, {0,1} };
int ans = 999999;
char Map[20][20];
struct coin{
	int y, x;
	bool life = true;
};
vector <coin> coins;
void Movecoin(int num, int d) {
	int cunY = coins[num].y;
	int cunX = coins[num].x;;
	int nextY = cunY + dir[d-1][0];
	int nextX = cunX + dir[d-1][1];
	if (Map[nextY][nextX] == '#') {
		return;
	}
	Map[cunY][cunX] = '.';
	if (Map[nextY][nextX] =='o' ) {
		coins[num].y = nextY;
		coins[num].x = nextX;
		return;
	}
	if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) {
		coins[num].life = false;
		return;
	}
	// .
	Map[nextY][nextX] = 'o';
	coins[num].y = nextY;
	coins[num].x = nextX;
}
void sol(int cnt, int d) {
	if (cnt>ans) {
		return;
	}
	if ((coins[0].life == false && coins[1].life == true) || (coins[0].life == true && coins[1].life == false)) {
		return;
	}
	if ((coins[0].life == false && coins[1].life == false)) {
		return;
	}
	if (cnt == 11) {
		return;
	}
	else {
		char tmpMap[20][20];
		int oney = coins[0].y;
		int onex = coins[0].x;
		int twoy = coins[1].y;
		int twox = coins[1].x;
		bool lifeone = coins[0].life;
		bool lifetwo = coins[1].life;
		memcpy(tmpMap, Map, sizeof(tmpMap));
		if ( d==1) {
			if (coins[0].y < coins[1].y) {
				Movecoin(0, 1);
				Movecoin(1, 1);
			}
			else {
				Movecoin(1, 1);
				Movecoin(0, 1);
			}
		}
		else if (d == 2) {
			if (coins[0].y > coins[1].y) {
				Movecoin(0, 2);
				Movecoin(1, 2);
			}
			else {
				Movecoin(1, 2);
				Movecoin(0, 2);
			}
		}
		else if (d==3) {
			if (coins[0].x < coins[1].x) {
				Movecoin(0, 3);
				Movecoin(1, 3);
			}
			else {
				Movecoin(1, 3);
				Movecoin(0, 3);
			}
		}
		else if (d == 4) {
			if (coins[0].x > coins[1].x) {
				Movecoin(0, 4);
				Movecoin(1, 4);
			}
			else {
				Movecoin(1, 4);
				Movecoin(0, 4);
			}
		}
		if ((coins[0].life==false && coins[1].life ==true) || (coins[0].life == true && coins[1].life == false)) {
			ans = min(ans, cnt);
		}
		sol(cnt +1, 1);
		sol(cnt +1, 2);
		sol(cnt +1, 3);
		sol(cnt +1, 4);
		coins[0].y= oney;
		coins[0].x= onex;
		coins[1].y= twoy;
		coins[1].x= twox;
		coins[0].life= lifeone;
		coins[1].life= lifetwo;
		memcpy(Map, tmpMap, sizeof(Map));
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j]== 'o') {
				coin c;
				c.y = i;
				c.x = j;
				coins.push_back(c);
			}
		}
	}
	sol(0, 0);
	if (ans ==999999) {
		cout << -1;
	}
	else {
		cout << ans;
	}
	return 0;
}
