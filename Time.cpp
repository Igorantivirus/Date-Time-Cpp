#include "Time.hpp"

namespace dt {


#pragma region class Time

Time::Time() : _milliseconds(0) {}
Time::Time(int hours, int minuts, int seconds, int milliseconds) {
	Assign(hours, minuts, seconds, milliseconds);
}
Time::Time(int milliseconds) {
	Assign(milliseconds);
}
Time::Time(const char* time) {
	Assign(time);
}
Time::Time(const std::string& time) {
	Assign(time.c_str());
}
Time::Time(const Time& time) : _milliseconds(time._milliseconds) {}

Time& Time::Assign(int hours, int minuts, int seconds, int milliseconds) {
	if (!IsTimeable(hours, minuts, seconds, milliseconds)) {
		return *this;
	}
	_milliseconds = hours * 3600000 + minuts * 60000 + seconds * 1000 + milliseconds;
	return *this;
}
Time& Time::Assign(const char* time) {
	if (time == nullptr) {
		return *this;
	}
	int arr[4] = {};
	for (int timeCount = 0; timeCount < 4; timeCount++) {
		if (time[0] == '-' || time[0] == '\0') {
			break;
		}
		arr[timeCount] = atoi(time);
		for (; time[0] >= '0' && time[0] <= '9'; time++) {}
		time++;
	}
	return Assign(arr[0], arr[1], arr[2], arr[3]);
}
Time& Time::Assign(const std::string& timeText) {
	return Assign(timeText.c_str());
}
Time& Time::Assign(int milliseconds) {
	_milliseconds = milliseconds;
	Round();
	return *this;
}
Time& Time::Assign(const Time& time) {
	_milliseconds = time._milliseconds;
	return *this;
}

int Time::AllMilliseconds() const {
	return _milliseconds;
}
int Time::Milliseconds() const {
	return _milliseconds % 1000;
}
int Time::Seconds() const {
	return _milliseconds / 1000 % 60;
}
int Time::Minutes() const {
	return _milliseconds / 60000 % 60;
}
int Time::Hours() const {
	return _milliseconds / 3600000;
}

void Time::SetAllMillieconds(int milliseconds) {
	_milliseconds = milliseconds;
	Round();
}
void Time::SetMilliseconds(int milliseconds) {
	if (milliseconds >= 1000 || milliseconds < 0) {
		return;
	}
	_milliseconds = _milliseconds / 1000 * 1000 + milliseconds;
	Round();
}
void Time::SetSeconds(int seconds) {
	if (seconds >= 60 || seconds < 0) {
		return;
	}
	_milliseconds = _milliseconds / 60000 * 60000 + seconds * 1000 + _milliseconds % 1000;
	Round();
}
void Time::SetMinutes(int minutes) {
	if (minutes >= 60 || minutes < 0) {
		return;
	}
	_milliseconds = _milliseconds / 3600000 * 3600000 + minutes * 60000 + _milliseconds % 60000;
	Round();
}
void Time::SetHours(int hours) {
	if (hours >= 24 || hours < 0) {
		return;
	}
	_milliseconds = _milliseconds % 3600000 + hours * 3600000;
	Round();
}
void Time::MakeOpposite() {
	_milliseconds = 86400000 - _milliseconds;
	Round();
}

Time& Time::operator=(const Time& time) {
	_milliseconds = time._milliseconds;
	return *this;
}

Time::operator std::string() {
	int h, m, s, mi = _milliseconds;
	ToTime(h, m, s, mi);
	char pr[13] = { char(h / 10 + '0'), char(h % 10 + '0'), ':', char(m / 10 + '0'), char(m % 10 + '0'), ':', char(s / 10 + '0'), char(s % 10 + '0'), ':', char(mi / 100 % 10 + '0'), char(mi / 10 % 10 + '0'), char(mi % 10 + '0'), '\0', };
	return std::string(pr);
}

bool Time::operator<(const Time& time) const {
	return _milliseconds < time._milliseconds;
}
bool Time::operator>(const Time& time) const {
	return _milliseconds > time._milliseconds;
}
bool Time::operator<=(const Time& time) const {
	return _milliseconds <= time._milliseconds;
}
bool Time::operator>=(const Time& time) const {
	return _milliseconds >= time._milliseconds;
}
bool Time::operator==(const Time& time) const {
	return _milliseconds == time._milliseconds;
}
bool Time::operator!=(const Time& time) const {
	return _milliseconds != time._milliseconds;
}

Time Time::operator+(const Time& time) const {
	return Time(_milliseconds + time._milliseconds);
}
Time Time::operator-(const Time& time) const {
	return Time(_milliseconds - time._milliseconds);
}
Time Time::operator*(float value) const {
	return Time(static_cast<int>(_milliseconds * value));
}
Time Time::operator/(float value) const {
	return Time(static_cast<int>(_milliseconds / value));
}
Time Time::operator%(int value) const {
	return Time(_milliseconds % value);
}

Time& Time::operator+=(const Time& time) {
	_milliseconds += time._milliseconds;
	Round();
	return *this;
}
Time& Time::operator-=(const Time& time) {
	_milliseconds -= time._milliseconds;
	Round();
	return *this;
}
Time& Time::operator*=(float value) {
	_milliseconds = static_cast<int>(_milliseconds * value);
	Round();
	return *this;
}
Time& Time::operator/=(float value) {
	_milliseconds = static_cast<int>(_milliseconds / value);
	Round();
	return *this;
}
Time& Time::operator%=(int value) {
	_milliseconds %= value;
	Round();
	return *this;
}

Time& Time::operator++() {
	_milliseconds++;
	Round();
	return *this;
}
Time& Time::operator--() {
	_milliseconds--;
	Round();
	return *this;
}
Time Time::operator++(int) {
	Time pr = *this;
	++(*this);
	return pr;
}
Time Time::operator--(int) {
	Time pr = *this;
	--(*this);
	return pr;
}

Time Time::Now(float TimeZone) {
	return Time((std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + static_cast<long long>(TimeZone * 3600000)) % 86400000);
}
Time Time::MaxTime() {
	return Time(86399999);
}
Time Time::MinTime() {
	return Time(0);
}
void Time::Round() {
	while (_milliseconds >= 86400000) {
		_milliseconds -= 86400000;
	}
	while (_milliseconds < 0.f) {
		_milliseconds += 86400000;
	}
}
void Time::ToTime(int& hours, int& minuts, int& seconds, int& milliseconds) {//переводит миллисекунды во время
	hours = minuts = seconds = 0;
	hours = milliseconds / 3600000;
	milliseconds %= 3600000;
	minuts = milliseconds / 60000;
	milliseconds %= 60000;
	seconds = milliseconds / 1000;
	milliseconds %= 1000;
}
bool Time::IsTimeable(int hours, int minuts, int seconds, int milliseconds) {
	return (hours >= 0 && hours < 24) && (minuts >= 0 && minuts < 60) && (seconds >= 0 && seconds < 60) && (milliseconds >= 0 && milliseconds < 1000);
}

#pragma endregion

std::ostream& operator<<(std::ostream& out, const Time& time) {
	int h, m, s, mi = time._milliseconds;
	time.ToTime(h, m, s, mi);
	out << char(h / 10 + '0') << char(h % 10 + '0') << ':' << char(m / 10 + '0') << char(m % 10 + '0') << ':' << char(s / 10 + '0') << char(s % 10 + '0') << ':' << char(mi / 100 + '0') << char(mi / 10 % 10 + '0') << char(mi % 10 + '0');
	return out;
}
std::istream& operator>>(std::istream& in, Time& time) {
	std::string pr;
	std::getline(in, pr);
	time.Assign(pr.c_str());
	return in;
}

Time Opposite(const Time& time)
{
	return Time(86400000 - time.Milliseconds());
}

void Sleep(long long milliseconds) {
	long long t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + milliseconds;
	while (t > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {}
}
void Sleep(const Time& time) {
	return Sleep(time.Milliseconds());
}

Time Milliseconds(int count) {
	return Time(count);
}
Time Seconds(int count) {
	return Time(count * 1000);
}
Time Minutes(int count) {
	return Time(count * 60000);
}
Time Hours(int count) {
	return Time(count * 3600000);
}

Time operator""_milliseconds(unsigned long long value) {
	return Time(static_cast<int>(value));
}
Time operator""_seconds(unsigned long long value) {
	return Time(static_cast<int>(value) * 1000);
}
Time operator""_minutes(unsigned long long value) {
	return Time(static_cast<int>(value) * 60000);
}
Time operator""_hours(unsigned long long value) {
	return Time(static_cast<int>(value) * 3600000);
}
Time operator""_time(const char* time, size_t len) {
	return Time(time);
}
}
