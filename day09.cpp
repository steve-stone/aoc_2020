#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <map>

using namespace std;

vector<long int> read_data(string file){

    ifstream ip("inputs/" + file + ".txt");
    vector<long int> result;
    string s;

    while (getline(ip, s)) {
      result.push_back(stol(s));
    }

    ip.close();
    
    return result;
}


int part1(vector<long int> vec, int preamble) {
  
  int vec_len = vec.size();
  bool valid = false;
  for (int i=preamble; i < vec_len; i++) {
    valid = false;
    for (int j=i-preamble; j<i-1; j++) {
      int tgt = vec.at(i) - vec.at(j);
      for (int k=j+1; k<i; k++) {
        if (vec.at(k)==tgt)
          valid = true; 
      }
      if (valid == true) {
        break;
      }
    }
    if (valid == false)
      return vec.at(i);
  }
  return -1;
}


int part2(vector<long int> vec, int tgt) {
  
  int vec_len = vec.size();
  long int _min;
  long int _max;
  for (int i=0; i<vec_len-1; i++) {
    long int count = vec.at(i);
    _min = count;
    _max = count;
    for (int j=i+1; j<vec_len; j++) {
      long int x = vec.at(j);
      if (x < _min) _min = x;
      if (x > _max) _max = x;
      count += x;
      if (count == tgt) {
        return _min + _max;
      }
    }

  }
  return -1;
}


void test() {
  cout << part1(read_data("testdata09"), 5) << endl;
}

int main()
{
  vector<long int> cmd_list = read_data("data09");
  //test();
  int invalid_num = part1(cmd_list, 25);
  cout << invalid_num << "\n";
  cout << part2(cmd_list, invalid_num) << "\n";
  return 0;
}
