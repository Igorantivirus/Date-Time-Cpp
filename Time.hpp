#pragma once

#include<string>
#include<chrono>
#include<iostream>

namespace dt {


class Time
{
	friend class DateTime;
	friend std::ostream& operator<<(std::ostream& out, const DateTime& dt);
	friend std::ostream& operator<<(std::ostream& out, const Time& time);
	friend std::istream& operator>>(std::istream& in, Time& time);
public:
	Time();
	Time(int hours, int minuts, int seconds, int milliseconds);
	Time(int milliseconds);
	Time(const char* time);
	Time(const std::string& time);
	Time(const Time& time);

	Time& Assign(int hours, int minuts, int seconds, int milliseconds);
	Time& Assign(const char* time);
	Time& Assign(const std::string& timeText);
	Time& Assign(int milliseconds);
	Time& Assign(const Time& time);

	int AllMilliseconds() const;
	int Milliseconds() const;
	int Seconds() const;
	int Minutes() const;
	int Hours() const;

	void SetAllMillieconds(int milliseconds);
	void SetMilliseconds(int milliseconds);
	void SetSeconds(int seconds);
	void SetMinutes(int minutes);
	void SetHours(int hours);

	void MakeOpposite();

	operator std::string();
	Time& operator=(const Time& time);

	bool operator<(const Time& time) const;
	bool operator>(const Time& time) const;
	bool operator<=(const Time& time) const;
	bool operator>=(const Time& time) const;
	bool operator==(const Time& time) const;
	bool operator!=(const Time& time) const;

	Time operator+(const Time& time) const;
	Time operator-(const Time& time) const;
	Time operator*(float value) const;
	Time operator/(float value) const;
	Time operator%(int value) const;

	Time& operator+=(const Time& time);
	Time& operator-=(const Time& time);
	Time& operator*=(float value);
	Time& operator/=(float value);
	Time& operator%=(int value);

	Time& operator++();
	Time& operator--();
	Time operator++(int);
	Time operator--(int);

	static Time Now(float TimeZone = 0.f);
	static Time MaxTime();
	static Time MinTime();
private:
	int _milliseconds = 0;
	void Round();
	static void ToTime(int& hours, int& minuts, int& seconds, int& milliseconds);
	static bool IsTimeable(int hours, int minuts, int seconds, int milliseconds);
};

std::ostream& operator<<(std::ostream& out, const Time& time);
std::istream& operator>>(std::istream& in, Time& time);

Time Opposite(const Time& time);

void Sleep(long long milliseconds);
void Sleep(const Time& time);

Time Milliseconds(int count);
Time Seconds(int count);
Time Minutes(int count);
Time Hours(int count);

Time operator""_milliseconds(unsigned long long value);
Time operator""_seconds(unsigned long long value);
Time operator""_minutes(unsigned long long value);
Time operator""_hours(unsigned long long value);
Time operator""_time(const char* time, size_t len);
}
