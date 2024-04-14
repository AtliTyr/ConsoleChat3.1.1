#pragma once
#include <exception>

class bad_Authorization : public std::exception
{
public:
	virtual const char* what() const noexcept override;
};

class bad_Registration : public std::exception
{
public:
	virtual const char* what() const noexcept override;
};

class bad_Recepient : public std::exception
{
public:
	virtual const char* what() const noexcept override;
};

class bad_Delete : public std::exception
{
public:
	virtual const char* what() const noexcept override;
};

