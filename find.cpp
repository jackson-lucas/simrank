#include <ctime>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Filme.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <assert.h>

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

vector< vector<double> > matriz;

void readFile(string path) {
  ifstream myfile (path);
  string line;

  while (getline (myfile, line)) {
    vector<double> row;
    vector<string> data = split(line, ',');

    if (data.size() == 1) continue;

    for (int index = 0; index < data.size()-1; index++) {
      row.push_back(stod(data[index]));
      // cout << row[index] << endl;
    }

    matriz.push_back(row);
  }
}

struct exemplar {
  int id;
  double similaridade;
};

bool compareBySimilarity(const exemplar &a, const exemplar &b) {
  return a.similaridade > b.similaridade;
}

vector<exemplar> exemplares;

void getSimilares(int index) {

  for (int indice = 0; indice < matriz[index].size(); indice++) {
    exemplares.push_back(exemplar());
    exemplares[indice].id = indice;
    exemplares[indice].similaridade = matriz[index][indice];
  }

  sort(exemplares.begin(), exemplares.end(), compareBySimilarity);
}

vector<string> names;

void readNames(string path) {
  ifstream myfile (path);
  string line;

  if (myfile.is_open()) {
    while (getline (myfile, line)) {
      vector<string> data = split(line, '|');
      names.push_back(data[1]);
    }
  }
}

int main() {
  cout.precision(2);

  readFile("result100.csv");

  getSimilares(0);

  readNames("u.item.txt");

  for (int indice=1; indice < 4; indice++) {
    cout << exemplares[indice].id << " : " << names[exemplares[indice].id] << " : " << fixed << exemplares[indice].similaridade << endl;
  }
}
