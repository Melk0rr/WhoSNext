#include <iostream>
#include "Person.class.hpp"

using namespace std;

Person::Person(string n)
{
  name = n;
}

Person::Person(string n, unsigned short int i)
{
  name = n;
  index = i;
}

string Person::getName()
{
  return name;
}

unsigned short int Person::getIndex()
{
  return index;
}

void Person::setIndex(unsigned short int i)
{
  index = i;
}