#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <unordered_map>
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


unordered_map<int, string> rules;

void set_rules(vector<string>& input)
{
  rules.clear();
  for (string s : input) {
    if (s=="")
    {
      break;
    }
    else
    {
      string key = s.substr(0, s.find(':'));
      string rule = s.substr(s.find(':')+2);
      rules[stoi(key)] = rule;
    }
  }
}

vector<string> cartesian(vector<string>& x, vector<string>& y)
{
  vector<string> sol;
  for (string xi : x) {
    for (string yi : y) {
      //cout << "  ++ " << xi+yi << endl;
      sol.emplace_back(xi+yi);
    }
  }
  return sol;
}

vector<string> parse_rule(string x)
{
  vector<string> comb;
  vector<string> tmp;
  string s;
  //cout << '|' << x << '|' << endl;
  if (x.find('|') != string::npos)
  {
    comb = parse_rule(x.substr(0, x.find('|')-1));
    tmp = parse_rule(x.substr(x.find('|')+2));
    comb.insert( comb.end(), tmp.begin(), tmp.end() );
  }
  else if (x == "")
  {
    return comb;
  }
  else if (x.at(0) == '"')
  {
    comb.emplace_back(x.substr(1, x.size()-2));
  }
  else
  {
    stringstream ss(x);
    int i;
    while (ss >> i)
    {
      tmp = parse_rule(rules[i]);
      if (comb.size() == 0)
        comb = tmp;
      else
      {
        comb = cartesian(comb, tmp);
      }
    }
  }
  return comb;
}

vector<string> build_valid()
{
  vector<string> sol = parse_rule(rules[0]);
  return sol;
}

int count_valid(vector<string>& in, vector<string>& valid)
{
  int res = 0;
  for ( string& s : in )
  {
    for (string& t : valid)
    {
      if (t==s)
        res++;
    }
  }
  return res;
}


int part1(vector<string> input) {
  set_rules(input);
  vector<string> valid_vec = build_valid();
  return count_valid(input, valid_vec);
}

int part2(vector<string> input) {
  return 0;
}


void test() {
  vector<string> instr = read_data("19", true);
  assert(part1(instr) == 2);
//  cout << part1(instr) << endl;
}


int main()
{
  test();
  vector<string> instr = read_data("19");
  cout << part1(instr) << endl;
  //cout << part2(instr) << endl;
  return 0;
}
