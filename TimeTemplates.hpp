#pragma once

#include<chrono>
#include<string>
#include<iostream>

namespace dt
{
	#pragma region TimePoint

	template<typename Duration = std::chrono::seconds>
	struct TimePoint
	{
		static_assert(
			std::is_same_v<Duration, std::chrono::seconds> ||
			std::is_same_v<Duration, std::chrono::milliseconds> ||
			std::is_same_v<Duration, std::chrono::microseconds> ||
			std::is_same_v<Duration, std::chrono::nanoseconds>,
			"Invalid duration type for TimePoint");

		unsigned short hours{};
		unsigned short minutes{};
		unsigned short seconds{};

		bool ValidTime() const
		{
			return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60 && seconds >= 0 && seconds < 60;
		}

		static constexpr const long long int roundConstant = 86400;
	};

	template<>
	struct TimePoint<std::chrono::milliseconds>
	{
		unsigned short hours{};
		unsigned short minutes{};
		unsigned short seconds{};
		unsigned short milliseconds{};

		bool ValidTime() const
		{
			return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60 && seconds >= 0 && seconds < 60 && milliseconds >= 0 && milliseconds < 1000;
		}

		static constexpr const long long int roundConstant = 86400000;
	};

	template<>
	struct TimePoint<std::chrono::microseconds>
	{
		unsigned short hours{};
		unsigned short minutes{};
		unsigned short seconds{};
		unsigned short milliseconds{};
		unsigned short microseconds{};

		bool ValidTime() const
		{
			return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60 && seconds >= 0 && seconds < 60 && milliseconds >= 0 && milliseconds < 1000 && microseconds >= 0 && microseconds < 1000;
		}

		static constexpr const long long int roundConstant = 86400000000;
	};

	template<>
	struct TimePoint<std::chrono::nanoseconds>
	{
		unsigned short hours{};
		unsigned short minutes{};
		unsigned short seconds{};
		unsigned short milliseconds{};
		unsigned short microseconds{};
		unsigned short nanoseconds{};

		bool ValidTime() const
		{
			return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60 && seconds >= 0 && seconds < 60 && milliseconds >= 0 && milliseconds < 1000 && microseconds >= 0 && microseconds < 1000 && nanoseconds >= 0 && nanoseconds < 1000;
		}

		static constexpr const long long int roundConstant = 86400000000000;
	};

	#pragma endregion

	template<typename Duration = std::chrono::seconds>
	class TimeT
	{
		static_assert(
			std::is_same_v<Duration, std::chrono::seconds> ||
			std::is_same_v<Duration, std::chrono::milliseconds> ||
			std::is_same_v<Duration, std::chrono::microseconds> ||
			std::is_same_v<Duration, std::chrono::nanoseconds>,
			"Invalid duration type for TimePoint");
	public:
		TimeT() = default;
		TimeT(const TimeT& other) = default;
		TimeT(const long long int v)
		{
			SetValueTime(v);
		}
		TimeT(const TimePoint<Duration>& p)
		{
			Assign(p);
		}
	
		#pragma region methods

		Time& MakeOpposite()
		{
			value = TimePoint<Duration>::roundConstant - value;
			ToTime(point, value);
			return *this;
		}

		const std::string ToString() const
		{
			std::string res;
			res.reserve(8);
			res += static_cast<char>(point.hours / 10) + '0';
			res += static_cast<char>(point.hours % 10) + '0';
			res += ':';
			res += static_cast<char>(point.minutes / 10) + '0';
			res += static_cast<char>(point.minutes % 10) + '0';
			res += ':';
			res += static_cast<char>(point.seconds / 10) + '0';
			res += static_cast<char>(point.seconds % 10) + '0';
			return res;
		}

		#pragma region Get
	
		const long long int& GetAllTimeValue() const
		{
			return value;
		}
		const TimePoint<Duration>& GetTimePoint() const
		{
			return point;
		}

		const int GetHours() const
		{
			return point.hours;
		}
		const int GetMinutes() const
		{
			return point.minutes;
		}
		const int GetSeconds() const
		{
			return point.seconds;
		}
	
		template<typename D = Duration>
		typename std::enable_if<
			std::is_same<D, std::chrono::milliseconds>::value ||
			std::is_same<D, std::chrono::microseconds>::value ||
			std::is_same<D, std::chrono::nanoseconds>::value, const int
		>::type GetMilliseconds() const
		{
			return point.milliseconds;
		}
	
		template<typename D = Duration>
		typename std::enable_if<
			std::is_same<D, std::chrono::microseconds>::value ||
			std::is_same<D, std::chrono::nanoseconds>::value, const int
		>::type GetMicroseconds() const
		{
			return point.microseconds;
		}
	
		template<typename D = Duration>
		typename std::enable_if<
			std::is_same<D, std::chrono::nanoseconds>::value, const int
		>::type GetNanoseconds() const
		{
			return point.nanoseconds;
		}
	
		#pragma endregion
	
		#pragma region Set
	
		void SetValueTime(const long long int v)
		{
			value = v;
			Round(value);
			ToTime(point, value);
		}
		void SetTimePoint(const TimePoint<Duration>& p)
		{
			if (!p.ValidTime())
				return;
			point = p;
			value = ToValue(point);
		}

		void SetHours(const int hours)
		{
			if (hours < 0 || hours >= 24)
				return;
			point.hours = hours;
			value = ToValue(point);
		}
		void SetMinutes(const int minutes)
		{
			if (minutes < 0 || minutes >= 60)
				return;
			point.minutes = minutes;
			value = ToValue(point);
		}
		void SetSeconds(const int seconds)
		{
			if (seconds < 0 || seconds >= 60)
				return;
			point.seconds = seconds;
			value = ToValue(point);
		}
	
		template<typename D = Duration>
		typename std::enable_if<
			std::is_same<D, std::chrono::milliseconds>::value ||
			std::is_same<D, std::chrono::microseconds>::value ||
			std::is_same<D, std::chrono::nanoseconds>::value, void
		>::type SetMilliseconds(const int millliseconds)
		{
			if (millliseconds < 0 || millliseconds >= 1000)
				return;
			point.millliseconds = millliseconds;
			value = ToValue(point);
		}
	
		template<typename D = Duration>
		typename std::enable_if<
			std::is_same<D, std::chrono::microseconds>::value ||
			std::is_same<D, std::chrono::nanoseconds>::value, void
		>::type SetMicroseconds(const int microseconds)
		{
			if (microseconds < 0 || microseconds >= 1000)
				return;
			point.microseconds = microseconds;
			value = ToValue(point);
		}
	
		template<typename D = Duration>
		typename std::enable_if<
			std::is_same<D, std::chrono::nanoseconds>::value, void
		>::type SetNanoseconds(const int nanoseconds)
		{
			if (nanoseconds < 0 || nanoseconds >= 1000)
				return;
			point.nanoseconds = nanoseconds;
			value = ToValue(point);
		}
	
		#pragma endregion

		#pragma endregion

		#pragma region operators
	
		TimeT& operator=(const TimeT& other) = default;
	
		#pragma region bool

		bool operator==(const TimeT& other) const
		{
			return value == other.value;
		}
		bool operator!=(const TimeT& other) const
		{
			return value != other.value;
		}
		bool operator<=(const TimeT& other) const
		{
			return value <= other.value;
		}
		bool operator>=(const TimeT& other) const
		{
			return value >= other.value;
		}
		bool operator<(const TimeT& other) const
		{
			return value < other.value;
		}
		bool operator>(const TimeT& other) const
		{
			return value > other.value;
		}
	
		TimeT& operator+=(const TimeT& other)
		{
			Assign(value + other.value);
			return *this;
		}
		TimeT& operator-=(const TimeT& other)
		{
			Assign(value - other.value);
			return *this;
		}
	
		#pragma endregion

		TimeT operator+(const TimeT& other) const
		{
			Time res(*this);
			return res += other;
		}
		TimeT operator-(const TimeT& other) const
		{
			Time res(*this);
			return res -= other;
		}

		friend std::ostream& operator<<(std::ostream& out, const TimeT<Duration>& t)
		{
			return out << t.ToString();
		}

		#pragma endregion

		#pragma region static

		static const TimeT UnixNow()
		{
			return TimeT(std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch()).count());
		}
		static const TimeT SystemNow()
		{
			return TimeT(
				std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch()).count() +
				static_cast<long long int>(SystemUTC() * (TimePoint<Duration>::roundConstant / 24))
			);
		}
		static const float SystemUTC()
		{
			static const float res = UTCOneCall();
			return res;
		}

		static const TimeT MaxTime()
		{
			return TimeT(TimePoint<Duration>::roundConstant - 1);
		}
		static const TimeT MinTime()
		{
			return TimeT(0);
		}

		#pragma endregion

	private:
		long long int value{};
		TimePoint<Duration> point;

		static void Round(long long int& value)
		{
			value %= TimePoint<Duration>::roundConstant;
			if (value < 0)
				value += TimePoint<Duration>::roundConstant;
		}

		static long long int ToValue(const TimePoint<Duration>& point)
		{
			return point.hours * 60LL * 60LL +
				point.minutes * 60LL +
				point.seconds;
		}
		static void ToTime(TimePoint<Duration>& point, long long int value)
		{
			long long int hours{}, minutes{};
		
			minutes = value / 60;
			value -= minutes * 60;
		
			hours = minutes / 60;
			minutes -= hours * 60;
		
			point.hours = static_cast<int>(hours);
			point.minutes = static_cast<int>(minutes);
			point.seconds = static_cast<int>(value);
		}

	private:
		static float UTCOneCall()
		{
			time_t now = time(nullptr);
			tm localTime1, localTime2;
			localtime_s(&localTime1, &now);
			gmtime_s(&localTime2, &now);
			if (localTime1.tm_hour == 0)
				localTime1.tm_hour = 24;
			if (localTime2.tm_hour == 0)
				localTime2.tm_hour = 24;
			return
				((localTime1.tm_hour * 3600 + localTime1.tm_min * 60 + localTime1.tm_sec) -
					(localTime2.tm_hour * 3600 + localTime2.tm_min * 60 + localTime2.tm_sec)) / 3600.f;
		}
	};

	#pragma region ToString

	template<>
	const std::string TimeT<std::chrono::milliseconds>::ToString() const
	{
		std::string res;
		res.reserve(12);
		res += point.hours / 10 + '0';
		res += point.hours % 10 + '0';
		res += ':';
		res += point.minutes / 10 + '0';
		res += point.minutes % 10 + '0';
		res += ':';
		res += point.seconds / 10 + '0';
		res += point.seconds % 10 + '0';
		res += ':';
		res += point.milliseconds / 100 + '0';
		res += point.milliseconds / 10 % 10 + '0';
		res += point.milliseconds % 10 + '0';
		return res;
	}
	template<>
	const std::string TimeT<std::chrono::microseconds>::ToString() const
	{
		std::string res;
		res.reserve(16);
		res += point.hours / 10 + '0';
		res += point.hours % 10 + '0';
		res += ':';
		res += point.minutes / 10 + '0';
		res += point.minutes % 10 + '0';
		res += ':';
		res += point.seconds / 10 + '0';
		res += point.seconds % 10 + '0';
		res += ':';
		res += point.milliseconds / 100 + '0';
		res += point.milliseconds / 10 % 10 + '0';
		res += point.milliseconds % 10 + '0';
		res += ':';
		res += point.microseconds / 100 + '0';
		res += point.microseconds / 10 % 10 + '0';
		res += point.microseconds % 10 + '0';
		return res;
	}
	template<>
	const std::string TimeT<std::chrono::nanoseconds>::ToString() const
	{
		std::string res;
		res.reserve(20);
		res += static_cast<char>(point.hours / 10 + '0');
		res += static_cast<char>(point.hours % 10 + '0');
		res += ':';
		res += static_cast<char>(point.minutes / 10 + '0');
		res += static_cast<char>(point.minutes % 10 + '0');
		res += ':';
		res += static_cast<char>(point.seconds / 10 + '0');
		res += static_cast<char>(point.seconds % 10 + '0');
		res += ':';
		res += static_cast<char>(point.milliseconds / 100 + '0');
		res += static_cast<char>(point.milliseconds / 10 % 10 + '0');
		res += static_cast<char>(point.milliseconds % 10 + '0');
		res += ':';
		res += static_cast<char>(point.microseconds / 100 + '0');
		res += static_cast<char>(point.microseconds / 10 % 10 + '0');
		res += static_cast<char>(point.microseconds % 10 + '0');
		res += ':';
		res += static_cast<char>(point.nanoseconds / 100 + '0');
		res += static_cast<char>(point.nanoseconds / 10 % 10 + '0');
		res += static_cast<char>(point.nanoseconds % 10 + '0');
		return res;
	}

	#pragma endregion

	#pragma region ToValue

	template<>
	long long int TimeT<std::chrono::milliseconds>::ToValue(const TimePoint<std::chrono::milliseconds>& point)
	{
		return point.hours * 60LL * 60LL * 1000LL +
			point.minutes * 60LL * 1000LL +
			point.seconds * 1000LL +
			point.milliseconds;
	}
	template<>
	long long int TimeT<std::chrono::microseconds>::ToValue(const TimePoint<std::chrono::microseconds>& point)
	{
		return point.hours * 60LL * 60LL * 1000LL * 1000LL +
			point.minutes * 60LL * 1000LL * 1000LL +
			point.seconds * 1000LL * 1000LL +
			point.milliseconds * 1000LL +
			point.microseconds;
	}
	template<>
	long long int TimeT<std::chrono::nanoseconds>::ToValue(const TimePoint<std::chrono::nanoseconds>& point)
	{
		return point.hours * 60LL * 60LL * 1000LL * 1000LL * 1000LL +
			point.minutes * 60LL * 1000LL * 1000LL * 1000LL +
			point.seconds * 1000LL * 1000LL * 1000LL +
			point.milliseconds * 1000LL * 1000LL +
			point.microseconds * 1000LL +
			point.nanoseconds;
	}

	#pragma endregion

	#pragma region ToTime

	template<>
	void TimeT<std::chrono::milliseconds>::ToTime(TimePoint<std::chrono::milliseconds>& point, long long int value)
	{
		long long int hours{}, minutes{}, seconds{};

		seconds = value / 1000;
		value -= seconds * 1000;

		minutes = seconds / 60;
		seconds -= minutes * 60;

		hours = minutes / 60;
		minutes -= hours * 60;

		point.hours = static_cast<int>(hours);
		point.minutes = static_cast<int>(minutes);
		point.seconds = static_cast<int>(seconds);
		point.milliseconds = static_cast<int>(value);
	}
	template<>
	void TimeT<std::chrono::microseconds>::ToTime(TimePoint<std::chrono::microseconds>& point, long long int value)
	{
		long long int hours{}, minutes{}, seconds{}, milliseconds{};

		milliseconds = value / 1000;
		value -= milliseconds * 1000;

		seconds = milliseconds / 1000;
		milliseconds -= seconds * 1000;

		minutes = seconds / 60;
		seconds -= minutes * 60;

		hours = minutes / 60;
		minutes -= hours * 60;

		point.hours = static_cast<int>(hours);
		point.minutes = static_cast<int>(minutes);
		point.seconds = static_cast<int>(seconds);
		point.milliseconds = static_cast<int>(milliseconds);
		point.microseconds = static_cast<int>(value);
	}
	template<>
	void TimeT<std::chrono::nanoseconds>::ToTime(TimePoint<std::chrono::nanoseconds>& point, long long int value)
	{
		long long int microseconds = value / 1000;
		value -= microseconds * 1000;

		long long int milliseconds = microseconds / 1000;
		microseconds -= milliseconds * 1000;

		long long int seconds = milliseconds / 1000;
		milliseconds -= seconds * 1000;

		long long int minutes = seconds / 60;
		seconds -= minutes * 60;

		long long int hours = minutes / 60;
		minutes -= hours * 60;

		point.hours = static_cast<int>(hours);
		point.minutes = static_cast<int>(minutes);
		point.seconds = static_cast<int>(seconds);
		point.milliseconds = static_cast<int>(milliseconds);
		point.microseconds = static_cast<int>(microseconds);
		point.nanoseconds = static_cast<int>(value);
	}

	#pragma endregion

}

using TimeS = dt::TimeT<std::chrono::seconds>;
using TimeMILS = dt::TimeT<std::chrono::milliseconds>;
using TimeMICS = dt::TimeT<std::chrono::microseconds>;
using TimeNANS = dt::TimeT<std::chrono::nanoseconds>;