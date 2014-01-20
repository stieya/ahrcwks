#include <cstdlib>
#include <iostream>
//#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

int initialState[] = { 1, 2, 3, 4, 8, 0, 7, 6, 5 }; // initial state
int goalState[] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 }; // goal state
int resetValue = 0;
int tempHeuristic[] = { resetValue, resetValue, resetValue, resetValue }; // penyimpan sementara evaluation value
int totalSolution = 0; // total solusi yang dihasilkan

// prosedur untuk mencetak isi sebuah state ke layar
void printState(int state[]) {
    for (int i=0; i < 9; i++) {
		if (i % 3 == 0) {
			cout << "\n";
		}
        cout << state[i];
		cout << " ";
    }
	cout << "\n";
}

// prosedur untuk menggerakkan kotak kosong ke arah kiri
void moveLeft(int state[]) {
	int index0;
	for (int i = 0; i < 9; i++) {
        if (state[i] == 0) {
            index0 = i;
        }
    }
	if (index0 % 3 > 0) {
		int temp = state[index0];
		state[index0] = state[index0-1];
		state[index0-1] = temp;
	}
}

// prosedur untuk menggerakkan kotak kosong ke arah kanan
void moveRight(int state[]) {
	int index0;
	for (int i = 0; i < 9; i++) {
        if (state[i] == 0) {
            index0 = i;
        }
    }
	if (index0 % 3 < 2) {
		int temp = state[index0];
		state[index0] = state[index0+1];
		state[index0+1] = temp;
	}
}

// prosedur untuk menggerakkan kotak kosong ke arah atas
void moveUp(int state[]) {
	int index0;
	for (int i = 0; i < 9; i++) {
        if (state[i] == 0) {
            index0 = i;
        }
    }
	if (index0 > 2) {
		int temp = state[index0];
		state[index0] = state[index0-3];
		state[index0-3] = temp;
	}
}

// prosedur untuk menggerakkan kotak kosong ke arah bawah
void moveDown(int state[]) {
	int index0;
	for (int i = 0; i < 9; i++) {
        if (state[i] == 0) {
            index0 = i;
        }
    }
	if (index0 < 6) {
		int temp = state[index0];
		state[index0] = state[index0+3];
		state[index0+3] = temp;
	}
}

// fungsi yang menghasilkan nilai 1 jika array1 identik dengan array2, menghaslkan 0 jika tidak
int hasSameElement(int array1[], int array2[]) {
	int temp = 1;
	int i = 0;
	for (int i = 0; i < 9; i++) {
		if (array1[i] != array2[i]) {
			temp = 0;
		}
	}
	return temp;
}

// fungsi yang menghasilkan nilai heuristic untuk masing-masing sisi 8 puzzle
//	benar 1 dinilai 1, benar 2 dinilai 5, benar 3 dinilai 40 --> Pak Sabar's Heuristic :p
int sideHeuristic(int side, int currentState[], int goalState[]) {
	// side : 
	//	upside = 1
	//	rightside = 2
	//	downside = 3
	//	leftside = 4
	//	center vertical = 5
	//	center horizontal = 6
	int temp = 0;
	int match = 0;
	switch (side) {
		case 1:
			match = 0;
			for (int i = 0; i < 2; i++) {
				if (currentState[i] == goalState[i] && currentState[i] != 0) {
					match++;
				}
			}
			if (match == 1) {
				temp = temp + 1;
			} else if (match == 2) {
				temp = temp + 5;
			} else if (match == 3) {
				temp = temp + 40;
			}
		break;
		case 2:
			match = 0;
			for (int i = 2; i < 9; i=i+3) {
				if (currentState[i] == goalState[i] && currentState[i] != 0) {
					match++;
				}
			}
			if (match == 1) {
				temp = temp + 1;
			} else if (match == 2) {
				temp = temp + 5;
			} else if (match == 3) {
				temp = temp + 40;
			}
		break;
		case 3:
			match = 0;
			for (int i = 6; i < 9; i++) {
				if (currentState[i] == goalState[i] && currentState[i] != 0) {
					match++;
				}
			}
			if (match == 1) {
				temp = temp + 1;
			} else if (match == 2) {
				temp = temp + 5;
			} else if (match == 3) {
				temp = temp + 40;
			}
		break;
		case 4:
			match = 0;
			for (int i = 0; i < 7; i=i+3) {
				if (currentState[i] == goalState[i] && currentState[i] != 0) {
					match++;
				}
			}
			if (match == 1) {
				temp = temp + 1;
			} else if (match == 2) {
				temp = temp + 5;
			} else if (match == 3) {
				temp = temp + 40;
			}
		break;
		case 5:
			match = 0;
			for (int i = 1; i < 8; i=i+3) {
				if (currentState[i] == goalState[i]) {
					match++;
				}
			}
			if (match == 1) {
				temp = temp + 1;
			} else if (match == 2) {
				temp = temp + 5;
			} else if (match == 3) {
				temp = temp + 5;
			}
		break;
		case 6:
			match = 0;
			for (int i = 3; i < 6; i++) {
				if (currentState[i] == goalState[i]) {
					match++;
				}
			}
			if (match == 1) {
				temp = temp + 1;
			} else if (match == 2) {
				temp = temp + 5;
			} else if (match == 3) {
				temp = temp + 5;
			}
		break;
	}
	return temp;
}

// fungsi yang menghasilkan kolom ke- dari sebuah index value pada state
int getCol(int val) {
	return ((val/3)+1);
}

// fungsi yang menghasilkan baris ke- dari sebuah index value pada state
int getRow(int val) {
    return ((val%3)+1);
}

// fungsi yang menghasilkan jarak langkah suatu kotak terhadap kondisi goalnya
int stepCounter(int condition1, int condition2) {
	int temp1 = getCol(condition1)-getCol(condition2);
	if (temp1 < 0) {
		temp1 = (temp1 * -1) * 2;
	}
	int temp2 = getRow(condition1)-getRow(condition2);
	if (temp2 < 0) {
		temp2 = (temp2 * -1) * 2;
	}
    return (((temp1 + temp2) * -1) + 4);
	//return (temp1 + temp2);
}

// menghasilkan nilai Manhattan Heuristic untuk current state terhadap goal state
int manhattanHeuristic(int currentState[], int goalState[]) {
    int temp = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (currentState[i] != 0) {
                if (currentState[i] == goalState[j]) {
                    temp = temp + stepCounter(i, j);
                }
            }
        }
    }
    return temp;
}

// menghasilkan nilai heuristic total (Manhattan + Pak Sabar's) untuk setiap current state terhadap goal state
int heuristicValue(int currentState[], int goalState[]) {
	return sideHeuristic(1, currentState, goalState) + 
		sideHeuristic(2, currentState, goalState) + 
		sideHeuristic(3, currentState, goalState) + 
		sideHeuristic(4, currentState, goalState) + 
		sideHeuristic(5, currentState, goalState) + 
		sideHeuristic(6, currentState, goalState) + 
		manhattanHeuristic(currentState, goalState);
}

// prosedur yang melakukan penyalinan nilai setiap elemen pada array2 ke setiap elemen pada array2
//	array1 dan array2 sama-sama telah terdefinisi sebelumnya
void copyArray(int array1[], int array2[]) {
	for (int i = 0; i < 9; i++) {
		array2[i] = array1[i];
	}
}

int getTheBestIndex(int arrayHeuristic[]) {
	int temp = 0;
	int tempValue = arrayHeuristic[0];
	for (int i = 0; i < 4; i++) {
		if (arrayHeuristic[i] > tempValue) {
			tempValue = arrayHeuristic[i];
			temp = i;
		}
	}
	return temp;
}

int main(int argc, char *argv[])
{
    int currentState[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	copyArray(initialState, currentState);
	int childState[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	while (hasSameElement(currentState, goalState) == 0) {
		printState(currentState);
		copyArray(currentState, childState);
		moveUp(childState);
		if (hasSameElement(childState, currentState) == 1) {
			tempHeuristic[0] = 0;
		} else {
			tempHeuristic[0] = heuristicValue(childState, goalState);
			moveDown(childState);
		}
		moveLeft(childState);
		if (hasSameElement(childState, currentState) == 1) {
			tempHeuristic[1] = 0;
		} else {
			tempHeuristic[1] = heuristicValue(childState, goalState);
			moveRight(childState);
		}
		moveRight(childState);
		if (hasSameElement(childState, currentState) == 1) {
			tempHeuristic[2] = 0;
		} else {
			tempHeuristic[2] = heuristicValue(childState, goalState);
			moveLeft(childState);
		}
		moveDown(childState);
		if (hasSameElement(childState, currentState) == 1) {
			tempHeuristic[3] = 0;
		} else {
			tempHeuristic[3] = heuristicValue(childState, goalState);
			moveUp(childState);
		}
		int tempIndex = getTheBestIndex(tempHeuristic);
		switch (tempIndex) {
			case 0:
				moveUp(currentState);
			break;
			case 1:
				moveLeft(currentState);
			break;
			case 2:
				moveRight(currentState);
			break;
			case 3:
				moveDown(currentState);
			break;
		}
		totalSolution++;
	}
	printState(currentState);
	cout << "\nTotal Solution = ";
	cout << totalSolution;
	
	getchar();
	return 0;
}
