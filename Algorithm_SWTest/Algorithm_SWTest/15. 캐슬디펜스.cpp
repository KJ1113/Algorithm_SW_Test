#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
#include<vector>
using namespace std;
int N, M, D;
bool selpoint[16];
int ans = 0;
struct aimMan{
	int y;
	int x;
	bool life = true;
};
vector<aimMan> aimMans;
vector<aimMan> tmp_aimMans;
void down() {
	for (int index = 0; index < tmp_aimMans.size(); index++) {
		if (tmp_aimMans[index].life == true) {
			tmp_aimMans[index].y++;
			if (tmp_aimMans[index].y == N) {
				tmp_aimMans[index].life = false;
			}
		}
	}
}
bool alldie() {
	for (int index = 0; index < tmp_aimMans.size(); index++) {
		if (tmp_aimMans[index].life == true) {
			return false;
		}
	}
	return true;
}
void selectPoint(int cnt, int Maxcnt, int index) {
	if (cnt == Maxcnt) {
		vector<pair <int, int>> attackMan;
		int diePoint = 0;
		tmp_aimMans = aimMans;
		for (int i = 0; i < M; i++) {
			if (selpoint[i] == true) {
				attackMan.push_back(pair <int, int>(N, i));
			}
		}
		while (!alldie()){
			vector<int> dieMan_index;
			for (int index = 0; index < attackMan.size(); index++) {
				int d_index , dieMan_y, dieMan_x, dieMan_long;
				bool dieflag = false;

				for (int i = 0; i < tmp_aimMans.size(); i++) {
					int D_long = abs(tmp_aimMans[i].y - attackMan[index].first) + abs(tmp_aimMans[i].x - attackMan[index].second);
					if (tmp_aimMans[i].life == false) continue;
					if (D >= D_long) {
						if (dieflag == false) {
							d_index = i;
							dieMan_y = tmp_aimMans[i].y;
							dieMan_x = tmp_aimMans[i].x;
							dieMan_long = D_long;
							dieflag = true;
						}
						else {
							if (dieMan_long > D_long) {
								d_index = i;
								dieMan_y = tmp_aimMans[i].y;
								dieMan_x = tmp_aimMans[i].x;
								dieMan_long = D_long;
							}
							else if (dieMan_long == D_long) {
								if (tmp_aimMans[i].x < dieMan_x) {
									d_index = i;
									dieMan_y = tmp_aimMans[i].y;
									dieMan_x = tmp_aimMans[i].x;
									dieMan_long = D_long;
								}
							}
							else {
								continue;
							}
						}
					}
				}
				if (dieflag == true) {
					bool f = true;
					for (int i = 0; i < dieMan_index.size(); i++) {
						if (dieMan_index[i] == d_index) {
							f = false;
							break;
						}

					}
					if (f == true && dieflag == true)
						dieMan_index.push_back(d_index);
				}

			}
			for (int i = 0; i < dieMan_index.size(); i++) {
				tmp_aimMans[dieMan_index[i]].life = false;
			}
			diePoint += dieMan_index.size();
			down();
		}
		ans = max(ans, diePoint);
	}
	else {
		for (int i = index; i < M; i++) {
			if (selpoint[i] == true) continue;
			selpoint[i] = true;
			selectPoint(cnt + 1, Maxcnt, i);
			selpoint[i] = false;
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int input;
			scanf("%d", &input);
			if (input == 1) {
				aimMan a;
				a.y = i;
				a.x = j;
				aimMans.push_back(a);
			}
		}
	}
	for (int num = 1; num <= 3; num++) {
		selectPoint(0, num, 0);
	}
	printf("%d", ans);
	return 0;
}