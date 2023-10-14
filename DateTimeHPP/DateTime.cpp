#include "DateTime.hpp"

#include<chrono>

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

	DateTime::DateTime() {}
	DateTime::DateTime(long long days, int milliseconds)
	{
		Assign(days, milliseconds);
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
	DateTime::DateTime(const Date& date, const Time& time)
	{
		Assign(date, time);
	}
	DateTime::DateTime(const Date& date)
	{
		Assign(date);
	}
	DateTime::DateTime(const Time& time)
	{
		Assign(time);
	}
	DateTime::DateTime(const DateTime& other)
	{
		Assign(other.date, other.time);
	}

	#pragma endregion

	#pragma region Методы

	void DateTime::Assign(long long days, int milliseconds)
	{
		date.days = days;
		time.milliseconds = milliseconds;
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
		date.day = days;
		date.month = months;
		date.year = years;
		date.days = Date::ToDay(days, months, years);
		time.milliseconds = Time::ToMilliseconds(hours, minuts, seconds, milliseconds);
	}
	void DateTime::Assign(int days, int months, long long years)
	{
		if (!Date::IsDatable(days, months, years))
			return;
		date.day = days;
		date.month = months;
		date.year = years;
		date.days = Date::ToDay(days, months, years);
	}
	void DateTime::Assign(int hours, int minuts, int seconds, int milliseconds)
	{
		if (!Time::IsTimeabe(hours, minuts, seconds, milliseconds))
			return;
		time.milliseconds = Time::ToMilliseconds(hours, minuts, seconds, milliseconds);
	}
	void DateTime::Assign(const Date& date, const Time& time)
	{
		this->date.days = date.days;
		this->date.day = date.day;
		this->date.month = date.month;
		this->date.year = date.year;
		this->time.milliseconds = time.milliseconds;
	}
	void DateTime::Assign(const Date& date)
	{
		this->date.days = date.days;
		this->date.day = date.day;
		this->date.month = date.month;
		this->date.year = date.year;
	}
	void DateTime::Assign(const Time& time)
	{
		this->time.milliseconds = time.milliseconds;
	}
	void DateTime::Assign(const DateTime& other)
	{
		this->date.days = other.date.days;
		this->date.day = other.date.day;
		this->date.month = other.date.month;
		this->date.year = other.date.year;
		this->time.milliseconds = other.time.milliseconds;
	}

	bool DateTime::IsLeap() const
	{
		return date.IsLeap();
	}

	DateTime& DateTime::SetAllDays(long long days)	
	{
		Assign(days, time.milliseconds);
		return*this;
	}
	DateTime& DateTime::SetDay(int day)
	{
		Assign(static_cast<int>(day), static_cast<int>(date.month), date.year);
		return *this;
	}
	DateTime& DateTime::SetMonth(int month)
	{
		Assign(static_cast<int>(date.day), static_cast<int>(month), date.year);
		return *this;
	}
	DateTime& DateTime::SetYear(long long year)
	{
		Assign(static_cast<int>(date.day), static_cast<int>(date.month), year);
		return *this;
	}
	DateTime& DateTime::SetDate(const Date& date)
	{
		Assign(date);
		return *this;
	}
	DateTime& DateTime::SetAllMilliseconds(int value)
	{
		Assign(date.days, value);
		return *this;
	}
	DateTime& DateTime::SetMilliseconds(int value)
	{
		time.SetMilliseconds(value);
		return *this;
	}
	DateTime& DateTime::SetSeconds(int value)
	{
		time.SetSeconds(value);
		return *this;
	}
	DateTime& DateTime::SetMinuts(int value)
	{
		time.SetMinuts(value);
		return *this;
	}
	DateTime& DateTime::SetHours(int value)
	{
		time.SetHours(value);
		return *this;
	}
	DateTime& DateTime::SetTime(const Time& time)
	{
		Assign(time);
		return *this;
	}

	long long	DateTime::GetAllDays()			const
	{
		return date.GetAllDays();
	}
	int			DateTime::GetDay()				const
	{
		return date.GetDay();
	}
	int			DateTime::GetMonth()			const
	{
		return date.GetMonth();
	}
	long long	DateTime::GetYear()				const
	{
		return date.GetYear();
	}
	int			DateTime::GetWeekCount()		const
	{
		return date.GetWeekCount();
	}
	int			DateTime::GetDayWeek()			const
	{
		return date.GetDayWeek();
	}
	Date		DateTime::GetDate()				const
	{
		return date;
	}
	int			DateTime::GetAllMilliseconds()	const
	{
		return time.GetAllMilliseconds();
	}
	int			DateTime::GetMilliseconds()		const
	{
		return time.GetMilliseconds();
	}
	int			DateTime::GetSeconds()			const
	{
		return time.GetSeconds();
	}
	int			DateTime::GetMinuts()			const
	{
		return time.GetMinuts();
	}
	int			DateTime::GetHours()			const
	{
		return time.GetHours();
	}
	Time		DateTime::GetTime()				const
	{
		return time;
	}

	DateTime& DateTime::MakeOpposite()
	{
		date.MakeOpposite();
		time.MakeOpposite();
		return *this;
	}
	DateTime& DateTime::MakeOppositeTime()
	{
		time.MakeOpposite();
		return *this;
	}
	DateTime& DateTime::MakeOppositeDate()
	{
		date.MakeOpposite();
		return *this;
	}

	std::string DateTime::ToString() const
	{
		return date.ToString() + '-' + time.ToString();
	}
	std::string DateTime::ToString(std::string example) const
	{
		int hour, minut, second, millisecond = time.milliseconds;
		Time::ToTime(hour, minut, second, millisecond);
		fillStrDT(date.day, example, 'D');
		fillStrDT(date.month, example, 'M');
		fillStrDT(date.year, example, 'Y');
		fillStrDT(hour, example, 'h');
		fillStrDT(minut, example, 'm');
		fillStrDT(second, example, 's');
		fillStrDT(millisecond, example, 'S');
		return example;
	}

	#pragma endregion

	#pragma region Операторы
	
	DateTime::operator Time() const {
		return time;
	}
	DateTime::operator Date() const {
		return date;
	}

	bool DateTime::operator<(const DateTime& dt) const {
		if (date.days < dt.date.days)
			return true;
		if (date.days == dt.date.days)
		{
			if (date.days < 0)
				return time.milliseconds > dt.time.milliseconds;
			else
				return time.milliseconds < dt.time.milliseconds;
		}
		else
			return false;
	}
	bool DateTime::operator>(const DateTime& dt) const {
		if (date.days > dt.date.days)
			return true;
		if (date.days == dt.date.days)
		{
			if (date.days < 0)
				return time.milliseconds < dt.time.milliseconds;
			else
				return time.milliseconds > dt.time.milliseconds;
		}
		else
			return false;
	}
	bool DateTime::operator==(const DateTime& dt) const {
		return date.days == dt.date.days && time.milliseconds == dt.time.milliseconds;
	}
	bool DateTime::operator!=(const DateTime& dt) const {
		return !(date.days == dt.date.days && time.milliseconds == dt.time.milliseconds);
	}
	bool DateTime::operator<=(const DateTime& dt) const {
		return !(*this > dt);
	}
	bool DateTime::operator>=(const DateTime& dt) const {
		return !(*this < dt);
	}

	DateTime DateTime::operator+(const DateTime& dt) const {
		return DateTime(
			date.days + dt.date.days, 
			time.milliseconds + ((date.days >= 0) ? (dt.time.milliseconds) : (-dt.time.milliseconds))
		);
	}
	DateTime DateTime::operator-(const DateTime& dt) const {
		return DateTime(
			date.days - dt.date.days,
			time.milliseconds - ((date.days >= 0) ? (dt.time.milliseconds) : (-dt.time.milliseconds))
		);
	}
	DateTime DateTime::operator*(long long value) const {
		return DateTime(
			date.days * value,
			static_cast<int>(time.milliseconds * value)
		);
	}
	DateTime DateTime::operator/(long long value) const {
		return DateTime(
			date.days / value,
			static_cast<int>(time.milliseconds / value)
		);
	}

	DateTime& DateTime::operator+=(const DateTime& dt) {
		Assign(
			date.days + dt.date.days, 
			time.milliseconds + ((date.days >= 0) ? (dt.time.milliseconds) : (-dt.time.milliseconds))
		);
		return *this;
	}
	DateTime& DateTime::operator-=(const DateTime& dt) {
		Assign(
			date.days - dt.date.days,
			time.milliseconds - ((date.days >= 0) ? (dt.time.milliseconds) : (-dt.time.milliseconds))
		);
		return *this;
	}
	DateTime& DateTime::operator*=(long long value) {
		Assign(
			date.days * value, static_cast<int>(time.milliseconds * value)
		);
		return *this;
	}
	DateTime& DateTime::operator/=(long long value) {
		Assign(
			date.days / value, static_cast<int>(time.milliseconds / value)
		);
		return *this;
	}

	#pragma endregion

	DateTime DateTime::Now() {
		long long milliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + static_cast<long long>(Time::UTC() * 3600000));
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
		long long plus = (date.days >= 0) ? 1 : -1;
		while (time.milliseconds >= Time::maxValue)
		{
			time.milliseconds -= Time::maxValue;
			date.days += plus;
		}
		while (time.milliseconds < 0)
		{
			time.milliseconds += Time::maxValue;
			date.days -= plus;
		}
		if (date.days < Date::minValue)
		{
			date.days = date.days % Date::minValue + Date::maxValue + 1;
			time.milliseconds = Time::maxValue - time.milliseconds;
		}
		else if (date.days > Date::maxValue)
		{
			date.days = date.days % Date::maxValue + Date::minValue - 1;
			time.milliseconds = Time::maxValue - time.milliseconds;
		}
		date.day = date.days;
		Date::ToDate(date.day, date.month, date.year);
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
		in.get();
		in >> prt;
		dt.Assign(prd, prt);
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