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


int count_char(char c, string s) {
  int count = 0;
  for (char x : s) {
    if (x == c) {
      count++;
    }
  }
  return count;
}

class Policy {
  public:
    int min;
    int max;
    char tgt_char;
    Policy(string line) {
      
      int space_idx = line.find(' ');
      int hyphen_idx = line.find('-');

      min = stoi(line.substr(0, hyphen_idx));
      max = stoi(line.substr(hyphen_idx+1, space_idx-hyphen_idx-1));
      tgt_char = line.at(line.length()-1);
    }
};


void part1(vector<string> res) {
  int num_valid = 0;
  for (string line : res) {
    int n = line.length();
    int colon_idx = line.find(':');
    Policy pol(line.substr(0, colon_idx));
    string password = line.substr(colon_idx+2, n);

    int x = count_char(pol.tgt_char, password);
    if ((pol.min <= x) & (x <= pol.max)) num_valid++;
  }
  cout << num_valid << "\n";
}



void part2(vector<string> res) {
  int num_valid = 0;
  for (string line : res) {
    int n = line.length();
    int colon_idx = line.find(':');
    Policy pol(line.substr(0, colon_idx));
    string password = line.substr(colon_idx+2, n);

    if ((password.at(pol.min-1) == pol.tgt_char) ^ (password.at(pol.max-1) == pol.tgt_char)) num_valid++;
  }
  cout << num_valid << "\n";
}

int main()
{
  vector<string> res = read_data("02");
  part1(res);
  part2(res);
  return 0;
}
