#pragma once

#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <string>
#include <fstream>

using namespace std;

const int INITIAL_CAPACITY = 30;
const int MAX_REVIEW_LENGTH = 25;
const string FILE_PATH = "movies.txt";

struct Movie {
    string name;
    int rating;
    double releaseYear;
    string review;
};

class MovieList {
public:
    MovieList();
    ~MovieList();

    void runMovieSystem();
    void addMovie();
    void removeMovie();
    void modifyMovie();
    void displayMovieList();
    void displayMoviesInRange();
    void searchMovie();
    void mergeSort(int, int);
    void merge(int, int, int);
    void mergeSortWrapper();
    void resizeArrays();
    void saveDataToFile();
    void loadDataFromFile();

private:
    Movie* movies;
    int capacity;
    int pos;
};

#endif // MOVIELIST_H
