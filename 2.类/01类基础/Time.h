#pragma once
class Time
{
public:
	int Hour;
	int Minute;
	int Second;
	void initTime(int tmphour, int tmpmin, int tmpsec);

private:
	int Millisecond;
private:
	void initMillTime(int mls);

};

