#include "DateTime.hpp"

namespace dt
{


#pragma region class DateTime

DateTime::DateTime() : _milliseconds(0), _days(0) {}
DateTime::DateTime(int day, int month, int year, int hour, int minut, int second, int millisecond) {
	Assign(day, month, year, hour, minut, second, millisecond);
}
DateTime::DateTime(const char* dt) {
	Assign(dt);
}
DateTime::DateTime(const std::string& dt) {
	Assign(dt.c_str());
}
DateTime::DateTime(int day, int month, int year) {
	Assign(day, month, year, 0, 0, 0, 0);
}
DateTime::DateTime(int hour, int minut, int seconds, int millisecond) {
	Assign(1, 1, 1, hour, minut, seconds, millisecond);
}
DateTime::DateTime(int days, int milliseconds) : _days(days), _milliseconds(milliseconds) {
	Round();
}
DateTime::DateTime(int days) : _days(days), _milliseconds(0) {}
DateTime::DateTime(const Time& time) : _milliseconds(time._milliseconds), _days(0) {}
DateTime::DateTime(const Date& date) : _milliseconds(0), _days(date._days) {}
DateTime::DateTime(const DateTime& dt) : _days(dt._days), _milliseconds(dt._milliseconds) {}

DateTime& DateTime::Assign(int day, int month, int year, int hour, int minut, int second, int millisecond) {
	if (Date::IsDatable(abs(day), abs(month), abs(year)) && Time::IsTimeable(hour, minut, second, millisecond)) {
		_days = Date::ToDay(day, month, year);
		if (year > 1) {
			_days++;
		}
		_milliseconds = hour * 3600000 + minut * 60000 + second * 1000 + millisecond;
		Round();
	}
	return *this;
}
DateTime& DateTime::Assign(const char* dt) {
	if (dt == nullptr) {
		return *this;
	}
	int arr[7] = {};
	int end = 7;
	for (size_t timeCount = 0; timeCount < 7; timeCount++) {
		if (dt[0] == '\0') {
			end = static_cast<int>(timeCount);
			break;
		}
		arr[timeCount] = atoi(dt);
		if (dt[0] == '-') {
			dt++;
		}
		for (; dt[0] >= '0' && dt[0] <= '9'; dt++) {}
		dt++;
	}
	if (end < 3 || end == 4) {
		return Assign(0, 0, 0, arr[0], arr[1], arr[2], arr[3]);
	}
	else if (end == 3) {
		if (Date::IsDatable(arr[0], arr[1], arr[2])) {
			return Assign(arr[0], arr[1], arr[2], 0, 0, 0, 0);
		}
		else {
			return Assign(0, 0, 0, arr[0], arr[1], arr[2], 0);
		}
	}
	else {
		return Assign(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
	}
}
DateTime& DateTime::Assign(const std::string& dt) {
	return Assign(dt.c_str());
}
DateTime& DateTime::Assign(int day, int month, int year) {
	return Assign(day, month, year, 0, 0, 0, 0);
}
DateTime& DateTime::Assign(int hour, int minut, int seconds, int millisecond) {
	return Assign(1, 1, 1, hour, minut, seconds, millisecond);
}
DateTime& DateTime::Assign(int days, int milliseconds) {
	_days = days;
	_milliseconds = milliseconds;
	Round();
	return *this;
}
DateTime& DateTime::Assign(int days) {
	_days = days;
	_milliseconds = 0;
	return *this;
}
DateTime& DateTime::Assign(const Time& time) {
	_milliseconds = time._milliseconds;
	_days = 0;
	return *this;
}
DateTime& DateTime::Assign(const Date& date) {
	_days = date._days;
	_milliseconds = 0;
	return *this;
}
DateTime& DateTime::Assign(const DateTime& dt) {
	_days = dt._days;
	_milliseconds = dt._milliseconds;
	return *this;
}

int DateTime::AllMilliseconds() const {
	return _milliseconds;
}
int DateTime::Milliseconds() const {
	return _milliseconds % 1000;
}
int DateTime::Seconds() const {
	return _milliseconds / 1000 % 60;
}
int DateTime::Minutes() const {
	return _milliseconds / 60000 % 60;
}
int DateTime::Hours() const {
	return _milliseconds / 3600000;
}
void DateTime::SetAllMillieconds(int milliseconds) {
	_milliseconds = milliseconds;
	Round();
}
void DateTime::SetMilliseconds(int milliseconds) {
	if (milliseconds >= 1000 || milliseconds < 0) {
		return;
	}
	_milliseconds = _milliseconds / 1000 * 1000 + milliseconds;
}
void DateTime::SetSeconds(int seconds) {
	if (seconds >= 60 || seconds < 0) {
		return;
	}
	_milliseconds = _milliseconds / 60000 * 60000 + seconds * 1000 + _milliseconds % 1000;
	Round();
}
void DateTime::SetMinutes(int minutes) {
	if (minutes >= 60 || minutes < 0) {
		return;
	}
	_milliseconds = _milliseconds / 3600000 * 3600000 + minutes * 60000 + _milliseconds % 60000;
	Round();
}
void DateTime::SetHours(int hours) {
	if (hours >= 24 || hours < 0) {
		return;
	}
	_milliseconds = _milliseconds % 3600000 + hours * 3600000;
}
bool DateTime::IsLeap() const {
	int d, m, g;
	Date::ToDate(d, m, g);
	return (!(g % 4) && (g % 100) || !(g % 400));
}
int DateTime::AllDays() const {
	return _days;
}
int DateTime::Days() const {
	int d = _days, m = 0, g = 0;
	Date::ToDate(d, m, g);
	return d;
}
int DateTime::Months() const {
	int d = _days, m = 0, g = 0;
	Date::ToDate(d, m, g);
	return m;
}
int DateTime::Years() const {
	int d = _days, m = 0, g = 0;
	Date::ToDate(d, m, g);
	return g;
}
int DateTime::Weeks() const {
	return _days / 7;
}
int DateTime::DayWeek() const {
	return (_days % 7) + 1;
}
void DateTime::SetAllDays(int days) {
	_days = days;
}
void DateTime::SetDay(int day) {
	int d = _days, m, g;
	Date::ToDate(d, m, g);
	Assign(Date::ToDay(day, m, g) + 1, _milliseconds);
}
void DateTime::SetMonth(int month) {
	int d = _days, m, g;
	Date::ToDate(d, m, g);
	Assign(Date::ToDay(d, month, g) + 1, _milliseconds);
}
void DateTime::SetYear(int year) {
	int d = _days, m, g;
	Date::ToDate(d, m, g);
	Assign(Date::ToDay(d, m, year) + 1, _milliseconds);
}
void DateTime::SetWeeks(int weeks) {
	_days = weeks * 7 - 1;
}
void DateTime::SetTime(const Time& time) {
	_milliseconds = time._milliseconds;
}
void DateTime::SetDate(const Date& time) {
	_days = time._days;
}
void DateTime::MakeOpposite() {
	_days = (_days + 1) * -1;
	_milliseconds = 86400000 - _milliseconds;
}
void DateTime::MakeOppositeDate() {
	_days = (_days + 1) * -1;
}
void DateTime::MaleOppositeTime() {
	_milliseconds = 86400000 - _milliseconds;
}

DateTime& DateTime::operator=(const DateTime& dt) {
	_days = dt._days;
	_milliseconds = dt._milliseconds;
	return *this;
}
DateTime::operator std::string() const {
	std::string result;
	int d1 = _days, m1, g1;
	if (d1 < 0) {
		result += '-';
	}
	Date::ToDate(d1, m1, g1);
	d1 = abs(d1);
	m1 = abs(m1);
	g1 = abs(g1);
	char pr1[] = { static_cast<char>(d1 / 10 + '0'), static_cast<char>(d1 % 10 + '0'), ':', static_cast<char>(m1 / 10 + '0'), static_cast<char>(m1 % 10 + '0'), ':', '\0' };
	result += pr1;
	result += std::to_string(g1) + '-';
	int h2, m2, s2, mi2 = _milliseconds;
	Time::ToTime(h2, m2, s2, mi2);
	char pr2[] = { static_cast<char>(h2 / 10 + '0'), static_cast<char>(h2 % 10 + '0'), ':' , static_cast<char>(m2 / 10 + '0'), static_cast<char>(m2 % 10 + '0'), ':' , static_cast<char>(s2 / 10 + '0'), static_cast<char>(s2 % 10 + '0'), ':' , static_cast<char>(mi2 / 100 + '0'), static_cast<char>(mi2 / 10 % 10 + '0'), static_cast<char>(mi2 % 10 + '0'), '\0' };
	result += pr2;
	return result;
}
DateTime::operator Time() const {
	return Time(_milliseconds);
}
DateTime::operator Date() const {
	return Date(_days);
}

bool DateTime::operator<(const DateTime& dt) const {
	if (_days < dt._days) {
		return true;
	}
	if (_days == dt._days) {
		if (_days < 0) {
			return _milliseconds > dt._milliseconds;
		}
		else {
			return _milliseconds < dt._milliseconds;
		}
	}
	else {
		return false;
	}
}
bool DateTime::operator>(const DateTime& dt) const {
	if (_days > dt._days) {
		return true;
	}
	if (_days == dt._days) {
		if (_days < 0) {
			return _milliseconds < dt._milliseconds;
		}
		else {
			return _milliseconds > dt._milliseconds;
		}
	}
	else {
		return false;
	}
}
bool DateTime::operator==(const DateTime& dt) const {
	return _days == dt._days && _milliseconds == dt._milliseconds;
}
bool DateTime::operator!=(const DateTime& dt) const {
	return !(_days == dt._days && _milliseconds == dt._milliseconds);
}
bool DateTime::operator<=(const DateTime& dt) const {
	return !(*this > dt);
}
bool DateTime::operator>=(const DateTime& dt) const {
	return !(*this < dt);
}

DateTime DateTime::operator+(const DateTime& dt) const {
	return DateTime(_days + dt._days, _milliseconds + ((_days >= 0) ? (dt._milliseconds) : (-dt._milliseconds)));
}
DateTime DateTime::operator-(const DateTime& dt) const {
	return DateTime(_days - dt._days, _milliseconds - ((_days >= 0) ? (dt._milliseconds) : (-dt._milliseconds)));
}
DateTime DateTime::operator*(float value) const {
	return DateTime(static_cast<int>(_days * value), static_cast<int>(_milliseconds * ((_days >= 0) ? (value) : (-value))));
}
DateTime DateTime::operator/(float value) const {
	return DateTime(static_cast<int>(_days / value), static_cast<int>(_milliseconds / ((_days >= 0) ? (value) : (-value))));
}
DateTime DateTime::operator%(int value) const {
	return DateTime(_days % value, _milliseconds % ((_days >= 0) ? (value) : (-value)));
}

DateTime& DateTime::operator+=(const DateTime& dt) {
	return Assign(_days + dt._days, _milliseconds + ((_days >= 0) ? (dt._milliseconds) : (-dt._milliseconds)));
}
DateTime& DateTime::operator-=(const DateTime& dt) {
	return Assign(_days - dt._days, _milliseconds - ((_days >= 0) ? (dt._milliseconds) : (-dt._milliseconds)));
}
DateTime& DateTime::operator*=(float value) {
	return Assign(static_cast<int>(_days * value), static_cast<int>(_milliseconds * ((_days >= 0) ? (value) : (-value))));
}
DateTime& DateTime::operator/=(float value) {
	return Assign(static_cast<int>(_days / value), static_cast<int>(_milliseconds / ((_days >= 0) ? (value) : (-value))));
}
DateTime& DateTime::operator%=(int value) {
	return Assign(_days % value, _milliseconds % ((_days >= 0) ? (value) : (-value)));
}

DateTime DateTime::Now(float TimeZone) {
	long long milliseconds = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + static_cast<long long>(TimeZone * 3600000));
	return DateTime(static_cast<int>(milliseconds / 86400000 + 719162), static_cast<int>(milliseconds % 86400000));
}
DateTime DateTime::MaxDateTime() {
	return DateTime(2147483646, 86399999);
}
DateTime DateTime::MinDateTime() {
	return DateTime(-2147483647, 86399999);
}

void DateTime::Round() {
	while (_milliseconds >= 86400000) {
		_milliseconds -= 86400000;
		if (_days >= 0) {
			_days++;
		}
		else {
			_days--;
		}
	}
	while (_milliseconds < 0) {
		_milliseconds += 86400000;
		if (_days >= 0) {
			_days--;
		}
		else {
			_days++;
		}
	}
}

#pragma endregion

std::ostream& operator<<(std::ostream& out, const DateTime& dt) {
	int d1 = dt._days, m1, g1;
	if (d1 < 0) {
		out << '-';
	}
	Date::ToDate(d1, m1, g1);
	d1 = abs(d1);
	m1 = abs(m1);
	g1 = abs(g1);
	out << d1 / 10 << d1 % 10 << ':' << m1 / 10 << m1 % 10 << ':' << g1;
	out << '-';
	int h2, m2, s2, mi2 = dt._milliseconds;
	Time::ToTime(h2, m2, s2, mi2);
	out << h2 / 10 << h2 % 10 << ':' << m2 / 10 << m2 % 10 << ':' << s2 / 10 << s2 % 10 << ':' << mi2 / 100 << mi2 / 10 % 10 << mi2 % 10;
	return out;
}
std::istream& operator>>(std::istream& in, DateTime& dt) {
	std::string pr;
	std::getline(in, pr);
	dt.Assign(pr.c_str());
	return in;
}

DateTime Opposite(const DateTime& dt) {
	return DateTime((dt._days + 1) * -1, 86400000 - dt._milliseconds);
}
DateTime OppositeDate(const DateTime& dt) {
	return DateTime((dt._days + 1) * -1, dt._milliseconds);
}
DateTime OppositeTime(const DateTime& dt) {
	return DateTime(dt._days, 86400000 - dt._milliseconds);
}

DateTime operator""_dt(const char* dt, size_t len) {
	return DateTime(dt);
}
}
