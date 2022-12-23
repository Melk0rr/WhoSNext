#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "class/Person.class.hpp"

#define print(s) (cout << s)

using namespace std;

/**
 * @brief Checks if an integer is present in the given integer vector
 *
 * @param arr : vector of integers
 * @param value : value to check
 * @return true : the value is present
 * @return false : the value is not present
 */
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

/**
 * @brief Returns the difference between 2 integer vectors
 *
 * @param a : first vector
 * @param b : second vector
 * @return vector<int> : difference between vector a and vector b
 */
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

/**
 * @brief Splits a string based on a given delimiter
 *
 * @param str : string to split
 * @param delimiter : character to use as delimiter
 * @return vector<string> : splitted string
 */
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

/**
 * @brief Assign indexes randomly based on available indexes
 *
 * @param rankedPeople : vector of people with already assigned indexes
 * @param unrankedPeople : vector of people without their index assigned
 * @param places : available indexes to assign
 */
void order(vector<Person> &rankedPeople, vector<Person> &unrankedPeople, vector<int> places)
{
  // Shuffles the available indexes
  srand(time(0));
  random_shuffle(places.begin(), places.end());

  // Assigning indexes and adding unranked persons to the ranked vector
  for (int i = 0; i < unrankedPeople.size(); i++)
  {
    unrankedPeople[i].setIndex(places[i]);
    rankedPeople.push_back(unrankedPeople[i]);
  }

  // Sorting based on the index
  sort(rankedPeople.begin(), rankedPeople.end(), [](Person &p1, Person &p2) -> bool
       { return p1.getIndex() < p2.getIndex(); });
}

/**
 * @brief Read the lines of a file and print them based on a computed order
 *
 * @param filename : path to the file to read
 */
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

    // If the line contains a comma : we assign name and index to the person
    if (s.find(',') != string::npos)
    {
      vector<string> splitLine = split(s, ',');
      int index = stoi(splitLine[0]);
      p.setName(splitLine[1]);
      p.setIndex(index);

      ranked.push_back(p);
      usedIndexes.push_back(index);
    }
    // If not: we only assign the name
    else
    {
      p.setName(s);
      unranked.push_back(p);
    }

    indexes.push_back(i);
    i++;
  }

  // Order names then print the result
  order(ranked, unranked, indexDiff(indexes, usedIndexes));
  for (Person p : ranked)
  {
    print(p.getIndex() + 1 << ": " << p.getName() << "\n");
  }
}

/**
 * @brief Main entry point
 *
 * @param argc
 * @param argv function arguments
 * @return int
 */
int main(int argc, char *argv[])
{
  const char *filename = argv[1];
  readLines(filename);
}