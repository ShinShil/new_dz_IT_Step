#include <iostream>
using namespace std;

class Time {
private:
	int sec;
	int hour;
	int min;

	Time* t;
public:
	Time();
	Time(int, int, int);
	Time(const Time&);
	~Time();

	Time& operator=(const Time&);
	Time operator+(const Time&);
	Time operator-(const Time&);
	int operator>(const Time&);
	int operator>=(const Time&);
	int operator<(const Time&);
	int operator<=(const Time&);
	int operator==(const Time&);
	int operator!=(const Time&);
	friend istream& operator>>(istream&, Time&);
	friend ostream& operator<<(ostream&, const Time&);
	void convert();
};

Time::Time() {
	min = 0;
	sec = 0;
	hour = 0;
	t = nullptr;
}

Time::Time(int u_hour, int u_min, int u_sec) {
	t = (Time*)malloc(sizeof(Time));
	min = u_min;
	sec = u_sec;
	hour = u_hour;
}

Time::Time(const Time& old) {
	t = (Time*)malloc(sizeof(Time));
	min = old.min;
	sec = old.sec;
	hour = old.hour;
}

Time::~Time() {
	free(t);
}

Time& Time::operator=(const Time& old) {
	
	if(this == &old) {
		return *this;
	}

	if(old.t != nullptr) {
		t = (Time*)malloc(sizeof(Time));
	}
	else {
		t = nullptr;
	}
	min = old.min;
	sec = old.sec;
	hour = old.hour;

	return *this;
}

Time Time::operator+(const Time& second_obj) {
	int m = 0, h = 0, s = 0;

	s += sec + second_obj.sec;
	if(s>=60) {
		++m;
		s-=60;
	}

	m += min + second_obj.min;
	if(min>=60) {
		++h;
		m -= 60;
	}

	h += hour + second_obj.hour;
	if(h>=24) {
		h -= 24;
	}

	Time res(h,m,s);
	
	return res;
}

void Time::convert() {
	if(hour>=12) {
		hour -= 12;
	}
}

istream& operator>>(istream& is, Time& u_time) {
	cout<<"Enter seconds: ";
	cin>>u_time.sec;
	cout<<"Enter minutes: ";
	cin>>u_time.min;
	cout<<"Enter hours: ";
	cin>>u_time.hour;
	return is;
}

ostream& operator<<(ostream& os,const Time& u_time) {
	//u_time.hour/10?cout<<"0";
	if(!(u_time.hour/10)) {
		cout<<"0";
	}
	cout<<u_time.hour<<":";
	if(!(u_time.min/10)) {
		cout<<"0";
	}
	cout<<u_time.min<<":";
	if(!(u_time.sec/10)) {
		cout<<"0";
	}
	cout<<u_time.sec;
	return os;
}

int Time::operator>(const Time& second_obj){
	if(hour>second_obj.hour)
		return 1;
	else if(min>second_obj.min && hour==second_obj.hour)
			return 1;
		else if(sec>second_obj.sec && min==second_obj.min && hour == second_obj.hour)
				return 1;
	return 0;
}

int Time::operator<(const Time& second_obj){
	if(hour<second_obj.hour)
		return 1;
	else if(min<second_obj.min && hour==second_obj.hour)
			return 1;
		else if(sec<second_obj.sec && min==second_obj.min && hour == second_obj.hour)
				return 1;
	return 0;
}

int Time::operator>=(const Time& second_obj){
	if(hour>=second_obj.hour)
		return 1;
	else if(min>=second_obj.min && hour==second_obj.hour)
			return 1;
		else if(sec>=second_obj.sec && min==second_obj.min && hour == second_obj.hour)
				return 1;
	return 0;
}

int Time::operator<=(const Time& second_obj){
	printf("\n\n%d && %d\n\n", min<=second_obj.min, hour == second_obj.hour);
	if(hour<=second_obj.hour)
		return 1;
	else if(hour==second_obj.hour && min<=second_obj.min)
			return 1;
		else if(sec<=second_obj.sec && min==second_obj.min && hour == second_obj.hour)
				return 1;
	return 0;
}

int Time::operator==(const Time& second_obj){
	if(hour==second_obj.hour && min == second_obj.min && sec == second_obj.sec)
		return 1;
	else
		return 0;
}

int Time::operator!=(const Time& second_obj){
	if(hour!=second_obj.hour || min != second_obj.min || sec != second_obj.sec)
		return 1;
	else
		return 0;
}

Time Time::operator-(const Time& second_obj) {
	//01.00.05 12.12.12 5-12 = 65 - 12 = 53
	int h = hour, s = 0, m = min;

	if(sec<second_obj.sec) {
		sec+=60;
		--m;
	}
	s = sec - second_obj.sec;

	if(m == -1) {
		m = 59;
	}
	if(m < second_obj.min) {
		m+=60;
		--h;
	}
	m -= second_obj.min;

	if(h == -1) {
		h = 23;
	}
	if(h < second_obj.hour) {
		h+=24;
	}
	h-=second_obj.hour;

	Time res(h,m,s);

	return res;

}

int main() {
	Time t(10, 15, 15);
	Time n(12, 15, 15);
	Time q;

	cout<<"t = "<<t<<endl<<"n = "<<n<<endl;
	cout<<"q = t + n = "<< t + n<<endl<<endl<<endl;

	q = t+n;
	cout<<t<<"| "<<q<<"| "<<q<<endl;
	cout<<"    +   |"<<"    -    |"<<"    -    "<<endl;
	cout<<n<<"| "<<t<<"| "<<n<<endl;
	cout<<"--------|"<<"---------|"<<"---------"<<endl;
	cout<<q<<"| "<<q-t<<"| "<<q-n<<endl;
	


	n.convert();
	cout<<endl<<endl<<"Convert n from AM(13 to 01, 14 to 02 and etc.): "<<n<<endl;

	Time e;
	cout<<endl<<endl<<"Set new time"<<endl;
	cin>>e;
	cout<<"You set: "<<e<<endl<<endl;
	
	int comp;
	cout<<"Compare your time("<<e<<") with n("<<n<<")"<<endl;
	comp = e>n;
	cout<<"> : "<<comp<<endl;
	comp = e>=n;
	cout<<">=: "<<comp<<endl;
	comp = e<n;
	cout<<"< : "<<comp<<endl;
	comp = e<=n;
	cout<<"<=: "<<comp<<endl;
	comp = e==n;
	cout<<"==: "<<comp<<endl;
	comp = e!=n;
	cout<<"!=: "<<comp<<endl;

	cout<<endl;
}