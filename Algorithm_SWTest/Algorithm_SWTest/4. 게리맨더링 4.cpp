#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include <vector>
#include <queue>
#include<algorithm>
using namespace std;
int N;
int local[10];
int ens = 1000000;
bool flag = false;
bool vistedLocal[10];
vector <int> local_Nearlist [10];
int bfs(bool redOrblue ,  int myindex) {

	bool visted_Myteam[10];
	for (int i = 0; i < N;i++) {
		visted_Myteam[i] = false;
	}
	queue<int> Myteamq;
	visted_Myteam[myindex] = true;
	Myteamq.push(myindex);
	int myteam_sum = local[myindex];
	while (!Myteamq.empty()) {

		int index = Myteamq.front();
		Myteamq.pop();
		for (int i = 0; i < local_Nearlist[index].size(); i++) {
			int near_Index = local_Nearlist[index][i];
			if (visted_Myteam[near_Index]==true) continue;
			if (vistedLocal[near_Index] != redOrblue) continue;

			visted_Myteam[near_Index] = true;
			Myteamq.push(near_Index);
			myteam_sum += local[near_Index];
		}
	}
	return myteam_sum;
}
void choiceLocal(int index, int cnt ,int Maxcnt) {
	if (cnt == Maxcnt) {
		int red;
		int blue;

		int redNum=0;
		int blueNum=0;
		for (int i = 0; i < N;i++) {
			if (vistedLocal[i] == false) {
				redNum += local[i];
				red = i;
			}
			else {
				blueNum += local[i];
				blue = i;
			}
		}
		if ((bfs(false, red) + bfs(true, blue)) == redNum+blueNum) {
			flag = true;
			ens = min(ens, abs(redNum - blueNum));
		}
	}
	else {
		for (int i = index; i < N; i++) {

			if (vistedLocal[i] == true) continue;
			vistedLocal[i] = true;
			choiceLocal(i+1,cnt+1,Maxcnt);
			vistedLocal[i] = false;
		}
	}
}
int main() {
	//freopen("input.txt","r",stdin);
	scanf("%d", &N);
	for (int i = 0; i< N ;i++) {
		scanf("%d", &local[i]);
	}

	for (int i = 0; i < N; i++) {
		int nears=0;
		scanf("%d", &nears);
		for (int j = 0; j < nears;j++) {
			int num;
			scanf("%d", &num);
			local_Nearlist[i].push_back(num-1);
		}
	}
	for (int maxcnt = 1; maxcnt <= N/2 ; maxcnt++) {
		choiceLocal(0, 0,maxcnt);
	}
	if (flag == false) {
		printf("%d", -1);
	}
	else {
		printf("%d", ens);
	}
	return 0;
}