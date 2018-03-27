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

void Login::changePassword(char filename[]) {
	cout << "Change password"<<endl;
	cout << "Please, retype your current password: ";
	char oldP[200];
	do {
		cin.get(oldP, 200, '\n');
		cin.ignore(200, '\n');
		if (match(password, oldP)) break;
		else cout << "Wrong password, please retype: ";
	} while (1);
	changePasswordInit(filename);
}
int Login::changePasswordInit(char filename[]) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	//store file content from starting to before stt into a char[]
	char *c=new char[50], *pW=new char[100000];
	int id = -1;
	for (int i = 0; i < stt; ++i) {
		in.get(c, 50, '\n');
		for (int i = 0; i < strlen(c); ++i) {
			pW[++id] = c[i];
		}
		pW[++id] = '\n';
		in.ignore(5, '\n');
	}
	cout << "Type in your new password, password must be at least 6 characters" << endl;
	cout << "New password: ";
	char newP[200];
	do {
		cin.get(newP, 200, '\n');
		cin.ignore(200, '\n');//watch this!!!
		//cout << newP << endl;//for checking only
		if (strlen(newP) < 6) {
			cout << "Password must be at least 6 characters!" << endl<<"Retype: ";
		} 
		else if(match(password, newP)) {
			cout << "New password must differ from your old password" << endl << "Retype: ";
		}
		else break;
	} while (1);//limit to 6 chars
	cout << "Password changed successfully!" << endl;
	//append new password to position at stt
	delete[]password;
	password = new char[50];
	for (int i = 0; i < strlen(newP); ++i) {
		pW[++id] = newP[i];
		password[i] = newP[i];
	}
	//ignore char: 1
	//in.get(c, 50, '\n');
	in.ignore(50, '\n');
	pW[++id] = '\n';
	password[strlen(newP)] = '\0';
	//add the rest of the stream into the char[]
	delete[]c;
	c = new char[50];

	while (!in.eof()) {
		in.get(c, 50, '\n');
		for (int i = 0; i < strlen(c); ++i) {
			pW[++id] = c[i];
		}
		pW[++id] = '\n';
		in.ignore(5, '\n');
	}
	pW[id] = '\0';
	in.clear();
	in.close();

	//time to overwrite the file with char[]
	fstream out;
	out.open(filename,ios::out);
	if (!out.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	out << pW;
	out.close();
	delete[]pW;
	delete[]c;
	return 1;
}
/*bool Login::matchPassword(char inputted[], char pN[], int id) {
	if (strlen(inputted) != strlen(pN))return false;
	for (int i = 0; i <= id; ++i) {
		if (inputted[i] != pN[i])return false;
	}
	return true;
}*/
bool Login::match(char inputted[], char sN[]) {
	if (strlen(inputted) != strlen(sN))return false;
	for (int i = 0; i < strlen(inputted); ++i) {
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

	char c[50], *pW=new char[50];
	for (int i = 0; i < stt; ++i) {
		//ignore stt-1 rows of record
		//in.get(c, 50, '\n');
		in.ignore(50, '\n');
	}
	in.get(pW, 50, '\n');
	//pW[strlen(pW)] = '\0';
	if(match(password,pW)){
		in.close();
		return 1;
	}	
	delete[]pW;
	cout << "Wrong password, please check your typing" << endl;
	type = 1;
	stt = -1;
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
	char *sN=new char[50];
	int id = -1;
	while (!in.eof()) {
		in.get(sN,50, '\n');
		in.ignore(1, '\n');
		if (sN[0] == '-')++type;
		//sN[strlen(sN)] = '\0';
		++stt;
		//sN loaded, now check if this sN matches the inputted one:
		if (match(username, sN)) {
			in.close();
			return 1;
		}
		delete[]sN;
		sN = new char[50];
		id = -1;
	}
	cout << "User non-existed, please check your typing" << endl;

	type=1;
	stt = -1;

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
			type = 1;//redundant?
		}
		cout << "Password: ";
		cin.ignore(50, '\n');
		cin.get(password, 50, '\n');
		cin.ignore(50, '\n');

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
	password = new char[50];
	stt = -1;
	type = 1;
}