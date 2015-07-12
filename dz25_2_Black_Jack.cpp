#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;
#define SIX_DECKS 52 //Deck for black jack is 52 cards
#define SUCCESS 1
#define FAIL 0
#define START  1
#define PLAYERS_AMOUNT  2
#define CHANGE_NAMES 3
#define EXIT 4
#define TAKE 0
#define NO_TAKE 1

class Player;

class Counter_Incr_Read{
private:
	int val;
	int max_val;
public:
	Counter_Incr_Read();
	Counter_Incr_Read(int);
	Counter_Incr_Read(int, int);
	int operator++();
	int operator++(int k);
	operator int();
};

Counter_Incr_Read::Counter_Incr_Read() {
	val = 0;
	max_val = 100;
}

Counter_Incr_Read::Counter_Incr_Read(int max_val) {
	val = 0;
	this->max_val = max_val;
}

Counter_Incr_Read::Counter_Incr_Read(int val, int max_val) {
	this->val = val;
	this->max_val = max_val;
}

int Counter_Incr_Read::operator++() {
	++val;
	if(val == max_val) {
		val = 0;
	}
	return val;
}

int Counter_Incr_Read::operator++(int k) {
	int temp = val;
	++val;
	if(val == max_val) {
		val = 0;
	}
	return temp;
}

Counter_Incr_Read::operator int() {
	return val;
}

void print_start_menu(int);
int dialog_start_menu();
void change_players_amount(int&);
void change_names(char[6][32], int);
void init_pre_game_loop_elements(int&, Player*&,char[6][32]);
int pre_game_interact(int);
void game_loop(int, Player*&);
void print_results();
int enter(int&, int, int);
void take_y_n_dialog();
void show_inform_active_player(int, int, Player*);
void give_first_two_cards(int, Player*, Player);
void finish_game(int, Player*);


class Player {
private:
	int cards;
	int* hand;
	int cards_in_deck;
	static int deck[SIX_DECKS];
public:
	char* name;
	int summ;
	int condition; //if player stoppped or still taking cards
	Player();
	void print_deck() {
		int two = 0;
		for(int i = 0;i<SIX_DECKS;++i) {
			cout<<deck[i]<<" ";
			if(deck[i] == 2)
				++two;
		}
		cout<<endl<<two;	
	}
	static void init_deck();
	void init_player();
	void take_card();
	void show_hand();
	void show_mask_hand();
	int take_card_dialog();
	void set_name(char* str);
	friend void game_loop(int, Player*&);
	friend void finish_game(int, Player*);
};

Player::Player() {
	hand = nullptr;
	cards = 0;
	condition = 0;
	cards = 0;
	summ = 0;
	cards_in_deck = SIX_DECKS;
}

int Player::deck[SIX_DECKS]; 

void Player::init_deck() {
	//fill cards from 2 to 9, 24 cards
	int curr_card = 2;
	int i;
	for(i = 0;i<SIX_DECKS;++i) {
		deck[i] = curr_card;
		if(curr_card == 10)
			break;
		if((i + 1) % 4 == 0) {
			++curr_card;
		}
		
	}
	for(;i<48;++i) {
		deck[i] = 10;
	}
	for(;i<52;++i) {
		deck[i] = 11;
	}
}

void Player::init_player() {
	hand = nullptr;
	cards = 0;
	condition = 0;
	cards = 0;
	summ = 0;
	cards_in_deck = SIX_DECKS;
}

void Player::show_hand() {
	cout<<name<<": ";
	for(int i = 0; i<cards; ++i) {
		cout<<hand[i]<<" ";
	}
	int t;
	if(hand[cards - 1] == 10 || hand[cards - 1] == 11) {
		t = 6;
	}
	else t = 7;
		for(int i = 0;i<t-cards;++i) {
		cout<<"\t";
	}
}

void Player::show_mask_hand() {
	cout<<name<<": ";
	for(int i = 0; i<cards; ++i) {
		cout<<"* ";
	}
	//cout<<"\t\t\t\t\t\t"; 6 -t
	for(int i = 0;i<8-cards;++i) {
		cout<<"\t";
	}
	if(condition == 0)
		cout<<"Playing . . .";
	else
		cout<<"Stopped . . .";
}

int Player::take_card_dialog() {
	int choice;
	do{
	cout<<endl<<"Would you like to take a card?(yes - 1/no - 0)"<<endl;
	}while(!enter(choice, 0, 1));
	if(choice) {
		take_card();
		return TAKE;
	}
	else {
		condition = 1;
		return NO_TAKE;
	}
}

void Player::take_card() {
	
	int rand_card, i;

	srand((unsigned int)time(NULL));
	rand_card = rand()%cards_in_deck;

	++cards;
	if(hand!=nullptr){
		int* temp = (int*)malloc(sizeof(int)*cards);
		for(i = 0;i<cards - 1;++i) {
			temp[i] = hand[i];
		}
		temp[i] = deck[rand_card];
		summ+=temp[i];
		free(hand);
		hand = temp;
	}
	else {
		hand = (int*)malloc(sizeof(int));
		hand[0] = deck[rand_card];
		summ+=hand[0];
	}
	cout<<endl<<"You have just taken: "<<hand[cards - 1]<<endl;
	for(int i = rand_card;i<cards_in_deck - 1;++i) {
		deck[i] = deck[i + 1];
	}
	--cards_in_deck;

}

void Player::set_name(char* str) {
	name = (char*)malloc(sizeof(char) * strlen(str) + 1);
	strcpy(name, str);
}

int main() {

	int players_amount = 2;
	Player* p;
	char names[6][32] = {
		"Player 1", "Player 2", "Player 3", "Player 4", "Player 5", "Player 6"
	};
	for(;;) {
		system("cls");
		print_start_menu(players_amount);
		switch(dialog_start_menu()) {
			case START:
				init_pre_game_loop_elements(players_amount, p, names);
				game_loop(players_amount, p);
				finish_game(players_amount, p);
				break;
			case PLAYERS_AMOUNT:
				change_players_amount(players_amount);
				break;
			case CHANGE_NAMES:
				change_names(names,players_amount);
				break;
			case EXIT:
				cout<<endl;
				return 0;
		}
	}
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

void print_start_menu(int players_amount) {
	cout<<"\t\t\\Black Jack/"<<endl<<"\t\t ----------"<<endl;
	cout<<"1.Start game"<<endl;
	cout<<"2.Change players amount(current is "<<players_amount<<")"<<endl;
	cout<<"3.Change players names"<<endl;
	cout<<"4.Exit"<<endl;
}

int dialog_start_menu() {
	int choice;
	
	do {
		cout<<endl<<"Select a point: ";
	}while(!enter(choice,1,4));
	switch(choice) {
	case START:
		return START;
	case PLAYERS_AMOUNT:
		return PLAYERS_AMOUNT;
	case CHANGE_NAMES:
		return CHANGE_NAMES;
	case EXIT:
		return EXIT;
	default:
		return EXIT;
	}
}

void init_pre_game_loop_elements(int& players_amount, Player*& p, char names[6][32]) {
	Player::init_deck();
	p = (Player*)malloc(sizeof(Player)*players_amount);
	for(int i = 0;i<players_amount;++i) {
		p[i].init_player();
		p[i].set_name(names[i]);
	}

}

int pre_game_interact(int players_amount) {
	cout<<"Diller: Hi, guys!!! Now there are "<<players_amount<<" players in game"<<endl;
	cout<<"Crowd: ooooooo";
	cout<<"Diller: We will play the Black Jack, I hope you know the rules, let's start"<<endl<<endl;
	system("pause");
	for(int i = 0; i<players_amount; ++i) {
		
	}
	return SUCCESS;
}

void show_inform_active_player(int active_player, int amount_player, Player* p) {
	cout<<"Player's "<<active_player + 1<<" turn"<<endl<<endl;
	p[active_player].show_hand();
	cout<<"\tThe summ is "<<p[active_player].summ;
	cout<<endl;
	for(int i = 0;i<amount_player;++i) {
		if(i == active_player)
			continue;
		p[i].show_mask_hand();
		cout<<endl;
	}
}

void give_first_two_cards(int players_amount, Player* p, Player diller) {
	diller.take_card();
	diller.take_card();
	for(int i = 0;i<players_amount; ++i) {
		p[i].take_card();
		p[i].take_card();
	}
}

void game_loop(int players_amount, Player*& p) {
	int cond_end = 0;
	Counter_Incr_Read curr_player(0,players_amount);
	Player diller;
	diller.init_player();
	give_first_two_cards(players_amount, p, diller);
	for(;;){
		system("cls");
		show_inform_active_player(curr_player, players_amount, p);
		if(!p[curr_player].condition)
			if(p[curr_player].take_card_dialog() == NO_TAKE)
				++cond_end;
		if(p[curr_player].summ > 21) {
			for(int i = 0;i<p[curr_player].cards;++i) {
				if(p[curr_player].hand[i] == 11) {
					p[curr_player].hand[i] = 10;
					p[curr_player].summ -= 10;
				}
			}
			if(p[curr_player].summ > 21)
			{
				cout<<endl<<"Diller: Oh, no! You have too many points. You can't take cards any more."<<endl<<endl;
				p[curr_player].condition = 1;
				++cond_end;
			}
		}
		if(p[curr_player].summ == 21) {
			cout<<endl<<"Diller: Woooh!!! You have the best combination. Now you should wait for others."<<endl<<endl;
			p[curr_player].condition = 1;
			++cond_end;
		}
		system("pause");
		if(cond_end == players_amount)
			return;		
		++curr_player;
	}
}

void change_players_amount(int& players_amount) {
	do{
		cout<<endl<<"Enter the new amount(from 2 to 6): ";
	}while(!enter(players_amount, 2, 6));
}

void finish_game(int players_amount, Player* p) {
	int max = 0;
	system("cls");
	cout<<"Results of the match"<<endl<<endl;
	for(int i = 0;i<players_amount;++i) {
		if(max<p[i].summ && p[i].summ<=21) {
			max = p[i].summ;
		}
	}

	for(int i = 0;i<players_amount;++i) {
		cout<<p[i].name<<": "<<p[i].summ<<" points";
		cout<<"\tThe hand: ";
		for(int j = 0;j<p[i].cards;++j) {
			cout<<p[i].hand[j]<<" ";
		}
		if(max == p[i].summ) {
			cout<<"  !!!Winner!!!";
		}
		cout<<endl;
	}

	if(!max) {
		cout<<"\nDiller: we have one winner - friendship :)\n";
	}

	cout<<endl<<"Diller: thank you for game, always welcome."<<endl<<endl;
	system("pause");
}

void change_names(char names[6][32], int players_amount) {
	for(;;) {
		system("cls");
		for(int i = 0;i<players_amount;++i) {
			cout<<"Player "<<i + 1<<": "<<names[i]<<endl;
		}

		int choice;
		do{
		cout<<endl<<"Choose the player to change his name(enter "<<players_amount+1<<" for exit): ";
		}while(enter(choice,1,players_amount + 1)!=SUCCESS);

		if(choice == players_amount + 1) {
			return;
		}
		else {
			do{
			cout<<endl<<"Enter new name: ";
			cin.getline(names[choice - 1],32);
			cout<<endl;
			}while(names[choice - 1][0] == '\n');
		}
	}
}