#pragma once

#include<string>
#include<iostream>

namespace dt
{
	inline bool Leap(long long year);

	class Date
	{
		friend std::ostream& operator<<(std::ostream& out, const Date& date);
		friend std::istream& operator>>(std::istream& in, Date& date);
		friend class DateTime;
	public:

		#pragma region Конструкторы

		Date();
		Date(const char* date);
		Date(const std::string& date);
		Date(const char* date, const char* example);
		Date(const std::string& date, const std::string& example);
		Date(int day, int month, long long year);
		Date(long long days);
		Date(const Date& other);

		#pragma endregion

		#pragma region Методы

		void Assign(const char* date);
		void Assign(const std::string& date);
		void Assign(const char* date, const char* example);
		void Assign(const std::string& date, const std::string& example);
		void Assign(int day, int month, long long year);
		void Assign(long long days);
		void Assign(const Date& other);

		bool IsLeap() const;

		Date& SetAllDays(long long days);
		Date& SetDay(int day);
		Date& SetMonth(int month);
		Date& SetYear(long long year);
		
		long long	GetAllDays()	const;
		int			GetDay()		const;
		int			GetMonth()		const;
		long long	GetYear()		const;
		int			GetWeekCount()	const;
		int			GetDayWeek()	const;

		Date& MakeOpposite();

		std::string ToString()						const;
		std::string ToString(std::string example)	const;

		#pragma endregion

		#pragma region Операторы

		Date& operator=(const Date& other);

		bool operator==(const Date& other) const;
		bool operator!=(const Date& other) const;
		bool operator<=(const Date& other) const;
		bool operator>=(const Date& other) const;
		bool operator<(const Date& other) const;
		bool operator>(const Date& other) const;

		Date operator+(const Date& other) const;
		Date operator-(const Date& other) const;
		Date operator*(long long value) const;
		Date operator/(long long value) const;
		Date operator%(long long value) const;

		Date& operator+=(const Date& other);
		Date& operator-=(const Date& other);
		Date& operator*=(long long value);
		Date& operator/=(long long value);
		Date& operator%=(long long value);

		Date& operator++();
		Date& operator--();
		Date operator++(int);
		Date operator--(int);

		#pragma endregion

		static Date Now();
		static Date MaxDate();
		static Date MinDate();

	private:
		long long days = 0;
		long long day = 1;
		long long month = 1;
		long long year = 1;

		void Round();

		static long long ToDay(long long day, long long month, long long year);
		static void ToDate(long long& day, long long& month, long long& year);
		static bool IsDatable(long long day, long long month, long long year);

		static const unsigned char days_in_months[12];
		static const unsigned char days_in_months_leap[12];

		static const long long maxValue;
		static const long long minValue;
	};

	Date Opposite(Date date);

	std::ostream& operator<<(std::ostream& out, const Date& date);
	std::istream& operator>>(std::istream& in, Date& date);

	Date operator""_date(const char* date, size_t size);
}
