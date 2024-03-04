#include "movieList.h"
#include <fstream>
#include<iostream>
using namespace std;

int main() {
    ifstream inFile;
    inFile.open("movies.txt");

    if (!inFile.is_open())
        cout << "File: movies.txt is not found" << endl;

    MovieList movieListSystem;

    movieListSystem.runMovieSystem();

    inFile.close();

    return 0;
}
