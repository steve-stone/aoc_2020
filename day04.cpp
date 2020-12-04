#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

int part1(){

    vector<string> expected_flds = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    ifstream ip("inputs/data04.txt");

    vector<string> result;
    string line;

    int num_valid = 0;
    while (getline(ip, line)) {

      istringstream iss(line);
      string item;
      while (getline(iss, item, ' ')) {
        int split_idx = item.find(':');
        string key = item.substr(0, split_idx);
        
        expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());

      }
      if (line == "") {
        if (expected_flds.size()==0) num_valid++;
        expected_flds = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
      }
      result.push_back(line);
    }

    ip.close();
    
    return num_valid;
}


int part2(){

    vector<string> expected_flds = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    ifstream ip("inputs/data04.txt");

    vector<string> result;
    string line;

    int num_valid = 0;
    while (getline(ip, line)) {

      istringstream iss(line);
      string item;
      while (getline(iss, item, ' ')) {
        int split_idx = item.find(':');
        string key = item.substr(0, split_idx);
        string val = item.substr(split_idx+1, item.length()-split_idx-1);
        
        if (key=="byr") {
          if ( (val.length()==4) & (stoi(val) >= 1920) & (stoi(val) <= 2002) ) {
            expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
          }
        }
        if (key=="iyr") {
          if ( (val.length()==4) & (stoi(val) >= 2010) & (stoi(val) <= 2020) )
            expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
        }
        if (key=="eyr") {
          if ( (val.length()==4) & (stoi(val) >= 2020) & (stoi(val) <= 2030) )
            expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
        }
        if (key=="hgt") {
          regex valid_regex("[0-9]+(in|cm)");
          if (!regex_match(val, valid_regex)) {
            continue;
          }
          string units = val.substr(val.length() - 2, 2);
          int measurement = stoi(val.substr(0, val.length() - 2));
          if (units == "cm") {
            if ((measurement >= 150) & (measurement <= 193)) {
              expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
            }
          }
          if (units == "in") {
            if ((measurement >= 59) & (measurement <= 76)) {
              expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
            }
          }
        }
        if (key=="hcl") {
          regex valid_regex("#[0-9|a-f]{6}");
          if (regex_match(val, valid_regex)) {
            expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
          }
        }
        if (key=="ecl") {
          regex valid_regex("(blu|amb|brn|gry|grn|hzl|oth)");
          if (regex_match(val, valid_regex)) {
            expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
          }
        }
        if (key=="pid") {
          regex valid_regex("[0-9]{9}");
          if (regex_match(val, valid_regex)) {
            expected_flds.erase(remove(expected_flds.begin(), expected_flds.end(), key), expected_flds.end());
          }
        }

      }
      if (line == "") {
        if (expected_flds.size()==0) num_valid++;
        expected_flds = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
      }
      result.push_back(line);
    }

    ip.close();
    
    return num_valid;
}


int main()
{
  cout << part1() << "\n";
  cout << part2() << "\n";
  return 0;
}
