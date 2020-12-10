#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

vector<int> read_data(string file){

    ifstream ip("inputs/" + file + ".txt");
    vector<int> result;
    string s;

    while (getline(ip, s)) {
      result.push_back(stoi(s));
    }

    ip.close();
    
    return result;
}


int part1(vector<int> vec) {
  
  sort(vec.begin(), vec.end());
  int diff1 = 0;
  int diff3 = 1; // for device

  int last_el = 0;
  int this_diff;

  for (int i : vec) {
    this_diff = i - last_el;
    if (this_diff == 1)
      diff1++;
    if (this_diff == 3)
      diff3++;
    last_el = i;
  }
  return diff1 * diff3;
}


long long part2(vector<int> vec) {

  sort(vec.begin(), vec.end(), std::greater<>());
  vec.push_back(0);

  map<int, long long> path_count;

  path_count[vec.at(0)] = 1; // one path from max

  for (vector<int>::iterator it = ++vec.begin(); it != vec.end(); ++it) {
    path_count[*it] = path_count[*it+1] + path_count[*it+2] + path_count[*it+3];
  }
  
  return path_count[vec.back()];
}

void test() {
  int sol = part2(read_data("testdata10"));
  cout << "sol=" << sol << endl;
}

int main()
{
  vector<int> jolts = read_data("data10");
  cout << part1(jolts) << "\n";
  //test();
  cout << part2(jolts) << "\n";
  return 0;
}
