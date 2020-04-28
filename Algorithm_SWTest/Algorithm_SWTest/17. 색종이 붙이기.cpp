#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
#include<vector>
using namespace std;
bool delable = false;
int tmpMap[10][10];
int ans = 999999;
int sizePaper[6] = { 0,5,5,5,5,5 };
vector <pair <int, int>> oneList;
bool check(int cunY, int cunX, int size) {

	for (int i = cunY; i < cunY + size; i++) {
		for (int j = cunX; j < cunX + size; j++) {
			if (i < 0 || i >= 10 || j < 0 || j >= 10) {
				return false;
			}
			if (tmpMap[i][j] == 0) {
				return  false;
			}
		}
	}
	return  true;
}
void solve(int index, int cnt) {

	if (cnt > ans) {
		return;
	}
	if (index == oneList.size()) {
		ans = min(ans, cnt);
		delable = true;
		return;
	}
	else {
		int cunY = oneList[index].first;
		int cunX = oneList[index].second;
		if (tmpMap[cunY][cunX] == 0) {
			solve(index + 1, cnt);
		}
		else {

			for (int size = 5; size >= 1; size--) {
				bool falg = true;
				if (sizePaper[size] == 0) continue;
				if (check(cunY, cunX, size) == false) continue;

				for (int i = cunY; i < cunY + size; i++) {
					for (int j = cunX; j < cunX + size; j++) {
						tmpMap[i][j] = 0;
					}
				}
				sizePaper[size]--;
				solve(index + 1, cnt + 1);
				sizePaper[size]++;
				for (int i = cunY; i < cunY + size; i++) {
					for (int j = cunX; j < cunX + size; j++) {
						tmpMap[i][j] = 1;
					}
				}
			}
		}

	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%d", &tmpMap[i][j]);
			if (tmpMap[i][j] == 1) {
				oneList.push_back(pair <int, int>(i, j));
			}
		}
	}
	solve(0, 0);
	if (delable == false) printf("%d", -1);
	else printf("%d", ans);
	return 0;
}