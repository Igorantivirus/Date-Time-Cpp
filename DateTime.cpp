#include "DateTime.hpp"

#include"DateTimeHelpers.hpp"

namespace dt
{
	#pragma region Конструкторы

	DateTime::DateTime(const long long days, const long long nanoseconds)
	{
		Assign(days, nanoseconds);
	}
	DateTime::DateTime(const std::string& dt)
	{
		Assign(dt);
	}
	DateTime::DateTime(const std::string& dt, const std::string& example)
	{
		Assign(dt, example);
	}
	DateTime::DateTime(const Date::DatePoint& dp, const Time::TimePoint& tp)
	{
		Assign(dp, tp);
	}
	DateTime::DateTime(const Date& date, const Time& time)
	{
		Assign(date, time);
	}
	DateTime::DateTime(const Date& d)
	{
		Assign(d, {});
	}
	DateTime::DateTime(const Time& t)
	{
		Assign({}, t);
	}

	#pragma endregion

	#pragma region Методы

	void DateTime::Assign(const long long days, const long long nanoseconds)
	{
		date.days = days;
		time.nanoseconds = nanoseconds;
		Round();
	}
	void DateTime::Assign(const std::string& dt)
	{
		long long arr[9] = { 1,1,1,0,0,0,0,0,0 };
		char pr = fillFromStrDT(dt.c_str(), arr, 9);
		if (pr == 3)
		{
			Date::DatePoint p;
			p.ad = arr[0] > 0;
			p.day = toUShort(std::abs(arr[0]));
			p.month = toUShort(arr[1]);
			p.year = arr[2];
			Assign(p, {});
		}
		else if (pr == 2 || pr == 3 || pr == 4)
		{
			Time::TimePoint tp;
			tp.hours = toUShort(arr[0]);
			tp.minutes = toUShort(arr[1]);
			tp.seconds = toUShort(arr[2]);
			tp.milliseconds = toUShort(arr[3]);
			Assign({}, tp);
		}
		else if (pr == 5)
		{
			Date::DatePoint p;
			p.ad = arr[0] > 0;
			p.day = toUShort(std::abs(arr[0]));
			p.month = toUShort(arr[1]);
			p.year = arr[2];
			Time::TimePoint tp;
			tp.hours = toUShort(arr[3]);
			tp.minutes = toUShort(arr[4]);
			Assign(p, tp);
		}
		else
		{
			Date::DatePoint p;
			p.ad = arr[0] > 0;
			p.day = toUShort(std::abs(arr[0]));
			p.month = toUShort(arr[1]);
			p.year = arr[2];

			Time::TimePoint tp;
			tp.hours = toUShort(arr[3]);
			tp.minutes = toUShort(arr[4]);
			tp.seconds = toUShort(arr[5]);
			tp.milliseconds = toUShort(arr[6]);
			tp.microseconds = toUShort(arr[7]);
			tp.nanoseconds = toUShort(arr[8]);

			Assign(p, tp);
		}
	}
	void DateTime::Assign(const std::string& dt, const std::string& example)
	{
		long long arr[9] = { 1,1,1,0,0,0,0,0,0 };
		fillFromStrDT(dt.c_str(), arr, 9);
		const char* exmpl = example.c_str();
		long long d = 1, m = 1, y = 1, h = 0, mi = 0, s = 0, mil = 0, mic = {}, nan = {};
		for (auto i = 0; i < 7 && *exmpl != '\0'; i++)
		{
			while (*exmpl != '\0' && *exmpl++ != '%') {}
			if (*exmpl == 'D')
				d = arr[i];
			else if (*exmpl == 'M')
				m = arr[i];
			else if (*exmpl == 'Y')
				y = arr[i];
			else if (*exmpl == 'h')
				h = arr[i];
			else if (*exmpl == 'm')
				mi = arr[i];
			else if (*exmpl == 's')
				s = arr[i];
			else if (*exmpl == 'S')
				mil = arr[i];
			else if (*exmpl == 'C')
				mic = arr[i];
			else if (*exmpl == 'N')
				nan = arr[i];
		}
		Date::DatePoint dp;
		dp.ad = d > 0;
		dp.day = toUShort(std::abs(d));
		dp.month = toUShort(m);
		dp.year = y;

		Time::TimePoint tp;
		tp.hours = toUShort(h);
		tp.minutes = toUShort(mi);
		tp.milliseconds = toUShort(mil);
		tp.microseconds = toUShort(mic);
		tp.nanoseconds = toUShort(nan);

		Assign(dp, tp);
	}
	void DateTime::Assign(const Date::DatePoint& dp, const Time::TimePoint& tp)
	{
		date.Assign(dp);
		time.Assign(tp);
	}
	void DateTime::Assign(const Date& date, const Time& time)
	{
		this->date = date;
		this->time = time;
	}

	bool DateTime::IsLeap() const
	{
		return date.IsLeap();
	}

	DateTime& DateTime::SetAllDays(const long long v)
	{
		date.Assign(v);
		return *this;
	}
	DateTime& DateTime::SetDay(const unsigned short v)
	{
		date.SetDay(v);
		return *this;
	}
	DateTime& DateTime::SetMonth(const unsigned short v)
	{
		date.SetMonth(v);
		return *this;
	}
	DateTime& DateTime::SetYear(const long long v)
	{
		date.SetYear(v);
		return *this;
	}
	DateTime& DateTime::SetDate(const Date& v)
	{
		date = v;
		return *this;
	}
	DateTime& DateTime::SetDatePoint(const Date::DatePoint& v)
	{
		date.point = v;
		return *this;
	}
	DateTime& DateTime::SetAllNanoseconds(const long long v)
	{
		Assign(date.days, v);
		return *this;
	}
	DateTime& DateTime::SetNanoseconds(const unsigned short v)
	{
		time.SetNanoseconds(v);
		return *this;
	}
	DateTime& DateTime::SetMicroseconds(const unsigned short v)
	{
		time.SetMicroseconds(v);
		return *this;
	}
	DateTime& DateTime::SetMilliseconds(const unsigned short v)
	{
		time.SetMilliseconds(v);
		return *this;
	}
	DateTime& DateTime::SetSeconds(const unsigned short v)
	{
		time.SetSeconds(v);
		return *this;
	}
	DateTime& DateTime::SetMinutes(const unsigned short v)
	{
		time.SetMinuts(v);
		return *this;
	}
	DateTime& DateTime::SetHours(const unsigned short v)
	{
		time.SetHours(v);
		return *this;
	}
	DateTime& DateTime::SetTime(const Time& v)
	{
		time = v;
		return *this;
	}
	DateTime& DateTime::SetTimePoint(const Time::TimePoint& v)
	{
		time.point = v;
		return *this;
	}

	long long				DateTime::GetAllDays()			const
	{
		return date.days;
	}
	unsigned short			DateTime::GetDay()				const
	{
		return date.point.day;
	}
	unsigned short			DateTime::GetMonth()			const
	{
		return date.point.month;
	}
	long long				DateTime::GetYear()				const
	{
		return date.point.year;
	}
	long long				DateTime::GetWeekCount()		const
	{
		return date.GetWeekCount();
	}
	unsigned short			DateTime::GetDayWeek()			const
	{
		return date.GetDayWeek();
	}
	const Date&				DateTime::GetDate()				const
	{
		return date;
	}
	const Date::DatePoint&	DateTime::GetDatePoint()		const
	{
		return date.point;
	}
	long long				DateTime::GetAllNanoseconds()	const
	{
		return time.nanoseconds;
	}
	unsigned short			DateTime::GetNanoseconds()		const
	{
		return time.point.nanoseconds;
	}
	unsigned short			DateTime::GetMicroseconds()		const
	{
		return time.point.microseconds;
	}
	unsigned short			DateTime::GetMilliseconds()		const
	{
		return time.point.milliseconds;
	}
	unsigned short			DateTime::GetSeconds()			const
	{
		return time.point.seconds;
	}
	unsigned short			DateTime::GetMinutes()			const
	{
		return time.point.minutes;
	}
	unsigned short			DateTime::GetHours()			const
	{
		return time.point.hours;
	}
	const Time&				DateTime::GetTime()				const
	{
		return time;
	}
	const Time::TimePoint&	DateTime::GetTimePoint()		const
	{
		return time.point;
	}
	unsigned short			DateTime::GetCountDaysInMonth()	const
	{
		return date.GetCountDaysInMonth();
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
		fillStrDT(date.point.year, example, 'Y');
		fillStrDT(date.point.month, example, 'M');
		fillStrDT(date.point.day, example, 'D');
		fillStrDT(time.point.hours, example, 'h');
		fillStrDT(time.point.minutes, example, 'm');
		fillStrDT(time.point.seconds, example, 's');
		fillStrDT(time.point.milliseconds, example, 'S');
		fillStrDT(time.point.microseconds, example, 'C');
		fillStrDT(time.point.nanoseconds, example, 'N');
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
		if (date.days == dt.date.days)
		{
			if (date.days < 0)
				return time.nanoseconds > dt.time.nanoseconds;
			else
				return time.nanoseconds < dt.time.nanoseconds;
		}
		else
			return date.days < dt.date.days;
	}
	bool DateTime::operator>(const DateTime& dt) const {
		if (date.days == dt.date.days)
		{
			if (date.days < 0)
				return time.nanoseconds < dt.time.nanoseconds;
			else
				return time.nanoseconds > dt.time.nanoseconds;
		}
		else
			return date.days > dt.date.days;
	}
	bool DateTime::operator==(const DateTime& dt) const {
		return date.days == dt.date.days && time.nanoseconds == dt.time.nanoseconds;
	}
	bool DateTime::operator!=(const DateTime& dt) const {
		return !(date.days == dt.date.days && time.nanoseconds == dt.time.nanoseconds);
	}
	bool DateTime::operator<=(const DateTime& dt) const {
		return !(*this > dt);
	}
	bool DateTime::operator>=(const DateTime& dt) const {
		return !(*this < dt);
	}

	DateTime DateTime::operator+(const DateTime& dt) const {
		DateTime res(*this);
		return res += dt;
	}
	DateTime DateTime::operator-(const DateTime& dt) const {
		DateTime res(*this);
		return res -= dt;
	}

	DateTime& DateTime::operator+=(const DateTime& dt) {
		Assign(
			date.days + dt.date.days, 
			time.nanoseconds + ((date.days >= 0) ? (dt.time.nanoseconds) : (-dt.time.nanoseconds))
		);
		return *this;
	}
	DateTime& DateTime::operator-=(const DateTime& dt) {
		Assign(
			date.days - dt.date.days,
			time.nanoseconds - ((date.days >= 0) ? (dt.time.nanoseconds) : (-dt.time.nanoseconds))
		);
		return *this;
	}

	#pragma endregion

	DateTime DateTime::UnixNow()
	{
		long long nanoseconds = GetNowNanoseconds();
		return DateTime(static_cast<long long>(nanoseconds / MAX_NANOSECONDS_VALUE + 719162), static_cast<long long>(nanoseconds % MAX_NANOSECONDS_VALUE));
	}
	DateTime DateTime::SystemNow() {
		const long long nanoseconds = (GetNowNanoseconds() + static_cast<long long>(GetSystemUTC()) * (MAX_NANOSECONDS_VALUE / 24));
		return DateTime(static_cast<long long>(nanoseconds / MAX_NANOSECONDS_VALUE + 719162), static_cast<long long>(nanoseconds % MAX_NANOSECONDS_VALUE));
	}
	DateTime DateTime::MaxDateTime() {
		return DateTime(MAX_DAYS_VALUE, MAX_NANOSECONDS_VALUE-1);
	}
	DateTime DateTime::MinDateTime() {
		return DateTime(MIN_DAYS_VALUE, MAX_NANOSECONDS_VALUE - 1);
	}

	std::string DateTime::TimeZoneName()
	{
		return Date::TimeZoneName();
	}

	void DateTime::Round()
	{
		long long plus = (date.days >= 0) ? 1 : -1;
		while (time.nanoseconds >= MAX_NANOSECONDS_VALUE)
		{
			time.nanoseconds -= MAX_NANOSECONDS_VALUE;
			date.days += plus;
		}
		while (time.nanoseconds < 0)
		{
			time.nanoseconds += MAX_NANOSECONDS_VALUE;
			date.days -= plus;
		}
		if (date.days < MIN_DAYS_VALUE)
		{
			date.days = date.days % MIN_DAYS_VALUE + MAX_DAYS_VALUE + 1;
			time.nanoseconds = MAX_NANOSECONDS_VALUE - time.nanoseconds;
		}
		else if (date.days > MAX_DAYS_VALUE)
		{
			date.days = date.days % MAX_DAYS_VALUE + MIN_DAYS_VALUE - 1;
			time.nanoseconds = MAX_NANOSECONDS_VALUE - time.nanoseconds;
		}
		time.Round();
		Date::ToDate(date.point, date.days);
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