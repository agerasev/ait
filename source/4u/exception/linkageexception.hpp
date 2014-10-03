#ifndef LINKAGEEXCEPTION_HPP
#define LINKAGEEXCEPTION_HPP

#include"exception.hpp"
#include<string>

class LinkageException : public Exception
{
private:
	const std::string message;
public:
	LinkageException(const std::string &m) noexcept
		: Exception(), message(m)
	{

	}
	virtual ~LinkageException() noexcept
	{

	}
	std::string getMessage() const noexcept
	{
		return "Linkage exception:\n" + message;
	}
};

#endif // LINKAGEEXCEPTION_HPP
