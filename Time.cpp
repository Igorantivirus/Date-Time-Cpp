#include "Time.hpp"

#include<chrono>

void fillFromStrTime(const char* time, int arr[4])
{
	if (time == nullptr) {
		return;
	}
	for (char DateCount = 0; DateCount < 4; DateCount++) {
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
void fillStrTime(const int num, std::string& res, const char c)
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
	#pragma region class Time

	const int Time::maxValue = 86400000;

	#pragma region Конструкторы

	Time::Time() : milliseconds(0) {}
	Time::Time(int milliseconds) : milliseconds(milliseconds)
	{
		Round();
	}
	Time::Time(int hours, int minuts, int seconds, int milliseconds)
	{
		Assign(hours, minuts, seconds, milliseconds);
	}
	Time::Time(const char* time)
	{
		Assign(time);
	}
	Time::Time(const std::string& time)
	{
		Assign(time);
	}
	Time::Time(const char* time, const char* example)
	{
		Assign(time, example);
	}
	Time::Time(const std::string& time, const std::string& example)
	{
		Assign(time, example);
	}
	Time::Time(const Time& other) : milliseconds(other.milliseconds) {}

	#pragma endregion

	#pragma region Методы

	void Time::Assign(int milliseconds)
	{
		this->milliseconds = milliseconds;
		Round();
	}
	void Time::Assign(int hours, int minuts, int seconds, int milliseconds)
	{
		if (!IsTimeabe(hours, minuts, seconds, milliseconds))
			return;
		this->milliseconds = ToMilliseconds(hours, minuts, seconds, milliseconds);
		Round();
	}
	void Time::Assign(const char* time)
	{
		int arr[4] = {};
		fillFromStrTime(time, arr);
		Assign(arr[0], arr[1], arr[2], arr[3]);
	}
	void Time::Assign(const std::string& time)
	{
		Assign(time.c_str());
	}
	void Time::Assign(const char* time, const char* example)
	{
		int arr[4] = {};
		fillFromStrTime(time, arr);
		int h = 0, m = 0, s = 0, mi = 0;
		for (char i = 0; i < 3 && *example != '\0'; i++)
		{
			while (*example != '\0' && *example++ != '%') {}
			if (*example == 'h')
				h = arr[i];
			else if (*example == 'm')
				m = arr[i];
			else if (*example == 's')
				s = arr[i];
			else if (*example == 'S')
				mi = arr[i];
		}
		Assign(h, m, s, mi);
	}
	void Time::Assign(const std::string& time, const std::string& example)
	{
		Assign(time.c_str(), example.c_str());
	}
	void Time::Assign(const Time& other)
	{
		milliseconds = other.milliseconds;
	}

	int Time::GetAllMilliseconds() const
	{
		return milliseconds;
	}
	int Time::GetMilliseconds() const
	{
		return milliseconds % 1000;
	}
	int Time::GetSeconds() const
	{
		return milliseconds / 1000 % 60;
	}
	int Time::GetMinuts() const
	{
		return milliseconds / 60000 % 60;
	}
	int Time::GetHours() const
	{
		return milliseconds / 3600000;
	}

	Time& Time::SetAllMilliseconds(int value)
	{
		milliseconds = value;
		Round();
		return *this;
	}
	Time& Time::SetMilliseconds(int value)
	{
		if (value >= 1000 || value < 0)
			return *this;
		milliseconds = milliseconds / 1000 * 1000 + value;
		Round();
		return *this;
	}
	Time& Time::SetSeconds(int value)
	{
		if (value >= 60 || value < 0)
			return *this;
		milliseconds = milliseconds / 60000 * 60000 + value * 1000 + milliseconds % 1000;
		Round();
		return *this;
	}
	Time& Time::SetMinuts(int value)
	{
		if (value >= 60 || value < 0)
			return *this;
		milliseconds = milliseconds / 3600000 * 3600000 + value * 60000 + milliseconds % 60000;
		Round();
		return *this;
	}
	Time& Time::SetHours(int value)
	{
		if (value >= 24 || value < 0)
			return *this;
		milliseconds = milliseconds % 3600000 + value * 3600000;
		Round();
		return *this;
	}

	Time Time::MakeOpposite()
	{
		milliseconds = 86400000 - milliseconds;
		Round();
		return *this;
	}

	std::string Time::ToString() const
	{
		int h, m, s, mi = milliseconds;
		ToTime(h, m, s, mi);
		char pr[13] = {
			char(h / 10 + '0'), char(h % 10 + '0'), ':',
			char(m / 10 + '0'), char(m % 10 + '0'), ':',
			char(s / 10 + '0'), char(s % 10 + '0'), ':',
			char(mi / 100 % 10 + '0'), char(mi / 10 % 10 + '0'), char(mi % 10 + '0'), '\0'
		};
		return std::string(pr);
	}
	std::string Time::ToString(std::string example) const
	{
		int h, m, s, mi = milliseconds;
		ToTime(h, m, s, mi);
		fillStrTime(h, example, 'h');
		fillStrTime(m, example, 'm');
		fillStrTime(s, example, 's');
		fillStrTime(mi, example, 'S');
		return example;
	}

	#pragma endregion

	#pragma region Операторы

	Time& Time::operator=(const Time& other)
	{
		milliseconds = other.milliseconds;
		return *this;
	}

	bool Time::operator==(const Time& other) const
	{
		return milliseconds == other.milliseconds;
	}
	bool Time::operator!=(const Time& other) const
	{
		return milliseconds != other.milliseconds;
	}
	bool Time::operator<(const Time& other) const
	{
		return milliseconds < other.milliseconds;
	}
	bool Time::operator>(const Time& other) const
	{
		return milliseconds > other.milliseconds;
	}
	bool Time::operator<=(const Time& other) const
	{
		return milliseconds <= other.milliseconds;
	}
	bool Time::operator>=(const Time& other) const
	{
		return milliseconds >= other.milliseconds;
	}

	Time Time::operator+(const Time& other) const
	{
		return Time(milliseconds + other.milliseconds);
	}
	Time Time::operator-(const Time& other) const
	{
		return Time(milliseconds - other.milliseconds);
	}
	Time Time::operator*(int value) const
	{
		return Time(milliseconds * value);
	}
	Time Time::operator/(int value) const
	{
		return Time(milliseconds / value);
	}
	Time Time::operator%(int value) const
	{
		return Time(milliseconds % value);
	}

	Time Time::operator+=(const Time& other)
	{
		milliseconds += other.milliseconds;
		Round();
		return *this;
	}
	Time Time::operator-=(const Time& other)
	{
		milliseconds -= other.milliseconds;
		Round();
		return *this;
	}
	Time Time::operator*=(int value)
	{
		milliseconds *= value;
		Round();
		return *this;
	}
	Time Time::operator/=(int value)
	{
		milliseconds /= value;
		Round();
		return *this;
	}
	Time Time::operator%=(int value)
	{
		milliseconds %= value;
		Round();
		return *this;
	}

	#pragma endregion

	Time Time::Now(float UTC)
	{
		return Time(
			(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() +
				static_cast<long long>(UTC * 3600000)) % 86400000
		);
	}
	Time Time::MaxTime()
	{
		return Time(maxValue - 1);
	}
	Time Time::MinTime()
	{
		return Time(0);
	}

	void Time::Round()
	{
		while (milliseconds < 0)
			milliseconds += maxValue;
		milliseconds %= 86400000;
	}

	int Time::ToMilliseconds(int hours, int minuts, int seconds, int milliseconds)
	{
		return
			milliseconds +
			seconds * 1000 +
			minuts * 60 * 1000 +
			hours * 60 * 60 * 1000;
	}
	void Time::ToTime(int& hours, int& minuts, int& seconds, int& milliseconds)
	{
		seconds = milliseconds / 1000;
		milliseconds -= seconds * 1000;
		minuts = seconds / 60;
		seconds -= minuts * 60;
		hours = minuts / 60;
		minuts -= hours * 60;
	}
	bool Time::IsTimeabe(int hours, int minuts, int seconds, int milliseconds)
	{
		return
			(hours >= 0 && hours < 24) &&
			(minuts >= 0 && minuts < 60) &&
			(seconds >= 0 && seconds < 60) &&
			(milliseconds >= 0 && milliseconds < 1000);
	}

	#pragma endregion

	Time Opposite(Time value)
	{
		return value.MakeOpposite();
	}

	void Sleep(int milliseconds) {
		long long t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + milliseconds;
		while (t > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {}
	}
	void Sleep(const Time& time) {
		return Sleep(time.GetAllMilliseconds());
	}

	std::ostream& operator<<(std::ostream& out, const Time& time)
	{
		return out << time.ToString();
	}
	std::istream& operator>>(std::istream& in, Time& time)
	{
		char pr[12] = {};
		in.getline(pr, 12);
		time.Assign(pr);
		return in;
	}

	Time operator""_time(const char* time, size_t size)
	{
		return Time(time);
	}

	Time hours(int value)
	{
		return Time(value, 0, 0, 0);
	}
	Time minuts(int value)
	{
		return Time(0, value, 0, 0);
	}
	Time seconds(int value)
	{
		return Time(0, 0, value, 0);
	}
	Time milliseconds(int value)
	{
		return Time(0, 0, 0, value);
	}
}