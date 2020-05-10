#pragma warning (disable : 4996)
#include <iostream>
#include <cstdio>
#include<queue>
#include<vector>
using namespace std;
int ans = -999999;
int length;
string input;
int cal(int a ,char c , int b) {
	if (c=='+') {
		return a+b;
	}
	else if (c == '-') {
		return a - b;
	}
	else  {
		return a * b;
	}
}
void calcurate(int index, int nowNum) {
	if (index >= length-1) {
		ans = max(ans, nowNum);
		return;
	}
	else {
		int tmp = cal(nowNum, input[index + 1], input[index + 2]-'0');
		calcurate(index + 2, tmp);
		if (index+4 <= length) {
			int temp = cal(input[index + 2] - '0', input[index + 3], input[index + 4] - '0');
			int next = cal(nowNum, input[index + 1], temp);
			calcurate(index+4, next);
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	scanf("%d", &length);
	cin >> input;
	calcurate(0, input[0]-'0');
	cout << ans;
	return 0;
}