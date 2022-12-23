#include <iostream>

using namespace std;

class Person
{
private:
  string name;
  int index;

public:
  Person();
  Person(string n);
  Person(string n, int i);

  string getName();
  int getIndex();

  void setName(string n);
  void setIndex(int i);
};