#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <cassert>

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


class Seat {
  private:
    int str_to_row(string seat_str);
    int str_to_col(string seat_str);
  public:
    Seat(string s);
    int row;
    int col;
    int seat_id;
};


Seat::Seat(string s) {
  regex seat_re("[F|B]{7}[L|R]{3}");
  if (!regex_match(s, seat_re)) {
    // TODO fix exception
    throw "invalid input";
  }
  row = str_to_row(s);
  col = str_to_col(s);
  seat_id = row * 8 + col;
}

int Seat::str_to_row(string x) {
  int low = 0;
  int high = 127;
  float mid = (float)(high - low) / 2.0;
  for (char c : x.substr(0,7)) {
    //cout << low << '-' << high << ' ' << mid << ',' << c << "\n";
    if (c == 'F')
      high = (int)(mid - 0.5);
    if (c == 'B')
      low = (int)(mid + 0.5);
    mid = (float)(low) + (float)(high - low) / 2.0;

  }
  assert(low==high);
  return low;
}

int Seat::str_to_col(string x) {
  int low = 0;
  int high = 7;
  float mid = (float)(high - low) / 2.0;
  for (char c : x.substr(7,10)) {
    //cout << low << '-' << high << ' ' << mid << ',' << c << "\n";
    if (c == 'L')
      high = (int)(mid - 0.5);
    if (c == 'R')
      low = (int)(mid + 0.5);
    mid = (float)(low) + (float)(high - low) / 2.0;

  }
  assert(low==high);
  return low;
}

int part1(vector<Seat> vec) {
  int max_id = 0;
  for (Seat i: vec)
    max_id = max(i.seat_id, max_id);
  return max_id;
}


int part2(vector<Seat> vec){
  vector<int> seat_ids;
  for (Seat i: vec)
    seat_ids.push_back(i.seat_id);

  sort(seat_ids.begin(), seat_ids.end());
  int last_id = seat_ids.at(0);
  for (int a : seat_ids) {
    if ((a-last_id) == 2)
      return last_id+1;
    last_id = a;
  }

  return 0;
}


void test() {
  string test = "FBFBBFFRLR";
  Seat s(test);
  cout << s.row << ',' << s.col << ',' << s.seat_id << "\n";
}

int main()
{
  vector<string> seats = read_data("05");
  vector<Seat> seat_vec;
  for (string seat_str : seats) {
    Seat s(seat_str);
    seat_vec.push_back(s);
  }
  cout << part1(seat_vec) << "\n";
  cout << part2(seat_vec) << "\n";
  return 0;
}
