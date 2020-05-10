#pragma warning (disable :4996)
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
char list[9];
bool numlist[10];
int k;
vector <char> v;
vector <char> minAns;
vector <char> maxAns;
bool check() {
	for (int i = 0; i < k; i++) {
		if (list[i] == '<') {
			if (v[i] > v[i + 1]) {
				return false;
			}
		}
		else {
			if (v[i] < v[i + 1]) {
				return false;
			}
		}
	}
	return true;
}
void sol(int cnt , int index) {
	if (cnt == k+1) {
		for (int i = 0; i < 10; i++) {
			if (numlist[i] == true) {
				v.push_back(i+'0');
			}
		}
		do {
			if (check()) {
				if (minAns.empty()) {
					for (int i = 0; i < v.size(); i++) {
						minAns.push_back(v[i]);
					}
				}
				else {
					maxAns.clear();
					for (int i = 0; i < v.size(); i++) {					
						maxAns.push_back(v[i]);
					}
				}
			}
		} while (next_permutation(v.begin(), v.end()));
		v.clear();
	}
	else {
		for (int i = index; i < 10; i++) {
			if (numlist[i] == true) continue;
			numlist[i] = true;
			sol(cnt + 1,i);
			numlist[i] = false;
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> k;
	for (int i = 0; i < k;i++) {
		cin >> list[i];
	}
	sol(0, 0);
	for (int i = 0; i < maxAns.size(); i++) {
		cout << maxAns[i];
	}
	cout << endl;
	for (int i = 0; i < minAns.size(); i++) {
		cout << minAns[i];
	}
	return 0;
}