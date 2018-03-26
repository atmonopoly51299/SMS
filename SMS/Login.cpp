#include"Login.h"

/*void Login::getType(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
	}
	char c, pW[50];
	int id = -1;
	for (int i = 0; i < stt; ++i) {
		//ignore stt-1 rows of record
		while (in >> c && c != '\n');
	}
	in>>type;
	in.close();
}*/
int Login::changePassword(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	//store file content from starting to before stt into a char[]
	char c, pW[100000];
	int id = -1;
	for (int i = 0; i < stt; ++i) {

		while (in >> c && c != '\n')pW[++id] = c;
		pW[++id] = c;//store that '\n'
	}
	cout << "Type in your new password, password must be at least 6 characters" << endl;
	cout << "New password: ";
	char newP[200];
	do {
		cin.ignore(200, '\n');//watch this!!!
		cin.get(newP, 200, '\n');
	} while (strlen(newP) < 6);//limit to 6 chars

	//append new password to position at stt
	for (int i = 0; i < strlen(newP); ++i)pW[++id] = newP[i];
	//add newline char
	pW[++id] = '\n';

	//ignore two chars: 1\n
	in >> c;
	in >> c;

	//add the rest of the stream into the char[]
	while (in >> c) {
		pW[++id] = c;
	}
	in.close();

	//time to overwrite the file with char[]
	fstream out;
	out.open(filename);
	if (!out.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	out << pW;
	out.close();
	return 1;
}
bool Login::matchPassword(char inputted[], char pN[], int id) {
	if (strlen(inputted) != strlen(pN))return false;
	for (int i = 0; i <= id; ++i) {
		if (inputted[i] != pN[i])return false;
	}
	return true;
}
bool Login::match(char inputted[], char sN[], int id) {
	if (strlen(inputted) != strlen(sN))return false;
	for (int i = 0; i <= id; ++i) {
		if (inputted[i] != sN[i])return false;
	}
	return true;
}
int Login::passWord(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}

	char c, pW[50];
	int id = -1;
	for (int i = 0; i < stt; ++i) {
		//ignore stt-1 rows of record
		while (in >> c && c != '\n');
	}

	while (in >> c && c != '\n')pW[++id] = c;
	if(match(password,pW,id)){
		in.close();
		return 1;
	}	
	cout << "Wrong password, please check your typing" << endl;
	in.close();
	return 2;
}
int Login::foundUsername(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	char sN[50], c;
	int id = -1;
	while (!in.eof()) {
		while (in>>c && c != '\n') {
			sN[++id] = c;
			if (c == '-')++type;
		}
		++stt;
		//sN loaded, now check if this sN matches the inputted one:
		if (match(username, sN, id)) {
			in.close();
			return 1;
		}
	}
	cout << "User non-existed, please check your typing" << endl;
	type=1;
	in.close();
	return 2;
}
void Login::login() {
	char filenameUsername[50], filenamePassword[50];
	do {
		cout << "Username: ";
		cin.get(username, 50, '\n');
		if (username[0] >= '1'&&username[0] <= '9') {
			strcpy_s(filenameUsername, Const::usernameStudent);
			strcpy_s(filenamePassword, Const::passwordStudent);
			type = 0;
		}
		else {
			strcpy_s(filenameUsername, Const::usernameSL);
			strcpy_s(filenamePassword, Const::passwordSL);
			type = 1;
		}
		cout << "Password: ";
		cin.ignore(50, '\n');
		cin.get(password, 50, '\n');
		if (username[0] != ' '&&password[0] != ' '&&foundUsername(filenameUsername) == 1 && passWord(filenamePassword) == 1)break;
	} while (1);
	cout << "Login successfully!" << endl;
	if (strlen(password)==1 &&password[0]==defaultPass) {
		cout << "Please change your password" << endl;
		changePassword(filenamePassword);
	}
	//if(type==1)getType(Const::typeSL);
}
Login::Login() {
	type = 1;
}