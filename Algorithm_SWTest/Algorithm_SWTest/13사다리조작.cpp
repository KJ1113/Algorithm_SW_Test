#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
using namespace std;
int N, M, H;
int map[100][100];
int ens = -1;
bool go(int startx)
{
	int cony = 0;
	int conx = startx;
	while (true){
		if (cony == H + 1){
			map[cony][conx] = startx;

			if (conx == startx)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		if (map[cony][conx] == 0){
			cony = cony + 1;
		}
		else{
			if (map[cony][conx] == 1)
			{
				cony = cony + 1;
				conx = conx + 1;
			}
			else
			{
				cony = cony + 1;
				conx = conx - 1;
			}
		}
	}
}
void dfs(int indexY, int indexX, int cnt, int size)
{
	if (size == cnt){
		bool flag = true;
		for (int j = 1; j <= N; j++){
			flag = go(j);
			if (flag == false)
			{
				return;
			}
		}
		ens = cnt;
		return;
	}

	for (int i = indexY; i <= H; i++){
		for (int j = indexX; j < N; j++){
			if (map[i][j] == 1 || map[i][j] == 2)
			{
				continue;
			}
			if (map[i][j] == 0 && map[i][j + 1] == 0)
			{
				map[i][j] = 1;
				map[i][j + 1] = 2;

				dfs(i, j, cnt + 1, size);

				map[i][j] = 0;
				map[i][j + 1] = 0;
			}
		}
		indexX = 1;
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N, &M, &H);
	// 세로선갯수 (열) // 가로선의 수 (행)
	// 세로선 = 열;
	//가로선 = 행;

	for (int i = 0; i < M; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		map[a][b] = 1;
		map[a][b + 1] = 2;
	}
	for (int h = 0; h <= 3; h++){
		dfs(1, 1, 0, h);
		if (ens != -1)
		{
			printf("%d", ens);
			return 0;
		}
	}
	printf("%d", -1);
	return 0;
}