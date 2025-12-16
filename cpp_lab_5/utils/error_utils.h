#pragma once
#ifndef ERROR_UTILS_H
#define ERROR_UTILS_H

#include <iostream>
#include <climits>
#include <string>
#include "../headers/errors/InputException.h"

/* Коды ошибок (1–50 ввод) */
#define NUMBER_FORMAT_EXCEPTION_CODE 1
#define OUT_OF_RANGE_EXCEPTION_CODE 2
#define STRING_FORMAT_EXCEPTION_CODE 3

/* Числа */
int checkNumber(std::istream &inputStream);
int checkNumber(std::istream &inputStream, int minValue, int maxValue);

/* Строки */
std::string checkEnglishMultiWord(std::istream &inputStream,
                                  const char *message);

std::string checkAlphaNumericSingleWord(std::istream &inputStream,
                                        const char *message);

#endif
