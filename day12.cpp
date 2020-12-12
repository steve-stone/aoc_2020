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
  

map<int, char> HEADING = {{0,'E'}, {90,'N'}, {180,'W'}, {270,'S'}};

struct Boat
{
  int heading_deg;
  char heading_str; 
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
      _move(pos, heading_str, val);
    } else if (cmd=='E' || cmd == 'N' || cmd == 'W' || cmd == 'S') {
      _move(pos, cmd, val);
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
    } else if (cmd=='E' || cmd == 'N' || cmd == 'W' || cmd == 'S') {
      _move(waypoint, cmd, val);
    }
  }
  void display_pos() {
    cout << "pos:" << pos.first << ',' << pos.second << endl;
  } 
  void waypoint_hop(int x) {
    pos.first += x * waypoint.first;
    pos.second += x * waypoint.second;
  }
  void _move(pair<int,int> &p, char direction, int amount) {
    if (direction == 'E') {
      p.first += amount;
    } else if (direction == 'N') {
      p.second += amount;
    } else if (direction == 'W') {
      p.first -= amount;
    } else if (direction == 'S') {
      p.second -= amount;
    } else {
      assert(false);
    }
  }
  void rotate_waypoint(int val) {
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
  }
  void adjust_heading(int val) {
    heading_deg += val;
    while (heading_deg<0)
      heading_deg += 360;
    heading_deg %= 360;
    heading_str = HEADING[heading_deg];
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
