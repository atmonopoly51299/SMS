#include"ViewInfo.h"
int viewInfo(char filename[], int stt) {
	fstream out;
	out.open(filename);
	if (!out.is_open()) {
		cout << "Sorry, our service encountered an error, please retry!" << endl;
		return 0;
	}
	GotoLine(out, stt);

}