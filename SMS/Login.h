#ifndef _LOGIN_H_
#define _LOGIN_H_
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Login {
private:
	char username[50];
	char password[50];
	int stt;
	bool firstTime;
	const char defaultPass = '1';
	int foundUsername(char filename[]);
	int passWord(char filename[]);
	bool match(char inputted[], char sN[], int id);
	bool matchPassword(char inputted[], char pN[], int id);
	int changePassword(char filename[]);
	fstream& GotoLine(fstream& file, int num);
public:
	Login();
	bool login(char filenameUsername[], char filenamePassword[]);
};
#endif