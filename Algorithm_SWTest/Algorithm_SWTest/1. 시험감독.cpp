#pragma warning (disable :4996)
#include <iostream>
using namespace std;
int N; // �������� ����
int B, C; // �Ѱ���üũ �ο� , �ΰ��� üũ�ο�
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