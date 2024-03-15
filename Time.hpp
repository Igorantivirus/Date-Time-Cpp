#pragma once

#include<iostream>
#include<string>

#define MAX_NANOSECONDS_VALUE 86'400'000'000'000

namespace dt
{
	class Time
	{
	public:
		friend std::ostream& operator<<(std::ostream& out, const Time& time);
		friend std::istream& operator>>(std::istream& in, Time& time);
		friend class DateTime;
		
		struct TimePoint
		{
			unsigned short hours{};
			unsigned short minutes{};
			unsigned short seconds{};
			unsigned short milliseconds{};
			unsigned short microseconds{};
			unsigned short nanoseconds{};

			bool ValidTime() const;
		};

	public:

		#pragma region Конструкторы

		Time() = default;
		Time(const Time& other) = default;
		Time(const long long nanoseconds);
		Time(const TimePoint& point);
		Time(const std::string& time);
		Time(const std::string& time, const std::string& example);

		#pragma endregion

		#pragma region Методы

		void Assign(const long long n);
		void Assign(const TimePoint& p);
		void Assign(const std::string& time);
		void Assign(const std::string& time, const std::string& example);

		const long long int GetAllNanoseconds() const;
		const TimePoint& GetTimePoint() const;

		const unsigned short GetHours()			const;
		const unsigned short GetMinutes()		const;
		const unsigned short GetSeconds()		const;
		const unsigned short GetMilliseconds()	const;
		const unsigned short GetMicroseconds()	const;
		const unsigned short GetNanoseconds()	const;

		Time& SetHours(const unsigned short v);
		Time& SetMinuts(const unsigned short v);
		Time& SetSeconds(const unsigned short v);
		Time& SetMilliseconds(const unsigned short v);
		Time& SetMicroseconds(const unsigned short v);
		Time& SetNanoseconds(const unsigned short v);

		Time MakeOpposite();

		std::string ToString() const;
		std::string ToString(std::string example) const;

		#pragma endregion

		#pragma region Операторы

		Time& operator=(const Time& other) = default;

		bool operator==(const Time& other) const;
		bool operator!=(const Time& other) const;
		bool operator<(const Time& other) const;
		bool operator>(const Time& other) const;
		bool operator<=(const Time& other) const;
		bool operator>=(const Time& other) const;

		Time operator+(const Time& other) const;
		Time operator-(const Time& other) const;
		Time operator*(int value) const;
		Time operator/(int value) const;

		Time operator+=(const Time& other);
		Time operator-=(const Time& other);
		Time operator*=(int value);
		Time operator/=(int value);

		#pragma endregion

		static Time UnixNow();
		static Time SystemNow();

		static Time MaxTime();
		static Time MinTime();

		static float SystemUTC();

	private:
		long long nanoseconds = 0;
		TimePoint point;

		void Round();

		static long long ToNanoseconds(const TimePoint& point);
		static void ToTime(TimePoint& point, long long nanoseconds);
	};

	Time Opposite(Time value);

	void Sleep(const Time& time);
	void Sleep(const long long int nanoseconds);

	std::ostream& operator<<(std::ostream& out, const Time& time);
	std::istream& operator>>(std::istream& in, Time& time);

	Time operator""_time(const char* time, size_t size);

	Time hours(const long long value);
	Time minutes(const long long value);
	Time seconds(const long long value);
	Time milliseconds(const long long value);
	Time microseconds(const long long value);
	Time nanoseconds(const long long value);
}