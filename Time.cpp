#include "Time.hpp"

#include"DateTimeHelpers.hpp"

namespace dt
{
	#pragma region class Time

	bool Time::TimePoint::ValidTime() const
	{
		return hours < 24 && minutes < 60 && seconds < 60 && milliseconds < 1000 && microseconds < 1000 && nanoseconds < 1000;
	}

	#pragma region Конструкторы

	Time::Time(const long long n)
	{
		Assign(n);
	}
	Time::Time(const Time::TimePoint& p)
	{
		Assign(p);
	}
	Time::Time(const std::string& time)
	{
		Assign(time);
	}
	Time::Time(const std::string& time, const std::string& example)
	{
		Assign(time, example);
	}

	#pragma endregion

	#pragma region Методы

	void Time::Assign(const long long n)
	{
		nanoseconds = n;
		Round();
	}
	void Time::Assign(const Time::TimePoint& p)
	{
		if (!p.ValidTime())
			return;
		point = p;
		nanoseconds = ToNanoseconds(point);
	}
	void Time::Assign(const std::string& time)
	{
		long long arr[6] = {};
		fillFromStrDT(time.c_str(), arr, 6);
		Assign(Time::TimePoint{ toUShort(arr[0]), toUShort(arr[1]), toUShort(arr[2]), toUShort(arr[3]), toUShort(arr[4]), toUShort(arr[5])});
	}
	void Time::Assign(const std::string& time, const std::string& example)
	{
		long long arr[6] = { 1,1,1,0,0,0 };
		fillFromStrDT(time.c_str(), arr, 6);
		const char* exmpl = example.c_str();
		long long h = 0, mi = 0, s = 0, mil = 0, mic = {}, nan = {};
		for (auto i = 0; i < 7 && *exmpl != '\0'; i++)
		{
			while (*exmpl != '\0' && *exmpl++ != '%') {}
			if (*exmpl == 'h')
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

		Time::TimePoint tp;
		tp.hours = h;
		tp.minutes = mi;
		tp.milliseconds = mil;
		tp.microseconds = mic;
		tp.nanoseconds = nan;

		Assign(tp);
	}

	const long long int Time::GetAllNanoseconds() const
	{
		return nanoseconds;
	}
	const Time::TimePoint& Time::GetTimePoint() const
	{
		return point;
	}

	const unsigned short Time::GetHours()			const
	{
		return point.hours;
	}
	const unsigned short Time::GetMinutes()			const
	{
		return point.minutes;
	}
	const unsigned short Time::GetSeconds()			const
	{
		return point.seconds;
	}
	const unsigned short Time::GetMilliseconds()	const
	{
		return point.milliseconds;
	}
	const unsigned short Time::GetMicroseconds()	const
	{
		return point.microseconds;
	}
	const unsigned short Time::GetNanoseconds()		const
	{
		return point.nanoseconds;
	}

	Time& Time::SetHours(const unsigned short v)
	{
		if (v < 0 && v >= 24)
			return *this;
		point.hours = v;
		nanoseconds = ToNanoseconds(point);
		return *this;
	}
	Time& Time::SetMinuts(const unsigned short v)
	{
		if (v < 0 && v >= 60)
			return *this;
		point.minutes = v;
		nanoseconds = ToNanoseconds(point);
		return *this;
	}
	Time& Time::SetSeconds(const unsigned short v)
	{
		if (v < 0 && v >= 60)
			return *this;
		point.seconds = v;
		nanoseconds = ToNanoseconds(point);
		return *this;
	}
	Time& Time::SetMilliseconds(const unsigned short v)
	{
		if (v < 0 && v >= 1000)
			return *this;
		point.milliseconds = v;
		nanoseconds = ToNanoseconds(point);
		return *this;
	}
	Time& Time::SetMicroseconds(const unsigned short v)
	{
		if (v < 0 && v >= 1000)
			return *this;
		point.microseconds = v;
		nanoseconds = ToNanoseconds(point);
		return *this;
	}
	Time& Time::SetNanoseconds(const unsigned short v)
	{
		if (v < 0 && v >= 1000)
			return *this;
		point.nanoseconds = v;
		nanoseconds = ToNanoseconds(point);
		return *this;
	}

	Time Time::MakeOpposite()
	{
		nanoseconds = MAX_NANOSECONDS_VALUE - nanoseconds;
		Round();
		return *this;
	}

	std::string Time::ToString() const
	{
		char pr[21] = {
			char(point.hours / 10 + '0'), char(point.hours % 10 + '0'), ':',
			char(point.minutes / 10 + '0'), char(point.minutes % 10 + '0'), ':',
			char(point.seconds / 10 + '0'), char(point.seconds % 10 + '0'), ':',
			char(point.milliseconds / 100 % 10 + '0'), char(point.milliseconds / 10 % 10 + '0'), char(point.milliseconds % 10 + '0'), ':',
			char(point.microseconds / 100 % 10 + '0'), char(point.microseconds / 10 % 10 + '0'), char(point.microseconds % 10 + '0'), ':',
			char(point.nanoseconds / 100 % 10 + '0'), char(point.nanoseconds / 10 % 10 + '0'), char(point.nanoseconds % 10 + '0'), '\0'
		};
		return std::string(pr);
	}
	std::string Time::ToString(std::string example) const
	{
		fillStrDT(point.hours, example, 'h');
		fillStrDT(point.minutes, example, 'm');
		fillStrDT(point.seconds, example, 's');
		fillStrDT(point.milliseconds, example, 'S');
		fillStrDT(point.microseconds, example, 'C');
		fillStrDT(point.nanoseconds, example, 'N');
		return example;
	}

	#pragma endregion

	#pragma region Операторы

	bool Time::operator==(const Time& other) const
	{
		return nanoseconds == other.nanoseconds;
	}
	bool Time::operator!=(const Time& other) const
	{
		return nanoseconds != other.nanoseconds;
	}
	bool Time::operator<(const Time& other) const
	{
		return nanoseconds < other.nanoseconds;
	}
	bool Time::operator>(const Time& other) const
	{
		return nanoseconds > other.nanoseconds;
	}
	bool Time::operator<=(const Time& other) const
	{
		return nanoseconds <= other.nanoseconds;
	}
	bool Time::operator>=(const Time& other) const
	{
		return nanoseconds >= other.nanoseconds;
	}

	Time Time::operator+(const Time& other) const
	{
		Time res(*this);
		return res += other;
	}
	Time Time::operator-(const Time& other) const
	{
		Time res(*this);
		return res -= other;
	}
	Time Time::operator*(int value) const
	{
		Time res(*this);
		return res *= value;
	}
	Time Time::operator/(int value) const
	{
		Time res(*this);
		return res /= value;
	}

	Time Time::operator+=(const Time& other)
	{
		nanoseconds += other.nanoseconds;
		Round();
		return *this;
	}
	Time Time::operator-=(const Time& other)
	{
		nanoseconds -= other.nanoseconds;
		Round();
		return *this;
	}
	Time Time::operator*=(int value)
	{
		nanoseconds *= value;
		Round();
		return *this;
	}
	Time Time::operator/=(int value)
	{
		nanoseconds /= value;
		Round();
		return *this;
	}

	#pragma endregion

	Time Time::SystemNow()
	{
		return Time(
			GetNowNanoseconds() + static_cast<long long int>(SystemUTC()) * (MAX_NANOSECONDS_VALUE / 24)
		);
	}
	Time Time::UnixNow()
	{
		return Time(GetNowNanoseconds());
	}
	Time Time::MaxTime()
	{
		return Time(MAX_NANOSECONDS_VALUE - 1);
	}
	Time Time::MinTime()
	{
		return Time(0);
	}
	float Time::SystemUTC()
	{
		return GetSystemUTC();
	}

	void Time::Round()
	{
		nanoseconds %= MAX_NANOSECONDS_VALUE;
		if (nanoseconds < 0)
			nanoseconds += MAX_NANOSECONDS_VALUE;
		ToTime(point, nanoseconds);
	}

	long long Time::ToNanoseconds(const Time::TimePoint& point)
	{
		return point.hours * 60LL * 60LL * 1000LL * 1000LL * 1000LL +
			point.minutes * 60LL * 1000LL * 1000LL * 1000LL +
			point.seconds * 1000LL * 1000LL * 1000LL +
			point.milliseconds * 1000LL * 1000LL +
			point.microseconds * 1000LL +
			point.nanoseconds;
	}
	void Time::ToTime(Time::TimePoint& point, long long nanoseconds)
	{
		long long int microseconds = nanoseconds / 1000;
		nanoseconds -= microseconds * 1000;

		long long int milliseconds = microseconds / 1000;
		microseconds -= milliseconds * 1000;

		long long int seconds = milliseconds / 1000;
		milliseconds -= seconds * 1000;

		long long int minutes = seconds / 60;
		seconds -= minutes * 60;

		long long int hours = minutes / 60;
		minutes -= hours * 60;

		point.hours = static_cast<int>(hours);
		point.minutes = static_cast<int>(minutes);
		point.seconds = static_cast<int>(seconds);
		point.milliseconds = static_cast<int>(milliseconds);
		point.microseconds = static_cast<int>(microseconds);
		point.nanoseconds = static_cast<int>(nanoseconds);
	}

	#pragma endregion

	Time Opposite(Time value)
	{
		return value.MakeOpposite();
	}

	void Sleep(const long long int nanoseconds) {
		long long t = GetNowNanoseconds() + nanoseconds;
		while (t > GetNowNanoseconds()) {}
	}
	void Sleep(const Time& time) {
		return Sleep(time.GetAllNanoseconds());
	}

	std::ostream& operator<<(std::ostream& out, const Time& time)
	{
		return out << time.ToString();
	}
	std::istream& operator>>(std::istream& in, Time& time)
	{
		char pr[21] = {};
		in.getline(pr, 21);
		time.Assign(pr);
		return in;
	}

	Time operator""_time(const char* time, size_t size)
	{
		return Time(time);
	}

	Time hours(const long long value)
	{
		return Time(value * 1000 * 1000 * 1000 * 60 * 60);
	}
	Time minutes(const long long value)
	{
		return Time(value * 1000 * 1000 * 1000 * 60);
	}
	Time seconds(const long long value)
	{
		return Time(value * 1000 * 1000 * 1000);
	}
	Time milliseconds(const long long value)
	{
		return Time(value * 1000 * 1000);
	}
	Time microseconds(const long long value)
	{
		return Time(value * 1000);
	}
	Time nanoseconds(const long long value)
	{
		return Time(value);
	}
}