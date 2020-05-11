#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int N;
int ans = 0;
vector <pair<int, int>> v;
void solve(int cnt, int MaxCnt ,int pulsNum ,int index){
	if (index > v.size()) {
		return;
	}
	if (MaxCnt == cnt) {
		ans = max(ans, pulsNum);
	}
	else {
		for (int day = index; day < v.size(); day++) {
			if (day +v[day].first > N+1) continue;
			solve(cnt+1, MaxCnt, pulsNum+v[day].second , day +v[day].first);
		}
	}
}
int main() {
	scanf("%d",&N);
	for (int i = 0; i < N;i++) {
		int input1, input2;
		scanf("%d %d", &input1 , &input2);
		v.push_back(pair<int, int>(input1, input2));
	}
	for (int num = 1; num <= N; num++) {
		solve(0,num,0,0);
	}
	printf("%d",ans);
	return 0;
}