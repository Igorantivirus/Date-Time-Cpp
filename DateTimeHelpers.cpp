#include"DateTimeHelpers.hpp"

#include<chrono>

float UTCOnceCall()
{
	time_t now = time(nullptr);
	tm localTime1, localTime2;
	localtime_s(&localTime1, &now);
	gmtime_s(&localTime2, &now);
	return
		((localTime1.tm_hour * 3600 + localTime1.tm_min * 60 + localTime1.tm_sec) -
			(localTime2.tm_hour * 3600 + localTime2.tm_min * 60 + localTime2.tm_sec)) / 3600.f;
}

const float& GetSystemUTC()
{
	const float res = UTCOnceCall();
	return res;
}

const std::string& GetTimeZoneInfo()
{
	const static std::string res(std::chrono::current_zone()->name().begin(), std::chrono::current_zone()->name().end());
	return res;
}

const long long GetNowNanoseconds()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
const long long GetNowDays()
{
	return std::chrono::duration_cast<std::chrono::days>(std::chrono::system_clock::now().time_since_epoch()).count();
}

char fillFromStrDT(const char* dt, long long* arr, const unsigned size)
{
	if (dt == nullptr)
		return 0;
	char DateCount{};
	for (DateCount = 0; DateCount < size; DateCount++) {
		if (dt[0] == '\0')
			break;
		arr[DateCount] = atoll(dt);
		if (dt[0] == '-')
			dt++;
		for (; (dt[0] >= '0' && dt[0] <= '9'); dt++) {}
		dt++;
	}
	return DateCount;
}

void fillStrDT(const long long num, std::string& res, const char c)
{
	size_t pos{};
	const char pr[3] = { '%', c, '\0' };
	if ((pos = res.find(pr)) == std::string::npos)
		return;
	int count = 1;
	for (size_t i = pos + 2; i < res.size(); i++)
		if (res[i] == c)
			count++;
	std::string newV = std::to_string(num);
	if (newV.size() < count)
		newV = std::string(count - newV.size(), '0') + newV;
	res.replace(pos, count + 1, newV);
}