#pragma warning (disable : 4996)
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct Word
{
	int pos = 1;
	int myHeight = 1;
	bool move = true;
};
struct WordSpace
{
	int  tmp = 1;
	bool goable = true;
};
WordSpace Map[42];
Word Words[4];
int selctW_index[10];
int turnSize[10];
int ans = 0;
bool goWord(int goPos) {
	if (goPos == 41) {
		return true;
	}
	else {
		if (Map[goPos].goable == false) {
			return false;
		}
		return true;
	}
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
				nextPos = 32;
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
			if (conPos + goSize == 21) { //5
				nextPos = 33;
			}
			else {
				nextPos = conPos + goSize;
			}
		}
		else if (conPos == 17) {
			if (conPos + goSize == 22) { //5
				nextPos = 33;
			}
			else if (conPos + goSize == 21) {//4
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
			//cout << selctW_index[i] << " ";
			int goPos = nextPos(Words[selctW_index[i]].pos, turnSize[i]);
			sum += Map[goPos].tmp;
			if (goWord(goPos) == false) {
				//cout << selctW_index[i] <<"번째 말이 "<< goPos << " 위치에 갈려다 이미자리가 있어 못감."<< endl;
				for (int i = 0; i < 42; i++) {
					Map[i].goable = true;
				}
				for (int i = 0; i < 4; i++) {
					Words[i].pos = 1;
					Words[i].move = true;
				}
				return;
			}
			else if (Words[selctW_index[i]].move == false) {
				//cout << selctW_index[i] << "번째 말이 " << goPos << " 위치에 갈려다 이미 목표지점에 있어 못감." << endl;
				for (int i = 0; i < 42; i++) {
					Map[i].goable = true;
				}
				for (int i = 0; i < 4; i++) {
					Words[i].pos = 1;
					Words[i].move = true;
				}
				return;
			}
			else {
				int conPos = Words[selctW_index[i]].pos;
				Map[conPos].goable = true; // 원래위치 이동가능

				//위치설정 끝난 후
				if (goPos == 33) {
					Words[selctW_index[i]].move = false; // 해당말 못움직임
				}
				else {
					Map[goPos].goable = false; // 옮긴 위치 못가도록
				}
			}
		}
		//cout << endl;
		for (int i = 0; i < 42; i++) {
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
			selctW_index[index] = i;
			selWord(cnt + 1, index + 1);
		}
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	for (int i = 0; i < 10; i++) {
		scanf("%d", &turnSize[i]);
	}
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

	Map[29].tmp = 24;
	Map[29].tmp = 24;
	Map[29].tmp = 24;
	Map[29].tmp = 24;

	cout << endl;
	selWord(0, 0);
	cout << ans;
}