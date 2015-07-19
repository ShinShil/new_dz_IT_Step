#include <iostream>
using namespace std;
#define MAX_DIGITS_IN_INT 10

int max_int(char* str);

int main() {

	
	char str[MAX_DIGITS_IN_INT];
	cout<<"INT_MAX: "<<INT_MAX<<endl;
	cout<<"Enter a digit: ";

	try {
		max_int(str);
	}
	catch(int err) {
		cout<<"bad_value, error code: "<<err<<endl;
	}

	cout<<endl;
	return 0;
}

int max_int(char* str) {
	char ch = '1';
	int res;
	int max = 0;
	ch = cin.get();
	while(1) {
		ch = cin.get();
		if(ch == '\n') {
			
			break;
			
		}
		if(ch <'0' || ch>'9') {
			throw -1;
			return -1;
		}
		str[max++] = ch;
		if(max==11) {
			throw -2;
			return -2;
		}
	}
		res = atoi(str);
		if(res<0) {
			throw -3;
			return -3;
		}

		return res;
}