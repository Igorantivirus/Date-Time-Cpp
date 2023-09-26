#pragma once

#include<string>
#include<iostream>

#include"Date.hpp"
#include"Time.hpp"

namespace dt {


class DateTime {
	friend std::ostream& operator<<(std::ostream& out, const DateTime& dt);
	friend std::istream& operator>>(std::istream& in, DateTime& dt);
	friend DateTime Opposite(const DateTime& dt);
	friend DateTime OppositeDate(const DateTime& dt);
	friend DateTime OppositeTime(const DateTime& dt);
public:
	DateTime();
	DateTime(int day, int month, int year, int hour, int minut, int second, int millisecond = 0);
	DateTime(const char* dt);
	DateTime(const std::string& dt);
	DateTime(int day, int month, int year);
	DateTime(int hour, int minut, int seconds, int millisecond);
	DateTime(int days, int milliseconds);
	DateTime(int days);
	DateTime(const Time& time);
	DateTime(const Date& date);
	DateTime(const DateTime& dt);

	DateTime& Assign(int day, int month, int year, int hour, int minut, int second, int millisecond = 0);
	DateTime& Assign(const char* dt);
	DateTime& Assign(const std::string& dt);
	DateTime& Assign(int day, int month, int year);
	DateTime& Assign(int hour, int minut, int seconds, int millisecond);
	DateTime& Assign(int days, int milliseconds);
	DateTime& Assign(int days);
	DateTime& Assign(const Time& time);
	DateTime& Assign(const Date& date);
	DateTime& Assign(const DateTime& dt);

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
	bool IsLeap() const;
	int AllDays() const;
	int Days() const;
	int Months() const;
	int Years() const;
	int Weeks() const;
	int DayWeek() const;
	void SetAllDays(int days);
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);
	void SetWeeks(int weeks);
	void SetTime(const Time& time);
	void SetDate(const Date& time);
	void MakeOpposite();
	void MakeOppositeDate();
	void MaleOppositeTime();

	DateTime& operator=(const DateTime& dt);
	operator std::string() const;
	operator Time() const;
	operator Date() const;

	bool operator<(const DateTime& dt) const;
	bool operator>(const DateTime& dt) const;
	bool operator==(const DateTime& dt) const;
	bool operator!=(const DateTime& dt) const;
	bool operator<=(const DateTime& dt) const;
	bool operator>=(const DateTime& dt) const;

	DateTime operator+(const DateTime& dt) const;
	DateTime operator-(const DateTime& dt) const;
	DateTime operator*(float value) const;
	DateTime operator/(float value) const;
	DateTime operator%(int value) const;

	DateTime& operator+=(const DateTime& dt);
	DateTime& operator-=(const DateTime& dt);
	DateTime& operator*=(float value);
	DateTime& operator/=(float value);
	DateTime& operator%=(int value);

	static DateTime Now(float TimeZone = 0.f);
	static DateTime MaxDateTime();
	static DateTime MinDateTime();
private:
	int _milliseconds = 0;
	int _days = 0;
	void Round();
};

std::ostream& operator<<(std::ostream& out, const DateTime& dt);
std::istream& operator>>(std::istream& in, DateTime& dt);

DateTime Opposite(const DateTime& dt);
DateTime OppositeDate(const DateTime& dt);
DateTime OppositeTime(const DateTime& dt);

DateTime operator""_dt(const char* dt, size_t len);
}
