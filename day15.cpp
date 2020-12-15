#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <map>
#include <cmath>
#include <bitset>

using namespace std;

vector<string> read_data(string file_num, bool testing = false){

    string filename = (testing) ? "testdata" : "data";
    filename += file_num;
    ifstream ip("inputs/" + filename + ".txt");
    vector<string> result;
    string s;

    while (getline(ip, s)) {
      result.push_back(s);
    }

    ip.close();
    
    return result;
}


long part1(vector<string> input, long tgt_el) {
  long val;
  long turn = 1;
  unordered_map<long, long> last;

  // initialize game with inputs
  stringstream ss;
  ss << input.at(0);
  for (int i; ss >> i;) {
    val = i;
    last[val] = turn++;
    if (ss.peek() == ',')
      ss.ignore();
  }


  // play the game
  long v;
  while (turn < tgt_el + 1) {
    v = (last[val] == 0) ? 0 : turn - 1 - last[val];
    last[val] = turn - 1;
    turn++;
    val = v;
  }
  return val;

}


int part2(vector<string> input) {
  return part1(input, 30000000);
}


void test() {
  vector<string> input = read_data("15", true);
  assert(part1(input, 2020)==436);
}


void test2() {
  vector<string> input = read_data("15", true);
  assert(part2(input)==175594);
}


int main()
{
  test();
  vector<string> instr = read_data("15");
  cout << part1(instr, 2020) << endl;
  //test2();
  cout << part2(instr) << endl;
  return 0;
}
