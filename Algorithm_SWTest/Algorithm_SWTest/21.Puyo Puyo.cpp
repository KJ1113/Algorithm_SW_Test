#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
using namespace std;
int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
int ans = -1;
int Map[12][6];
bool visted[12][6];
bool falg = true;
void down() {
	for (int j = 0; j < 6; j++) {
		queue<int>q;
		for (int i = 11; i >=0; i--) {
			visted[i][j] = false;
			if (Map[i][j] != 0) {
				q.push(Map[i][j]);
			}
		}
		for (int i = 11; i >= 0; i--) {
			if (!q.empty()) {
				Map[i][j] = q.front();
				q.pop();
			}
			else {
				Map[i][j] = 0;
			}
		}
	}
}
void solve() {
	
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			queue<pair<int, int>>q;
			queue<pair<int, int>>tmpq;
			
			if (Map[i][j] != 0) {
				
				if (visted[i][j] ==false) {
					
					tmpq.push(pair<int, int>(i, j));
					q.push(pair<int, int>(i, j));
					visted[i][j] = true;

					while (!q.empty()){
						int cunY = q.front().first;
						int cunX = q.front().second;
						q.pop();
						
						for (int d = 0; d < 4;d++) {
							int nextY = cunY + dir[d][0];
							int nextX = cunX + dir[d][1];

							if (nextY < 0 || nextY >= 12 || nextX < 0 || nextX >= 6) continue;
							if (visted[nextY][nextX] == true) continue;
							if (Map[nextY][nextX] == Map[cunY][cunX]) {
								
								q.push(pair<int, int>(nextY, nextX));
								tmpq.push(pair<int, int>(nextY, nextX));
								visted[nextY][nextX] = true;
							}

						}
					}

					if (tmpq.size() >=4) {
						falg = true;
						while (!tmpq.empty()) {
							int cunY = tmpq.front().first;
							int cunX = tmpq.front().second;
							tmpq.pop();
							Map[cunY][cunX] = 0;
						}
					}

				}
			}
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			char input;
			cin >> input;
			if (input == '.') {
				Map[i][j] = 0;
			}
			else if (input == 'R') {
				Map[i][j] = 1;
			}
			else if (input == 'G') {
				Map[i][j] = 2;
			}
			else if (input == 'B') {
				Map[i][j] = 3;
			}
			else if (input == 'P') {
				Map[i][j] = 4;
			}
			else {
				Map[i][j] = 5;
			}
		}
	}
	while (falg){
		ans++;
		falg = false;
		solve();
		down();
	}
	cout << ans;
	return 0;
}