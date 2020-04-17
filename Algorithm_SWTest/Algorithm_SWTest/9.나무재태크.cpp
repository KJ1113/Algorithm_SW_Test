#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 10;
int N, M, K;
int Map[MAX][MAX];
int foodMap[MAX][MAX];
int ans = 0;
int dir[8][2] = { {1,0} ,{-1,0} ,{0,1} ,{0,-1} ,{1,1} ,{1,-1} ,{-1,1} ,{-1,-1} };
struct plant
{
	int y, x;
	int lifecnt = 1;
	bool life = true;
};
vector<plant> plist;
void sortInput(plant inputP) {
	if (plist.size() > 0) {
		if (plist[plist.size()-1].lifecnt > inputP.lifecnt) {
			plant tmpP = plist[plist.size() - 1];
			plist.pop_back();
			plist.push_back(inputP);
			plist.push_back(tmpP);
		}
		else {
			plist.push_back(inputP);
		}
	}
	else {
		plist.push_back(inputP);
	}
}
void delPlant() {
	vector<plant> tmplist;
	for (int index = 0; index < plist.size(); index++) {
		if (plist[index].life == true) {
			tmplist.push_back(plist[index]);
		}
	}
	plist.clear(); 
	plist = tmplist;
}
void oneYear(){
	//봄
	for (int index = 0; index < plist.size(); index++) {
		int conY = plist[index].y;
		int conX = plist[index].x;
		if (Map[conY][conX] < plist[index].lifecnt) {
			cout << "!" << plist[index].lifecnt << foodMap[conY][conX] << endl;;
			plist[index].life = false;
		}
		else {
			Map[conY][conX] -= plist[index].lifecnt;
			plist[index].lifecnt++;
		}
	}
	//여름 ,가을
	int size = plist.size();
	for (int index = 0; index < size; index++) {
		int conY = plist[index].y;
		int conX = plist[index].x;

		if (plist[index].life == false) {
			int sumfood = plist[index].lifecnt/2;
			Map[conY][conX] += sumfood;
		}
		
	}
	for (int index = 0; index < size; index++) {
		int conY = plist[index].y;
		int conX = plist[index].x;
		if (plist[index].lifecnt % 5 == 0) {

			for (int i = 0; i < 8; i++) {
				int nextY = conY + dir[i][0];
				int nextX = conX + dir[i][1];
				if (nextY < 0 || nextY >= N || nextX < 0 || nextX >= N) continue;
				//cout << i << endl;
				plant p;
				p.y = nextY;
				p.x = nextX;
				p.lifecnt = 1;
				sortInput(p);
			}
		}
	}


	//겨울
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Map[i][j] += foodMap[i][j];
		}
	}

}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N,&M,&K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d",&foodMap[i][j]);
			Map[i][j]=5;
		}
	}
	for (int i = 0; i < M; i++) {
		plant p;
		scanf("%d %d %d", &p.y,&p.x,&p.lifecnt);
		p.y--;
		p.x--;
		sortInput(p);
	}
	for (int year = 0; year < K; year++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", Map[i][j]);
			}
			cout << endl;
		}
		cout << endl;
		oneYear();
		delPlant();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", Map[i][j]);
			}
			cout << endl;
		}
		for (int index = 0; index < plist.size(); index++) {
			cout << "( " << plist[index].y << ", " << plist[index].x << ", " << plist[index].lifecnt << ") ";
		}
		cout << endl;
		cout <<"---------------" <<endl;
	}
	for (int index = 0; index < plist.size(); index++) {
		if (plist[index].life == true) ans++;
	}
	printf("%d",ans);
	return 0;
}