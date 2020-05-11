#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int N, M, T; //반지름(높이) , 원판안의 수,  회전수
int Map[50][50];
bool visted[50][50];
bool flag = false;
void inputQueue(int nextY, int nextX, queue <pair<int, int>>& q) {
	flag = true;
	Map[nextY][nextX] = 0;
	visted[nextY][nextX] = true;
	q.push(pair<int, int>(nextY, nextX));
}
void bfs(int inputY, int inputX) {

	int conTmp = Map[inputY][inputX];
	queue <pair<int, int>> q;
	q.push(pair<int, int>(inputY, inputX));
	visted[inputY][inputX] = true;

	while (!q.empty()) {
		int conY = q.front().first;
		int conX = q.front().second;
		q.pop();

		int next_up = conY - 1;
		int next_down = conY + 1;
		int next_right = conX + 1;
		int next_left = conX - 1;
		if (next_left < 0) next_left = M - 1;
		if (next_right >= M) next_right = 0;

		if (conTmp == Map[conY][next_right]) {
			if (visted[conY][next_right] == false) {
				Map[conY][conX] = 0;
				inputQueue(conY, next_right, q);
			}
		}
		if (conTmp == Map[conY][next_left]) {
			if (visted[conY][next_left] == false) {
				Map[conY][conX] = 0;
				inputQueue(conY, next_left, q);
			}
		}
		if (next_up >= 0) {
			if (conTmp == Map[next_up][conX]) {
				if (visted[next_up][conX] == false) {
					Map[conY][conX] = 0;
					inputQueue(next_up, conX, q);
				}
			}
		}
		if (next_down < N) {
			if (conTmp == Map[next_down][conX]) {
				if (visted[next_down][conX] == false) {
					Map[conY][conX] = 0;
					inputQueue(next_down, conX, q);
				}
			}
		}
	}
}
void runRotation(int index, int dir, int K) {
	// 0인경우 시계 방향
	for (int go = 0; go < K; go++) {
		if (dir == 0) {
			int tmp = Map[index][0];
			Map[index][0] = Map[index][M - 1];
			for (int j = 1; j < M; j++) {
				int tmp2 = Map[index][j];
				Map[index][j] = tmp;
				tmp = tmp2;
			}
		}
		else {
			int tmp = Map[index][M - 1];
			Map[index][M - 1] = Map[index][0];
			for (int j = M - 2; j >= 0; j--) {
				int tmp2 = Map[index][j];
				Map[index][j] = tmp;
				tmp = tmp2;
			}
		}
	}
}
int main() {
	//freopen("input.txt","r",stdin);
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
	for (int go = 0; go < T; go++) {
		// x배수의 원판들을 //d 방향으로 // k칸회전
		int x, d, k;
		scanf("%d %d %d", &x, &d, &k);
		for (int i = 0; i < N; i++) {
			if ((i + 1) % x == 0) {
				runRotation(i, d, k);
			}
		}
		//---회전 완료----
		int sumNum = 0;
		vector <pair<int, int>> v;
		flag = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				visted[i][j] = false;
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visted[i][j] == false && Map[i][j] != 0) {
					sumNum += Map[i][j];
					bfs(i, j);
					v.push_back(pair<int, int>(i, j));
				}
			}
		}

		if (flag == false) {
			for (int i = 0; i < v.size(); i++) {
				int y = v[i].first;
				int x = v[i].second;
				if (visted[y][x] == true && Map[y][x] != 0) {
					double avg = (double)sumNum / v.size();
					if ((double)Map[y][x] > avg) {
						Map[y][x]--;
					}
					else if ((double)Map[y][x] == avg) {
						continue;
					}
					else {
						Map[y][x]++;
					}
				}
			}
		}
	}
	int ens = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ens += Map[i][j];
		}
	}
	printf("%d",ens);
	return 0;
}