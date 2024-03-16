#pragma once

#include<string>

#define toUShort(a) static_cast<unsigned short>(a)

const float& GetSystemUTC();
const std::string& GetTimeZoneInfo();

const long long GetNowNanoseconds();
const long long GetNowDays();

char fillFromStrDT(const char* dt, long long* arr, const unsigned size);
void fillStrDT(const long long num, std::string& res, const char c);