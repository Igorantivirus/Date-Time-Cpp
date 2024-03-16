#include "Date.hpp"

#include"DateTimeHelpers.hpp"

namespace dt
{
	inline const bool Leap(const long long year)
	{
		return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	}

	unsigned CountDaysInMonth(const unsigned char month, const bool leap)
	{
		if (month == 0 || month > 12)
			return 0U;
		return leap ? Date::days_in_months_leap[month - 1] : Date::days_in_months[month - 1];
	}

	#pragma region class Date

	bool Date::DatePoint::ValidDate() const
	{
		if (year <= 0 || month > 12 || day > 31)
			return false;
		if (day > (Leap(year) ? (days_in_months_leap[month - 1]) : (days_in_months[month - 1])))
			return false;
		return true;
	}

	#pragma region Конструкторы

	Date::Date(const std::string& date)
	{
		Assign(date);
	}
	Date::Date(const std::string& date, const std::string& example)
	{
		Assign(date, example);
	}
	Date::Date(const DatePoint& point)
	{
		Assign(point);
	}
	Date::Date(long long days)
	{
		Assign(days);
	}

	#pragma endregion

	#pragma region Методы

	void Date::Assign(const std::string& date)
	{
		long long arr[3] = { 1,1,1 };
		fillFromStrDT(date.c_str(), arr, 3);

		Date::DatePoint p;
		p.ad = arr[0] > 0;
		arr[0] = std::abs(arr[0]);

		p.day = toUShort(arr[0]);
		p.month = toUShort(arr[1]);
		p.year = arr[2];

		Assign(p);
	}
	void Date::Assign(const std::string& date, const std::string& example)
	{
		long long arr[3] = { 1,1,1 };
		fillFromStrDT(date.c_str(), arr, 3);
		const char* exmpl = example.c_str();
		long long d = 1, m = 1, y = 1;
		for (char i = 0; i < 3 && *exmpl != '\0'; i++)
		{
			while (*exmpl != '\0' && *exmpl++ != '%') {}
			if (*exmpl == 'D')
				d = arr[i];
			else if (*exmpl == 'M')
				m = arr[i];
			else if (*exmpl == 'Y')
				y = arr[i];
		}

		Date::DatePoint p;
		p.ad = d > 0;
		d = std::abs(d);

		p.day = toUShort(d);
		p.month = toUShort(m);
		p.year = y;

		Assign(p);
	}
	void Date::Assign(const Date::DatePoint& p)
	{
		if (!p.ValidDate())
			return;
		point = p;
		days = ToDay(point);
	}
	void Date::Assign(const long long int d)
	{
		days = d;
		Round();
	}

	bool Date::IsLeap() const
	{
		return Leap(point.year);
	}

	Date& Date::SetDay(int day)
	{
		Date::DatePoint p = point;
		p.day = day;
		Assign(p);
		return *this;
	}
	Date& Date::SetMonth(int month)
	{
		Date::DatePoint p = point;
		p.month = month;
		Assign(p);
		return *this;
	}
	Date& Date::SetYear(long long year)
	{
		Date::DatePoint p = point;
		p.year = year;
		Assign(p);
		return *this;
	}

	long long			Date::GetAllDays()			const
	{
		return days;
	}
	unsigned short		Date::GetDay()				const
	{
		return point.day;
	}
	unsigned short		Date::GetMonth()			const
	{
		return point.month;
	}
	long long			Date::GetYear()				const
	{
		return point.year;
	}
	long long			Date::GetWeekCount()		const
	{
		return static_cast<int>(std::abs(days) / 7);
	}
	unsigned short		Date::GetDayWeek()			const
	{
		if (days >= 0)
			return days % 7 + 1;
		else
			return  8 - ((std::abs(days) - 1) % 7 + 1);
	}
	unsigned short		Date::GetCountDaysInMonth()	const
	{
		return IsLeap() ? days_in_months_leap[point.month - 1] : days_in_months[point.month - 1];
	}
	const Date::DatePoint&	Date::GetDatePoint()	const
	{
		return point;
	}

	Date& Date::MakeOpposite()
	{
		days = (days + 1) * -1;
		point.ad = !point.ad;
		return *this;
	}

	std::string Date::ToString() const
	{
		std::string res = "";
		int prDay = std::abs(static_cast<int>(point.day));
		if (!point.ad)
			res = '-';
		char pr[] = { static_cast<char>(prDay / 10) + '0', static_cast<char>(prDay % 10) + '0', ':',
			static_cast<char>(point.month / 10) + '0', static_cast<char>(point.month % 10) + '0', ':', '\0'
		};
		return res += pr + std::to_string(point.year);
	}
	std::string Date::ToString(std::string example) const
	{
		fillStrDT(point.day, example, 'D');
		fillStrDT(point.month, example, 'M');
		fillStrDT(point.year, example, 'Y');
		return example;
	}

	#pragma endregion

	#pragma region Операторы

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
		Date res(*this);
		return res += other;
	}
	Date Date::operator-(const Date& other) const
	{
		Date res(*this);
		return res -= other;
	}

	Date& Date::operator+=(const Date& other)
	{
		Assign(days + other.days);
		return *this;
	}
	Date& Date::operator-=(const Date& other)
	{
		Assign(days - other.days);
		return *this;
	}

	Date&	Date::operator++()
	{
		Assign(days + 1);
		return *this;
	}
	Date&	Date::operator--()
	{
		Assign(days - 1);
		return *this;
	}
	Date	Date::operator++(int)
	{
		Date res(*this);
		Assign(days + 1);
		return res;
	}
	Date	Date::operator--(int)
	{
		Date res(*this);
		Assign(days - 1);
		return res;
	}

	#pragma endregion

	Date Date::UnixNow()
	{
		return Date(GetNowDays());
	}
	Date Date::SystemNow()
	{
		return Date(GetNowDays() + 719162);
	}
	Date Date::MaxDate()
	{
		return Date(MAX_DAYS_VALUE);
	}
	Date Date::MinDate()
	{
		return Date(MIN_DAYS_VALUE);
	}

	void Date::Round()
	{
		if (days < MIN_DAYS_VALUE)
			days = MAX_DAYS_VALUE - (MIN_DAYS_VALUE - days);
		else if (days > MAX_DAYS_VALUE)
			days = MIN_DAYS_VALUE + (days - MAX_DAYS_VALUE);
		ToDate(point, days);
	}

	long long Date::ToDay(const Date::DatePoint& point)
	{
		long long res = point.day;
		if (!point.ad)
			res++;
		const unsigned char* arr = Leap(point.year) ? days_in_months_leap : days_in_months;
		for (int i = 0; i < point.month; i++)
			res += arr[i];
		res -= arr[point.month - 1];
		long long year = point.year - 1;
		res += year * 365 + year / 4 - year / 100 + year / 400 - 1;
		return !point.ad ? -res : res;
	}
	void Date::ToDate(Date::DatePoint& point, const long long days)
	{
		long long day = days, month = 0, year = 1;
		char zn = 1;
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
		
		point.ad = (zn == 1);
		point.day = (unsigned short)day;
		point.month = (unsigned short)month;
		point.year = year;
	}
	std::string Date::TimeZoneName()
	{
		return GetTimeZoneInfo();
	}

	#pragma endregion

	std::ostream& operator<<(std::ostream& out, const Date& date)
	{
		return out << date.ToString();
	}
	std::istream& operator>>(std::istream& in, Date& date)
	{
		long long arr[3]{1, 1, 1};
		in >> arr[0] >> arr[1] >> arr[2];
		Date::DatePoint p;
		p.ad = arr[0] > 0;

		p.day = static_cast<unsigned short>(std::abs(arr[0]));
		p.month = static_cast<unsigned short>(arr[1]);
		p.year = arr[2];

		date.Assign(p);

		return in;
	}

	Date Opposite(Date date)
	{
		return date.MakeOpposite();
	}

	const Date operator""_date(const char* date, const size_t size)
	{
		return Date(date);
	}
}