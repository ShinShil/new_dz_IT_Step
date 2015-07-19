#include <iostream>
#include <typeinfo.h>
using namespace std;

#define TEST 3

class stack
{
private:
	int arr[32];
	int ind_top = -1;
public:
	stack(){
		memset(arr, -1, sizeof(int[32]));
	}

	void push(int a) {
		if (ind_top < 31)
			arr[++ind_top] = a;
		else
			throw "\nStack is ovewrflow\n";
	}

	void pop() {
		if (ind_top != -1)
			arr[ind_top--] = -1;
		else
			throw"\nStack is empty";
	
	}

	int top(){
		if (ind_top != -1)
			return arr[ind_top];
		else
			throw"\nStack is empty";
	}
};

void print_ramka(char* str)
{
	int i = 0;
	while (str[i++] != '\0');
	printf("\n");

	printf("%s\n", str);

	for (int j = 0; j < i; ++j)
		printf("-");
}

int main() {

	int choice, temp;
	stack st;
	set_terminate(error);
	for (;;) {
		cout << "\n------------------------------------";
		print_ramka("Stack");
		cout << "\n1.Push";
		cout << "\n2.Pop";
		cout << "\n3.See top";
		cout << "\n4.Exit";
		cout << "\n\n";

		cin >> choice;
		try {
			switch (choice)
			{
			case 1:
				cout << "\nEnter the value: ";
				cin >> temp;
				st.push(temp);
				break;
			case 2:
				st.pop();
				break;
			case 3:
				st.top();
				break;
			case 4:
				throw 1;
			case 5:
				throw 'c';
			}
		}
		catch (char* ex) {
			cout << ex<<endl;
		}
		catch (int a) {
			break;
		}
	}
	
	cout << endl << endl;
	return 0;
}
