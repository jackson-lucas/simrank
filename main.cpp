#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Filme.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

using namespace std;

template<typename Out>

void split(const string &s, char delim, Out result) {
  stringstream ss;
  ss.str(s);
  string item;
  while (getline(ss, item, delim)) {
    *(result++) = item;
  }
}

vector<string> split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, back_inserter(elems));
  return elems;
}

vector<Filme> readFile(string path) {
  ifstream myfile (path);
  string line;
  vector<Filme> filmes;

  if (myfile.is_open()) {
    while (getline (myfile, line)) {
      vector<string> data = split(line, '|');
      Filme filme;
      filme.categories[1] = (0 != stoi(data[5]));
      filme.categories[2] = (0 != stoi(data[6]));
      filme.categories[3] = (0 != stoi(data[7]));
      filme.categories[4] = (0 != stoi(data[8]));
      filme.categories[5] = (0 != stoi(data[9]));
      filme.categories[6] = (0 != stoi(data[10]));
      filme.categories[7] = (0 != stoi(data[11]));
      filme.categories[8] = (0 != stoi(data[12]));
      filme.categories[9] = (0 != stoi(data[13]));
      filme.categories[10] = (0 != stoi(data[14]));
      filme.categories[11] = (0 != stoi(data[15]));
      filme.categories[12] = (0 != stoi(data[17]));
      filme.categories[13] = (0 != stoi(data[18]));
      filme.categories[14] = (0 != stoi(data[19]));
      filme.categories[15] = (0 != stoi(data[20]));
      filme.categories[16] = (0 != stoi(data[21]));
      filme.categories[17] = (0 != stoi(data[22]));
      filme.categories[18] = (0 != stoi(data[23]));
      filmes.push_back(filme);
    }
    myfile.close();
  } else {
    cout << "no such file" << endl;
  }

  return filmes;
}


int main() {

  vector<Filme> filmes = readFile("u.item.txt");

  return 0;
}