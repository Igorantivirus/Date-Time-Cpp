#include "DateTime.hpp"

#include<chrono>

//#define maxValue 86400000

char fillFromStrDT(const char* dt, long long arr[7])
{
	if (dt == nullptr) {
		return 0;
	}
	char DateCount;
	for (DateCount = 0; DateCount < 7; DateCount++) {
		if (dt[0] == '\0') {
			break;
		}
		arr[DateCount] = atoll(dt);
		if (dt[0] == '-') {
			dt++;
		}
		for (; (dt[0] >= '0' && dt[0] <= '9'); dt++) {}
		dt++;
	}
	return DateCount;
}
void fillStrDT(const long long num, std::string& res, const char c)
{
	size_t pos;
	const char pr[3] = { '%', c, '\0' };
	if ((pos = res.find(pr)) == std::string::npos)
		return;
	int count = 1;
	for (size_t i = pos + 2; i < res.size(); i++)
		if (res[i] == c)
			count++;
	std::string newV = std::to_string(num);
	while (newV.size() < count)
		newV = '0' + newV;
	res.replace(pos, count + 1, newV);
}

namespace dt
{
	#pragma region Конструкторы

	DateTime::DateTime() : days(0), milliseconds(0) {}
	DateTime::DateTime(long long days, int milliseconds) : days(days), milliseconds(milliseconds)
	{
		Round();
	}
	DateTime::DateTime(const char* dt)
	{
		Assign(dt);
	}
	DateTime::DateTime(const std::string& dt)
	{
		Assign(dt.c_str());
	}
	DateTime::DateTime(const char* dt, const char* example)
	{
		Assign(dt, example);
	}
	DateTime::DateTime(const std::string& dt, const std::string& example)
	{
		Assign(dt.c_str(), example.c_str());
	}
	DateTime::DateTime(int days, int months, long long years, int hours, int minuts, int seconds, int milliseconds)
	{
		Assign(days, months, years, hours, minuts, seconds, milliseconds);
	}
	DateTime::DateTime(int days, int months, long long years)
	{
		Assign(days, months, years);
	}
	DateTime::DateTime(int hours, int minuts, int seconds, int milliseconds)
	{
		Assign(hours, minuts, seconds, milliseconds);
	}
	DateTime::DateTime(const Date& date, const Time& time) : days(date.days), milliseconds(time.milliseconds) {}
	DateTime::DateTime(const Date& date) : days(date.days), milliseconds(0) {}
	DateTime::DateTime(const Time& time) : days(0), milliseconds(time.milliseconds) {}
	DateTime::DateTime(const DateTime& other) : days(other.milliseconds), milliseconds(other.milliseconds) {}

	#pragma endregion

	#pragma region Методы

	void DateTime::Assign(long long days, int milliseconds)
	{
		this->days = days;
		this->milliseconds = milliseconds;
		Round();
	}
	void DateTime::Assign(const char* dt)
	{
		long long arr[7] = {1,1,1,0,0,0,0};
		char pr = fillFromStrDT(dt, arr);
		if (pr == 3)
			Assign(static_cast<int>(arr[0]), static_cast<int>(arr[1]), arr[2]);
		else if (pr == 2)
			Assign(static_cast<int>(arr[0]), static_cast<int>(arr[1]), 0, 0);
		else if (pr == 4)
			Assign(static_cast<int>(arr[0]), static_cast<int>(arr[1]), static_cast<int>(arr[2]), static_cast<int>(arr[3]));
		else
			Assign(static_cast<int>(arr[0]), static_cast<int>(arr[1]), arr[2], static_cast<int>(arr[3]), static_cast<int>(arr[4]), static_cast<int>(arr[5]), static_cast<int>(arr[6]));
	}
	void DateTime::Assign(const std::string& dt)
	{
		Assign(dt.c_str());
	}
	void DateTime::Assign(const char* dt, const char* example)
	{
		std::cout << strlen(example) << std::endl;
		long long arr[7] = {1,1,1,0,0,0,0};
		fillFromStrDT(dt, arr);
		long long d = 1, m = 1, y = 1, h = 0, mi = 0, s =0, mil = 0;
		for (auto i = 0; i < 7 && *example != '\0'; i++)
		{
			while (*example != '\0' && *example++ != '%') {}
			if (*example == 'D')
				d = arr[i];
			else if (*example == 'M')
				m = arr[i];
			else if (*example == 'Y')
				y = arr[i];
			else if (*example == 'h')
				h = arr[i];
			else if (*example == 'm')
				mi = arr[i];
			else if (*example == 's')
				s = arr[i];
			else if (*example == 'S')
				mil = arr[i];
		}
		Assign(static_cast<int>(d), static_cast<int>(m), y, static_cast<int>(h), static_cast<int>(mi), static_cast<int>(s), static_cast<int>(mil));
	}
	void DateTime::Assign(const std::string& dt, const std::string& example)
	{
		Assign(dt.c_str(), example.c_str());
	}
	void DateTime::Assign(int days, int months, long long years, int hours, int minuts, int seconds, int milliseconds)
	{
		if (!Date::IsDatable(days, months, years) || !Time::IsTimeabe(hours, minuts, seconds, milliseconds))
			return;
		this->days = Date::ToDay(days, months, years);
		this->milliseconds = Time::ToMilliseconds(hours, minuts, seconds, milliseconds);
		Round();
	}
	void DateTime::Assign(int days, int months, long long years)
	{
		if (!Date::IsDatable(days, months, years))
			return;
		this->days = Date::ToDay(days, months, years);
		Round();
	}
	void DateTime::Assign(int hours, int minuts, int seconds, int milliseconds)
	{
		if (!Time::IsTimeabe(hours, minuts, seconds, milliseconds))
			return;
		this->milliseconds = Time::ToMilliseconds(hours, minuts, seconds, milliseconds);
		Round();
	}
	void DateTime::Assign(const Date& date, const Time& time)
	{
		days = date.days;
		milliseconds = time.milliseconds;
	}
	void DateTime::Assign(const Date& date)
	{
		days = date.days;
	}
	void DateTime::Assign(const Time& time)
	{
		milliseconds = time.milliseconds;
	}
	void DateTime::Assign(const DateTime& other)
	{
		days = other.days;
		milliseconds = other.milliseconds;
	}

	bool DateTime::IsLeap() const
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		return Leap(y);
	}

	DateTime& DateTime::SetAllDays(long long days)	
	{
		this->days = days;
		return*this;
	}
	DateTime& DateTime::SetDay(int day)
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		Assign(static_cast<int>(day), static_cast<int>(m), y);
		return *this;
	}
	DateTime& DateTime::SetMonth(int month)
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		Assign(static_cast<int>(d), static_cast<int>(month), y);
		return *this;
	}
	DateTime& DateTime::SetYear(long long year)
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		Assign(static_cast<int>(d), static_cast<int>(m), year);
		return *this;
	}
	DateTime& DateTime::SetDate(const Date& date)
	{
		days = date.days;
		return *this;
	}
	DateTime& DateTime::SetAllMilliseconds(int value)
	{
		milliseconds = value;
		Round();
		return *this;
	}
	DateTime& DateTime::SetMilliseconds(int value)
	{
		if (value >= 1000 || value < 0)
			return *this;
		milliseconds = milliseconds / 1000 * 1000 + value;
		Round();
		return *this;
	}
	DateTime& DateTime::SetSeconds(int value)
	{
		if (value >= 60 || value < 0)
			return *this;
		milliseconds = milliseconds / 60000 * 60000 + value * 1000 + milliseconds % 1000;
		Round();
		return *this;
	}
	DateTime& DateTime::SetMinuts(int value)
	{
		if (value >= 60 || value < 0)
			return *this;
		milliseconds = milliseconds / 3600000 * 3600000 + value * 60000 + milliseconds % 60000;
		Round();
		return *this;
	}
	DateTime& DateTime::SetHours(int value)
	{
		if (value >= 24 || value < 0)
			return *this;
		milliseconds = milliseconds % 3600000 + value * 3600000;
		Round();
		return *this;
	}
	DateTime& DateTime::SetTime(const Time& time)
	{
		milliseconds = time.milliseconds;
		return *this;
	}

	long long	DateTime::GetAllDays()			const
	{
		return this->days;
	}
	int			DateTime::GetDay()				const
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		return static_cast<int>(d);
	}
	int			DateTime::GetMonth()			const
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		return static_cast<int>(m);
	}
	long long	DateTime::GetYear()				const
	{
		long long d = this->days, m, y;
		Date::ToDate(d, m, y);
		return y;
	}
	int			DateTime::GetWeekCount()		const
	{
		return static_cast<int>(days / 7);
	}
	int			DateTime::GetDayWeek()			const
	{
		if (days >= 0)
			return days % 7 + 1;
		else
			return  8 - ((abs(days) - 1) % 7 + 1);
	}
	int			DateTime::GetAllMilliseconds()	const
	{
		return milliseconds;
	}
	Date		DateTime::GetDate()				const
	{
		return Date(days);
	}
	int			DateTime::GetMilliseconds()		const
	{
		return milliseconds % 1000;
	}
	int			DateTime::GetSeconds()			const
	{
		return milliseconds / 1000 % 60;
	}
	int			DateTime::GetMinuts()			const
	{
		return milliseconds / 60000 % 60;
	}
	int			DateTime::GetHours()			const
	{
		return milliseconds / 3600000;
	}
	Time		DateTime::GetTime()				const
	{
		return Time(milliseconds);
	}

	DateTime& DateTime::MakeOpposite()
	{
		days = (days + 1) * -1;
		milliseconds = Time::maxValue - milliseconds;
		return *this;
	}
	DateTime& DateTime::MakeOppositeTime()
	{
		milliseconds = Time::maxValue - milliseconds;
		return *this;
	}
	DateTime& DateTime::MakeOppositeDate()
	{
		days = (days + 1) * -1;
		return *this;
	}

	std::string DateTime::ToString() const
	{
		return Date(days).ToString() + '-' + Time(milliseconds).ToString();
	}
	std::string DateTime::ToString(std::string example) const
	{
		long long d = days, m, y;
		Date::ToDate(d, m, y);
		int ho, mi, se, mil = milliseconds;
		Time::ToTime(ho, mi, se, mil);
		fillStrDT(d, example, 'D');
		fillStrDT(m, example, 'M');
		fillStrDT(y, example, 'Y');
		fillStrDT(ho, example, 'h');
		fillStrDT(mi, example, 'm');
		fillStrDT(se, example, 's');
		fillStrDT(mil, example, 'S');
		return example;
	}

	#pragma endregion

	#pragma region Операторы
	
	DateTime::operator Time() const {
		return Time(milliseconds);
	}
	DateTime::operator Date() const {
		return Date(days);
	}

	bool DateTime::operator<(const DateTime& dt) const {
		if (days < dt.days)
			return true;
		if (days == dt.days) {
			if (days < 0)
				return milliseconds > dt.milliseconds;
			else 
				return milliseconds < dt.milliseconds;
		}
		else
			return false;
	}
	bool DateTime::operator>(const DateTime& dt) const {
		if (days > dt.days)
			return true;
		if (days == dt.days) {
			if (days < 0)
				return milliseconds < dt.milliseconds;
			else
				return milliseconds > dt.milliseconds;
		}
		else
			return false;
	}
	bool DateTime::operator==(const DateTime& dt) const {
		return days == dt.days && milliseconds == dt.milliseconds;
	}
	bool DateTime::operator!=(const DateTime& dt) const {
		return !(days == dt.days && milliseconds == dt.milliseconds);
	}
	bool DateTime::operator<=(const DateTime& dt) const {
		return !(*this > dt);
	}
	bool DateTime::operator>=(const DateTime& dt) const {
		return !(*this < dt);
	}

	DateTime DateTime::operator+(const DateTime& dt) const {
		return DateTime(days + dt.days, milliseconds + ((days >= 0) ? (dt.milliseconds) : (-dt.milliseconds)));
	}
	DateTime DateTime::operator-(const DateTime& dt) const {
		return DateTime(days - dt.days, milliseconds - ((days >= 0) ? (dt.milliseconds) : (-dt.milliseconds)));
	}
	DateTime DateTime::operator*(long long value) const {
		return DateTime(static_cast<int>(days * value), static_cast<int>(milliseconds * ((days >= 0) ? (value) : (-value))));
	}
	DateTime DateTime::operator/(long long value) const {
		return DateTime(static_cast<int>(days / value), static_cast<int>(milliseconds / ((days >= 0) ? (value) : (-value))));
	}

	DateTime& DateTime::operator+=(const DateTime& dt) {
		Assign(days + dt.days, milliseconds + ((days >= 0) ? (dt.milliseconds) : (-dt.milliseconds)));
		return *this;
	}
	DateTime& DateTime::operator-=(const DateTime& dt) {
		Assign(days - dt.days, milliseconds - ((days >= 0) ? (dt.milliseconds) : (-dt.milliseconds)));
		return *this;
	}
	DateTime& DateTime::operator*=(long long value) {
		Assign(static_cast<int>(days * value), static_cast<int>(milliseconds * ((days >= 0) ? (value) : (-value))));
		return *this;
	}
	DateTime& DateTime::operator/=(long long value) {
		Assign(static_cast<int>(days / value), static_cast<int>(milliseconds / ((days >= 0) ? (value) : (-value))));
		return *this;
	}

	#pragma endregion

	DateTime DateTime::Now(float TimeZone) {
		long long milliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + static_cast<long long>(TimeZone * 3600000));
		return DateTime(static_cast<int>(milliseconds / 86400000 + 719162), static_cast<int>(milliseconds % 86400000));
	}
	DateTime DateTime::MaxDateTime() {
		return DateTime(Date::maxValue, Time::maxValue-1);
	}
	DateTime DateTime::MinDateTime() {
		return DateTime(Date::minValue, Time::maxValue - 1);
	}

	void DateTime::Round()
	{
		long long plus = (days >= 0) ? 1 : -1;
		while (milliseconds >= Time::maxValue)
		{
			milliseconds -= Time::maxValue;
			days+= plus;
		}
		while (milliseconds < 0)
		{
			milliseconds += Time::maxValue;
			days-= plus;
		}
		if (days < Date::minValue)
		{
			days = days % Date::minValue + Date::maxValue + 1;
			milliseconds = Time::maxValue - milliseconds;
		}
		else if (days > Date::maxValue)
		{
			days = days % Date::maxValue + Date::minValue - 1;
			milliseconds = Time::maxValue - milliseconds;
		}
	}

	std::ostream& operator<<(std::ostream& out, const DateTime& dt)
	{
		return out << dt.ToString();
	}
	std::istream& operator>>(std::istream& in, DateTime& dt)
	{
		Date prd;
		Time prt;
		in >> prd;
		char pr;
		in.get(pr);
		in >> prt;
		return in;
	}

	DateTime Opposite(DateTime dt)
	{
		return dt.MakeOpposite();
	}
	DateTime OppositeTime(DateTime time)
	{
		return time.MakeOppositeTime();
	}
	DateTime OppositeDate(DateTime date)
	{
		return date.MakeOppositeDate();
	}

	DateTime operator""_dt(const char* dt, size_t size)
	{
		return DateTime(dt);
	}
}