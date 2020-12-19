#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <tuple>
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

unsigned long long calc(string o, unsigned long long x, unsigned long long y) {
  //cout << x << o << y << endl;
  unsigned long long res;
  if (o=="+")
    res = x + y;
  else if (o=="*")
    res = x * y;
  return res;
}


unsigned long long eval(string s) {
  //cout << "input: " << s << endl;
  stringstream ss(s);
  string tmp;
  unsigned long long res = 0;
  string op;
  string sub_exp;
  int nests;
  while (ss >> tmp) {
    //cout << tmp << endl;
    if ( (tmp == "*") || (tmp == "+") ) {
      op = tmp;
      //cout << "op = " << op << endl;
    }
    else if (tmp.at(0) == '(') {
      sub_exp = tmp;
      nests = count(tmp.begin(), tmp.end(), '(');
      while (ss >> tmp) {
        //cout << '|' << tmp << endl;
        sub_exp += " " + tmp;
        if (tmp.at(0) == '(') {
          nests++;
        }
        else if (tmp.at(tmp.size()-1) == ')') {
          nests -= count(tmp.begin(), tmp.end(), ')'); // for "x))"
          if (nests == 0)
            break;
        }
      }
      sub_exp = sub_exp.substr(1,sub_exp.size()-2); // trim brackets
      //cout << "sub:" << sub_exp << endl;
      if (res == 0) {
        res = eval(sub_exp);
        //cout << 'e' << eval(sub_exp) << endl;
      } else {
        res = calc(op, res, eval(sub_exp));
      }
    }
    else if ( res==0 ) {
      res = stoi(tmp); // x > 0 in all inputs
    }
    else {
      res = calc(op, res, stoi(tmp));
    }
  }
  return res;
}


unsigned long long part1(vector<string> input) {
  unsigned long long sol = 0;
  for (string s : input)
  {
    //cout << s << "|||" << eval(s) << endl;
    sol += eval(s);
  }
  return sol;
}

string add_brackets(string s):
  stringstream ss(s);
  string tmp;
  string op = "";
  string x = "";
  string y = "";
  string new_string;
  int nests = 0;
  while (ss >> tmp) {
    if ( (tmp == "*") || (tmp == "+") ) {
      op = tmp;
    }
    else if (tmp.at(0) == '(') {
      sub_exp = tmp;
      nests = count(tmp.begin(), tmp.end(), '(');
      while (ss >> tmp) {
        //cout << '|' << tmp << endl;
        sub_exp += " " + tmp;
        if (tmp.at(0) == '(') {
          nests++;
        }
        else if (tmp.at(tmp.size()-1) == ')') {
          nests -= count(tmp.begin(), tmp.end(), ')'); // for "x))"
          if (nests == 0)
            break;
        }
      }
      sub_exp = sub_exp.substr(1,sub_exp.size()-2); // trim brackets
      cout << "sub:" << sub_exp << endl;
      new_string += add_brackets(sub_exp);
    }
    else if (op == "") {
      x = tmp;
    }
    else {
      y = tmp;
      if (op == "+")
        new_string += "(" + x + " " + "+" + " " + y + ")";
      else
        new_string += x + " " + "+" + " " + y;
    }
  }
  return new_string;
}


int part2(vector<string> input) {
  string new_input;
  for (string s : input) {
    new_input = add_brackets(s);
    
  return 0;
}


void test() {
  string eg = "2 * 3 + (4 * 5)";
  string eg2 = "5 + (8 * 3 + 9 + 3 * 4 * 3)";
  string eg3 = "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))";
  string eg4 = "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2";
  //cout << eval(eg2) << endl;
  vector<string> v;
  v.push_back(eg);
  v.push_back(eg2);
  v.push_back(eg3);
  v.push_back(eg4);
  assert(part1(v) == 26335);
  //cout << part1(v) << endl;
}

void test2(){
  string x = "(5 + 3 * (2 + 3 * 7 + 6) + 3)";
  string x2 = "(8 * (5 * 8 * 5 + 9) * 9)";
  string x3 = "(3 + 4 + 2 * 6 * (2 + 5 * 8))";
  cout << eval(x) << endl;
  cout << eval(x2) << endl;
  cout << eval(x3) << endl;
  string y = "(5 + 3 * (2 + 3 * 7 + 6) + 3) * (8 * (5 * 8 * 5 + 9) * 9) * (3 + 4 + 2 * 6 * (2 + 5 * 8)) * 6";
  cout << eval(y) << endl;
}


int main()
{
  //test();
  test2();
  vector<string> instr = read_data("18");
  cout << part1(instr) << endl;
  cout << part2(instr) << endl;
  return 0;
}
