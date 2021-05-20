#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<dos.h>
#include<fstream>
#include<ctype.h>
#include<windows.h>
using namespace std;

//global variables to define common paths
char ran[30];
int w_len;
ofstream fout;
ifstream fin;
char path[100] = "";
char pathnew[100] = "";

//structure to store user information
struct userinfo {
	char username[30];
	double last;
}u;

//function to input username
void user() {
	cout << "enter username: "; cin >> u.username;
	strcat(path, u.username);
	strcat(path, ".dat");
	strcat(pathnew, u.username);
	strcat(pathnew, "all");
	strcat(pathnew, ".txt");
	fout.open(path, ios::app | ios::binary);
	fin.open(path, ios::binary | ios::in);
}

//function to generate a random word
void randWordGen(int u, int l) {
	unsigned int seedval;
	char alp[30] = "abcdefghijklmnopqrstuvwxyz";
	time_t t;
	seedval = (unsigned)time(&t);
	srand(seedval);
	char curr;
	w_len = (rand() % l) + u;

	for (int i = 0; i < w_len; i++) {
		w_len = (rand() % l) + u;
		curr = (rand() % 26) + 0;
		ran[i] = alp[curr];
	}
}


//checks the string for equality
int stringcheck(char inp[], char gen[]) {
	return (!strcmp(inp, gen));
}

//takes input from user and
double MAIN(int u, int l) {
	double total_time = 0;
	int corrwordcount = 0;
	double elapsed_secs;
	int n = 10;
	char inp[10] = { 0 };
	for (int i = 1; i <= n; i++) {
		randWordGen(u, l);
		cout << ran << endl;
		clock_t begin = clock();
		cin >> inp;
		clock_t end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		if (stringcheck(inp, ran)) {
			corrwordcount++;
		}
	}
	for (int i = 0; i < n; i++) {
		total_time += elapsed_secs;
	}
	long double minutes = total_time / 60;
	double wpm = corrwordcount / minutes;
	return wpm;
}

//adds new record
void addnewrec(double wpm) {
	cout << "processing...";
	Sleep(5000);
	u.last = wpm;
	fout.write((char*)&u, sizeof(u));
	fout.close();
	ofstream foutnew(pathnew, ios::app);
	foutnew << wpm << endl;
	foutnew.close();
	fin.read((char*)&u, sizeof(u));
	cout << "your typing speed is: " << u.last << " wpm." << endl;
	fin.close();
}

//displays all previous records
void displayall() {
	ifstream finnew(pathnew, ios::in);
	cout << "all your records are (wpm): " << endl;
	while (!finnew.eof()) {
		char ch;
		finnew.get(ch);
		cout << ch;
	}
}

//main menu screen
void mainmenu() {










	cout << R"(
         _|_|_|_|_|                      _|_|_|
             _|      _|    _|  _|_|_|    _|    _|  _|  _|_|    _|_|
             _|      _|    _|  _|    _|  _|_|_|    _|_|      _|    _|
             _|      _|    _|  _|    _|  _|        _|        _|    _|
             _|        _|_|_|  _|_|_|    _|        _|          _|_|
                           _|  _|
                       _|_|    _|
)";

}

//checks if file exists
bool fexist(const char *filename) {
	ifstream ifile(filename);
	return (bool)ifile;
}

int main() {
	mainmenu();
	user();
	int ch;
	do {
		cout << endl;
		cout << "what do you want to do? \n1. play new game\n2. see all records \n3. EXIT " << endl;
		cin >> ch;
		switch (ch) {
		case 1:
			int diff;
			cout << "what difficulty do you want?\n1.easy\n2.medium\n3.hard: " << endl;
			cin >> diff;
			system("cls");
			cout << "starting..." << endl;
			Sleep(1000);
			cout << "3...";
			Sleep(1000);
			cout << "2...";
			Sleep(1000);
			cout << "1...";
			Sleep(1000);
			system("cls");
			if (diff == 1) {
				addnewrec(MAIN(1, 4));
				break;
			}
			if (diff == 2) {
				addnewrec(MAIN(2, 6));
				break;
			}
			if (diff == 3) {
				addnewrec(MAIN(5, 10));
				break;
			}

		case 2:
			if (!fexist(path)) {
				cout << "NO PREVIOUS RECORDS!" << endl;
				break;
			}
			else {
				displayall();
			}
			break;
		default:
			exit(0);
		}
	} while (ch != 3);

	system("PAUSE");
}

