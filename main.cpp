#include <ctime>
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

const int QT_FILME = 18;
const double C = 0.8;
vector< vector<double> > matriz;
vector<Filme> filmes;

void readFile(string path) {
  ifstream myfile (path);
  string line;

  if (myfile.is_open()) {
    while (getline (myfile, line)) {
      vector<string> data = split(line, '|');
      Filme filme;
      filme.id = stoi(data[5]);
      filme.categorias[1] = (0 != stoi(data[5]));
      filme.categorias[2] = (0 != stoi(data[6]));
      filme.categorias[3] = (0 != stoi(data[7]));
      filme.categorias[4] = (0 != stoi(data[8]));
      filme.categorias[5] = (0 != stoi(data[9]));
      filme.categorias[6] = (0 != stoi(data[10]));
      filme.categorias[7] = (0 != stoi(data[11]));
      filme.categorias[8] = (0 != stoi(data[12]));
      filme.categorias[9] = (0 != stoi(data[13]));
      filme.categorias[10] = (0 != stoi(data[14]));
      filme.categorias[11] = (0 != stoi(data[15]));
      filme.categorias[12] = (0 != stoi(data[17]));
      filme.categorias[13] = (0 != stoi(data[18]));
      filme.categorias[14] = (0 != stoi(data[19]));
      filme.categorias[15] = (0 != stoi(data[20]));
      filme.categorias[16] = (0 != stoi(data[21]));
      filme.categorias[17] = (0 != stoi(data[22]));
      filme.categorias[18] = (0 != stoi(data[23]));
      filmes.push_back(filme);
    }
    myfile.close();
  } else {
    cout << "no such file" << endl;
  }
}

bool temVizinho(Filme filme, int indiceDoVizinho) {
  for (int indice = 0; indice < filme.vizinhos.size(); indice++) {
    if (filme.vizinhos[indice] == indiceDoVizinho) {
      return true;
    }
  }
  return false;
}

void setNeighbours(vector<Filme> filmes) {
  for (int indice = 0; indice < filmes.size(); indice++ ) {
    for (int indice2 = 1; indice2 < filmes.size(); indice2++ ) {
      for (int indCategoria = 0; indCategoria < QT_FILME; indCategoria++) {
        Filme filme = filmes[indice];
        Filme filme2 = filmes[indice2];

        if (temVizinho(filme, indice2)) continue;

        if (filme.categorias[indCategoria] == filme2.categorias[indCategoria]) {
          filme.vizinhos.push_back(indice2);
          filme2.vizinhos.push_back(indice);
          filmes[indice] = filme;
          filmes[indice2] = filme2;
          break;
        }
      }
    }
  }
}

double simrank (int index, int index2) {
  Filme filme = filmes[index];
  Filme filme2 = filmes[index2];

  int qtVizinhos = filme.vizinhos.size();
  int qtVizinhos2 = filme2.vizinhos.size();

  double total = 0;
  int similarity;

  for (int indice = 0; indice < qtVizinhos; indice++) {
    for (int indice2 = 0; indice2 < qtVizinhos2; indice2++) {
      total += simrank(filme.vizinhos[indice], filme2.vizinhos[indice2]);
    }
  }

  similarity = total * (C / (qtVizinhos * qtVizinhos2));
  matriz[index][index2] = similarity;
  return total;
}

int main() {
  const int K = 5;
  clock_t begin;
  clock_t end;
  double elapsedSecs;

  begin = clock();
  readFile("u.item.txt");

  matriz.resize(filmes.size());

  for (int indice = 0; indice < filmes.size(); indice++) {
    matriz[indice].resize(filmes.size());
    matriz[indice][indice] = 1;
  }

  setNeighbours(filmes);

  for (int contador = 0; contador < K; contador++) {
    for (int indice = 0; indice < filmes.size(); indice++) {
      for (int indice2 = 0; indice2 < filmes.size(); indice2++) {
        if (indice <= indice2) continue;
        simrank(indice, indice2);
      }
    }
  }

  for (int index = 0; index < filmes.size(); index++) {
    for (int index2 = 0; index2 < filmes.size(); index2++) {
      cout << matriz[index][index2] << ",";
    }
    cout << endl;
  }
  end = clock();

  elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Tempo: " << elapsedSecs << "s" << endl;

  return 0;
}
