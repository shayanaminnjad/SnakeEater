#pragma once

class UnCopyable
{
protected:
	UnCopyable() = default;
	~UnCopyable() = default;
	
	UnCopyable(const UnCopyable&) = delete;
	UnCopyable& operator=(const UnCopyable&) = delete;
};
