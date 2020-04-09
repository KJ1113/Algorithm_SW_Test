#pragma warning (disable :4996)
#include<iostream>
#include<cstdio>
using namespace std;
int N, M;
int Map[501][501];
int main() {
	freopen("input.txt","r",stdin);
	scanf("%d %d",&N,&M);
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M;j++) {
			scanf("%d", &Map[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%d", Map[i][j]);
		}
		printf("\n");
	}

	return 0;
}