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

		DateTime() = default;
		DateTime(const DateTime& other) = default;
		DateTime(const long long days, const long long nanoseconds);
		DateTime(const std::string& dt);
		DateTime(const std::string& dt, const std::string& example);
		DateTime(const Date::DatePoint& dp, const Time::TimePoint& tp);
		DateTime(const Date& date, const Time& time);
		DateTime(const Date& d);
		DateTime(const Time& t);

		#pragma endregion

		#pragma region Методы

		void Assign(const long long days, const long long nanoseconds);
		void Assign(const std::string& dt);
		void Assign(const std::string& dt, const std::string& example);
		void Assign(const Date::DatePoint& dp, const Time::TimePoint& tp);
		void Assign(const Date& date, const Time& time);

		bool IsLeap() const;

		DateTime& SetAllDays(const long long v);
		DateTime& SetDay(const unsigned short v);
		DateTime& SetMonth(const unsigned short v);
		DateTime& SetYear(const long long v);
		DateTime& SetDate(const Date& v);
		DateTime& SetDatePoint(const Date::DatePoint& v);
		DateTime& SetAllNanoseconds(const long long v);
		DateTime& SetNanoseconds(const unsigned short v);
		DateTime& SetMicroseconds(const unsigned short v);
		DateTime& SetMilliseconds(const unsigned short v);
		DateTime& SetSeconds(const unsigned short v);
		DateTime& SetMinutes(const unsigned short v);
		DateTime& SetHours(const unsigned short v);
		DateTime& SetTime(const Time& v);
		DateTime& SetTimePoint(const Time::TimePoint& v);

		long long				GetAllDays()			const;
		unsigned short			GetDay()				const;
		unsigned short			GetMonth()				const;
		long long				GetYear()				const;
		long long				GetWeekCount()			const;
		/*@result value from range [1;7]*/
		unsigned short			GetDayWeek()			const;
		const Date&				GetDate()				const;
		const Date::DatePoint&	GetDatePoint()			const;
		long long				GetAllNanoseconds()		const;
		unsigned short			GetNanoseconds()		const;
		unsigned short			GetMicroseconds()		const;
		unsigned short			GetMilliseconds()		const;
		unsigned short			GetSeconds()			const;
		unsigned short			GetMinutes()			const;
		unsigned short			GetHours()				const;
		const Time&				GetTime()				const;
		const Time::TimePoint&	GetTimePoint()			const;
		unsigned short			GetCountDaysInMonth()	const;

		DateTime& MakeOpposite();
		DateTime& MakeOppositeTime();
		DateTime& MakeOppositeDate();

		std::string ToString() const;
		/*
		%D - day
		%M - month
		%Y - year
		%h - hour
		%m - minute
		%s - second
		%S - millisecond
		%C - microsecond
		%N - nanosecond
		*/
		std::string ToString(std::string example) const;

		#pragma endregion

		#pragma region Операторы

		operator Date() const;
		operator Time() const;

		DateTime& operator=(const DateTime& other) = default;

		bool operator==(const DateTime& dt) const;
		bool operator!=(const DateTime& dt) const;
		bool operator<=(const DateTime& dt) const;
		bool operator>=(const DateTime& dt) const;
		bool operator<(const DateTime& other) const;
		bool operator>(const DateTime& other) const;

		DateTime operator+(const DateTime& dt) const;
		DateTime operator-(const DateTime& dt) const;

		DateTime& operator+=(const DateTime& dt);
		DateTime& operator-=(const DateTime& dt);

		#pragma endregion

		static DateTime UnixNow();
		static DateTime SystemNow();
		static DateTime MaxDateTime();
		static DateTime MinDateTime();
		static std::string TimeZoneName();

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