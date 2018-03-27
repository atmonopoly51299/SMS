#ifndef _LOGIN_H_
#define _LOGIN_H_
#include<iostream>
#include<fstream>
#include<string>
#include"Utils.h"
#include"Const.h"
using namespace std;
class Login {
private:
	char username[50];
	char *password;
	const char defaultPass = '1';
	int foundUsername(char filename[]);
	int passWord(char filename[]);
	bool match(char inputted[], char sN[]);
	//bool matchPassword(char inputted[], char pN[], int id);
	int changePasswordInit(char filename[]);
	//void getType(char filename[]);
public:
	int stt;//so thu tu cua hoc sinh trong file
	int type;//student/lecturer/staff
	Login();
	void login();
	void changePassword(char filename[]);
};
#endif