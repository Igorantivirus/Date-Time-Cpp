#pragma once

#include<string>
#include<chrono>
#include<iostream>
namespace dt {


bool Leap(int year);

class Date
{
	friend class DateTime;
	friend std::ostream& operator<<(std::ostream& out, const DateTime& dt);
	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);
public:
	Date();
	Date(const char* date);
	Date(const std::string& date);
	Date(int days);
	Date(int day, int month, int year);
	Date(const Date& date);

	Date& Assign(int day, int month, int year);
	Date& Assign(const char* date);
	Date& Assign(const std::string& date);
	Date& Assign(int days);
	Date& Assign(const Date& date);

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

	void MakeOpposite();

	Date& operator=(const Date& date);
	operator std::string();

	bool operator<(const Date& date) const;
	bool operator>(const Date& date) const;
	bool operator<=(const Date& date) const;
	bool operator>=(const Date& date) const;
	bool operator==(const Date& date) const;
	bool operator!=(const Date& date) const;

	Date operator+(const Date& date) const;
	Date operator-(const Date& date) const;
	Date operator*(int value) const;
	Date operator/(int value) const;
	Date operator%(int value) const;

	Date& operator+=(const Date& date);
	Date& operator-=(const Date& date);
	Date& operator*=(int value);
	Date& operator/=(int value);
	Date& operator%=(int value);

	Date operator++();
	Date operator--();
	Date operator++(int);
	Date operator--(int);

	static Date Now(float TimeZone = 0.f);
	static Date MaxDate();
	static Date MinDate();
private:
	int _days = 0;
	static void ToDate(int& d, int& m, int& g);
	static int ToDay(int d, int m, int g);
	static bool IsDatable(int d, int m, int g);
	static const int days_in_month[12];
	static const int days_in_month_leap[12];
	static const int sum_month_days[14];
	static const int sum_month_days_leap[14];
};

std::ostream& operator<<(std::ostream& out, const Date& date);
std::istream& operator>>(std::istream& in, Date& date);

Date Opposite(const Date& date);

Date operator""_days(unsigned long long days);
Date operator""_day(unsigned long long days);
Date operator""_month(unsigned long long months);
Date operator""_year(unsigned long long years);
Date operator""_date(const char* date, size_t len);

Date Days(int count);
}
