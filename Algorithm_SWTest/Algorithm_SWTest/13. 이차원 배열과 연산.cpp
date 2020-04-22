#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
int r, c, k;
vector <vector <int>> Xlist ; //����
vector <vector <int>> Ylist; //����
int cnt[101];
int Map[1000][1000];
int Rsize = 3; // �� ���� y [y][]
int Csize = 3; // �� ���� x [][x]
bool desc(pair<int, int>  a, pair<int, int>  b) {
	if (a.second==0 || b.second == 0) {
		return a.second > b.second;
	}
	else {
		if (a.second < b.second || a.second > b.second) {
			return a.second < b.second;
		}
		else {
			return a.first < b.first;
		}
	}
}
void move() {
	vector < vector <pair<int, int>>> list;
	if (Rsize >= Csize) {
		//R����
		
		for (int Y = 0; Y < Rsize; Y++) {
			vector <int> tmplist;
			
			for (int j = 0; j < Xlist[Y].size() ; j++) {
				int num = Xlist[Y][j];
				cnt[num]++;
			}
			vector <pair<int, int>> v;
			for (int num = 0; num < 101; num++) {
				if (cnt[num + 1] != 0) {
					v.push_back(pair<int, int>(num + 1, cnt[num + 1]));
				}
			}
			list[Y].push_back(v);
			cout << "?";
			for (int i = 1; i<101;i++) {
				cnt[i] = 0;
			}
		}
		for (int index = 0; index < list.size();index++) {
			sort(list[index].begin() , list[index].end(), desc);
		}
		for (int index = 0; index < list.size(); index++) {
			for (int idx = 0; idx < list[index].size(); idx++) {
				cout << list[index][idx].first << " " << list[index][idx].second << " ";
			}
			cout << endl;
		}
		

	}
	else { // ���ΰ� ��� �Ʒ��γ����� ����
		
	}

	for (int i = 0; i < Rsize; i++) {
		for (int j = 0; j < Csize; j++) {
			cout << Map[i][j]<<" ";
		}
		cout << endl;
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d",&r,&c,&k);
	r--;
	c--;
	for (int i = 0; i < 3;i++) {
		vector <int> v;
		for (int j = 0; j < 3; j++) {
			scanf("%d", &Map[i][j]);
			v.push_back(Map[i][j]);
		}
		Xlist.push_back(v);
	}
	for (int i = 0; i < 3; i++) {
		vector <int> v;
		for (int j = 0; j < 3; j++) {
			v.push_back(Map[j][i]);
		}
		Ylist.push_back(v);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << Map[i][j]<<" ";
		}
		cout << endl;
	}

	int time = 0;
	move();
	while (true) {
		if (time==101) {
			time = -1;
			break;
		}
		else if (Map[r][c] == k) {
			break;
		}
		else {
			cout << time << endl;
			move();
			time++;
		}
	}
	printf("%d",time);

	return 0;
}