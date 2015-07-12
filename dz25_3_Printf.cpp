#include <iostream>
using namespace std;
#include <stdarg.h>

void Printf(char* str, ...);

int main() {

	Printf("q\n: %d %d %lf %s", 5, 7, 2.256,"str");

	cout<<endl<<endl;
	return 0;
}

void Printf(char* str, ...) {
	va_list arg_ptr;
	va_start(arg_ptr, str);
	while(*str!='\0') {
		if(*str == '%' && *(str + 1) == 'd' ){
			cout<<va_arg(arg_ptr, int);
			str+=2;
		}
		else if(*str == '%' && *(str + 1) == 'l' && *(str+2) == 'f'){
			cout<<va_arg(arg_ptr, double);
			str+=3;
		}
		else if(*str == '%' && *(str + 1) == 's') {
			cout<<va_arg(arg_ptr, char*);
			str+=2;
		}
		else {
			cout.put(*str);
			++str;
		}
	}
	va_end(arg_ptr);
}