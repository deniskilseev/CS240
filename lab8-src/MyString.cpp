
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include "MyString.h"

// My own implementation of strlen
int MyString::slength(const char *s) const
{
  int counter = 0;
  while (*(s + counter) != '\0')
  {
    counter++;
  }
  return counter;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void MyString::initialize(const char *s)
{
  int length = slength(s);
  MyString::_s = new char[200];
  for (int i = 0; i < length; i++)
  {
    *(_s + i) = *(s + i);
  }
  *(_s + length) = '\0';
}

// Create a MyString from a C string
MyString::MyString(const char *s)
{
  initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  _s = new char[1];
  *_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator=(const MyString &other)
{
  if (this != &other) // protect against invalid self-assignment
  {
    // deallocate old memory
    delete[] _s;

    // Initialize _s with the "other" object.
    initialize(other._s);

    // by convention, always return *this
    return *this;
  }
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
  // Add implementation here
  char *string = this->_s;
  int length = slength(this->_s);
  MyString *emptyString = new MyString();
  int index = 0;
  if (i > length)
  {
    return *emptyString;
  }
  char *substring = new char[n];
  int last;
  for (int k = 0; k < n; k++)
  {
    substring[k] = *(string + i + k);
    last = k;
  }
  substring[last + 1] = '\0';
  MyString *returnString = new MyString(substring);
  return *returnString;

  // Make sure that i is not beyond the end of string

  // Allocate memory for substring

  // Copy characters of substring

  // Return substring
}

// Remove at most n chars starting at location i
void MyString::remove(int i, int n)
{
  char *string = this->_s;
  int length = slength(this->_s);
  int index = 0;
  if (i > length)
  {
    return;
  }
  char *newString = new char[length - n];
  int last;
  for (int k = 0; k < i; k++)
  {
    newString[k] = *string;
    string++;
    last = k;
  }
  last++;
  for (int k = 0; k < n; k++)
  {
    if (*string == '\0')
    {
      newString[last] = '\0';
      this->_s = newString;
      return;
    }
    string++;
  }
  while (*string != '\0')
  {
    newString[last++] = *string;
    string++;
  }
  newString[last + 1] = '\0';
  this->_s = newString;
}

// Return true if strings "this" and s are equal
bool MyString::operator==(const MyString &s)
{
  char *string1 = this->_s;
  char *string2 = s._s;
  if (slength(string1) != slength(string2))
  {
    return false;
  }
  for (int i = 0; i < slength(string1); i++)
  {
    if (*string1 != *string2)
    {
      return false;
    }
    string1++;
    string2++;
  }
  return true;
}

// Return true if strings "this" and s are not equal
bool MyString::operator!=(const MyString &s)
{
  char *string1 = this->_s;
  char *string2 = s._s;
  if (slength(string1) != slength(string2)) {
    return false;
  }
  for (int i = 0; i < slength(string1); i++)
  {
    if (*string1 != *string2)
    {
      return true;
    }
    string1++;
    string2++;
  }
  return false;
}

// Return true if string "this" and s is less or equal
bool MyString::operator<=(const MyString &s)
{
  char *string1 = this->_s;
  char *string2 = s._s; 
  if (this == &s) {
    return true;
  }
  while (*string1!= '\0' && *string2 != '\0') {
    if (*string1 == *string2) {
      string1++;
      string2++;
      continue;
    }
    if (*string1 < *string2) {
      return true;
    }
    else {
      return false;
    }

    string1++;
    string2++;
  }
  if (*string1 == '\0') {
    return true;
  }
  return false;
}

// Return true if string "this" is greater than s
bool MyString::operator>(const MyString &s)
{
  return !(this<=&s);
}


// Return character at position i.  Return '\0' if out of bounds.
char MyString::operator[](int i)
{
 char *string1 = this->_s;
 if (i > slength(string1)) {
  return '\0';
 }
 for (int k = 0; k < i; k++) {
  string1++;
 }
  return *string1;
}

// Return C representation of string
const char *
MyString::cStr()
{
  const char *string1 = this->_s;
  return string1;
}

// Get string length of this string.
int MyString::length() const
{
  // Add implementation here
  return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
  // Add implementation here
  delete[] _s;
}

// Concatanate two strings (non member method)
MyString operator+(const MyString &s1, const MyString &s2)
{
  char *string1 = s1._s;
  char *string2 = s2._s; 
  int cat = s1.length()+s2.length();
  char * s = new char[cat+1];
  int index = 0;
  for (int i = 0; i < s1.length(); i++) {
    s[index++] = *string1;
    string1++; 
  }
  for (int i = 0; i < s2.length(); i++) {
    s[index++] = *string2;
    string2++; 
  }
  s[index] = '\0';
  MyString * string = new MyString(s);
  return *string;
  // Add implementation here

  // Allocate memory for the concatenated string

  // Add s1

  // Add s2
}
