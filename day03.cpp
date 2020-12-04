#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

vector<string> read_data(string day_num){

    ifstream ip("inputs/data" + day_num + ".txt");

    vector<string> result;
    string line;

    while (getline(ip, line)) {
      result.push_back(line);
    }

    ip.close();
    
    return result;
}


int part1(vector<string> res, int moves_right, int moves_down) {
  int num_rows = res.size();
  int num_cols = res.at(0).length() - 1;

  int pos_x = 0;
  int pos_y = 0;
  int num_trees = 0;
  while(pos_y < num_rows) {
    if (res.at(pos_y).at(pos_x) == '#'){
      num_trees++;
    }
    pos_x += moves_right;
    pos_x %= num_cols;
    pos_y += moves_down;
  }
  return num_trees;

}



void part2(vector<string> res) {
  int sol = 1;
  sol *= part1(res, 1, 1);
  sol *= part1(res, 3, 1);
  sol *= part1(res, 5, 1);
  sol *= part1(res, 7, 1);
  sol *= part1(res, 1, 2);
  cout << sol << "\n";
}

int main()
{
  vector<string> res = read_data("03");
  int n = part1(res, 3, 1);
  cout << n << "\n";
  part2(res);
  return 0;
}
