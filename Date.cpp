#include "Date.hpp"

#include<chrono>
#include<limits>

void fillFromStrDate(const char* date, long long arr[3])
{
	if (date == nullptr) {
		return;
	}
	for (int DateCount = 0; DateCount < 3; DateCount++) {
		if (date[0] == '\0') {
			break;
		}
		arr[DateCount] = atoll(date);
		if (date[0] == '-') {
			date++;
		}
		for (; (date[0] >= '0' && date[0] <= '9'); date++) {}
		date++;
	}
}
void fillStrDate(const long long num, std::string& res, const char c)
{
	size_t pos;
	const char pr[3] = { '%', c, '\0' };
	if ((pos = res.find(pr)) == std::string::npos)
		return;
	int count = 1;
	for (size_t i = pos + 2; i < res.size(); i++)
		if (res[i] == c)
			count++;
	std::string newV = std::to_string(abs(num));
	while (newV.size() < count)
		newV = '0' + newV;
	if (num < 0)
		newV = '-' + newV;
	res.replace(pos, count + 1, newV);
}

namespace dt
{
	const unsigned char Date::days_in_months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	const unsigned char Date::days_in_months_leap[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };

	const long long Date::maxValue = LLONG_MAX / 400 - 1;
	const long long Date::minValue = LLONG_MIN / 400;

	inline bool Leap(long long year)
	{
		return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	}

	#pragma region class Date

	#pragma region Конструкторы

	Date::Date() : days(0) {}
	Date::Date(const char* date)
	{
		Assign(date);
	}
	Date::Date(const std::string& date)
	{
		Assign(date.c_str());
	}
	Date::Date(const char* date, const char* example)
	{
		Assign(date, example);
	}
	Date::Date(const std::string& date, const std::string& example)
	{
		Assign(date, example);
	}
	Date::Date(int day, int month, long long year)
	{
		Assign(day, month, year);
	}
	Date::Date(long long days) : days(days)
	{
		Round();
	}
	Date::Date(const Date& other) : days(other.days) {}

	#pragma endregion

	#pragma region Методы

	void Date::Assign(const char* date)
	{
		long long arr[3] = {1,1,1};
		fillFromStrDate(date, arr);
		Assign(static_cast<int>(arr[0]), static_cast<int>(arr[1]), arr[2]);
	}
	void Date::Assign(const std::string& date)
	{
		Assign(date.c_str());
	}
	void Date::Assign(const char* date, const char* example)
	{
		long long arr[3] = {1,1,1};
		fillFromStrDate(date, arr);
		long long d = 1, m = 1, y = 1;
		for (char i = 0; i < 3 && *example != '\0'; i++)
		{
			while (*example != '\0' && *example++ != '%') {}
			if (*example == 'D')
				d = arr[i];
			else if (*example == 'M')
				m = arr[i];
			else if (*example == 'Y')
				y = arr[i];
		}
		Assign(static_cast<int>(d), static_cast<int>(m), y);
	}
	void Date::Assign(const std::string& date, const std::string& example)
	{
		Assign(date.c_str(), example.c_str());
	}
	void Date::Assign(int day, int month, long long year)
	{
		if (!IsDatable(day, month, year))
			return;
		this->days = ToDay(day, month, year);
	}
	void Date::Assign(long long days)
	{
		this->days = days;
		Round();
	}
	void Date::Assign(const Date& other)
	{
		this->days = other.days;
	}

	bool Date::IsLeap() const
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		return Leap(y);
	}

	Date& Date::SetAllDays(long long days)
	{
		this->days = days;
		return* this;
	}
	Date& Date::SetDay(int day)
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		Assign(static_cast<int>(day), static_cast<int>(m), y);
		return *this;
	}
	Date& Date::SetMonth(int month)
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		Assign(static_cast<int>(d), static_cast<int>(month), y);
		return *this;
	}
	Date& Date::SetYear(long long year)
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		Assign(static_cast<int>(d), static_cast<int>(m), year);
		return *this;
	}

	long long	Date::GetAllDays()		const
	{
		return this->days;
	}
	int			Date::GetDay()			const
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		return static_cast<int>(d);
	}
	int			Date::GetMonth()		const
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		return static_cast<int>(m);
	}
	long long	Date::GetYear()			const
	{
		long long d = this->days, m, y;
		ToDate(d, m, y);
		return y;
	}
	int			Date::GetWeekCount()	const
	{
		return static_cast<int>(days / 7);
	}
	int			Date::GetDayWeek()		const
	{
		if (days >= 0)
			return days % 7 + 1;
		else
			return  8 - ((abs(days) - 1) % 7 + 1);
	}

	Date& Date::MakeOpposite()
	{
		days = (days + 1) * -1;
		return *this;
	}

	std::string Date::ToString() const
	{
		std::string res = "";
		long long d = days, m, y;
		if (d < 0)
			res = '-';
		ToDate(d, m, y);
		char pr[] = {
			static_cast<char>(abs(d)/10) + '0', static_cast<char>(abs(d) % 10) + '0', ':',
			static_cast<char>(m / 10) + '0', static_cast<char>(m % 10) + '0', ':', '\0'
		};
		res += pr + std::to_string(y);
		return res;
	}

	std::string Date::ToString(std::string example) const
	{
		long long d = days, m, y;
		ToDate(d, m, y);
		fillStrDate(d, example, 'D');
		fillStrDate(m, example, 'M');
		fillStrDate(y, example, 'Y');
		return example;
	}

	#pragma endregion

	#pragma region Операторы
	
	Date& Date::operator=(const Date& other)
	{
		this->days = other.days;
		return *this;
	}

	bool Date::operator==(const Date& other)	const
	{
		return this->days == other.days;
	}
	bool Date::operator!=(const Date& other)	const
	{
		return this->days != other.days;
	}
	bool Date::operator<=(const Date& other)	const
	{
		return this->days <= other.days;
	}
	bool Date::operator>=(const Date& other)	const
	{
		return this->days >= other.days;
	}
	bool Date::operator<(const Date& other)		const
	{
		return this->days < other.days;
	}
	bool Date::operator>(const Date& other)		const
	{
		return this->days > other.days;
	}

	Date Date::operator+(const Date& other) const
	{
		return Date(this->days + other.days);
	}
	Date Date::operator-(const Date& other) const
	{
		return Date(this->days - other.days);
	}
	Date Date::operator*(long long value)	const
	{
		return Date(this->days * value);
	}
	Date Date::operator/(long long value)	const
	{
		return Date(this->days / value);
	}
	Date Date::operator%(long long value)	const
	{
		return Date(this->days % value);
	}

	Date& Date::operator+=(const Date& other)
	{
		this->days += other.days;
		Round();
		return *this;
	}
	Date& Date::operator-=(const Date& other)
	{
		this->days -= other.days;
		Round();
		return *this;
	}
	Date& Date::operator*=(long long value)
	{
		this->days *= value;
		Round();
		return *this;
	}
	Date& Date::operator/=(long long value)
	{
		this->days /= value;
		Round();
		return *this;
	}
	Date& Date::operator%=(long long value)
	{
		this->days %= value;
		Round();
		return *this;
	}

	Date&	Date::operator++()
	{
		++this->days;
		Round();
		return *this;
	}
	Date&	Date::operator--()
	{
		--this->days;
		Round();
		return *this;
	}
	Date	Date::operator++(int)
	{
		Date res = this->days++;
		Round();
		return res;
	}
	Date	Date::operator--(int)
	{
		Date res = this->days--;
		Round();
		return res;
	}

	#pragma endregion

	Date Date::Now(float UTC)
	{
		return Date(static_cast<long long>((
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
			+ static_cast<long long>(UTC * 3600000)) / 86400000 
			+ 719162));
	}
	Date Date::MaxDate()
	{
		return Date(maxValue);
	}
	Date Date::MinDate()
	{
		return Date(minValue);
	}

	void Date::Round()
	{
		if (days < minValue)
			days = days % minValue + maxValue;
		else if (days > maxValue)
			days = days % maxValue + minValue;
	}

	long long Date::ToDay(long long day, long long month, long long year)
	{
		int zn = 1;
		if (day < 0)
			day = day * (zn = -1) + 1;
		long long res = day;
		const unsigned char* arr = Leap(year) ? days_in_months_leap: days_in_months;
		for (int i = 0; i < month; i++)
			res += arr[i];
		res -= arr[month - 1];
		year--;
		res += year * 365 + year / 4 - year / 100 + year / 400 - 1;
		return res * zn;
	}
	void Date::ToDate(long long& day, long long& month, long long& year)
	{
		month = 0,year = 1;
		int zn = 1;
		if (day < 0)
			day = (zn = -1) * day - 1;
		year = (day + 1) * 400 / 146097;
		day -= year * 365 + year / 4 - year / 100 + year / 400 - 1;
		year++;
		if (day == 0)
			day += (Leap(--year)) ? (366) : (365);
		else if (day == 366 && !Leap(year))
		{
			day = 1;
			year++;
		}

		int minusMonth = 0;
		const unsigned char* arr = (Leap(year) ? (days_in_months_leap) : (days_in_months));
		while (day > minusMonth)
			minusMonth += arr[month++];
		minusMonth -= arr[month - 1];
		day -= minusMonth;
		day *= zn;
	}
	bool Date::IsDatable(long long day, long long month, long long year)
	{
		if (day == 0 || month == 0 || year == 0)
			return false;
		if (day < 0 || month < 0 || year < 0)
		{
			day = abs(day);
			month = abs(month);
			year = abs(year);
		}
		if(month > 12)
			return false;
		if (day > (Leap(year) ? (days_in_months_leap[month - 1]) : (days_in_months[month - 1])))
			return false;
		long long d = maxValue, m, g;
		ToDate(d, m, g);
		if (year > g)
			return false;
		if (year == g && (month > m))
			return false;
		if (year == g && month == m && day > d)
			return false;
		return true;
	}

	#pragma endregion

	std::ostream& operator<<(std::ostream& out, const Date& date)
	{
		return out << date.ToString();
	}
	std::istream& operator>>(std::istream& in, Date& date)
	{
		long long arr[3] = {};
		in >> arr[0];
		for (char i = 1, pr; i < 3; i++)
		{
			in.get(pr);
			in >> arr[i];
		}
		date.Assign(static_cast<int>(arr[0]), static_cast<int>(arr[1]), arr[2]);
		return in;
	}

	Date Opposite(Date date)
	{
		return date.MakeOpposite();
	}

	Date operator""_date(const char* date, size_t size)
	{
		return Date(date);
	}
}

/*
	long long Date::ToDay(int day, int month, int year)
	{
		int zn = 1;
		if (day < 0)
			day = day * (zn = -1) + 1;
		long long res = day;
		const unsigned char* arr = Leap(year) ? days_in_months_leap: days_in_months;
		for (int i = 0; i < month; i++)
			res += arr[i];
		res -= arr[month - 1];
		year--;
		res += year * 365;
		res += year / 4 - year / 100 + year / 400 - 1;
		if (year > 0)
			res++;
		return res * zn;
	}
	void Date::ToDate(long long& day, int& month, int& year)
	{
		month = 0,year = 1;
		int zn = 1;
		if (day < 0)
			day = (zn = -1) * day - 1;
		day++;
		while (day > (Leap(year) ? 366 : 365))
			day -= (Leap(year++) ? 366 : 365);
		int minusMonth = 0;
		const unsigned char* arr = (Leap(year) ? (days_in_months_leap) : (days_in_months));
		while (day > minusMonth)
			minusMonth += arr[month++];
		minusMonth -= arr[month - 1];
		day -= minusMonth;
		day *= zn;
	}
*/
