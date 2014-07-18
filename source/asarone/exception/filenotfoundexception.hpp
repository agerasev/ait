#ifndef FILENOTFOUNDEXCEPTION_HPP
#define FILENOTFOUNDEXCEPTION_HPP

#include"exception.hpp"
#include<string>

class FileNotFoundException : public Exception
{
private:
	const std::string filename;
public:
	FileNotFoundException(const std::string &fname) noexcept
		: Exception(), filename(fname)
	{

	}
	virtual ~FileNotFoundException() noexcept
	{

	}
	std::string getMessage() const noexcept
	{
		return "File " + filename + " not found";
	}
};

#endif // FILENOTFOUNDEXCEPTION_HPP
