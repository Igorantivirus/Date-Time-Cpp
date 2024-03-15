#include "Time.hpp"

#include<chrono>

void fillFromStrTime(const char* time, unsigned short arr[6])
{
	if (time == nullptr) {
		return;
	}
	for (char DateCount = 0; DateCount < 6; DateCount++) {
		if (time[0] == '\0') {
			break;
		}
		arr[DateCount] = atoi(time);
		if (time[0] == '-') {
			time++;
		}
		for (; (time[0] >= '0' && time[0] <= '9'); time++) {}
		time++;
	}
}
void fillStrTime(const unsigned short num, std::string& res, const char c)
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

static float UTCOnceCall()
{
	time_t now = time(nullptr);
	tm localTime1, localTime2;
	localtime_s(&localTime1, &now);
	gmtime_s(&localTime2, &now);
	return
		((localTime1.tm_hour * 3600 + localTime1.tm_min * 60 + localTime1.tm_sec) -
			(localTime2.tm_hour * 3600 + localTime2.tm_min * 60 + localTime2.tm_sec)) / 3600.f;
}

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
		unsigned short arr[6] = {};
		fillFromStrTime(time.c_str(), arr);
		Assign(Time::TimePoint{arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]});
	}
	void Time::Assign(const std::string& time, const std::string& example)
	{
		unsigned short arr[6] = {};
		fillFromStrTime(time.c_str(), arr);
		int h = 0, m = 0, s = 0, mi = 0;

		const char* prExampl = example.c_str();

		for (char i = 0; i < 3 && *prExampl != '\0'; i++)
		{
			while (*prExampl != '\0' && *prExampl++ != '%') {}
			if (*prExampl == 'h')
				h = arr[i];
			else if (*prExampl == 'm')
				m = arr[i];
			else if (*prExampl == 's')
				s = arr[i];
			else if (*prExampl == 'S')
				mi = arr[i];
		}
		Assign(Time::TimePoint{ arr[0], arr[1], arr[2], arr[3], arr[4], arr[5] });
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
		fillStrTime(point.hours, example, 'h');
		fillStrTime(point.minutes, example, 'm');
		fillStrTime(point.seconds, example, 's');
		fillStrTime(point.milliseconds, example, 'S');
		fillStrTime(point.microseconds, example, 'C');
		fillStrTime(point.nanoseconds, example, 'N');
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
			std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
			static_cast<long long int>(SystemUTC()) * (MAX_NANOSECONDS_VALUE / 24)
		);
	}
	Time Time::UnixNow()
	{
		return Time(
			(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
		);
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
		static const float res = UTCOnceCall();
		return res;
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
		long long t = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + nanoseconds;
		while (t > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {}
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