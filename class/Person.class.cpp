#include <iostream>
#include "Person.class.hpp"

using namespace std;

Person::Person()
{
}

Person::Person(string n)
{
  name = n;
}

Person::Person(string n, int i)
{
  name = n;
  index = i;
}

string Person::getName()
{
  return name;
}

int Person::getIndex()
{
  return index;
}

void Person::setName(string s)
{
  name = s;
}

void Person::setIndex(int i)
{
  index = i;
}