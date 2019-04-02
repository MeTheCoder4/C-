#include <iostream>
#include "Tree.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(0));

    ifstream file("inlab04");

    if(!file.good())
        cout << "Error on opening a file!" << endl;

    string line;
    getline(file, line);
    istringstream iss(line);
    int X, k1, k2, k3, k4;
    iss >> X >> k1 >> k2 >> k3 >> k4;
    cout << "File data: " << X << ' ' << k1  << ' ' << k2 << ' ' << k3 << ' ' << k4 << endl;

    file.close();

    clock_t timeStart = clock();

    Tree tree;

    tree.insertRandom(X);

    cout << "Inorder: " << endl;
    tree.inorder(tree.getRoot());
    cout << "Number of visited nodes: " <<  tree.getEntryCounter() << endl;
    tree.zeroCounter();

    int cnt = 0;
    for(int i = 0; i < X; i++) {
        if(tree.remove((rand() % 20000) - 10000))
            cnt++;
    }

    clock_t timeStop = clock();

    cout << "Removed " << cnt << " random nodes." << endl;

    cout << "Inorder: " << endl;
    tree.inorder(tree.getRoot());
    cout << "Number of visited nodes: " <<  tree.getEntryCounter() << endl;
    tree.zeroCounter();

    cout << "Data structure: AVL tree. Running time: " << static_cast<double>(timeStop - timeStart) / CLOCKS_PER_SEC
         << " seconds." << endl;
    return 0;
}