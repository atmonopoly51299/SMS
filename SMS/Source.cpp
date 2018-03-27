#include"Login.h"
#include"ViewInfo.h"
int main() {
	cout << "welcome" << endl;
	Login login;
	login.login();
	login.changePassword(Const::passwordStudent);
	
	cout << "View Info" << endl;
	ViewInfo vi;
	vi.viewInfo(Const::infoStudent, 1);

	return 0;
}