#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int N, M, T; //������(����) , ���Ǿ��� ��,  ȸ����
int Map[51][51];
int dir[4][2] = { {1,0}, {0,1}, {0,-1} , {-1,0} };
bool visted[51][51];
bool flag = false;
void inputQueue(int nextY,int nextX, queue <pair<int, int>> &q) { //�ּҰ����� q �Ѱ������
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

	while (!q.empty()){
		int conY = q.front().first;
		int conX = q.front().second;
		int nextY = 0;
		int nextX = 0;
		q.pop();

		int next_up = conY-1;
		int next_down = conY+1;
		int next_right = conX+1;
		int next_left = conX-1;
		if (next_left < 0) next_left = M - 1;
		if (next_right >= M) next_right = 0;

		if (conTmp == Map[conY][next_right]) {
			if (visted[conY][next_right] == false) {
				Map[conY][conX] = 0;
				inputQueue(conY, next_right,q);
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
void runRotation(int index , int dir , int K) {
	// 0�ΰ�� �ð� ����
	for (int go = 0; go< K;go++) {
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
	freopen("input.txt","r",stdin);
	scanf("%d %d %d", &N,&M,&T);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M;j++) {
			scanf("%d", &Map[i][j]);
		}
	}
	for (int go = 0; go < T; go++) {
		// x����� ���ǵ��� //d �������� // kĭȸ��
		int x, d, k;
		scanf("%d %d %d", &x, &d, &k);
		for (int i = 0; i < N; i++) {
			if ((i + 1) % x == 0) {
				runRotation(i, d, k);
			}
		}
		//---ȸ�� �Ϸ�----
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				visted[i][j] = false;
			}
		}
		int cntNum = 0;
		int sumNum = 0;
		flag = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				sumNum += Map[i][j];
				if (visted[i][j] == false && Map[i][j] != 0) {
					cntNum++;

					bfs(i, j);
				}
			}
		}

		if (flag == false) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (visted[i][j] == true && Map[i][j] != 0) {
						double avg = (double)sumNum / cntNum;
						if ((double)Map[i][j] > avg) {
							Map[i][j] = Map[i][j] - 1;
						}
						else if ((double)Map[i][j] == avg) {
							Map[i][j];
						}
						else {
							Map[i][j] = Map[i][j] + 1;
						}
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
	cout << ens ;
	return 0;
}