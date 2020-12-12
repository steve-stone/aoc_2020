#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>

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


int count_adj(int row, int col, vector<string> seat_map) {
  int sol = 0;
  int row_count = seat_map.size();
  int col_count = seat_map.at(0).size();
  for (int i=row-1; i<=row+1; i++) {
    if (i == -1)
      continue;
    if (i == row_count )
      continue;
    for (int j=col-1; j<=col+1; j++) {
      if (j == -1)
        continue;
      if (j == col_count )
        continue;
      if ( i==row && j==col )
        continue;
      if (seat_map.at(i).at(j) == '#')
        sol++;
    }
  }
  return sol;
}



vector<string> parse_map(vector<string> seat_map) {

  vector<string> next_state;

  int row_idx = 0;
  int col_idx = 0;
  int num_adj;
  for (string row : seat_map) {
    string new_row = "";
    for (char c : row) {
      if (c=='.') {
        // floor
        new_row += '.';
      } else if (c=='#') {
        // occupied
        // switch if 4 or more adj occupied
        num_adj = count_adj(row_idx, col_idx, seat_map);
        if (num_adj > 3)
          new_row += 'L';
        else
          new_row += '#';
          
      } else if (c=='L') {
        // free
        // switch if 0 adj occupied 
        num_adj = count_adj(row_idx, col_idx, seat_map);
        if (num_adj == 0)
          new_row += '#';
        else
          new_row += 'L';
      }
      col_idx++;
    }
    row_idx++;
    col_idx = 0;
    next_state.push_back(new_row);
  }
  return next_state;
}

int part1(vector<string> seat_map) {
  bool stable = false;
  vector<string> curr_map = seat_map;
  vector<string> next_map;
  int i = 0;
  while (!stable) {
    next_map.clear();
    next_map = parse_map(curr_map);
    //for (string x : next_map)
    //  cout << x << endl;
    //cout << endl;
    i++;
    stable = equal(curr_map.begin(), curr_map.end(), next_map.begin());
    curr_map = next_map;
  }
  
  int num_occ = 0;
  for (string row : curr_map) {
    for (char c : row) {
      if (c=='#')
        num_occ++;
    }
  }
  return num_occ;
}

int count_vis(int row, int col, vector<string> seat_map) {
  int sol = 0;
  int row_count = seat_map.size();
  int col_count = seat_map.at(0).size();
  for (int i=row-1; i>=0; i--) {
    //N
    if (seat_map.at(i).at(col) == '.')
      continue;
    else if (seat_map.at(i).at(col) == '#')
      sol++;
    break;
  }
  for (int i=row+1; i<row_count; i++) {
    //S
    if (seat_map.at(i).at(col) == '.')
      continue;
    else if (seat_map.at(i).at(col) == '#')
      sol++;
    break;
  }
  for (int i=col-1; i>=0; i--) {
    //W
    if (seat_map.at(row).at(i) == '.')
      continue;
    else if (seat_map.at(row).at(i) == '#')
      sol++;
    break;
  }
  for (int i=col+1; i<col_count; i++) {
    //E
    if (seat_map.at(row).at(i) == '.')
      continue;
    else if (seat_map.at(row).at(i) == '#')
      sol++;
    break;
  }
  int i;
  int j;
  int limit = min(row,col);
  limit = min(row,col);
  for (int z = 1; z <=limit; z++) {
    //NW
    i = row - z;
    j = col - z;
    if (seat_map.at(i).at(j) == '.')
      continue;
    else if (seat_map.at(i).at(j) == '#')
      sol++;
    break;
  }
  limit = min(row_count - row, col_count - col);
  for (int z = 1; z <limit; z++) {
    //SE
    i = row + z;
    j = col + z;
    if (seat_map.at(i).at(j) == '.')
      continue;
    else if (seat_map.at(i).at(j) == '#')
      sol++;
    break;
  }
  limit = min(row, col_count - col - 1);
  for (int z = 1; z <=limit; z++) {
    //NE
    i = row - z;
    j = col + z;
    if (seat_map.at(i).at(j) == '.')
      continue;
    else if (seat_map.at(i).at(j) == '#')
      sol++;
    break;
  }
  limit = min(row_count - row - 1, col);
  for (int z = 1; z <=limit; z++) {
    //SE
    i = row + z;
    j = col - z;
    if (seat_map.at(i).at(j) == '.')
      continue;
    else if (seat_map.at(i).at(j) == '#')
      sol++;
    break;
  }


  return sol;
}

vector<string> parse_map2(vector<string> seat_map) {

  vector<string> next_state;

  int row_idx = 0;
  int col_idx = 0;
  int num_adj;
  for (string row : seat_map) {
    string new_row = "";
    for (char c : row) {
      if (c=='.') {
        // floor
        new_row += '.';
      } else if (c=='#') {
        // occupied
        // switch if 4 or more adj occupied
        num_adj = count_vis(row_idx, col_idx, seat_map);
        if (num_adj > 4)
          new_row += 'L';
        else
          new_row += '#';
          
      } else if (c=='L') {
        // free
        // switch if 0 adj occupied 
        num_adj = count_vis(row_idx, col_idx, seat_map);
        if (num_adj == 0)
          new_row += '#';
        else
          new_row += 'L';
      }
      col_idx++;
    }
    row_idx++;
    col_idx = 0;
    next_state.push_back(new_row);
  }
  return next_state;
}

int part2(vector<string> seat_map) {
  bool stable = false;
  vector<string> curr_map = seat_map;
  vector<string> next_map;
  int i = 0;
  while (!stable) {
    next_map.clear();
    next_map = parse_map2(curr_map);
    i++;
    stable = equal(curr_map.begin(), curr_map.end(), next_map.begin());
    curr_map = next_map;
  }
  
  int num_occ = 0;
  for (string row : curr_map) {
    for (char c : row) {
      if (c=='#')
        num_occ++;
    }
  }
  return num_occ;
}


void test() {
  
  vector<string> seat_map = read_data("testdata11");
  assert(part1(seat_map)==37);
}

void test2() {
  
  vector<string> seat_map = read_data("testdata11");
  assert(part2(seat_map) == 26);
}

int main()
{
  test();
  test2();
  vector<string> seat_map = read_data("data11");
  cout << part1(seat_map) << endl;
  cout << part2(seat_map) << endl;
  return 0;
}
