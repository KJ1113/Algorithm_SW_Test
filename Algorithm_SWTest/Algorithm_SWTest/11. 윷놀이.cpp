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
	else if (21 <= conPos && conPos <= 26) {
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
	/*for (int i = 0; i < 10; i++) {
		cout << turnSize[i] << " ";
	}
	cout << endl;*/
	selWord(0, 0);
	cout << ans;
}