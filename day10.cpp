#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

vector<int> read_data(string file){

    ifstream ip("inputs/" + file + ".txt");
    vector<int> result;
    int s;

    while (ip >> s) {
      result.push_back(s);
    }

    ip.close();
    
    return result;
}


int part1(vector<int> vec) {
  
  sort(vec.begin(), vec.end());

  adjacent_difference(vec.begin(), vec.end(), vec.begin());
  
  int diff1 = count(vec.begin(), vec.end(), 1);
  int diff3 = count(vec.begin(), vec.end(), 3) + 1; // +1 for last adaptor to device

  return diff1 * diff3;
}


long long part2(vector<int> vec) {

  sort(vec.begin(), vec.end(), std::greater<>());
  vec.push_back(0);

  map<int, long long> path_count;

  path_count[vec.at(0)] = 1; // one path from max
  vec.erase(vec.begin()); // max already added to map, don't have to skip in following loop

  for (int j : vec)
    path_count[j] = path_count[j+1] + path_count[j+2] + path_count[j+3];
    
  return path_count[vec.back()];
}

int test() {
  return part2(read_data("testdata10"));
}

int main()
{
  vector<int> jolts = read_data("data10");
  cout << part1(jolts) << "\n";
  assert(test()==19208);
  cout << part2(jolts) << "\n";
  return 0;
}
