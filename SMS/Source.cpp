#include"Login.h"
int main() {
	cout << "welcome" << endl;
	Login login;
	login.login("username.txt", "password.txt","type.txt");
	switch (login.type)
	{
	case 0://student,...to show proper menu
	default:
		break;
	}
	return 0;
}