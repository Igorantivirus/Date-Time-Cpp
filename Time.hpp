#pragma once

#include<iostream>
#include<string>

namespace dt
{
	class Time
	{
		friend std::ostream& operator<<(std::ostream& out, const Time& time);
		friend std::istream& operator>>(std::istream& in, Time& time);
		friend class DateTime;
	public:

		#pragma region Конструкторы

		Time();
		Time(int milliseconds);
		Time(int hours, int minuts, int seconds, int milliseconds);
		Time(const char* time);
		Time(const std::string& time);
		Time(const char* time, const char* example);
		Time(const std::string& time, const std::string& example);
		Time(const Time& other);

		#pragma endregion

		#pragma region Методы

		void Assign(int milliseconds);
		void Assign(int hours, int minuts, int seconds, int milliseconds);
		void Assign(const char* time);
		void Assign(const std::string& time);
		void Assign(const char* time, const char* example);
		void Assign(const std::string& time, const std::string& example);
		void Assign(const Time& other);

		int GetAllMilliseconds() const;
		int GetMilliseconds() const;
		int GetSeconds() const;
		int GetMinuts() const;
		int GetHours() const;

		Time& SetAllMilliseconds(int value);
		Time& SetMilliseconds(int value);
		Time& SetSeconds(int value);
		Time& SetMinuts(int value);
		Time& SetHours(int value);

		Time MakeOpposite();

		std::string ToString() const;
		std::string ToString(std::string example) const;

		#pragma endregion

		#pragma region Операторы

		Time& operator=(const Time& other);

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
		Time operator%(int value) const;

		Time operator+=(const Time& other);
		Time operator-=(const Time& other);
		Time operator*=(int value);
		Time operator/=(int value);
		Time operator%=(int value);

		#pragma endregion

		static Time Now();
		static Time SystemNow();
		static Time MaxTime();
		static Time MinTime();
		static float UTC();

	private:
		int milliseconds = 0;
		void Round();

		static int ToMilliseconds(int hours, int minuts, int seconds, int milliseconds);
		static void ToTime(int& hours, int& minuts, int& seconds, int& milliseconds);
		static bool IsTimeabe(int hours, int minuts, int seconds, int milliseconds);
		constexpr static const int maxValue = 86400000;
	};

	Time Opposite(Time value);

	void Sleep(const Time& time);
	void Sleep(int milliseconds);

	std::ostream& operator<<(std::ostream& out, const Time& time);
	std::istream& operator>>(std::istream& in, Time& time);

	Time operator""_time(const char* time, size_t size);

	Time hours(int value);
	Time minuts(int value);
	Time seconds(int value);
	Time milliseconds(int value);
}