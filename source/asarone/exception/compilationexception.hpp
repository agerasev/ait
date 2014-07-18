#ifndef COMPILATIONEXCEPTION_HPP
#define COMPILATIONEXCEPTION_HPP

#include"exception.hpp"
#include<string>

class CompilationException : public Exception
{
private:
	const std::string message;
public:
	CompilationException(const std::string &m) noexcept
		: Exception(), message(m)
	{

	}
	virtual ~CompilationException() noexcept
	{

	}
	std::string getMessage() const noexcept
	{
		return "Compilation exception:\n" + message;
	}
};

#endif // COMPILATIONEXCEPTION_HPP
