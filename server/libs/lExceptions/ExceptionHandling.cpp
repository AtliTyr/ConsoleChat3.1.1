#include "ExceptionHandling.h"

const char* bad_Authorization::what() const noexcept
{
	return "ERROR: Authorization failed";
}

const char* bad_Registration::what() const noexcept
{
	return "ERROR: Registration failed";
}

const char* bad_Recepient::what() const noexcept
{
	return "ERROR: Invalid message recipient";
}

const char* bad_Delete::what() const noexcept
{
	return "ERROR: This user cannot be deleted";
}
