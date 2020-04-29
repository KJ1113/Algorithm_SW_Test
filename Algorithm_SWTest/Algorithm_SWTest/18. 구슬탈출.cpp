#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAX = 11;
int Map[MAX][MAX];
int N, M;
int dir[4][2] = { {-1,0} ,{1,0}, {0,-1}, {0,1} }; // 상하좌우
pair<int, int> bluepos;
pair<int, int> redpos;
int ans = 999999;
bool goal = false;
void solve(int cnt, bool redgoal, bool bluegoal) {

	if (redgoal == true && bluegoal == false) {
		goal = true;
		ans = min(ans, cnt - 1);
		return;
	}
	else if (redgoal == false && bluegoal == true) {
		return;
	}
	else  if (redgoal == true && bluegoal == true) {
		
		return;
	}
	else {
		if (cnt == 11) {
			
			return;
		}
		else {		
			int cunRY = redpos.first;
			int cunRX = redpos.second;
			int cunBX = bluepos.second;
			int cunBY = bluepos.first;
			for (int i = 0; i < 4; i++) {
				bool redg = redgoal;
				bool blueg = bluegoal;
				int nextRY = cunRY;
				int nextRX = cunRX;
				int lastRY = nextRY;
				int lastRX = nextRX;

				int nextBY = cunBY;
				int nextBX = cunBX;
				int lastBY = nextBY;
				int lastBX = nextBX;

				bool blueFirst = false; // 레드선 디폴트
				if (i == 0) {
					if (redpos.first > bluepos.first) blueFirst = true;
				}
				else if (i == 1) {
					if (redpos.first < bluepos.first) blueFirst = true;
				}
				else if (i == 2) {
					if (redpos.second > bluepos.second) blueFirst = true;
				}
				else {
					if (redpos.second < bluepos.second) blueFirst = true;
				}

				if (blueFirst == false) {
					
					while (true) {
						nextRY = nextRY + dir[i][0];
						nextRX = nextRX + dir[i][1];
						if (Map[nextRY][nextRX] == 1 || Map[nextRY][nextRX] == 3) {
							break;
						}
						if (Map[nextRY][nextRX] == 4) {
							Map[lastRY][lastRX] = 0;
							redg = true;
							break;
						}
						Map[lastRY][lastRX] = 0;
						Map[nextRY][nextRX] = 2;
						lastRY = nextRY;
						lastRX = nextRX;

					}

					while (true) {
						nextBY = nextBY + dir[i][0];
						nextBX = nextBX + dir[i][1];
						if (Map[nextBY][nextBX] == 1 || Map[nextBY][nextBX] == 2) {
							break;
						}
						if (Map[nextBY][nextBX] == 4) {
							Map[lastBY][lastBX] = 0;
							
							blueg = true;
							if (cnt == 3) {
							}
							break;
						}
						Map[lastBY][lastBX] = 0;
						Map[nextBY][nextBX] = 3;
						lastBY = nextBY;
						lastBX = nextBX;

					}
				}
				else {
					while (true) {
						nextBY = nextBY + dir[i][0];
						nextBX = nextBX + dir[i][1];
						if (Map[nextBY][nextBX] == 1 || Map[nextBY][nextBX] == 2) {
							break;
						}
						if (Map[nextBY][nextBX] == 4) {
							Map[lastBY][lastBX] = 0;
							if (cnt == 3) {
							}
							blueg = true;
							
							break;
						}
						Map[lastBY][lastBX] = 0;
						Map[nextBY][nextBX] = 3;
						lastBY = nextBY;
						lastBX = nextBX;

					}
					while (true) {
						nextRY = nextRY + dir[i][0];
						nextRX = nextRX + dir[i][1];
						if (Map[nextRY][nextRX] == 1 || Map[nextRY][nextRX] == 3) {
							break;
						}
						if (Map[nextRY][nextRX] == 4) {
							Map[lastRY][lastRX] = 0;
							redg = true;
							break;
						}
						Map[lastRY][lastRX] = 0;
						Map[nextRY][nextRX] = 2;
						lastRY = nextRY;
						lastRX = nextRX;

					}
			
				}
				redpos.first = lastRY;
				redpos.second = lastRX;
				bluepos.first = lastBY;
				bluepos.second = lastBX;
				solve(cnt + 1, redg, blueg);
				Map[lastRY][lastRX] = 0;
				Map[cunRY][cunRX] = 2;
				Map[lastBY][lastBX] = 0;
				Map[cunBY][cunBX] = 3;
			}
		}
	}
}
int main() {

	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		string input;
		cin >> input;
		for (int j = 0; j < input.size(); j++) {
			if (input[j] == '#') {
				Map[i][j] = 1;
			}
			else if (input[j] == '.') {
				Map[i][j] = 0;
			}
			else if (input[j] == 'R') {
				Map[i][j] = 2;
				redpos.first = i;
				redpos.second = j;
			}
			else if (input[j] == 'B') {
				Map[i][j] = 3;
				bluepos.first = i;
				bluepos.second = j;
			}
			else {
				Map[i][j] = 4;
			}
		}
	}
	solve(1, false, false);
	if (goal == true) {
		cout << ans;
	}
	else {
		cout << -1;
	}
	return 0;
}