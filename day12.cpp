#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

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


float calc_distance(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
  

map<int, string> HEADING = {{0,"e"}, {90,"n"}, {180,"w"}, {270,"s"}};

struct Boat
{
  int heading_deg;
  string heading_str; 
  pair<int, int> waypoint;
  pair<int, int> pos;
  Boat() {
    heading_deg = 0;
    heading_str = HEADING[heading_deg];
    pos = make_pair(0, 0);
    waypoint = make_pair(10, 1);}

  void move(string cmd_str) {
    char cmd = cmd_str.at(0);
    int val = stoi(cmd_str.substr(1,cmd_str.size()));
    if (cmd=='R') {
      adjust_heading(-val);
    } else if (cmd=='L') {
      adjust_heading(val);
    } else if (cmd=='F') {
      _move(heading_str, val);
    } else if (cmd=='E') {
      _move("e", val);
    } else if (cmd=='N') {
      _move("n", val);
    } else if (cmd=='W') {
      _move("w", val);
    } else if (cmd=='S') {
      _move("s", val);
    }
  }

  void move_waypoint(string cmd_str) {
    char cmd = cmd_str.at(0);
    int val = stoi(cmd_str.substr(1,cmd_str.size()));
    if (cmd=='R') {
      rotate_waypoint(-val);
    } else if (cmd=='L') {
      rotate_waypoint(val);
    } else if (cmd=='F') {
      waypoint_hop(val);
    } else if (cmd=='E') {
      _move_waypoint("e", val);
    } else if (cmd=='N') {
      _move_waypoint("n", val);
    } else if (cmd=='W') {
      _move_waypoint("w", val);
    } else if (cmd=='S') {
      _move_waypoint("s", val);
    }
  }
  void display_pos() {
    cout << "pos:" << pos.first << ',' << pos.second << endl;
  } 
  void waypoint_hop(int x) {
    pos.first += x * waypoint.first;
    pos.second += x * waypoint.second;
  }
  void _move(string direction, int amount) {
    if (direction == "e") {
      pos.first += amount;
    } else if (direction == "n") {
      pos.second += amount;
    } else if (direction == "w") {
      pos.first -= amount;
    } else if (direction == "s") {
      pos.second -= amount;
    } else {
      assert(false);
    }
  }
  void _move_waypoint(string direction, int amount) {
    if (direction == "e") {
      waypoint.first += amount;
    } else if (direction == "n") {
      waypoint.second += amount;
    } else if (direction == "w") {
      waypoint.first -= amount;
    } else if (direction == "s") {
      waypoint.second -= amount;
    } else {
      assert(false);
    }
  }
  void rotate_waypoint(int val) {
    //cout << "way " << waypoint.first << ',' << waypoint.second;
    while (val > 0) {
      // step one anti-clock
      int x = waypoint.first;
      waypoint.first = -waypoint.second;
      waypoint.second = x;
      val -= 90;
    }
    while (val < 0) {
      // step one clockwise
      int x = waypoint.first;
      waypoint.first = waypoint.second;
      waypoint.second = -x;
      val += 90;
    }
    assert(val==0);
    //cout << " -- " << waypoint.first << ',' << waypoint.second << endl;
  }
  void adjust_heading(int val) {
    //cout << "heading : " << heading_deg << ',' << heading_str;
    heading_deg += val;
    while (heading_deg<0)
      heading_deg += 360;
    heading_deg %= 360;
    heading_str = HEADING[heading_deg];
    //cout << " -- " << heading_deg << ',' << heading_str << endl;
  }
  int get_distance() { return abs(pos.first) + abs(pos.second); }
};


int part1(vector<string> instructions) {
  Boat b;
  for (string i : instructions) {
    b.move(i);
  }
  return b.get_distance();
  
}

int part2(vector<string> instructions) {
  Boat b;
  for (string i : instructions) {
    b.move_waypoint(i);
  }
  return b.get_distance();
}


void test() {
  
  vector<string> instructions = read_data("testdata12");
  assert(part1(instructions)==25);
}

void test2() {
  
  vector<string> instructions = read_data("testdata12");
  assert(part2(instructions)==286);
}

int main()
{
  test();
  test2();
  vector<string> instr = read_data("data12");
  cout << part1(instr) << endl;
  cout << part2(instr) << endl;
  return 0;
}
