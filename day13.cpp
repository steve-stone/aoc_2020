#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <chrono>

using namespace std;

vector<string> read_data(string file){

    ifstream ip("inputs/" + file + ".txt");
    vector<string> result;
    string s;

    while (ip >> s) {
      result.push_back(s);
    }

    ip.close();
    
    return result;
}

pair<vector<int>, vector<int>> parse_buses(string s) {
  vector<int> buses;
  vector<int> offsets;
  stringstream ss;
  ss << s;
  int bus;
  string tmp;
  int i = 0;

  while (getline(ss, tmp, ',')) {
    if (tmp == "x") {
      i++;
      continue;
    }
    else {
      bus = stoi(tmp);
      buses.push_back(bus);
      offsets.push_back(i);
      i++;
    }
  }
  return make_pair(buses, offsets);
}

  
int part1(vector<string> input) {
  int depart_t = stoi(input.at(0));
  vector<int> bus_vec = parse_buses(input.at(1)).first;

  int my_bus;
  int min_wait_time = 1000000;

  int wait_time;

  for (int bus : bus_vec) {
    wait_time = bus - depart_t % bus;
    if ( wait_time < min_wait_time ) {
      my_bus = bus;
      min_wait_time = wait_time;
    }
  }
  return my_bus * min_wait_time;
  
}


long long part2(vector<string> input) {
  pair<vector<int>, vector<int>> b = parse_buses(input.at(1));

  vector<int> bus_ids = b.first;
  vector<int> offsets = b.second;

  long long start = bus_ids.at(0);
  long long mult = bus_ids.at(0);

  for (size_t i = 1; i < bus_ids.size(); i++) {
    while ( (start + offsets.at(i)) % bus_ids.at(i) != 0 ) {
      start += mult;
    }
    mult *= bus_ids.at(i);
  }

  return start;
}


void test() {
  vector<string> instructions = read_data("testdata13");
  assert(part1(instructions)==295);
}

void test2() {
  vector<string> instructions = read_data("testdata13");
  assert(part2(instructions)==1068781);
  vector<string> x = {"3", "17,x,13,19"};
  assert(part2(x)==3417);
  x = {"3", "67,7,59,61"};
  assert(part2(x)==754018);
  x = {"3", "67,x,7,59,61"};
  assert(part2(x)==779210);
  x = {"3", "67,7,x,59,61"};
  assert(part2(x)==1261476);
  x = {"3", "1789,37,47,1889"};
  assert(part2(x)==1202161486);
}

int main()
{
  test();
  vector<string> instr = read_data("data13");
  cout << part1(instr) << endl;
  test2();
  cout << part2(instr) << endl;
  return 0;
}
