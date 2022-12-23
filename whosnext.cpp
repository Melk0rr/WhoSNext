#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "class/Person.class.hpp"

#define print(s) (cout << s)

using namespace std;

bool contains(vector<int> arr, int value)
{
  for (int i = 0; i < arr.size(); i++)
  {
    if (arr[i] == value)
    {
      return true;
    }
  }
  return false;
}

vector<int> indexDiff(vector<int> a, vector<int> b)
{
  vector<int> diff;

  for (int i = 0; i < a.size(); i++)
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

void order(vector<Person> &rankedPeople, vector<Person> &unrankedPeople, vector<int> places)
{
  srand(time(0));
  random_shuffle(places.begin(), places.end());

  for (int i = 0; i < unrankedPeople.size(); i++)
  {
    unrankedPeople[i].setIndex(places[i]);
    rankedPeople.push_back(unrankedPeople[i]);
  }

  sort(rankedPeople.begin(), rankedPeople.end(), [](Person &p1, Person &p2) -> bool
       { return p1.getIndex() < p2.getIndex(); });
}

void readLines(const char *filename)
{
  ifstream file(filename);

  vector<Person> ranked, unranked;
  vector<int> indexes, usedIndexes;

  int i = 0;
  string s;
  while (getline(file, s))
  {

    Person p;
    if (s.find(',') != string::npos)
    {
      vector<string> splitLine = split(s, ',');
      int index = stoi(splitLine[0]);
      p.setName(splitLine[1]);
      p.setIndex(index);

      ranked.push_back(p);
      usedIndexes.push_back(index);
    }
    else
    {
      p.setName(s);
      unranked.push_back(p);
    }
    indexes.push_back(i);
    i++;
  }

  order(ranked, unranked, indexDiff(indexes, usedIndexes));
  for (Person p : ranked)
  {
    print(p.getIndex() + 1 << ": " << p.getName() << "\n");
  }
}

int main(int argc, char *argv[])
{
  const char *filename = argv[1];
  readLines(filename);
}