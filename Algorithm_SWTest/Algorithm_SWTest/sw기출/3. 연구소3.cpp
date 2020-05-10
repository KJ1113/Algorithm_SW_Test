#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;
int N, M; //크기 , 바이러스 갯수
int Map[50][50]; //0은 빈칸 , 1은 벽 2는 바이러스의 위치
int tmpMap[50][50];
bool boolMap[50][50];
bool goindex[10];

vector <pair<int, int>> VposList; // 바이러스 위치 리스트
bool falg = false;

int dir[4][2] = { {1,0},{-1,0}, {0,1},{0,-1}};
int minResult = 99999999;
int zerocnt = 0;
void choiceVpos(int cnt, int index ) {

	if (cnt == M) {
		queue <pair<int, int >> goVlist;
		for (int i = 0; i < VposList.size();i++) {
			if (goindex[i]==true) {
				goVlist.push(pair<int, int >(VposList[i].first, VposList[i].second));
				boolMap[VposList[i].first][VposList[i].second] = true;
				tmpMap[VposList[i].first][VposList[i].second] = 0;
			}
		}
		//BFS 시작
		int second = 0;
		while (!goVlist.empty()) {
			second++;
			int SecondLength = goVlist.size(); //1초동안 활성화되는 활성 바이러스수
			for (int s = 0; s < SecondLength ;s++) {
				int ConY = goVlist.front().first;
				int ConX = goVlist.front().second;
				goVlist.pop();
				

				for (int i = 0; i < 4 ;i++) {
					int NextY = ConY + dir[i][0];
					int NextX = ConX + dir[i][1];

					if (NextY< 0 || NextX <0 || NextY >= N || NextX >=N ) continue;
					if (boolMap[NextY][NextX] == true || Map[NextY][NextX] == 1) continue;

					tmpMap[NextY][NextX] = second;
					boolMap[NextY][NextX] = true;
					goVlist.push(pair<int, int >(NextY, NextX));	
				}
			}
		}
		int maxSecond = 0;
		int tmpcheck = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				boolMap[i][j] = false;
				if (Map[i][j] == 0 ) {
					if (tmpMap[i][j] != 0) {
						maxSecond = max ( maxSecond, tmpMap[i][j]);
						tmpcheck++;
					}
				}
				
				if (Map[i][j] == 1) {
					tmpMap[i][j] = -1;
				}
				else {
					tmpMap[i][j] = Map[i][j];
				}
			}
		}
		if (zerocnt == tmpcheck) {
			falg = true;
			minResult = min(maxSecond, minResult);
		}
	}
	else {
		for (int i = index; i < VposList.size() ; i++) {

			goindex[i] = true;
			choiceVpos(cnt + 1, i + 1);
			goindex[i] = false;
		}
	}
}
int main() {
	//freopen("input.txt","r",stdin);
	scanf("%d %d",&N, &M);
	for (int i = 0;i<N;i++) {
		for (int j = 0;j<N; j++) {
			scanf("%d", &Map[i][j]);

			if (Map[i][j]==2) {
				VposList.push_back(pair<int,int>(i,j));
			}
			if (Map[i][j] == 1) {
				tmpMap[i][j] = -1;
			}
			if (Map[i][j] == 0) {
				zerocnt++;
				tmpMap[i][j] = Map[i][j];
			}
		}
	}

	if (zerocnt == 0) {
		printf("%d", 0);
	}
	else {
		choiceVpos(0, 0);
		if (falg == false) {
			printf("%d", -1);
		}
		else {
			printf("%d", minResult);
		}
	}
	return 0;
}