#include <iostream>

using namespace std;

class Person
{
private:
  string name;
  unsigned short int index;

public:
  Person(string n);
  Person(string n, unsigned short int i);

  string getName();
  unsigned short int getIndex();

  void setIndex(unsigned short int i);
};