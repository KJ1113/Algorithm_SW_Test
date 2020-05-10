#pragma warning (disable :4996)
#include <iostream>
using namespace std;
int N; // 시험장의 갯수
int B, C; // 총감독체크 인원 , 부감독 체크인원
int A[1000000];
int main() {
    freopen("input.txt","r",stdin);
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int input;
        scanf("%d", &A[i]);
    }
    scanf("%d %d", &B, &C);
    long long cnt = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] - B <= 0) {
            cnt++;
        }
        else {
            if ((A[i] - B) % C != 0) {
                cnt += (A[i] - B) / C + 2;
            }
            else {
                cnt += (A[i] - B) / C + 1;
            }
        }
    }
    cout << cnt;
    return 0;
}