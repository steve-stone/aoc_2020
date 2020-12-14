#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <map>
#include <cmath>
#include <bitset>

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

map<unsigned long, unsigned long long> mem;


unsigned long long apply_mask(string mask, unsigned long long v) {
  string binary = bitset<36>(v).to_string();
  for (size_t i = 0; i < binary.size(); i++) {
    if (mask.at(i) == 'X')
      continue;
    else
      binary.at(i) = mask.at(i);
  }
  bitset<36> bits(binary);
  return bits.to_ullong();
}


vector<unsigned long long> apply_mask_v2(string mask, unsigned long long v) {
  vector<string> binaries;
  vector<unsigned long long> sol;
  string binary = bitset<36>(v).to_string();
  for (size_t i = 0; i < binary.size(); i++) {
    if (mask.at(i) == '0')
      continue;
    else
      binary.at(i) = mask.at(i);
  }
  binaries.push_back(binary);
  int idx;
  while (binaries.at(0).find('X') != std::string::npos) {
    idx = binaries.at(0).find('X');
    vector<string> new_binaries;
    for (auto& b_zero : binaries) {
      string b_one = b_zero;
      b_zero.at(idx) = '0';
      b_one.at(idx) = '1';
      new_binaries.push_back(b_one);
    }
    binaries.insert(binaries.end(), new_binaries.begin(), new_binaries.end());
  }

  for (auto i : binaries) {
    bitset<36> bits(i);
    sol.push_back(bits.to_ullong());
  }
  return sol;
}


unsigned long long part1(vector<string> input) {
  mem.clear();
  string mask;
  unsigned long k;
  unsigned long long v;
  string tmp;

  for (string s : input) {
    if (s.substr(0,3) == "mas") {
      mask = s.substr(7, 36); 
    }
    else if (s.substr(0,3) == "mem") {
      stringstream ss(s);
      ss >> tmp;
      k = stoi(tmp.substr(4, tmp.size()-5));
      ss >> tmp;
      assert(tmp=="=");
      ss >> v;

      mem[k] = apply_mask(mask, v);
    }
  }

  unsigned long long sol = 0;
  for (auto const& x : mem) {
    sol += x.second;
  }
    
  return sol;
}

unsigned long long part2(vector<string> input) {
  mem.clear();
  string mask;
  vector<unsigned long long> addr_vec;
  unsigned long long addr;
  unsigned long long val;
  string tmp;

  for (string s : input) {
    if (s.substr(0,3) == "mas") {
      mask = s.substr(7, 36); 
    }
    else if (s.substr(0,3) == "mem") {
      stringstream ss(s);
      ss >> tmp;
      addr = stoi(tmp.substr(4, tmp.size()-5));
      ss >> tmp;
      assert(tmp=="=");
      ss >> val;

      addr_vec = apply_mask_v2(mask, addr);

      for (auto i : addr_vec)
        mem[i] = val;

    }
  }

  unsigned long long sol = 0;
  for (auto const& x : mem) {
    sol += x.second;
  }
    
  return sol;
}


void test() {
  vector<string> input = read_data("testdata14");
  assert(part1(input)==165);
  //cout << part1(input) << endl;
}

void test2() {
  vector<string> input = read_data("testdata14_2");
  assert(part2(input)==208);
}

int main()
{
  test();
  vector<string> instr = read_data("data14");
  cout << part1(instr) << endl;
  test2();
  cout << part2(instr) << endl;
  return 0;
}
