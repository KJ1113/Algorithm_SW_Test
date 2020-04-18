#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 101;
int R, C, M;
int Map[MAX][MAX];
int ans = 0;
struct Fish
{
	int  r, c, s, d, z;
	bool life = true;
};
vector<Fish> Flist;
void move(int index, int nextY, int nextX, int RC) {
	int moveSize = Flist[index].s % ((RC * 2) - 2);
	int nY = nextY;
	int nX = nextX;
	for (int t = 0; t < moveSize; t++) {
		if (Flist[index].d == 1) {
			nY--;
			if (nY < 0) {
				nY = 1;
				Flist[index].d = 2;
			}
		}
		else if (Flist[index].d == 2) {
			nY++;
			if (nY >= R) {
				nY = R - 2;
				Flist[index].d = 1;
			}
		}
		else if (Flist[index].d == 4) {
			nX--;
			if (nX < 0) {
				nX = 1;
				Flist[index].d = 3;
			}
		}
		else {
			nX++;
			if (nX >= C) {
				nX = C - 2;
				Flist[index].d = 4;
			}
		}
	}
	Map[nY][nX]++;
	Flist[index].r = nY;
	Flist[index].c = nX;
}
void fishing(int X) {
	vector<Fish> fishList;
	int dieY = 999999;
	int dieX = 999999;
	// 잡을 물고기 찾기
	for (int y = 0; y < R; y++) {
		if (Map[y][X] == 1) {
			dieY = y;
			dieX = X;
			break;
		}
	}
	//물고기 이동예정지 찾기, 기존자리 비우기
	for (int index = 0; index < Flist.size(); index++) {
		int conY = Flist[index].r;
		int conX = Flist[index].c;

		if (dieY == conY && dieX == conX) {
			Flist[index].life = false;
			ans += Flist[index].z;
			Map[dieY][dieX] --;
		}
		else {
			int nextY = conY;
			int nextX = conX;
			int moveSize;
			Map[conY][conX] --;
			if (Flist[index].d == 1 || Flist[index].d == 2) {
				move(index, nextY, nextX, R);
			}
			else {
				move(index, nextY, nextX, C);
			}
		}
	}
	vector<Fish> tmplist;
	for (int i = 0; i < Flist.size(); i++) {
		if (Map[Flist[i].r][Flist[i].c] > 1 && Flist[i].life == true)
		{
			int conY = Flist[i].r;
			int conX = Flist[i].c;


			Map[conY][conX] = 1;
			int maxSize = 0;;
			int maxListindex;

			for (int index = 0; index < Flist.size(); index++)
			{
				if (Flist[index].life == true && Flist[index].r == conY && Flist[index].c == conX)
				{
					if (Flist[index].z > maxSize)
					{
						maxSize = Flist[index].z;
						maxListindex = index;
					}
				}
			}

			for (int index = 0; index < Flist.size(); index++)
			{
				if (Flist[index].life == true && Flist[index].r == conY && Flist[index].c == conX)
				{
					if (maxListindex == index)
					{
						continue;
					}
					else
					{
						Flist[index].life = false;
					}
				}
			}
		}
	}
	for (int index = 0; index < Flist.size(); index++) {
		if (Flist[index].life == true) {
			tmplist.push_back(Flist[index]);
		}
	}
	Flist.clear();
	Flist.assign(tmplist.begin(), tmplist.end());

}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &R, &C, &M);

	for (int i = 0; i < M; i++) {
		Fish f;
		scanf("%d %d %d %d %d", &f.r, &f.c, &f.s, &f.d, &f.z);
		f.r--;
		f.c--;
		Map[f.r][f.c]++;
		Flist.push_back(f);
	}
	for (int X = 0; X < C; X++) {
		fishing(X);
	}
	printf("%d", ans);
	return 0;
}