#pragma once

#include<string>
#include<iostream>
#include<limits>

#define MAX_DAYS_VALUE LLONG_MAX / 400 - 1
#define MIN_DAYS_VALUE LLONG_MIN / 400

namespace dt
{
	inline constexpr bool Leap(long long year);

	class Date
	{
	public:
		friend std::ostream& operator<<(std::ostream& out, const Date& date);
		friend std::istream& operator>>(std::istream& in, Date& date);
		friend unsigned CountDaysInMonth(const unsigned char month, const bool leap);
		friend class DateTime;
		
		struct DatePoint
		{
			bool ad = true;
			unsigned short day{};
			unsigned short month{};
			long long int year{};

			bool ValidDate() const;

		};

	public:

		#pragma region Конструкторы

		Date() = default;
		Date(const Date& other) = default;
		Date(const std::string& date);
		Date(const std::string& date, const std::string& example);
		Date(const DatePoint& point);
		explicit	Date(long long days);

		#pragma endregion

		#pragma region Методы

		void Assign(const std::string& date);
		void Assign(const std::string& date, const std::string& example);
		void Assign(const DatePoint& point);
		void Assign(const long long int days);

		constexpr bool IsLeap() const;

		Date& SetDay(int day);
		Date& SetMonth(int month);
		Date& SetYear(long long year);
		
		long long			GetAllDays()			const;
		unsigned short		GetDay()				const;
		unsigned short		GetMonth()				const;
		long long			GetYear()				const;
		long long			GetWeekCount()			const;
		unsigned short		GetDayWeek()			const;
		unsigned short		GetCountDaysInMonth()	const;
		const DatePoint&	GetDatePoint()			const;

		Date& MakeOpposite();

		std::string ToString()						const;
		std::string ToString(std::string example)	const;

		#pragma endregion

		#pragma region Операторы

		Date& operator=(const Date& other) = default;

		bool operator==(const Date& other) const;
		bool operator!=(const Date& other) const;
		bool operator<=(const Date& other) const;
		bool operator>=(const Date& other) const;
		bool operator<(const Date& other) const;
		bool operator>(const Date& other) const;

		Date operator+(const Date& other) const;
		Date operator-(const Date& other) const;

		Date& operator+=(const Date& other);
		Date& operator-=(const Date& other);

		Date& operator++();
		Date& operator--();
		Date operator++(int);
		Date operator--(int);

		#pragma endregion

		static Date UnixNow();
		static Date SystemNow();
		static Date MaxDate();
		static Date MinDate();

	private:
		long long days = 0;
		DatePoint point;

		void Round();

		static long long ToDay(const DatePoint& point);
		static void ToDate(DatePoint& point, const long long days);

		static constexpr const unsigned char days_in_months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		static constexpr const unsigned char days_in_months_leap[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	};

	unsigned CountDaysInMonth(const unsigned char month, const bool leap = false);

	Date Opposite(Date date);

	std::ostream& operator<<(std::ostream& out, const Date& date);
	std::istream& operator>>(std::istream& in, Date& date);

	const Date operator""_date(const char* date, const size_t size);
}
