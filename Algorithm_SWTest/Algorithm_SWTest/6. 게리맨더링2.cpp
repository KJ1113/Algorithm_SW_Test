#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int N;
int Map[20][20];
int localMap[20][20];
int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
int ens = 1000000;
int sum[6] = { 0,0,0,0,0,0 };
bool visted[20][20];

void inputQueue(int ny, int nx , queue <pair<int, int>> &q , int num) {
	q.push(pair<int, int>(ny, nx));
	localMap[ny][nx] = num;
	visted[ny][nx] = true;
	sum[num] += Map[ny][nx];
}
void bfs(int y, int x ,int num ,int done, int dtwo , int conY, int conX) {

	queue <pair<int, int>> q;
	q.push(pair<int, int>(y, x));
	localMap[y][x] = num;
	visted[y][x] = true;
	sum[num] = Map[y][x];

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int ny = cy + dir[k][0];
			int nx = cx + dir[k][1];
			if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
			if (localMap[ny][nx] == 5 || localMap[ny][nx] == num) continue;

			if (localMap[ny][nx] == 0) {

				if (num ==1) {
					if (0<=ny && ny < conY+done && 0 <= nx && nx <= conX) {
						inputQueue(ny, nx, q, 1);
					}
				}
				else if (num ==2) {
					if (0 <= ny && ny <= conY + dtwo && conX < nx && nx <= N) {
						inputQueue(ny, nx, q, 2);
					}
				}
				else if (num == 3) {
					if (conY+done <= ny && ny <= N  && 0 <= nx && nx <conX-done+dtwo) {
						inputQueue(ny, nx, q, 3);
					}
				}
				else {
					if (conY + dtwo < ny && ny <= N && conX - done + dtwo <= nx && nx <= N) {
						inputQueue(ny, nx, q, 4);
					}
				}
			}
		}
	}
}
void makeLocals(int y, int x , int done, int dtwo) {
	
	//5¹ø
	for (int k = 0; k <= done; k++) {
		if (y + k < 0 || y + k >= N || x - k < 0 || x - k >= N) continue;
		localMap[y + k][x - k] = 5;
	}
	for (int k = 0; k <= done; k++) {
		if (y + dtwo + k < 0 || y + dtwo + k >= N || x + dtwo - k < 0 || x + dtwo - k >= N) continue;

		localMap[y + dtwo + k][x + dtwo - k] = 5;
	}
	for (int k = 0; k <= dtwo; k++) {
		if (y + k < 0 || y + k >= N || x + k < 0 || x + k >= N) continue;
		localMap[y + k][x + k] = 5;
	}
	for (int k = 0; k <= dtwo; k++) {
		if (y + done + k < 0 || y + done + k >= N || x - done + k < 0 || x - done + k >= N) continue;
		localMap[y + done + k][x - done + k] = 5;
	}

	bfs(0,0,1,done,dtwo,y,x);
	bfs(0,N-1,2, done, dtwo, y, x);
	bfs(N-1,0,3, done, dtwo, y, x);
	bfs(N-1,N-1,4, done, dtwo, y, x);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			localMap[i][j] = 0;
			visted[i][j] = false;
		}
	}
	sum[5] = sum[0] - (sum[1] + sum[2] + sum[3] + sum[4]);
	int maxSum = 0;
	int minSum = 1000000;
	for (int index = 1; index <=5 ; index++) {
		maxSum = max(maxSum ,sum[index]);
		minSum = min(minSum, sum[index]);
	}
	ens = min(ens, maxSum - minSum);
}
int main() {
	freopen("input.txt","r",stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
			sum[0] += Map[i][j];
		}
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int i = 1; i <= N-1; i++) {
				for (int j = 1; j <= N-1; j++) {
					if (0 <= y && y+i+j <N) {
						if (0 <= x-i && x-i < x && x < x + j && x + j < N) {
							makeLocals(y, x, i, j);
						}
					}
				}
			}
		}
	}
	printf("%d",ens);
	return 0;
}