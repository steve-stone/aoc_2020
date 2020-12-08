#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <map>

using namespace std;

vector<string> read_data(string file){

    ifstream ip("inputs/" + file + ".txt");
    vector<string> result;
    string s;

    while (getline(ip, s)) {
      result.push_back(s);
    }

    ip.close();
    
    return result;
}


int part1(vector<string> vec) {
  bool visited [vec.size()] = {};

  string cmd;
  string s;
  int val;
  int i=0; 
  int res=0;

  while (visited[i] == false) {
    visited[i] = true;
    s = vec.at(i);
    stringstream ss(s);
    ss >> cmd;
    ss >> val;
    //cout << i << '|' << s << '|' << cmd << '|' << val << '|' << endl;
    if (cmd=="acc") {
      res += val;
      i++;
    }
    else if (cmd=="jmp") {
      i += val;
    }
    else if (cmd=="nop") {
      i ++;
    }

  }
  
  return res;
}


int part2(vector<string> vec) {
  int n = vec.size();
  
  string cmd;
  string s;
  int val;
  int i=0; 
  int res=0;

  for (int toggle = 0; toggle < n; toggle++) {
    bool visited [n+1] = {};
    res=0;
    i=0;
    while (visited[i] == false) {
      visited[i] = true;
      if (i == n) {
        return res;
      }
      s = vec.at(i);
      stringstream ss(s);
      ss >> cmd;
      ss >> val;
      if (i==toggle) {
        if (cmd=="nop") {
          cmd = "jmp";
        }
        else if (cmd=="jmp") {
          cmd = "nop";
        }
      }
        
      //cout << i << '|' << s << '|' << cmd << '|' << val << '|' << res << '|' << endl;
      if (cmd=="acc") {
        res += val;
        i++;
      }
      else if (cmd=="jmp") {
        i += val;
      }
      else if (cmd=="nop") {
        i ++;
      }

    }
  }
  //cout << "i=" << toggle-1 << endl;
  
  return res;
}


void test() {
  cout << part1(read_data("testdata08")) << endl;
  cout << part2(read_data("testdata08")) << endl;
}

int main()
{
  vector<string> cmd_list = read_data("data08");
  //test();
  cout << part1(cmd_list) << "\n";
  cout << part2(cmd_list) << "\n";
  return 0;
}
