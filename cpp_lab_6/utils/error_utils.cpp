#include "error_utils.h"

int checkNumber(std::istream &inputStream)
{
    while (true)
    {
        try
        {
            int firstChar = inputStream.peek();
            if (firstChar == '0')
            {
                inputStream.get();
                int next = inputStream.peek();

                if (next != '\n')
                    throw InputException(
                        "leading zeros are not allowed",
                        NUMBER_FORMAT_EXCEPTION_CODE);

                inputStream.ignore(INT_MAX, '\n');
                return 0;
            }

            int value;
            inputStream >> value;

            if (inputStream.fail() || inputStream.peek() != '\n')
                throw InputException(
                    "invalid number format",
                    NUMBER_FORMAT_EXCEPTION_CODE);

            inputStream.ignore(INT_MAX, '\n');
            return value;
        }
        catch (InputException &e)
        {
            inputStream.clear();
            inputStream.ignore(INT_MAX, '\n');
            e.printCause();
            std::cerr << std::endl;
        }
    }
}

int checkNumber(std::istream &inputStream, int minValue, int maxValue)
{
    while (true)
    {
        try
        {
            int value = checkNumber(inputStream);
            if (value < minValue || value > maxValue)
                throw InputException("number out of allowed range",
                                     OUT_OF_RANGE_EXCEPTION_CODE);
            return value;
        }
        catch (InputException &e)
        {
            e.printCause();
            std::cerr << std::endl;
        }
    }
}

bool isEnglishLetter(char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

std::string checkEnglishMultiWord(std::istream &inputStream,
                                  const char *message)
{
    while (true)
    {
        try
        {
            std::string s;
            std::cout << message;
            std::getline(inputStream, s);

            if (inputStream.fail())
                throw InputException("stream error",
                                     STRING_FORMAT_EXCEPTION_CODE);

            if (s.empty())
                throw InputException("empty string",
                                     STRING_FORMAT_EXCEPTION_CODE);

            if (s.front() == ' ' || s.back() == ' ')
                throw InputException("leading or trailing spaces",
                                     STRING_FORMAT_EXCEPTION_CODE);

            bool prevSpace = false;
            bool hasLetter = false;

            for (char c : s)
            {
                if (c == ' ')
                {
                    if (prevSpace)
                        throw InputException("double spaces are forbidden",
                                             STRING_FORMAT_EXCEPTION_CODE);
                    prevSpace = true;
                }
                else if (isEnglishLetter(c))
                {
                    hasLetter = true;
                    prevSpace = false;
                }
                else
                {
                    throw InputException("invalid character (only A-Z a-z and spaces)",
                                         STRING_FORMAT_EXCEPTION_CODE);
                }
            }

            if (!hasLetter)
                throw InputException("string contains no letters",
                                     STRING_FORMAT_EXCEPTION_CODE);

            return s;
        }
        catch (InputException &e)
        {
            e.printCause();
            std::cerr << std::endl;
        }
    }
}

std::string checkAlphaNumericSingleWord(std::istream &inputStream,
                                        const char *message)
{
    while (true)
    {
        try
        {
            std::string s;
            std::cout << message;
            std::getline(inputStream, s);

            if (s.empty())
                throw InputException("empty string",
                                     STRING_FORMAT_EXCEPTION_CODE);

            for (char c : s)
            {
                if (!isEnglishLetter(c) && !isDigit(c))
                    throw InputException("only english letters and digits allowed",
                                         STRING_FORMAT_EXCEPTION_CODE);
            }

            return s;
        }
        catch (InputException &e)
        {
            e.printCause();
            std::cerr << std::endl;
        }
    }
}
