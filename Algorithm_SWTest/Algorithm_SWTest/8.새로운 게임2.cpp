#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 12;
int N, K;
int time = 0;
int nextY, nextX;
struct Word {
	int index;
	int y, x;
	int dir;
};
struct MapWords {
	int color = 0;
	vector<Word> myWordlist;
};
MapWords Map[MAX][MAX]; // 말판과 벡터에 둘다저장
vector <Word> wordspos;
void nextpos(int y, int x, int dir) {
	if (dir == 3) {
		nextY = y - 1;
		nextX = x;
	}
	else if (dir == 4) {
		nextY = y + 1;
		nextX = x;
	}
	else if (dir == 2) {
		nextY = y;
		nextX = x - 1;
	}
	else {
		nextY = y;
		nextX = x + 1;
	}
}
void move(int conY, int conX, int index) {
	int listsize = Map[conY][conX].myWordlist.size(); // conY, conX 위치에는 필연적으로 size가 1이상이므로 오류가 나지않는다.
	bool moveble = true;
	nextpos(conY, conX, wordspos[index].dir);
	if (Map[nextY][nextX].color == 2 || (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N)) {
		if (wordspos[index].dir == 1) {
			wordspos[index].dir = 2;
		}
		else if (wordspos[index].dir == 2) {
			wordspos[index].dir = 1;
		}
		else if (wordspos[index].dir == 3) {
			wordspos[index].dir = 4;
		}
		else {
			wordspos[index].dir = 3;
		}
		nextpos(conY, conX, wordspos[index].dir);
		if (Map[nextY][nextX].color == 2 || (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N)) {
			// 움직임 없음
			moveble = false;
		}
	}
	//내위에 몇명 있는지 체크
	if (Map[conY][conX].myWordlist[listsize - 1].index != index) {
		vector <Word> list;
		bool flag = false;
		for (int i = 0; i < listsize; i++) { // 현재 말의 위에있는 말들 저장
			if (Map[conY][conX].myWordlist[i].index == index) {
				flag = true;
			}
			if (flag == true) {
				list.push_back(Map[conY][conX].myWordlist[i]);
			}
		}
		if (moveble == true) {
			if (Map[nextY][nextX].color == 1) {
				vector <Word> tmplist;
				for (int i = list.size() - 1; i >= 0; i--) {
					tmplist.push_back(list[i]);
				}
				list = tmplist;
			}
			for (int i = 0; i < list.size(); i++) {
				int conindex = list[i].index;
				wordspos[conindex].y = nextY;
				wordspos[conindex].x = nextX;
				Map[nextY][nextX].myWordlist.push_back(wordspos[conindex]);
				Map[conY][conX].myWordlist.pop_back();
			}
		}

	}
	else {
		if (moveble == true) {
			wordspos[index].y = nextY;
			wordspos[index].x = nextX;
			Map[nextY][nextX].myWordlist.push_back(wordspos[index]);
			Map[conY][conX].myWordlist.pop_back();
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j].color);
		}
	}
	for (int index = 0; index < K; index++) {
		Word w;
		w.index = index;
		scanf("%d %d %d", &w.y, &w.x, &w.dir);
		w.y--;
		w.x--;
		Map[w.y][w.x].myWordlist.push_back(w);
		wordspos.push_back(w);
	}
	while (true)
	{
		if (time == 1001) {
			printf("%d", -1);
			return 0;
		}
		else {
			time++;
			for (int i = 0; i < wordspos.size(); i++) {

				int y = wordspos[i].y;
				int x = wordspos[i].x;
				move(y, x, i);
				if (Map[wordspos[i].y][wordspos[i].x].myWordlist.size() >= 4) {
					printf("%d", time);
					return 0;
				}
			}
		}
	}
	return 0;
}