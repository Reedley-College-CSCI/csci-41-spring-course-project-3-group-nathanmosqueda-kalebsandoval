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
    void mergeSortAsc(int, int);
    void mergeAsc(int, int, int);
    void mergeSortWrapperAsc();
    void mergeSortDesc(int, int);
    void mergeDesc(int, int, int);
    void mergeSortWrapperDesc();
    void mergeSortRatingDesc(int, int);
    void mergeRatingDesc(int, int, int);
    void mergeSortWrapperRatingDesc();
    void mergeSortRatingAsc(int, int);
    void mergeRatingAsc(int, int, int);
    void mergeSortWrapperRatingAsc();
    void resizeArrays();
    void saveDataToFile();
    void loadDataFromFile();

private:
    Movie* movies;
    int capacity;
    int pos;
};

#endif // MOVIELIST_H
