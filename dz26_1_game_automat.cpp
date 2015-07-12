#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;
#define PICTURE_AMOUNT 3
#define SYMBOLS_IN_PICTURE 32
#define HEIGHT 3
#define WIDTH 3
#define SUCCESS 1
#define FAIL 0

void pause();
void sleep(int);
void wait_one_ms();
int enter(int&, int, int);

class Automat {
public:
	int defined_pictures;
	static char pictures[PICTURE_AMOUNT][SYMBOLS_IN_PICTURE];

	int rnd_of_three();
	void show_game_going();
	void show_result();
	void set_and_show_game_result();
};

void Automat::set_and_show_game_result() {

	system("cls");
		cout<<"\t\t\tThe one hand GANGSTER!!!\n\n";
	int res[PICTURE_AMOUNT];
	int curr_str = WIDTH;
	srand((unsigned int)time(NULL));
	for(int i = 0;i<PICTURE_AMOUNT;++i) {
		res[i] = rand()%PICTURE_AMOUNT;
	}
	for(int i = 0;i<HEIGHT;++i) {
		cout<<"\n\t\t\t  ";
		for(int j = 0;j<WIDTH;++j) {
			cout<<"  ";
			for(int k = curr_str-WIDTH;k<curr_str;++k) {
				cout<<pictures[res[j]][k];
			}
		}
		curr_str+=(WIDTH + 1);
	}
	cout<<"\n\n\t\t\t  Game is finished\n";
	int if_win = 1;
	for(int i = 0;i<PICTURE_AMOUNT - 1;++i) {
		if(res[i] != res[i+1])
			if_win = 0;
	}

	if(if_win)
		cout<<"\n\t\t\t!!!Congratualations!!!\n\t\t\t     \\-YOU WIN-/\n";
	else
		cout<<"\n\t\t   Oh, nooooooo!!! YOU loooooose!!!\n";
}

int Automat::rnd_of_three() {
	srand((unsigned int)time(NULL));
	return rand()%PICTURE_AMOUNT+1;
}

void Automat::show_game_going() {
	int load = 0;
	int delay;
	int amount_of_i;
	srand((unsigned int)time(NULL));
	delay = rand()%51 + 20;
	amount_of_i = rand()%11+8;
	for(int i = 0;i<100;++i){
		sleep(delay);
		system("cls");
		cout<<"\t\t\tThe one hand GANGSTER!!!\n\n";
		if(load == 0) {
		cout<<"\t\t\t\t---"<<"|"<<"   "<<"|"<<"   "<<endl;
		cout<<"\t\t\t\t   "<<"|"<<"---"<<"|"<<"   "<<endl;
		cout<<"\t\t\t\t   "<<"|"<<"   "<<"|"<<"---"<<endl;
		cout<<"\n\t\t\t\tGame is going\n";
		}
		if(load == 1) {
		cout<<"\t\t\t\t   "<<"|"<<"   "<<"|"<<"---"<<endl;
		cout<<"\t\t\t\t---"<<"|"<<"   "<<"|"<<"   "<<endl;
		cout<<"\t\t\t\t   "<<"|"<<"---"<<"|"<<"   "<<endl;
		cout<<"\n\t\t\t\tGame is going\n";
		}
		if(load == 2) {
		cout<<"\t\t\t\t   "<<"|"<<"---"<<"|"<<"   "<<endl;
		cout<<"\t\t\t\t   "<<"|"<<"   "<<"|"<<"---"<<endl;
		cout<<"\t\t\t\t---"<<"|"<<"   "<<"|"<<"   "<<endl;
		cout<<"\n\t\t\t\tGame is going\n";
		load = 0;
		continue;
		}
		++load;
	}
}

/*
---
| |
---

\ /
 |
/ \

\-/
|5|
/-\
*/

char Automat::pictures[PICTURE_AMOUNT][SYMBOLS_IN_PICTURE] = 
{//012\n456\n8910\0
{"---\n| |\n---"},
{"\\ /\n | \n/ \\"},
{"\\-/\n|5|\n/-\\"},
};

int main() {
	
	Automat test;
	int choice;
	cout<<"\t\t\tThe one hand GANGSTER!!!\n\n";
	cout<<"This a simple imitation of famous playing automat - One Hand Gangster\n";
	do {
		cout<<"Would you like to play?(1 - yes, 0 - no):";
	}while(enter(choice, 0, 1)!=SUCCESS);
	
	if(!choice){
		cout<<"\nThanke you for visiting our club, good bye.\n\n";
		return 0;
	}
	system("cls");
	for(;;) {
		test.show_game_going();
		test.set_and_show_game_result();
		do {
		cout<<"\n\nWould you like to play one more time?(1 - yes, 0 - no): ";
		}while(enter(choice, 0, 1)!=SUCCESS);
		if(!choice){
			cout<<"\nThanke you for visiting our club, good bye.\n\n";
			break;
		}

	}
	
	return 0;
}

void sleep(int time) {
	for(int i = 0; i<time; ++i)
		wait_one_ms();
}
void wait_one_ms() {
	for(int i = 0;i<1000; ++i)
		for(int i = 0;i<1000;++i);
}
void pause(){
	cout<<endl<<"Press any ley to continue. . .";
	_getch();
}

int enter(int &q, int down, int up) {
	if(cin.peek()<'0' || cin.peek()>'9') {
		while(cin.get()!='\n');
		cout<<endl<<"!!!Incorrect input!!!"<<endl;
		return FAIL;
	}

	cin>>q;
	if(q<down || q>up) {
		while(cin.get()!='\n');
		cout<<endl<<"!!!Incorrect input!!!"<<endl;
		return FAIL;
	}
	if(cin.get()!='\n') {
		while(cin.get()!='\n');
		cout<<endl<<"!!!Incorrect input!!!"<<endl;
		return FAIL;
	}
	return SUCCESS;
}