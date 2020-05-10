#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
#include<vector>
using namespace std;
int N, L, R;
int ens = 0;
int Map[51][51];
int dir[4][2] = { {1,0} ,{0,1}, {-1,0} ,{0,-1} };
bool vistMap[51][51];
bool falg = false;
void BFS() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (vistMap[i][j] == true) continue;

			vector <pair<int, int>>v;
			queue <pair<int, int>> q;
			q.push(pair<int, int>(i, j));
			vistMap[i][j] = true;
			bool firstIntput = false;
			int sum = 0;

			while (!q.empty()) {
				int conY = q.front().first;
				int conX = q.front().second;
				q.pop();

				for (int d = 0; d < 4; d++) {
					int nextY = conY + dir[d][0];
					int nextX = conX + dir[d][1];

					if (vistMap[nextY][nextX] == true || nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;
					int tmp = abs(Map[conY][conX] - Map[nextY][nextX]);
					if (L <= tmp && tmp <= R) {
						q.push(pair<int, int>(nextY, nextX));
						v.push_back(pair<int, int>(nextY, nextX));
						vistMap[nextY][nextX] = true;
						sum += Map[nextY][nextX];
						falg = true;

						if (firstIntput == false) {
							v.push_back(pair<int, int>(conY, conX));
							sum += Map[conY][conX];
							firstIntput = true;
						}
					}
				}
			}
			if (firstIntput == true) {
				int avg = sum / v.size();
				for (int index = 0; index < v.size(); index++) {
					Map[v[index].first][v[index].second] = avg;
				}
			}

		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
	while (true) {
		BFS();
		if (falg == false) {
			printf("%d", ens);
			return 0;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				vistMap[i][j] = false;
			}
		}
		ens++;
		falg = false;
	}
	return 0;
}