#include "movieList.h"
#include <iostream>
#include<fstream>
using namespace std;

MovieList::MovieList() : capacity(INITIAL_CAPACITY), pos(0) {
    movies = new Movie[capacity];

}

MovieList::~MovieList() {

    delete[] movies;
}

void MovieList::saveDataToFile() {
    ofstream outfile(FILE_PATH);

    if (!outfile.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < pos; i++) {
        outfile << movies[i].name << "|" << movies[i].rating << "|" << movies[i].releaseYear << "|" << movies[i].review << endl;
    }

    outfile.close();
}

void MovieList::loadDataFromFile() {
    ifstream inFile(FILE_PATH);

    if (!inFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    pos = 0;
    while (getline(inFile, movies[pos].name, '|')) {
        inFile >> movies[pos].rating;
        inFile.ignore();
        inFile >> movies[pos].releaseYear;
        inFile.ignore();
        getline(inFile, movies[pos].review);
        pos++;
    }

    inFile.close();
}

void MovieList::runMovieSystem() {
    int decision = 0;
    pos = 0; // Initialize pos

    do {
        // Display Menu Options
        cout << "Movie List" << endl;
        cout << "Press [1] to add to the movie list" << endl;
        cout << "Press [2] to remove a movie" << endl;
        cout << "Press [3] to Modify from the movie list" << endl;
        cout << "Press [4] to display the movie list" << endl;
        cout << "Press [5] to display movies in a range of years" << endl;
        cout << "Press [6] to search a movie" << endl;
        cout << "Press [7] to exit the program" << endl;

        cin >> decision;
        cin.ignore(); // Clear the input buffer

        // Actions based on user input
        if (decision == 1) {
            addMovie();
        }
        else if (decision == 2) {
            removeMovie();
        }
        else if (decision == 3) {
            modifyMovie();
        }
        else if (decision == 4) {
            mergeSortWrapper();
            displayMovieList();
        }
        else if (decision == 5) {
            displayMoviesInRange();
        }
        else if (decision == 6) {
            searchMovie();
        }
        else if (decision == 7) {
            cout << "Exiting the program." << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (decision != 7); // Continue the loop until the user chooses to exit
}

void MovieList::addMovie() {
    ofstream outfile("movies.txt", ios::app);

    if (pos == capacity) {
        resizeArrays();
       
    }

    // Prompt and store the name of the movie
    cout << "Enter name of movie: ";
    getline(cin, movies[pos].name);
    outfile << movies[pos].name << "|";

    // Prompt and store the rating of the movie with validation
    do {
        cout << "Enter rating (1 - 5): ";
        cin >> movies[pos].rating;

        if (movies[pos].rating < 1 || movies[pos].rating > 5) {
            cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
        }
    } while (movies[pos].rating < 1 || movies[pos].rating > 5);

    outfile << movies[pos].rating << "|";

    // Prompt and store the release year of the movie
    cout << "Enter what year the movie released: ";
    cin >> movies[pos].releaseYear;
    outfile << movies[pos].releaseYear << "|";

    // Prompt and store the review of the movie
    cout << "Enter review for the movie (up to " << MAX_REVIEW_LENGTH << " characters): ";
    cin.ignore();
    getline(cin, movies[pos].review);

    outfile << movies[pos].review << endl;

    outfile.close();

    pos++;
}

void MovieList::removeMovie() {
    string removeMovie;
    ifstream inFile("movies.txt");

    // Prompt for the name of the movie to remove
    cout << "Enter the name of the movie you want to remove: ";
    getline(cin, removeMovie);
    // Convert to lowercase
    for (char& c : removeMovie) {
        c = tolower(c);
    }
    bool found = false;

    // Read data from the file into arrays
    pos = 0;
    while (getline(inFile, movies[pos].name, '|')) {
        inFile >> movies[pos].rating; // Read the rating
        inFile.ignore(); // Consume the '|' character
        inFile >> movies[pos].releaseYear; // Read the release year
        inFile.ignore(); // Consume the '|' character
        getline(inFile, movies[pos].review); // Read the review

        for (char& c : movies[pos].name) {
            c = tolower(c);
        }

        if (movies[pos].name == removeMovie) {
            found = true;
            // Shift all elements after the removal position to fill the gap
            for (int i = pos; i < capacity - 1; i++) {
                movies[i] = movies[i + 1];
            }
            pos--;
        }
        pos++;
    }

    inFile.close();

    // Rewrite the entire file with the modified data
    ofstream outfile("movies.txt");
    for (int i = 0; i < pos; i++) {
        outfile << movies[i].name << "|" << movies[i].rating << "|" << movies[i].releaseYear << "|" << movies[i].review << endl;
    }
    outfile.close();

    if (found) {
        cout << "Movie successfully removed from the inventory." << endl;
    }
    else {
        cout << "Movie not found in the inventory." << endl;
    }
}

void MovieList::modifyMovie() {
    string modifyMovie;
    ifstream inFile("movies.txt");

    // Prompt for the name of the movie to modify
    cout << "Enter the name of the movie you want to modify: ";
    getline(cin, modifyMovie);
    // Convert to lowercase
    for (char& c : modifyMovie) {
        c = tolower(c);
    }
    bool found = false;

    // Read data from the file into arrays
    pos = 0;
    while (getline(inFile, movies[pos].name, '|')) {
        inFile >> movies[pos].rating; // Read the rating
        inFile.ignore(); // Consume the '|' character
        inFile >> movies[pos].releaseYear; // Read the release year
        inFile.ignore(); // Consume the '|' character
        getline(inFile, movies[pos].review); // Read the review

        for (char& c : movies[pos].name) {
            c = tolower(c);
        }

        if (movies[pos].name == modifyMovie) {
            found = true;

            // Prompt and update the rating for the movie with validation
            do {
                cout << "Enter the new rating for the movie: ";
                cin >> movies[pos].rating;

                if (movies[pos].rating < 1 || movies[pos].rating > 5) {
                    cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
                }
            } while (movies[pos].rating < 1 || movies[pos].rating > 5);

            // Prompt and update the release year for the movie
            cout << "Enter the new release year for the movie: ";
            cin >> movies[pos].releaseYear;

            // Prompt and update the review for the movie
            cout << "Enter the new review for the movie (up to " << MAX_REVIEW_LENGTH << " characters): ";
            cin.ignore(); // Clear the input buffer
            getline(cin, movies[pos].review);
        }
        pos++;
    }

    inFile.close();

    // Rewrite the entire file with the modified data
    ofstream outfile("movies.txt");
    for (int i = 0; i < pos; i++) {
        outfile << movies[i].name << "|" << movies[i].rating << "|" << movies[i].releaseYear << "|" << movies[i].review << endl;
    }
    outfile.close();

    if (!found) {
        cout << "Movie not found in the inventory." << endl;
    }
}

void MovieList::displayMovieList() {
 
    loadDataFromFile();
   
  
    mergeSortWrapper();

    for (int i = 0; i < pos; i++) {
        cout << "Movie: " << movies[i].name << endl;
        cout << "Movie rating: " << movies[i].rating << endl;
        cout << "Release year: " << movies[i].releaseYear << endl;
        cout << "Review: " << movies[i].review << endl << endl;
    }
}

void MovieList::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }
}

void MovieList::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Movie* leftArray = new Movie[n1];
    Movie* rightArray = new Movie[n2];

    for (int i = 0; i < n1; i++) {
        leftArray[i] = movies[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = movies[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i].name <= rightArray[j].name) {
            movies[k] = leftArray[i];
            i++;
        } else {
            movies[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        movies[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        movies[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}
void MovieList::mergeSortWrapper() {
    mergeSort(0, pos - 1);
}

void MovieList::displayMoviesInRange() {
    int startYear, endYear;

    cout << "Enter the start year of the range: ";
    cin >> startYear;

    cout << "Enter the end year of the range: ";
    cin >> endYear;
    cout << endl;

    cout << "Movies Released in the Range " << startYear << " to " << endYear << ":" << endl;

    bool found = false;

    for (int i = 0; i < pos; i++) {
        if (movies[i].releaseYear >= startYear && movies[i].releaseYear <= endYear) {
            cout << "Name: " << movies[i].name << endl;
            cout << "Rating: " << movies[i].rating << endl;
            cout << "Release Year: " << movies[i].releaseYear << endl;
            cout << "Review: " << movies[i].review << endl << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No movies found in the specified range." << endl;
    }
}

void MovieList::searchMovie() {
    string exactSearch;

    cout << "Enter the name of the movie you want to search for: ";
    getline(cin, exactSearch);
    for (char& c : exactSearch) {
        c = tolower(c);
    }

    ifstream inFile("movies.txt");
    if (!inFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    bool found = false;

    pos = 0;
    while (getline(inFile, movies[pos].name, '|')) {
        inFile >> movies[pos].rating;
        inFile.ignore();
        inFile >> movies[pos].releaseYear;
        inFile.ignore();
        getline(inFile, movies[pos].review);

        for (char& c : movies[pos].name) {
            c = tolower(c);
        }

        if (movies[pos].name == exactSearch) {
            found = true;
            movies[pos].name[0] = toupper(movies[pos].name[0]);

            cout << "Movie: " << movies[pos].name << endl;
            cout << "Movie rating: " << movies[pos].rating << endl;
            cout << "Release year: " << movies[pos].releaseYear << endl;
            cout << "Review: " << movies[pos].review << endl << endl;
        }
        pos++;
    }

    inFile.close();

    if (!found) {
        cout << "Movie not found in the inventory." << endl;
    }
}

void MovieList::resizeArrays() {
    int newCapacity = capacity * 2;

    Movie* newMovies = new Movie[newCapacity];

    for (int i = 0; i < capacity; i++) {
        newMovies[i] = movies[i];
    }

    delete[] movies;

    movies = newMovies;

    capacity = newCapacity;

    cout << "Array resized. New capacity: " << capacity << endl;
}
