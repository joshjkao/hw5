// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(
  const std::string& in,
  std::string& current,
  unsigned int index,
  unsigned int spaces,
  std::string& unmet_constraints,
  const std::set<std::string>& dict,
  std::set<std::string>& list);

// Definition of primary wordle function
std::set<std::string> wordle(
  const std::string& in,
  const std::string& floating,
  const std::set<std::string>& dict)
{
  std::set<std::string> list;
  std::string unmet_constraints = floating;
  std::string current = "";
  int index = 0;

  int spaces = 0;
  for (unsigned int i = 0; i < in.size(); i++) {
    if (in[i] == '-') spaces++;
  }
  cout << spaces << endl;
  helper(in, current, index, spaces, unmet_constraints, dict, list);
  return list;
}

// Define any helper functions here
void helper(
  const std::string& in,
  std::string& current,
  unsigned int index,
  unsigned int spaces,
  std::string& unmet_constraints,
  const std::set<std::string>& dict,
  std::set<std::string>& list)

{
  if (current.length() == in.length()) {
    if (dict.find(current) != dict.end()) {
      list.insert(current);
      return;
    }
    else {
      return;
    }
  }
  else {
    if (in[index] != '-') {
      current += in[index];
      helper(in, current, index+1, spaces, unmet_constraints, dict, list);
      current.pop_back();
      return;
    }
    else {
      for (unsigned int i = 0; i < unmet_constraints.size(); i++) {
        current += unmet_constraints[i];
        std::string temp = unmet_constraints;
        unmet_constraints.erase(i,1);
        helper(in, current, index+1, spaces-1, unmet_constraints, dict, list);
        unmet_constraints = temp;
        current.pop_back();
      }

      if (spaces-1 >= unmet_constraints.size()) {
        current += 'a';
        for (int i = 0; i < 26; i++) {
          helper(in, current, index+1, spaces-1, unmet_constraints, dict, list);
          current[index]++;
        }
        current.pop_back();
      }
      return;
    }
  }
}