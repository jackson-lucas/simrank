#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Filme {
  public:
    int id;
    vector<int> vizinhos;
    bool categorias[19];
};
