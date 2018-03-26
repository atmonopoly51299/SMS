#ifndef _LOGIN_H_
#define _LOGIN_H_
#include<iostream>
#include<fstream>
#include<string.h>
#include"Utils.h"
#include"Const.h"
using namespace std;
class Login {
private:
	char username[50];
	char password[50];
	const char defaultPass = '1';
	int foundUsername(char filename[]);
	int passWord(char filename[]);
	bool match(char inputted[], char sN[], int id);
	bool matchPassword(char inputted[], char pN[], int id);
	int changePassword(char filename[]);
	void getType(char filename[]);
public:
	int stt;//so thu tu cua hoc sinh trong file
	int type;//student/lecturer/staff
	Login();
	void login();
};
#endif