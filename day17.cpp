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

void print_state(vector<vector<string>> x) {
  for (auto i : x) {
    cout << '-' << endl;
    for (auto j : i) {
      cout << j << endl;
    }
  }
}

vector<string> new_dimension(int x, int y) {
  vector<string> new_dim;
  for (int i = 0; i < x; i++) {
    new_dim.emplace_back(y,'.');
  }
  return new_dim;
}


void extend_x(vector<vector<string>>& state) {
  string tmp;
  for (auto& v : state) {
    for (string& s : v) {
      tmp = '.' + s + '.';
      s = tmp;
    }
    //string top(state.at(0).at(0), '.');
    //string bottom(state.at(0).at(0), '.');
    //v.emplace(v.begin(), top);
    //v.emplace(v.end(), bottom);
  }
}

void extend_y(vector<vector<string>>& state) {
  int n = state.at(0).at(0).size(); // number of cols
  for (auto& v : state) {
    v.emplace(v.begin(), string(n, '.'));
    v.emplace(v.end(), string(n, '.'));
  }
}

void extend_z(vector<vector<string>>& state) {
  vector<string> front = new_dimension(state.at(0).size(), state.at(0).at(0).size());
  vector<string> back = new_dimension(state.at(0).size(), state.at(0).at(0).size());
  state.emplace(state.begin(), front);
  state.emplace(state.end(), back);
}

void init_next_state(vector<vector<string>>& new_state, vector<vector<string>>& state) {
  // copy state into new state
  // add dimensions on all sides
  new_state = state;
  extend_x(new_state);
  extend_y(new_state);
  extend_z(new_state);
  cout << "\nORIG" << endl;
  print_state(state);
  cout << "\nNEW" << endl;
  print_state(new_state);
}

int count_adj(vector<vector<string>>& state, size_t dim, size_t row, size_t col) {
  int n = 0;
  for (size_t d = dim-1; d <= dim+1; d++) {
    for (size_t r = row-1; r <= row+1; r++) {
      for (size_t c = col-1; c <= col+1; c++) {
        if ( d==dim && c==col && r==row )
          continue; // this element
        if (state.at(d).at(r).at(c)=='#')
          n++;
      }
    }
  }
    
  return n;
}

int part1(vector<string> input) {
  vector<vector<string>> state;
  state.push_back(input);
  extend_x(state);
  extend_y(state);
  extend_z(state);
  vector<vector<string>> next_state;
  int n;
  string row;
  char c;
  for (int i = 0; i<6; i++) {
    init_next_state(next_state, state);
    cout << state.size() << '|' << state.at(0).size() << '|' << state.at(0).at(0).size() << endl;
    cout << "New:  " << next_state.size() << '|' << next_state.at(0).size() << '|' << next_state.at(0).at(0).size() << endl;
    for (size_t dim = 0; dim < state.size(); dim++) {
      //cout << "dimension " << dim << endl;
      for (size_t row_idx=0; row_idx < state.at(dim).size(); row_idx++) {
        row = state.at(dim).at(row_idx);
        for (size_t col_idx=0; col_idx < row.size(); col_idx++) {
          c = row.at(col_idx);
          n = count_adj(next_state, dim, row_idx, col_idx);
          if (c=='#')
            cout << dim << ',' << row_idx << ',' << col_idx << ',' << n << endl;
        }
      }
    }
    state = next_state;
  }

  int active = 0;
  for (size_t dim = 0; dim < state.size(); dim++) {
    for (string row : state.at(dim)) {
      for (char c : row) {
        if (c=='#')
          active++;
      }
    }
  }
  return active;
}

int part2(vector<string> input) {
  return 0;
}


void test() {
  vector<string> input = read_data("17", true);
  cout << part1(input) << endl;
}


int main()
{
  test();
  vector<string> instr = read_data("17");
  //part1(instr);
  //cout << part2(instr) << endl;
  return 0;
}
