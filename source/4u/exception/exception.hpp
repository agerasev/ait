#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include<exception>
#include<string>

class Exception : public std::exception
{
private:
	mutable std::string temp;
public:
	Exception() noexcept
		: std::exception()
	{

	}
	virtual ~Exception() noexcept
	{

	}
	virtual const char *what() const noexcept override
	{
		return (temp = getMessage()).data();
	}

	virtual std::string getMessage() const noexcept = 0;
};

#endif // EXCEPTION_HPP
