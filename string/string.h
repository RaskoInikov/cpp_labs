#ifndef STRING_H
#define STRING_H
#include <iostream>

class String
{
private:
  char *data;
  unsigned int length;

public:
  String();
  explicit String(const char *);
  String(const String &other);
  String(String &&other) noexcept;
  ~String();

  String &operator=(const String &other);
  String &operator=(String &&other) noexcept;

  String operator+(const String &other) const;
  String operator+(const char *other) const;

  String &operator+=(const String &other);
  String &operator+=(const char *other);
  String operator()(int start, int end);

  bool operator==(const String &other);
  bool operator!=(const String &other);
  bool operator<(const String &other);
  bool operator>(const String &other);
  bool operator<=(const String &other);
  bool operator>=(const String &other);

  char operator[](unsigned int index) const;

  friend std::ostream &operator<<(std::ostream &os, const String &s);
  friend std::istream &operator>>(std::istream &is, String &s);
  friend String operator+(const char *lhs, const String &rhs);

  String &operator++();
  String &operator--();
};

#endif