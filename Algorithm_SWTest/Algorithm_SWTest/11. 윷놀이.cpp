#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct Word
{
	int pos = 1;
	bool move = true;
};
struct WordSpace
{
	int  tmp = 1;
	bool goable = true;
};
WordSpace Map[42];
Word Words[4];
int selectW_index[10];
int turnSize[10];
int ans = 0;
bool goWord(int goPos) {
	if (goPos == 33) {
		return true;
	}
	else {
		if (Map[goPos].goable == false) {
			return false;
		}
		return true;
	}
}
void init() {
	Map[2].tmp = 2;
	Map[3].tmp = 4;
	Map[4].tmp = 6;
	Map[5].tmp = 8;
	Map[6].tmp = 10;
	Map[7].tmp = 12;
	Map[8].tmp = 14;
	Map[9].tmp = 16;
	Map[10].tmp = 18;
	Map[11].tmp = 20;
	Map[12].tmp = 22;
	Map[13].tmp = 24;
	Map[14].tmp = 26;
	Map[15].tmp = 28;
	Map[16].tmp = 30;
	Map[17].tmp = 32;
	Map[18].tmp = 34;
	Map[19].tmp = 36;
	Map[20].tmp = 38;
	Map[32].tmp = 40;
	Map[21].tmp = 13;
	Map[22].tmp = 16;
	Map[23].tmp = 19;
	Map[24].tmp = 28;
	Map[25].tmp = 27;
	Map[26].tmp = 26;
	Map[27].tmp = 22;
	Map[28].tmp = 24;
	Map[29].tmp = 25;
	Map[30].tmp = 30;
	Map[31].tmp = 35;
	Map[33].tmp = 0;
}
int nextPos(int conPos, int goSize) {
	int nextPos;
	if (1 <= conPos && conPos <= 20) {
		if (conPos == 6) {
			if (goSize == 5) { //5
				nextPos = 30;
			}
			else if (goSize == 4) {//4
				nextPos = 29;
			}
			else if (goSize == 3) {//4
				nextPos = 23;
			}
			else if (goSize == 2) {//4
				nextPos = 22;
			}
			else {
				nextPos = 21;
			}
		}
		else if (conPos == 11) {
			if (goSize == 5) { //5
				nextPos = 31;
			}
			else if (goSize == 4) {//4
				nextPos = 30;
			}
			else if (goSize == 3) {//4
				nextPos = 29;
			}
			else if (goSize == 2) {//4
				nextPos = 28;
			}
			else {
				nextPos = 27;
			}
		}
		else if (conPos == 16) {
			if (goSize == 5) { //5
				nextPos = 30;
			}
			else if (goSize == 4) {//4
				nextPos = 29;
			}
			else if (goSize == 3) {//4
				nextPos = 26;
			}
			else if (goSize == 2) {//4
				nextPos = 25;
			}
			else {
				nextPos = 24;
			}
		}
		else if (conPos == 17) {
			if (goSize == 5) { //5
				nextPos = 33;
			}
			else if (goSize == 4) {//4
				nextPos = 32;
			}
			else {
				nextPos = conPos + goSize;
			}
		}
		else if (18 <= conPos && conPos <= 20) {
			if (conPos + goSize >= 22) { //5
				nextPos = 33;
			}
			else if (conPos + goSize == 21) {//4
				nextPos = 32;
			}
			else {
				nextPos = conPos + goSize;
			}
		}
		else {
			nextPos = conPos + goSize;
		}
	}
	else if (21 == conPos || conPos == 24) {
		if (goSize == 3) { //5
			nextPos = 29;
		}
		else if (goSize == 4) {//4
			nextPos = 30;
		}
		else if (goSize == 5) {//4
			nextPos = 31;
		}
		else {
			nextPos = conPos + goSize;
		}
	}
	else if (22 == conPos || conPos == 25) {
		if (goSize == 2) { //5
			nextPos = 29;
		}
		else if (goSize == 3) {//4
			nextPos = 30;
		}
		else if (goSize == 4) {//4
			nextPos = 31;
		}
		else if (goSize == 5) {
			nextPos = 32;
		}
		else {
			nextPos = conPos + goSize;
		}
	}
	else if (23 == conPos || conPos == 26) {
		if (goSize == 2) { //5
			nextPos = 30;
		}
		else if (goSize == 3) {//4
			nextPos = 31;
		}
		else if (goSize == 4) {//4
			nextPos = 32;
		}
		else if (goSize == 5) {
			nextPos = 33;
		}
		else {
			nextPos = 29;
		}
	}
	else if (goSize == 27 || goSize == 28) {
		nextPos = conPos + goSize;
	}
	else {
		if (conPos + goSize >= 33) { //5
			nextPos = 33;
		}
		else {
			nextPos = conPos + goSize;
		}
	}
	return nextPos;
}
void selWord(int cnt, int index) {
	if (cnt == 10) {
		int sum = 0;
		
		for (int i = 0; i < 10; i++) {
			int selectIdx = selectW_index[i];
			int conPos = Words[selectIdx].pos;
			int goPos = nextPos(conPos, turnSize[i]);
			if (goWord(goPos) == false || Words[selectIdx].move == false) {
				for (int i = 1; i < 33; i++) {
					Map[i].goable = true;
				}
				for (int i = 0; i < 4; i++) {
					Words[i].pos = 1;
					Words[i].move = true;
				}
				return;
			}
			else {
				Map[conPos].goable = true; // ������ġ �̵�����
				Words[selectIdx].pos = goPos;
				//��ġ���� ���� ��
				if (goPos == 33) {
					Words[selectIdx].move = false; // �ش縻 ��������
				}
				else {
					Map[goPos].goable = false; // �ű� ��ġ ��������
					sum += Map[goPos].tmp;
				}
			}
		}
		for (int i = 1; i < 33; i++) {
			Map[i].goable = true;
		}
		for (int i = 0; i < 4; i++) {
			Words[i].pos = 1;
			Words[i].move = true;
		}
		ans = max(ans, sum);
	}
	else {
		for (int i = 0; i < 4; i++) {
			selectW_index[index] = i;
			selWord(cnt + 1, index + 1);
		}
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	for (int i = 0; i < 10; i++) {
		scanf("%d", &turnSize[i]);
	}
	init();
	selWord(0, 0);
	printf("%d",ans);
}