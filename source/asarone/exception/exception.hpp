#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include<exception>
#include<string>

class Exception : public std::exception
{
public:
	Exception() noexcept
		: std::exception()
	{

	}
	virtual ~Exception() noexcept
	{

	}
	virtual const char *what() const noexcept
	{
		return "libasarone exception";
	}

	virtual std::string getMessage() const noexcept = 0;
};

#endif // EXCEPTION_HPP
