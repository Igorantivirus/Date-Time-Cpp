#pragma once

#include<iostream>
#include<string>

#include"Date.hpp"
#include"Time.hpp"

namespace dt
{
	class DateTime
	{
	public:
		friend std::ostream& operator<<(std::ostream& out, const DateTime& dt);
		friend std::istream& operator>>(std::istream& in, DateTime& dt);
	public:

		#pragma region Конструкторы

		DateTime();
		DateTime(long long days, int milliseconds);
		DateTime(const char* dt);
		DateTime(const std::string& dt);
		DateTime(const char* dt, const char* example);
		DateTime(const std::string& dt, const std::string& example);
		DateTime(int days, int months, long long years, int hours, int minuts, int seconds, int milliseconds);
		DateTime(int days, int months, long long years);
		DateTime(int hours, int minuts, int seconds, int milliseconds);
		DateTime(const Date& date, const Time& time);
		DateTime(const Date& date);
		DateTime(const Time& time);
		DateTime(const DateTime& other);

		#pragma endregion

		#pragma region Методы

		void Assign(long long days, int milliseconds);
		void Assign(const char* dt);
		void Assign(const std::string& dt);
		void Assign(const char* dt, const char* example);
		void Assign(const std::string& dt, const std::string& example);
		void Assign(int days, int months, long long years, int hours, int minuts, int seconds, int milliseconds);
		void Assign(int days, int months, long long years);
		void Assign(int hours, int minuts, int seconds, int milliseconds);
		void Assign(const Date& date, const Time& time);
		void Assign(const Date& date);
		void Assign(const Time& time);
		void Assign(const DateTime& other);

		bool IsLeap() const;

		DateTime& SetAllDays(long long days);
		DateTime& SetDay(int day);
		DateTime& SetMonth(int month);
		DateTime& SetYear(long long year);
		DateTime& SetDate(const Date& date);
		DateTime& SetAllMilliseconds(int value);
		DateTime& SetMilliseconds(int value);
		DateTime& SetSeconds(int value);
		DateTime& SetMinuts(int value);
		DateTime& SetHours(int value);
		DateTime& SetTime(const Time& time);

		long long	GetAllDays()			const;
		int			GetDay()				const;
		int			GetMonth()				const;
		long long	GetYear()				const;
		int			GetWeekCount()			const;
		int			GetDayWeek()			const;
		Date		GetDate()				const;
		int			GetAllMilliseconds()	const;
		int			GetMilliseconds()		const;
		int			GetSeconds()			const;
		int			GetMinuts()				const;
		int			GetHours()				const;
		Time		GetTime()				const;
		unsigned	GetCountDaysInMonth()	const;

		DateTime& MakeOpposite();
		DateTime& MakeOppositeTime();
		DateTime& MakeOppositeDate();

		std::string ToString() const;
		std::string ToString(std::string example) const;

		#pragma endregion

		#pragma region Операторы

		operator Date() const;
		operator Time() const;

		DateTime& operator=(const DateTime& other);

		bool operator==(const DateTime& dt) const;
		bool operator!=(const DateTime& dt) const;
		bool operator<=(const DateTime& dt) const;
		bool operator>=(const DateTime& dt) const;
		bool operator<(const DateTime& other) const;
		bool operator>(const DateTime& other) const;

		DateTime operator+(const DateTime& dt) const;
		DateTime operator-(const DateTime& dt) const;
		DateTime operator*(long long value) const;
		DateTime operator/(long long value) const;

		DateTime& operator+=(const DateTime& dt);
		DateTime& operator-=(const DateTime& dt);
		DateTime& operator*=(long long value);
		DateTime& operator/=(long long value);

		#pragma endregion

		static DateTime Now();
		static DateTime MaxDateTime();
		static DateTime MinDateTime();

	private:
		Date date;
		Time time;

		void Round();
	};

	std::ostream& operator<<(std::ostream& out, const DateTime& dt);
	std::istream& operator>>(std::istream& in, DateTime& dt);

	DateTime Opposite(DateTime dt);
	DateTime OppositeTime(DateTime time);
	DateTime OppositeDate(DateTime date);

	DateTime operator""_dt(const char* dt, size_t size);
}