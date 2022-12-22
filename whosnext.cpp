#include <stdio.h>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Person.class.hpp"

using namespace std;

int *genIntArrayFromSize(int size)
{
  int *count = new int[size];
  for (int i = 0; i < size; i++)
  {
    count[i] = i;
  }
  return count;
}

int *genIntArrayFromPersonsIndex(vector<Person> &persons)
{
  int *count = new int[persons.size()];
  for (int i = 0; i < persons.size(); i++)
  {
    count[i] = persons[i].getIndex();
  }
  return count;
}

bool contains(int *arr, int value)
{
  for (int i = 0; i < sizeof(arr); i++)
  {
    if (arr[i] == value)
    {
      return true;
    }
  }
  return false;
}

vector<int> indexDiff(int *a, int *b)
{
  vector<int> diff;

  for (int i = 0; i < sizeof(a); i++)
  {
    if (!contains(b, a[i]))
    {
      diff.push_back(a[i]);
    }
  }

  return diff;
}

vector<string> split(const string &str, char delimiter)
{
  vector<string> tokens;
  stringstream tokenStream(str);
  string token;
  while (getline(tokenStream, token, delimiter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

void readLines(const char *filename, vector<string> &names, vector<int> &indexes)
{
  names.clear();
  stringstream file(filename);

  vector<Person> ranked, unranked;
  string s;
  while (getline(file, s))
  {

    if (s.find(',') != string::npos)
    {
      vector<string> splitLine = split(s, ',');
      string name = splitLine[0];
      unsigned short int index = stoi(splitLine[1]);
      Person rankedPerson(name, index);

      ranked.push_back(rankedPerson);
    }
    else
    {
      Person unrankedPerson(s);
      unranked.push_back(unrankedPerson);
    }
  }

  int *totalIndexes = genIntArrayFromSize(ranked.size() + unranked.size());
  int *rankedIndexes = genIntArrayFromPersonsIndex(ranked);
  vector<int> unrankedIndexes = indexDiff(totalIndexes, rankedIndexes);
  random_shuffle(unrankedIndexes.begin(), unrankedIndexes.end());

  for (int i = 0; i < unranked.size(); i++)
  {
    unranked[i].setIndex(unrankedIndexes[i]);
    ranked.push_back(unranked[i]);
  }

  sort(ranked.begin(), ranked.end(), [](Person &p1, Person &p2) -> bool
       { return p1.getIndex() > p2.getIndex(); });

  for (int i = 0; i < ranked.size(); i++)
  {
    string line = "\n" + (i + 1) + ranked[i].getName();
    printf(line.c_str());
  }
}

int main()
{
  const char *filename = "./src/names.txt";
  vector<string> names;
  vector<int> indexes;
  readLines(filename, names, indexes);
}