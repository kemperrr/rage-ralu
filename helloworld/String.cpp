#include "String.hpp"

#include <sstream>

#ifdef _WIN32
#define stricmp _stricmp
#include <stdarg.h>     // va_list, va_start, va_arg, va_end
#else
#define stricmp strcasecmp
#define vsprintf_s vsprintf
#define vsnprintf_s vsnprintf
#define sprintf_s sprintf
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#endif

#define BUFFER_SIZE 8192
#define NPOS std::string::npos // 77777? CrackHD: Find() and some other things will return actually std::string::npos, so 7777 will be incorrect ..

const size_t String::Limit = std::string::npos;

String::String(const char * szFormat, ...)
{
	Init();

	if (szFormat)
	{
		char szString[BUFFER_SIZE];
		va_list vaArgs;
		va_start(vaArgs, szFormat);
		vsnprintf_s(szString, sizeof(szString), szFormat, vaArgs);
		va_end(vaArgs);
		Set(szString);
	}
}

String::operator const char * () const
{
	return m_stdStr.c_str();
}

String& String::operator = (const char * szString)
{
	Set(szString);
	return *this;
}

String& String::operator = (const String strString)
{
	Set(strString.Get());
	return *this;
}

String& String::operator = (const unsigned char ucChar)
{
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';
	Set(szString);
	return *this;
}

String& String::operator += (const char * szString)
{
	Append(szString);
	return *this;
}

String& String::operator += (const String strString)
{
	Append(strString.Get());
	return *this;
}

String& String::operator += (const unsigned char ucChar)
{
	Append(ucChar);
	return *this;
}

String String::operator + (const char * szString) const
{
	String strNewString(*this);
	strNewString.Append(szString);
	return strNewString;
}

String String::operator + (const String strString) const
{
	String strNewString(*this);
	strNewString.Append(strString.Get());
	return strNewString;
}

String String::operator + (const unsigned char ucChar) const
{
	String strNewString(*this);
	strNewString.Append(ucChar);
	return strNewString;
}

unsigned char String::operator [] (size_t sOffset) const
{
	return GetChar(sOffset);
}

bool String::operator == (const char * szString) const
{
	return (Compare(szString) == 0);
}

bool String::operator == (const String strString) const
{
	return (Compare(strString.Get()) == 0);
}

bool String::operator != (const char * szString) const
{
	return (Compare(szString) != 0);
}

bool String::operator != (const String strString) const
{
	return (Compare(strString.Get()) != 0);
}

bool String::operator > (const char * szString) const
{
	return (Compare(szString) > 0);
}

bool String::operator > (const String strString) const
{
	return (Compare(strString.Get()) > 0);
}

bool String::operator >= (const char * szString) const
{
	return (Compare(szString) >= 0);
}

bool String::operator >= (const String strString) const
{
	return (Compare(strString.Get()) >= 0);
}

bool String::operator < (const char * szString) const
{
	return (Compare(szString) < 0);
}

bool String::operator < (const String strString) const
{
	return (Compare(strString.Get()) < 0);
}

bool String::operator <= (const char * szString) const
{
	return (Compare(szString) <= 0);
}

bool String::operator <= (const String strString) const
{
	return (Compare(strString.Get()) <= 0);
}

void String::Init()
{
	// TODO: Change no limit to 0?
	m_sLimit = Limit;
}

const char * String::Get() const
{
	return m_stdStr.c_str();
}

const char * String::C_String() const
{
	return m_stdStr.c_str();
}

void String::Set(const char * szString)
{
	// Make sure the string is valid
	if (szString)
	{
		// Set the string
		m_stdStr.assign(szString);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

void String::Set(const char * szString, size_t uiLength)
{
	// Make sure the string is valid
	if (szString)
	{
		// Ensure the length is valid
		size_t uiStringLength = strlen(szString);

		if (uiLength > uiStringLength)
			uiLength = uiStringLength;

		// Set the string
		m_stdStr.assign(szString, uiLength);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

void String::Set(const String strString)
{
	// Set the string
	m_stdStr.assign(strString.Get());

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

void String::Set(const String strString, size_t uiLength)
{
	// Ensure the length is valid
	if (uiLength > strString.GetLength())
		uiLength = strString.GetLength();

	// Set the string
	m_stdStr.assign(strString.Get(), uiLength);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

void String::Format(const char * szFormat, ...)
{
	char szString[BUFFER_SIZE];
	va_list vaArgs;
	va_start(vaArgs, szFormat);
	vsprintf_s(szString, szFormat, vaArgs);
	va_end(vaArgs);
	Set(szString);
}

size_t String::GetLength() const
{
	return m_stdStr.size();
}

bool String::IsEmpty() const
{
	return m_stdStr.empty();
}

bool String::IsNotEmpty() const
{
	return !m_stdStr.empty();
}

String& String::ToLower()
{
	for (size_t i = 0; i < GetLength(); i++)
		m_stdStr[i] = tolower(m_stdStr[i]);

	return *this;
}

bool String::IsLower() const
{
	for (size_t i = 0; i < GetLength(); i++)
	{
		unsigned char cChar = m_stdStr[i];

		if (((cChar >= 'a' && cChar <= 'Z') || (cChar >= 'A' && cChar <= 'Z')) && !islower(cChar))
			return false;
	}

	return true;
}

String& String::ToUpper()
{
	for (size_t i = 0; i < GetLength(); i++)
		m_stdStr[i] = toupper(m_stdStr[i]);

	return *this;
}

bool String::IsUpper() const
{
	for (size_t i = 0; i < GetLength(); i++)
	{
		unsigned char cChar = m_stdStr[i];

		if (((cChar >= 'a' && cChar <= 'Z') || (cChar >= 'A' && cChar <= 'Z')) && !isupper(cChar))
			return false;
	}

	return true;
}

void String::Truncate(size_t sOffset)
{
	if (sOffset < GetLength())
		m_stdStr.resize(sOffset);
}

void String::Erase(size_t sOffset, size_t sCount)
{
	m_stdStr.erase(sOffset, sCount);
}

void String::Clear()
{
	m_stdStr.clear();
}

int String::Compare(const char * szString) const
{
	return strcmp(Get(), szString);
}

int String::Compare(const String strString) const
{
	return strcmp(Get(), strString.Get());
}

int String::ICompare(const char * szString) const
{
	return stricmp(Get(), szString);
}

int String::ICompare(const String strString) const
{
	return stricmp(Get(), strString.Get());
}

bool String::ToBoolean() const
{
	if (ToInteger() == 1 || !ICompare("true"))
		return true;

	return false;
}

void String::FromBoolean(bool bValue)
{
	if (bValue)
		Set("true");
	else
		Set("false");
}

int String::ToInteger() const
{
	return atoi(Get());
}

void String::FromInteger(int iValue)
{
	char szBuffer[64];
	sprintf_s(szBuffer, "%i", iValue);
	Set(szBuffer);
}

float String::ToFloat() const
{
	return (float)atof(Get());
}

void String::FromFloat(float fValue)
{
	std::ostringstream ss;
	ss << fValue;
	Set(ss.str().c_str());
}

void String::SetChar(size_t sOffset, unsigned char cChar)
{
	// TODO: Use allocated size instead of/aswell as the string length?
	if (sOffset < GetLength())
		m_stdStr[sOffset] = cChar;
}

unsigned char String::GetChar(size_t sOffset) const
{
	// TODO: Use allocated size instead of/aswell as the string length?
	if (sOffset < GetLength())
		return m_stdStr[sOffset];

	return 0;
}

// Returns substring of this string by start index and count of symbols to copy
String String::Substring(size_t sOffset, size_t sCount) const
{
	return String(m_stdStr.substr(sOffset, sCount).c_str());
}

void String::Replace(size_t sOffset, const char * szString)
{
	// TODO:
	//m_stdStr.replace(sOffset, szString);
}

void String::Replace(size_t sOffset, String strString)
{
	// TODO:
	//m_stdStr.replace(sOffset, strString.Get());
}

// Appends current string with specified value
void String::Append(const char * szString)
{
	// Make sure the string is valid
	if (szString)
	{
		// Copy the string to the end of our string
		m_stdStr.append(szString);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

// Appends current string with specified value
void String::Append(const char * szString, size_t uiLength)
{
	// Make sure the string is valid
	if (szString)
	{
		// Ensure the length is valid
		size_t uiStringLength = strlen(szString);

		if (uiLength > uiStringLength)
			uiLength = uiStringLength;

		// Copy the string to the end of our string
		m_stdStr.append(szString, uiLength);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

// Appends current string with specified value
void String::Append(const String strString)
{
	// Copy the string to the end of our string
	m_stdStr.append(strString.Get());

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Appends current string with specified value
void String::Append(const String strString, size_t uiLength)
{
	// Ensure the length is valid
	if (uiLength > strString.GetLength())
		uiLength = strString.GetLength();

	// Copy the string to the end of our string
	m_stdStr.append(strString.Get(), uiLength);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Appends current string with specified value
void String::AppendF(const char * szFormat, ...)
{
	// Make sure the format is valid
	if (szFormat)
	{
		char szString[BUFFER_SIZE];
		va_list vaArgs;
		va_start(vaArgs, szFormat);
		vsprintf_s(szString, szFormat, vaArgs);
		va_end(vaArgs);

		// Copy the string to the end of our string
		m_stdStr.append(szString);

		// Ensure we haven't passed the string limit
		LimitTruncate();
	}
}

// Appends current string with specified value
void String::Append(const unsigned char ucChar)
{
	// Construct the string to append
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';

	// Copy the string to the end of our string
	m_stdStr.append(szString);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Inserts other string at index of this string
void String::Insert(size_t sOffset, const char * szString)
{
	m_stdStr.insert(sOffset, szString);

	// Ensure we haven't passed the string limit
	LimitTruncate();
}

// Returns index where specified substring starts, or std::string::npos if substring is not found
size_t String::Find(const char * szString, size_t sPos) const
{
	return m_stdStr.find(szString, sPos);
}

// Returns index where specified substring starts, or std::string::npos if substring is not found
size_t String::Find(const unsigned char ucChar, size_t sPos) const
{
	return m_stdStr.find(ucChar, sPos);
}

// Returns index where specified substring starts, or std::string::npos if substring is not found
size_t String::Find(const String strString, size_t sPos) const
{
	return m_stdStr.find(strString.Get(), sPos);
}

// Checks if string ends with specified substring
bool String::EndsWith(const String strSuffix) const
{
	if (m_stdStr.length() >= strSuffix.GetLength()) {
		return (0 == m_stdStr.compare(m_stdStr.length() - strSuffix.GetLength(), strSuffix.GetLength(), strSuffix.Get()));
	}
	else {
		return false;
	}
}

// Checks if one string contains another
bool String::Contains(const char * szString, size_t sPos) const
{
	return (Find(szString, sPos) != Limit);
}

// Checks if one string contains another
bool String::Contains(const unsigned char ucChar, size_t sPos) const
{
	return (Find(ucChar, sPos) != Limit);
}

// Checks if one string contains another
bool String::Contains(const String strString, size_t sPos) const
{
	return (Find(strString.Get(), sPos) != Limit);
}

size_t String::ReverseFind(const char * szString, size_t sPos) const
{
	return m_stdStr.rfind(szString, sPos);
}

size_t String::ReverseFind(const unsigned char ucChar, size_t sPos) const
{
	return m_stdStr.rfind(ucChar, sPos);
}

size_t String::ReverseFind(const String strString, size_t sPos) const
{
	return m_stdStr.rfind(strString.Get(), sPos);
}

size_t String::Substitute(const char * szString, const String strSubstitute)
{
	// Reset the find position and the instance count
	size_t uiFind = String::Limit;
	unsigned int uiInstanceCount = 0;

	// Loop until we have no more instances of the sequence left in the string
	while ((uiFind = Find(szString)) != String::Limit)
	{
		// Erase this instance of the sequence
		Erase(uiFind, strlen(szString));

		// Insert the substitute where the instance of the sequence used to be
		Insert(uiFind, strSubstitute);

		// Increment the instance count
		uiInstanceCount++;
	}

	// Return the instance count
	return uiInstanceCount;
}

size_t String::Substitute(const unsigned char ucChar, const String strSubstitute)
{
	// Construct the string to substitute
	char szString[2];
	szString[0] = ucChar;
	szString[1] = '\0';

	return Substitute(szString, strSubstitute);
}

size_t String::Substitute(const String strString, const String strSubstitute)
{
	return Substitute(strString.C_String(), strSubstitute);
}

bool String::IsNumeric() const
{
	for (size_t i = 0; i < GetLength(); i++)
	{
		unsigned char cChar = m_stdStr[i];

		if (!isdigit(cChar))
			return false;
	}

	return true;
}

bool String::SetLimit(size_t sLimit)
{
	m_sLimit = sLimit;
	return true;
}

size_t String::GetLimit() const
{
	return m_sLimit;
}

bool String::LimitTruncate()
{
	if (m_sLimit > Limit && GetLength() > m_sLimit)
	{
		m_stdStr[m_sLimit] = '\0';
		return true;
	}

	return false;
}

// NOTE: If size is less than is allocated this will
// free the extra memory, so allocate is bad naming,
// should be something along the lines of "Reallocate"
void String::Allocate(size_t sSize)
{
	// If the size is 0 or less free the buffer
	/*if(sSize == 0)
	{
	Free();
	return;
	}*/

	m_stdStr.reserve(sSize);
}

void String::Resize(size_t sSize)
{
	m_stdStr.resize(sSize);
}

void String::Free()
{
	m_stdStr.clear();
}

size_t String::GetDataSize() const
{
	return m_stdStr.capacity();
}

bool String::IsAllocated() const
{
	//return (m_stdStr->capacity() > 0);
	return true;
}

char * String::GetData() const
{
	// Better way?
	return (char *)m_stdStr.data();
}

char * String::CopyData() const
{
	char * c = new char[m_stdStr.length()];
#ifdef _WIN32
	strcpy_s(c, m_stdStr.length(), m_stdStr.c_str());
#else
	strcpy(c, m_stdStr.c_str());
#endif
	return c;
}