#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <cassert>

using namespace std;


vector<pair<string, int>> read_data(){

    ifstream ip("inputs/data06.txt");
    vector<pair<string, int>> result;
    string s;
    string sol = "";
    int num = 0;

    while (getline(ip, s)) {
      if (s=="") {
        result.push_back(make_pair(sol, num));
        sol = "";
        num = 0;
      } else {
        sol += s;
        num++;
      }
    }

    ip.close();
    
    return result;
}


int count_unique(string s) {
  vector<char> uniq;
  for (char c: s) {
    if (find(uniq.begin(), uniq.end(), c) == uniq.end())
      uniq.push_back(c);
  }

  return uniq.size();
}

int part1(vector<pair<string, int>> vec) {
  int sol = 0;
  for (pair<string, int> x : vec) {
    sol += count_unique(x.first);
  }
  return sol;
}


int part2(vector<pair<string,int>> vec){
  map<char, int> counter;
  int result = 0;
  for (pair<string, int> p : vec) {
    counter.clear();
    for (char c : p.first) {
      if (counter.find(c) == counter.end()) {
        counter[c] = 1;
      } else {
        counter[c]++;
      }
    }

    for (pair<char, int> x: counter) {
      if (x.second == p.second)
        result++;
    }
  }
    
  return result;
}


void test() {
  string x = "asdfa";
  cout << count_unique(x) << "\n";

}

int main()
{
  vector<pair<string, int>> answers = read_data();
  //test();
  cout << part1(answers) << "\n";
  cout << part2(answers) << "\n";
  return 0;
}
