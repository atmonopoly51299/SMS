#include"Login.h"
fstream & Login::GotoLine(fstream & file, int num)
{
	file.seekg(ios::beg);
	for (int i = 0; i <= num - 1; ++i) {
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return file;
}

int Login::changePassword(char filename[]) {
	fstream out;
	out.open(filename);
	if (!out.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	GotoLine(out, stt);	
	cout << "Type in your new password, password must be at least 6 characters" << endl;
	cout << "New password: ";
	char newP[200];
	do {
		cin.ignore(200, '\n');
		cin.get(newP, 200, '\n');
	} while (strlen(newP) < 6);
	out << newP;
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
		}
		++stt;
		//sN loaded, now check if this sN matches the inputted one:
		if (match(username, sN, id)) {
			in.close();
			return 1;
		}
	}
	cout << "User non-existed, please check your typing" << endl;
	in.close();
	return 2;
}
bool Login::login(char filenameUsername[], char filenamePassword[]) {
	do {
		cout << "Username: ";
		cin.get(username, 50, '\n');
		cout << "Username: ";
		cin.ignore(50, '\n');
		cin.get(password, 50, '\n');
		if (username[0] != ' '&&password[0] != ' '&&foundUsername(filenameUsername) == 1 && passWord(filenamePassword) == 1)break;
	} while (1);
	cout << "Login successfully!" << endl;
	if (strlen(password)==1 &&password[0]==defaultPass) {
		cout << "Please change your password" << endl;
		changePassword(filenamePassword);
	}
	return true;
}