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
#include <algorithm>

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


void print (vector<pair<int,int>> x) {
  int i=0;
  for (auto const& p : x) {
    cout << p.first << ',' << p.second << '-' << (i+2)/2 << endl;
    i++;
  }
}

void add_rule(string& s, vector<pair<int,int>>& rules) {
  int low;
  int high;
  low = stoi(s.substr(0, s.find('-')));
  high = stoi(s.substr(s.find('-')+1, s.size() - s.find('-')));
  rules.emplace_back(low, high);
}

int calc_scan_err(string& x, vector<pair<int,int>>& rules) {
  stringstream ss(x);
  int scan_err = 0;
  for (int i; ss >> i;) {
    bool valid = false;
    for (pair<int, int> rule : rules) {
      if ( (i >= rule.first) && (i <= rule.second) ) {
        valid = true;
        break;
      }
    }
    if (!valid) {
      scan_err += i;
      //cout << i << ',' << scan_err << endl;
    }
    if (ss.peek() == ',')
      ss.ignore();
  }
  return scan_err;
}

vector<int> str_to_ticket(string t) {
  vector<int> sol;
  stringstream ss(t);
  for (int i; ss >> i;) {
    sol.emplace_back(i);
    if (ss.peek() == ',')
      ss.ignore();
  }
  return sol;
}
  

void part1(vector<string> input) {

  // rules
  string s;
  size_t idx = 1;
  vector<pair<int,int>> rules;
  vector<string> fields;
  vector<vector<int>> tickets;
  string my_ticket;

  string x = input.at(0);
  while (x != "") {
    stringstream ss(x);
    
    getline(ss, s, ':'); // field name
    fields.push_back(s);
    ss >> s; // range
    add_rule(s, rules);
    
    ss >> s; // or
    ss >> s; // range
    add_rule(s, rules);

    x = input.at(idx++);
  }
  
  int scan_err = 0;

  x = input.at(idx++); // "your ticket: "
  x = input.at(idx++); // ticket values
  
  //scan_err += calc_scan_err(x, rules);
  my_ticket = x;

  x = input.at(idx++); // ""
  x = input.at(idx++); // "nearby ticket: "
  int err;
  while (idx < input.size()) {
    x = input.at(idx++); // ticket values
    err = calc_scan_err(x, rules);
    scan_err += err;
    if (err == 0)
      tickets.push_back(str_to_ticket(x));
  }
    
  cout << scan_err << endl;

  int v;
  pair<int, int> r;
  pair<int, int> r2;
  vector<string> sol;
  vector<string> f;
  bool found;
  string last_found = "";
  int f_idx = 0;
  int del_idx;
  while(fields.size() > 0) {
    if (last_found!="") {
      //fields.erase(remove(fields.begin(), fields.end(), last_found), fields.end());
      del_idx = fields.find(last_found);
      fields.erase(del_idx);
      rules.erase(del_idx);
    }
    f = fields;
    cout << " f " << f.size() << endl;
    found = false;
    for (vector<int> ticket : tickets) {
      cout << f_idx << '|' << ticket.size() << endl;;
      v = ticket.at(f_idx);
      cout << "val = " << v << endl;
      for (size_t rule_idx = 0; rule_idx < rules.size()/2; rule_idx++) {
        //cout << "Rule:" << rule_idx << endl; 
        //cout << rules.at(rule_idx).first << '|' << rules.at(rule_idx).second << endl;
        //cout << rules.at(rule_idx+1).first << '|' << rules.at(rule_idx+1).second << endl;
        r = rules.at(2*rule_idx);
        r2 = rules.at(2*rule_idx + 1);
        if ( (v < r.first) || (v > r2.second) || ( (v > r.second) && (v < r2.first) ) ) {
          f.erase(remove(f.begin(), f.end(), fields.at(rule_idx)), f.end());
          //cout << '-' << fields.at(rule_idx) << endl;
          //cout << "-- " << f.size() << " fields remaining" << endl;
          if (f.size() == 1) {
            last_found = f.at(0);
            cout << "!!! " << last_found << endl;
            sol.push_back(last_found);
            found = true;
            break;
          }
        }
      }
      if (found)
        break;
    }
    f_idx++;
  }
}


int part2(vector<string> input) {
  return 0;
}


void test() {
  vector<string> input = read_data("16", true);
  part1(input);
}


int main()
{
  test();
  vector<string> instr = read_data("16");
  //part1(instr);
  //cout << part2(instr) << endl;
  return 0;
}
