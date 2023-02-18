#include<iostream>
using namespace std;

class Time {
public:
	Time() {}
	Time(int tim) {
		while (tim < 0) { tim += 86400; }
		tim %= 86400;
		this->sec = tim;
	}
	Time(Time& tim) {
		this->sec = tim.sec;
	}
	Time(string tim) {
		this->sec = forstr(tim);
	}
	Time(const char* tim) {
		this->sec = forchar(tim);
	}
	static void time_sorted(int& h, int& m, int& s) {
		s += (h * 3600) + (m * 60);
		s %= 86400;
		h = s / 3600;
		s -= h * 3600;
		m = s / 60;
		s -= m * 60;
	}
	int seconds() { return this->sec; }
	int second() {
		int h = 0, m = 0, s = this->sec;
		time_sort(h, m, s);
		return s;
	}
	int minute() {
		int h = 0, m = 0, s = this->sec;
		time_sort(h, m, s);
		return m;
	}
	int hour() {
		int h = 0, m = 0, s = this->sec;
		time_sort(h, m, s);
		return h;
	}
	//==
	bool operator==(string tim) {
		return this->sec == forstr(tim);
	}
	bool operator==(char* tim) {
		return this->sec == forchar(tim);
	}
	bool operator==(int tim) {
		return this->sec == tim;
	}
	bool operator==(Time& tim) {
		return this->sec == tim.sec;
	}
	//<=
	bool operator<=(string tim) {
		return this->sec <= forstr(tim);
	}
	bool operator<=(char* tim) {
		return this->sec <= forchar(tim);
	}
	bool operator<=(int tim) {
		return this->sec <= tim;
	}
	bool operator<=(Time& tim) {
		return this->sec <= tim.sec;
	}
	//<
	bool operator<(string tim) {
		return this->sec < forstr(tim);
	}
	bool operator<(char* tim) {
		return this->sec < forchar(tim);
	}
	bool operator<(int tim) {
		return this->sec < tim;
	}
	bool operator<(Time& tim) {
		return this->sec < tim.sec;
	}
	//>=
	bool operator>=(string tim) {
		return this->sec >= forstr(tim);
	}
	bool operator>=(char* tim) {
		return this->sec >= forchar(tim);
	}
	bool operator>=(int tim) {
		return this->sec >= tim;
	}
	bool operator>=(Time& tim) {
		return this->sec >= tim.sec;
	}
	//>
	bool operator>(string tim) {
		return this->sec > forstr(tim);
	}
	bool operator>(char* tim) {
		return this->sec > forchar(tim);
	}
	bool operator>(int tim) {
		return this->sec > tim;
	}
	bool operator>(Time& tim) {
		return this->sec > tim.sec;
	}
	//-=
	void operator-=(string tim) {
		this->sec -= forstr(tim);
		this->sec %= 86400;
	}
	void operator-=(char* tim) {
		this->sec -= forchar(tim);
		this->sec %= 86400;
	}
	void operator-=(int tim) {
		this->sec -= tim;
		while (this->sec < 0) { this->sec += 86400; }
		this->sec %= 86400;
	}
	void operator-=(Time& tim) {
		this->sec -= tim.sec;
		this->sec %= 86400;
	}
	//-
	Time& operator-(string tim) {
		Time otv;
		otv = (this->sec - forstr(tim)) % 86400;
		return otv;
	}
	Time& operator-(char* tim) {
		Time otv;
		otv = (this->sec - forchar(tim)) % 86400;
		return otv;
	}
	Time& operator-(int tim) {
		Time otv;
		int pr = this->sec - tim;
		while (pr < 0) { pr += 86400; }
		pr %= 86400;
		otv = pr;
		return otv;
	}
	Time& operator-(Time& tim) {
		Time otv;
		int pr = this->sec - tim.sec;
		pr %= 86400;
		otv = pr;
		return otv;
	}
	//+=
	void operator+=(string tim) {
		this->sec += forstr(tim);
		this->sec %= 86400;
	}
	void operator+=(char* tim) {
		this->sec += forchar(tim);
		this->sec %= 86400;
	}
	void operator+=(int tim) {
		this->sec += tim;
		while (this->sec < 0) { this->sec += 86400; }
		this->sec %= 86400;
	}
	void operator+=(Time& tim) {
		this->sec += tim.sec;
		this->sec %= 86400;
	}
	//+
	Time& operator+(string tim) {
		Time otv;
		otv = (this->sec + forstr(tim)) % 86400;
		return otv;
	}
	Time& operator+(char* tim) {
		Time otv;
		otv = (this->sec + forchar(tim)) % 86400;
		return otv;
	}
	Time& operator+(int tim) {
		Time otv;
		int pr = this->sec + tim;
		while (pr < 0) { pr += 86400; }
		pr %= 86400;
		otv = pr;
		return otv;
	}
	Time& operator+(Time& tim) {
		Time otv;
		int pr = this->sec + tim.sec;
		pr %= 86400;
		otv = pr;
		return otv;
	}
	//++/--
	void operator++() {
		this->sec++;
		this->sec %= 86400;
	}
	void operator--() {
		this->sec--;
		while (this->sec < 0) { this->sec += 86400; }
		this->sec %= 86400;
	}
	//=
	Time& operator=(string tim) {
		this->sec = forstr(tim);
		return *this;
	}
	Time& operator=(char* tim) {
		this->sec = forchar(tim);
		return *this;
	}
	Time& operator=(int tim) {
		this->sec = tim;
		this->sec %= 86400;
		while (this->sec < 0) { this->sec += 86400; }
		return *this;
	}
	Time& operator=(Time& tim) {
		this->sec = tim.sec;
		this->sec %= 86400;
		return *this;
	}
	//out/in
	friend ostream& operator<<(ostream& out, Time tim) {
		int h = 0, m = 0, s = tim.seconds();
		tim.time_sort(h, m, s);
		out << tim.to_mas(h, m, s);
		return out;
	}
	friend istream& operator>>(istream& in, Time& tim) {
		char mas[9] = {};
		in >> mas;
		int h = 0, m = 0, s = 0;
		tim.in_mas(mas, h, m, s);
		tim.sec = tim.to_sec(h, m, s);
		return in;
	}
private:
	long long int sec = 0;
	void time_sort(int& h, int& m, int& s) {
		s += (h * 3600) + (m * 60);
		s %= 86400;
		h = s / 3600;
		s -= h * 3600;
		m = s / 60;
		s -= m * 60;
	}
	void to_time(int& h, int& m, int& s) {
		h = s / 3600;
		s -= h * 3600;
		m = s / 60;
		s -= m * 60;
	}
	int to_sec(int& h, int& m, int& s) {
		return s + (h * 3600) + (m * 60);
	}
	string to_mas(int& h, int& m, int& s) {
		string otv = "";
		otv += int(h / 10) + 48;
		otv += int(h % 10) + 48;
		otv += ":";
		otv += int(m / 10) + 48;
		otv += int(m % 10) + 48;
		otv += ":";
		otv += int(s / 10) + 48;
		otv += int(s % 10) + 48;
		return otv;
		}
	void in_mas(const char* mas, int& h, int& m, int& s) {
		h = ((int(mas[0]) - 48) * 10) + (int(mas[1]) - 48);
		m = ((int(mas[3]) - 48) * 10) + (int(mas[4]) - 48);
		s = ((int(mas[6]) - 48) * 10) + (int(mas[7]) - 48);
	}
	void in_mas(string mas, int& h, int& m, int& s) {
		h = ((int(mas[0]) - 48) * 10) + (int(mas[1]) - 48);
		m = ((int(mas[3]) - 48) * 10) + (int(mas[4]) - 48);
		s = ((int(mas[6]) - 48) * 10) + (int(mas[7]) - 48);
	}
	int forstr(string tim) {
		int h = 0, m = 0, s = 0;
		in_mas(tim, h, m, s);
		return to_sec(h, m, s);
	}
	int forchar(const char* tim) {
		int h = 0, m = 0, s = 0;
		in_mas(tim, h, m, s);
		return to_sec(h, m, s);
	}
};