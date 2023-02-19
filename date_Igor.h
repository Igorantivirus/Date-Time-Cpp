#include<iostream>
using namespace std;

class Date {
public:
	Date(){}
	Date(int dat) {
		this->den = dat;
	}
	Date(Date& dat) {
		this->den = dat.den;
	}
	Date(string dat) {
		this->den = for_str(dat);
	}
	Date(const char* dat) {
		this->den = for_char(dat);
	}
	//Статик функции:
	static void date_sort(int& d, int& m, int& g) {//Если день заведомо отрицательный, нужно сохранить отрицательный знак, кол-во дней сделать положительным, а к числу дней прибавить 1. В таком случае отрицательная дата создастся правильно
		const int sum_mes[14] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
		const int sum_mes_v[14] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
		while (m > 12) { m -= 12; g++; }
		d += ((g % 4 == 0) ? (sum_mes_v[m]) : (sum_mes[m])) + (g * 365.25);
		m = g = 0;
		d += 366;
		g = d / 365;
		d -= ((g * 365) + ((g + 3) / 4));
		while (d <= 0) {
			d += ((g - 1) % 4 == 0) ? (366) : (365);
			g--;
		}
		if (g % 4 == 0) {
			for (int i = 1; i < 14; i++) {
				if (sum_mes_v[i] >= d) {
					d -= sum_mes_v[i - 1];
					m += i - 1;
					break;
				}
			}
		}
		else {
			for (int i = 1; i < 14; i++) {
				if (sum_mes[i] >= d) {
					d -= sum_mes[i - 1];
					m += i - 1;
					break;
				}
			}
		}
	}
	//общедоступные методы:
	void date_count(int& d, int& m, int& g) {
		d = this->den, m = 0, g = 0;
		int zn = 1;
		if (d <= 0) { zn = -1; d = (d * -1) + 1; }
		to_date(d, m, g);
		if (g % 4 == 0) {
			if (d == sp_mes_v[m]) { d = 1; m++; }
		}
		else {
			if (d == sp_mes[m]) { d = 1; m++; }
		}
		d--;
		m--;
		if (m >= 12) { m -= 12; g++; }
		g--;
		g *= zn;
		m *= zn;
		d *= zn;
	}
	//void date_count(int& d, int& m, int& g) {
	//	//const int sp_mes[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//	d = this->den, m = 0, g = 0;
	//	int zn = 1;
	//	if (d <= 0) { zn = -1; d = (d * -1) + 1; }
	//	to_date(d, m, g);
	//	d += ((g % 4 == 0) ? (sum_mes_v[m]) : (sum_mes[m]));
	//	m = 0;
	//	int j = 1;
	//	if (g % 4 == 0) {
	//		if (d == 366) { d = 0; g++; }
	//		while (d >= sp_mes_v[j]) {
	//			d -= sp_mes_v[j];
	//			j++;
	//			m++;
	//		}
	//	}
	//	else {
	//		if (d == 365) { d = 0; g++; }
	//		while (d >= sp_mes[j]) {
	//			d -= sp_mes[j];
	//			j++;
	//			m++;
	//		}
	//	}
	//	if (m == 12) { m -= 12; g++; }
	//	g--;
	//	d--;
	//	g *= zn;
	//	m *= zn;
	//	d *= zn;
	//}
	int days() {
		return this->den;
	}
	int day() {
		int d = this->den, m = 0, g = 0, zn = 1;
		if (d <= 0) { zn = -1; d = (d * -1) + 1; }
		to_date(d, m, g);
		return d * zn;
	}
	int month() {
		int d = this->den, m = 0, g = 0, zn = 1;
		if (d <= 0) { zn = -1; d = (d * -1) + 1; }
		to_date(d, m, g);
		return m * zn;
	}
	int year() {
		int d = this->den, m = 0, g = 0, zn = 1;
		if (d <= 0) { zn = -1; d = (d * -1) + 1; }
		to_date(d, m, g);
		return g * zn;
	}
	//==
	bool operator==(char* dat) {
		return this->den == for_char(dat);
	}
	bool operator==(string dat) {
		return this->den == for_str(dat);
	}
	bool operator==(int dat) {
		return this->den == dat;
	}
	bool operator==(Date& dat) {
		return this->den == dat.den;
	}
	//<=
	bool operator<=(char* dat) {
		return this->den <= for_char(dat);
	}
	bool operator<=(string dat) {
		return this->den <= for_str(dat);
	}
	bool operator<=(int dat) {
		return this->den <= dat;
	}
	bool operator<=(Date& dat) {
		return this->den <= dat.den;
	}
	//<
	bool operator<(char* dat) {
		return this->den < for_char(dat);
	}
	bool operator<(string dat) {
		return this->den < for_str(dat);
	}
	bool operator<(int dat) {
		return this->den < dat;
	}
	bool operator<(Date& dat) {
		return this->den < dat.den;
	}
	//>=
	bool operator>=(char* dat) {
		return this->den >= for_char(dat);
	}
	bool operator>=(string dat) {
		return this->den >= for_str(dat);
	}
	bool operator>=(int dat) {
		return this->den >= dat;
	}
	bool operator>=(Date& dat) {
		return this->den >= dat.den;
	}
	//>
	bool operator>(char* dat) {
		return this->den > for_char(dat);
	}
	bool operator>(string dat) {
		return this->den > for_str(dat);
	}
	bool operator>(int dat) {
		return this->den > dat;
	}
	bool operator>(Date& dat) {
		return this->den > dat.den;
	}
	//-=
	void operator-=(char* dat) {
		this->den -= for_char(dat);
	}
	void operator-=(string dat) {
		this->den -= for_str(dat);
	}
	void operator-=(int dat) {
		this->den -= dat;
	}
	void operator-=(Date& dat) {
		this->den -= dat.den;
	}
	//-
	Date& operator-(char* dat) {
		Date otv;
		otv = this->den - for_char(dat);
		return otv;
	}
	Date& operator-(string dat) {
		Date otv;
		otv = this->den - for_str(dat);
		return otv;
	}
	Date& operator-(int dat) {
		Date otv;
		otv = this->den - dat;
		return otv;
	}
	Date& operator-(Date& dat) {
		Date otv;
		otv = this->den - dat.den;
		return otv;
	}
	//+=
	void operator+=(char* dat) {
		this->den += for_char(dat);
	}
	void operator+=(string dat) {
		this->den += for_str(dat);
	}
	void operator+=(int dat) {
		this->den += dat;
	}
	void operator+=(Date& dat) {
		this->den += dat.den;
	}
	//+
	Date& operator+(char* dat) {
		Date otv;
		otv = this->den + for_char(dat);
		return otv;
	}
	Date& operator+(string dat) {
		Date otv;
		otv = this->den + for_str(dat);
		return otv;
	}
	Date& operator+(int dat) {
		Date otv;
		otv = this->den + dat;
		return otv;
	}
	Date& operator+(Date& dat) {
		Date otv;
		otv = this->den + dat.den;
		return otv;
	}
	//--++
	void operator++() {
		this->den+=1;
	}
	void operator--() {
		this->den-=1;
	}
	//=
	Date& operator=(char* dat) {
		this->den = for_char(dat);
		return *this;
	}
	Date& operator=(string dat) {
		this->den = for_str(dat);
		return *this;
	}
	Date& operator=(int dat) {
		this->den = dat;
		return *this;
	}
	Date& operator=(Date& dat) {
		this->den = dat.den;
		return *this;
	}
	//out/in
	friend ostream& operator<<(ostream& out, Date& dat) {
		int d = dat.den, m = 0, g = 0, zn = 1;
		if (d <= 0) { out << '-'; d = (d * -1) + 1; }
		dat.to_date(d, m, g);
		out << dat.to_mas(d, m, g);
		return out;
	}
	friend istream& operator>>(istream& in, Date& dat) {
		char mas[12] = {};
		int d = 0, m = 0, g = 0, zn = 1;
		in >> mas;
		if (mas[0] == '-') { zn = -1; dat.to_chis(mas, d, m, g, 1); }
		else { dat.to_chis(mas, d, m, g); }
		dat.to_den(d, m, g);
		dat.den = (d * zn);
		return in;
	}
private:
	long long int den = 0;
	const int sp_mes[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	const int sp_mes_v[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	const int sum_mes[14] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	const int sum_mes_v[14] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
	void to_date(int& d, int& m, int& g) {//Если день заведомо отрицательный, нужно сохранить отрицательный знак, кол-во дней сделать положительным, а к числу дней прибавить 1. В таком случае отрицательная дата создастся правильно
		d += ((g % 4 == 0) ? (sum_mes_v[m]) : (sum_mes[m])) + (g * 365.25);
		m = g = 0;
		d += 366;
		g = d / 365;
		d -= ((g * 365) + ((g + 3) / 4));
		while (d <= 0) {
			d += ((g - 1) % 4 == 0) ? (366) : (365);
			g--;
		}
		if (g % 4 == 0) {
			for (int i = 1; i < 14; i++) {
				if (sum_mes_v[i] >= d) {
					d -= sum_mes_v[i - 1];
					m += i - 1;
					break;
				}
			}
		}
		else {
			for (int i = 1; i < 14; i++) {
				if (sum_mes[i] >= d) {
					d -= sum_mes[i - 1];
					m += i - 1;
					break;
				}
			}
		}
	}
	void to_den(int& d, int& m, int& g) {//Если дата заведомо отрицательная, то следует сохранить знак, сделать дату положительной, а к ответу в днях прибавить 1. В таком случает день из даты будет обработан правильно
		d = d + 1 + ((g % 4 == 0) ? (sum_mes_v[m]) : (sum_mes[m])) + (int(g * 365.25) - 366);
		m = g = 0;
	}
	string to_mas(int& d, int& m, int& g) {
		string dat = "";
		dat += char(int(d / 10) + 48);
		dat += char(int(d % 10) + 48);
		dat += ':';
		dat += char(int(m / 10) + 48);
		dat += char(int(m % 10) + 48);
		dat += ':';
		dat += char(int(g / 1000) + 48);
		dat += char(int(int(g / 100) % 10) + 48);
		dat += char(int(int(g / 10) % 10) + 48);
		dat += char(int(g % 10) + 48);
		return dat;
	};
	void to_chis(const char* dat, int& d, int& m, int& g, int i = 0) {
		d = ((dat[i] - 48) * 10) + (dat[i + 1] - 48);
		m = ((dat[i + 3] - 48) * 10) + (dat[i + 4] - 48);
		g = ((dat[i + 6] - 48) * 1000) + ((dat[i + 7] - 48) * 100) + ((dat[i + 8] - 48) * 10) + (dat[i + 9] - 48);
	}
	void to_chis(string dat, int& d, int& m, int& g, int i = 0) {
		d = ((dat[i] - 48) * 10) + (dat[i + 1] - 48);
		m = ((dat[i + 3] - 48) * 10) + (dat[i + 4] - 48);
		g = ((dat[i + 6] - 48) * 1000) + ((dat[i + 7] - 48) * 100) + ((dat[i + 8] - 48) * 10) + (dat[i + 9] - 48);
	}
	int for_str(string dat) {
		int d = 0, m = 0, g = 0, zn = 1;
		if (dat[0] == '-') { zn = -1; to_chis(dat, d, m, g, 1); }
		else { to_chis(dat, d, m, g); }
		to_den(d, m, g);
		if (zn == -1) { d--; }
		return (d * zn);
	}
	int for_char(const char* dat) {
		int d = 0, m = 0, g = 0, zn = 1;
		if (dat[0] == '-') { zn = -1; to_chis(dat, d, m, g, 1); }
		else { to_chis(dat, d, m, g); }
		to_den(d, m, g);
		if (zn == -1) { d--; }
		return (d * zn);
	}
};