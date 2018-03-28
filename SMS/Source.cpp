#include"Login.h"
#include"ViewInfo.h"
int main() {
	//if ever logout->login is the only option
	cout << "welcome" << endl;
	Login login;
	login.login();
	cout<<login.type<<endl;

	if(login.type)login.changePassword(Const::passwordSL);
	else login.changePassword(Const::passwordStudent);
	
	cout<<endl;
	cout << "View Info" << endl;
	ViewInfo vi;

	if(login.type)vi.viewInfo(Const::infoSL, login.stt);
	else vi.viewInfo(Const::infoStudent, login.stt);
	

	return 0;
}