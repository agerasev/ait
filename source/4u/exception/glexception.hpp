#ifndef GLEXCEPTION_HPP
#define GLEXCEPTION_HPP

#include"exception.hpp"
#include<string>

class GLException : public Exception
{
private:
	const std::string message;
public:
	GLException(const std::string &m) noexcept
		: Exception(), message(m)
	{

	}
	virtual ~GLException() noexcept
	{

	}
	std::string getMessage() const noexcept
	{
		return "GL exception:\n" + message;
	}
};

#endif // GLEXCEPTION_HPP
