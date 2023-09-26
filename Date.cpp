#include "Date.hpp"

namespace dt
{


bool Leap(int year)
{
	return (!(year % 4) && (year % 100) || !(year % 400));
}

#pragma region class Date

Date::Date() : _days(0) {}
Date::Date(const char* date) {
	Assign(date);
}
Date::Date(const std::string& date) {
	Assign(date);
}
Date::Date(int days) {
	Assign(days);
}
Date::Date(int day, int month, int year) {
	Assign(day, month, year);
}
Date::Date(const Date& date) {
	Assign(date);
}

Date& Date::Assign(int day, int month, int year) {
	if (!IsDatable(abs(day), abs(month), abs(year))) {
		return *this;
	}
	_days = ToDay(day, month, year);
	if (year > 1) {
		_days++;
	}
	return *this;
}
Date& Date::Assign(const char* date) {
	if (date == nullptr) {
		return *this;
	}
	int arr[3] = {};
	for (int DateCount = 0; DateCount < 3; DateCount++) {
		if (date[0] == '\0') {
			break;
		}
		arr[DateCount] = atoi(date);
		if (date[0] == '-') {
			date++;
		}
		for (; (date[0] >= '0' && date[0] <= '9'); date++) {}
		date++;
	}
	return Assign(arr[0], arr[1], arr[2]);
}
Date& Date::Assign(const std::string& date) {
	return Assign(date.c_str());
}
Date& Date::Assign(int days) {
	_days = days;
	return *this;
}
Date& Date::Assign(const Date& date) {
	_days = date._days;
	return *this;
}

bool Date::IsLeap() const {
	int d, m, g;
	ToDate(d, m, g);
	return (!(g % 4) && (g % 100) || !(g % 400));
}
int Date::AllDays() const {
	return _days;
}
int Date::Days() const {
	int d = _days, m = 0, g = 0;
	ToDate(d, m, g);
	return d;
}
int Date::Months() const {
	int d = _days, m = 0, g = 0;
	ToDate(d, m, g);
	return m;
}
int Date::Years() const {
	int d = _days, m = 0, g = 0;
	ToDate(d, m, g);
	return g;
}
int Date::Weeks() const {
	return _days / 7;
}
int Date::DayWeek() const {
	return (_days % 7) + 1;
}

void Date::SetAllDays(int days) {
	_days = days;
}
void Date::SetDay(int day) {
	int d = _days, m, g;
	ToDate(d, m, g);
	Assign(day, m, g);
}
void Date::SetMonth(int month) {
	int d = _days, m, g;
	ToDate(d, m, g);
	Assign(d, month, g);
}
void Date::SetYear(int year) {
	int d = _days, m, g;
	ToDate(d, m, g);
	Assign(d, m, year);
}
void Date::SetWeeks(int weeks) {
	_days = weeks * 7 - 1;
}

void Date::MakeOpposite() {
	_days = (_days + 1) * -1;
}

Date& Date::operator=(const Date& date) {
	_days = date._days;
	return *this;
}

Date::operator std::string() {
	std::string result = "";
	int d = _days, m, g;
	if (d < 0) {
		result = '-';
	}
	ToDate(d, m, g);
	d = abs(d);
	m = abs(m);
	g = abs(g);
	char pr[7] = { char(d / 10 + '0'), char(d % 10 + '0'), ':',char(m / 10 + '0'), char(m % 10 + '0'), ':', '\0' };
	result += pr;
	return result + std::to_string(g);

}

bool Date::operator<(const Date& date) const {
	return _days < date._days;
}
bool Date::operator>(const Date& date) const {
	return _days > date._days;
}
bool Date::operator<=(const Date& date) const {
	return _days <= date._days;
}
bool Date::operator>=(const Date& date) const {
	return _days >= date._days;
}
bool Date::operator==(const Date& date) const {
	return _days == date._days;
}
bool Date::operator!=(const Date& date) const {
	return _days != date._days;
}

Date Date::operator+(const Date& date) const {
	return Date(_days + date._days);
}
Date Date::operator-(const Date& date) const {
	return Date(_days - date._days);
}
Date Date::operator*(int value) const {
	return Date(_days * value);
}
Date Date::operator/(int value) const {
	return Date(_days / value);
}
Date Date::operator%(int value) const {
	return Date(_days % value);
}

Date& Date::operator+=(const Date& date) {
	_days += date._days;
	return *this;
}
Date& Date::operator-=(const Date& date) {
	_days -= date._days;
	return *this;
}
Date& Date::operator*=(int value) {
	_days *= value;
	return *this;
}
Date& Date::operator/=(int value) {
	_days /= value;
	return *this;
}
Date& Date::operator%=(int value) {
	_days %= value;
	return *this;
}

Date Date::operator++() {
	_days++;
	return *this;
}
Date Date::operator--() {
	_days--;
	return *this;
}
Date Date::operator++(int) {
	Date pr = *this;
	++(*this);
	return pr;
}
Date Date::operator--(int) {
	Date pr = *this;
	--(*this);
	return pr;
}

Date Date::Now(float TimeZone) {
	return Date(static_cast<int>((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + static_cast<long long>(TimeZone * 3600000)) / 86400000) + 719162);
}
Date Date::MaxDate() {
	return Date(2147483646);
}
Date Date::MinDate() {
	return Date(-2147483647);
}

void Date::ToDate(int& d, int& m, int& g) {//переводит день d в дату d:m:g
	bool lowerZero = false;
	if (d < 0) {
		lowerZero = true;
		d *= -1;
		d--;
	}
	d++;
	g = 1;
	bool leapYear = (!(g % 4) && (g % 100) || !(g % 400));
	while (d > (leapYear ? 366 : 365)) {
		d -= (leapYear ? 366 : 365);
		g++;
		leapYear = (!(g % 4) && (g % 100) || !(g % 400));
	}
	m = 0;
	const int* arr = leapYear ? days_in_month : days_in_month_leap;
	while (d > arr[m]) {
		d -= arr[m++];
	}
	m++;
	if (lowerZero) {
		d *= -1;
	}
}
int Date::ToDay(int d, int m, int g) {//дата переводится в кол-во дней, прошедших с 01.01.1 по выведенной формуле: (d + (дни в месяце) + g * 365 + (g - 1) / 4 - g / 100 + g / 400 - 365)
	bool lowerZero = false;
	if (d < 0 || m < 0 || g < 0) {
		d = abs(d);
		m = abs(m);
		g = abs(g);
		lowerZero = true;
	}
	int result = static_cast<int>(d + ((((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0)) ? (sum_month_days_leap[m]) : (sum_month_days[m])) + g * 365.2425 - 365 + ((g == 1) ? (0) : (-1)));
	if (lowerZero) {
		result = (result + 1) * -1;
	}
	return result;
}
bool Date::IsDatable(int d, int m, int g) {
	if (m > 12 || m < 1 || g < 1) {
		return false;
	}
	if (!Leap(g)) {
		if (d < 1 || d > days_in_month[m - 1]) {
			return false;
		}
	}
	else if (d < 1 || d > days_in_month_leap[m - 1]) {
		return false;
	}
	return true;
}

const int Date::days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int Date::days_in_month_leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int Date::sum_month_days[14] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int Date::sum_month_days_leap[14] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

#pragma endregion

std::ostream& operator<<(std::ostream& out, const Date& date) {
	int d = date._days, m = 0, g = 0, zn = 1;
	if (d < 0) {
		out << '-';
	}
	date.ToDate(d, m, g);
	d = abs(d);
	m = abs(m);
	g = abs(g);
	out << d / 10 << d % 10 << ':' << m / 10 << m % 10 << ':' << g;
	return out;
}
std::istream& operator>>(std::istream& in, Date& date) {
	std::string pr;
	std::getline(in, pr);
	date.Assign(pr);
	return in;
}

Date Opposite(const Date& date)
{
	return Date((date.AllDays() + 1) * -1);
}

Date operator""_days(unsigned long long days) {
	return Date(static_cast<int>(days));
}
Date operator""_day(unsigned long long days) {
	return Date(static_cast<int>(days), 1, 1);
}
Date operator""_month(unsigned long long months) {
	int years = static_cast<int>((months - 1) / 12 + 1);
	months -= (years - 1) * 12;
	return Date(1, static_cast<int>(months), years);
}
Date operator""_year(unsigned long long years) {
	return Date(1, 1, static_cast<int>(years));
}
Date operator""_date(const char* date, size_t len) {
	return Date(date);
}

Date Days(int count) {
	return Date(count);
}
}
