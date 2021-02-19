#pragma once
class Iterator
{
public:
	virtual int next(char flag) = 0;
	virtual bool has_next() = 0;
};