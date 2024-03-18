#include "movieList.h"
#include <iostream>
#include<fstream>
#include <windows.h>
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
DWORD start = GetTickCount();
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

DWORD end = GetTickCount(); // Stop measuring time

DWORD elapsedTime = end - start;
cout << "Elapsed time in runMovieSystem(): " << elapsedTime << " ms" << endl;
}

void MovieList::addMovie() {
DWORD start = GetTickCount();
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
if (movies[pos].review.length() > MAX_REVIEW_LENGTH){
  cout << "Review is too long. Please enter a review with a maximum of " << MAX_REVIEW_LENGTH << endl;
  cin.ignore();
  getline(cin, movies[pos].review);
}
outfile << movies[pos].review << endl;

DWORD end = GetTickCount();
DWORD elapsedTime = end - start;
cout << "Time taken to add movie: " << elapsedTime << " ms" << endl;

cout << "Movie added successfully. Big O: O(1)" << endl;

outfile.close();

pos++;
}

void MovieList::removeMovie() {
DWORD start = GetTickCount();
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

DWORD end = GetTickCount();
DWORD elapsedTime = end - start;
cout << "Time taken to remove movie: " << elapsedTime << " ms" << endl;

cout << "Movie removed successfully. Big O: O(n)" << endl;
}

void MovieList::modifyMovie() {
DWORD start = GetTickCount();
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

DWORD end = GetTickCount();
DWORD elapsedTime = end - start;
cout << "Time taken to modify movie: " << elapsedTime << " ms" << endl;

cout << "Movie modified successfully. Big O: O(n)" << endl;
}

void MovieList::displayMovieList() {
DWORD start = GetTickCount();
loadDataFromFile();
int sortChoice;
cout << "Choose list sorting format: " << endl;
cout << "1. Sort Alphabetically A-Z" << endl;
cout << "2. Sort Alphabetically Z-A" << endl;
cout << "3. Sort by Rating 5-1" << endl;
cout << "4. Sort by Rating 1-5" << endl;
cin >> sortChoice;
if (sortChoice == 1) {
mergeSortWrapperAsc();
}
else if (sortChoice == 2) {
mergeSortWrapperDesc();
}
else if (sortChoice == 3) {
mergeSortWrapperRatingDesc();
}
else if (sortChoice == 4) {
mergeSortWrapperRatingAsc();
}
else {
cout << "Invalid choice. Please try again." << endl;
}
for (int i = 0; i < pos; i++) {
cout << "Movie: " << movies[i].name << endl;
cout << "Movie rating: " << movies[i].rating << endl;
cout << "Release year: " << movies[i].releaseYear << endl;
cout << "Review: " << movies[i].review << endl << endl;
}

DWORD end = GetTickCount();
DWORD elapsedTime = end - start;
cout << "Time taken to display movie list: " << elapsedTime << " ms" << endl;

cout << "Movies displayed successfully. Big O: O(n log n)" << endl;
}

void MovieList::mergeSortAsc(int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;

mergeSortAsc(left, mid);
mergeSortAsc(mid + 1, right);

mergeAsc(left, mid, right);
}
}

void MovieList::mergeAsc(int left, int mid, int right) {
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
}
else {
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
void MovieList::mergeSortWrapperAsc() {
mergeSortAsc(0, pos - 1);
}
void MovieList::mergeSortDesc(int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;

mergeSortDesc(left, mid);
mergeSortDesc(mid + 1, right);

mergeDesc(left, mid, right);
}
}

void MovieList::mergeDesc(int left, int mid, int right) {
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

if (leftArray[i].name > rightArray[j].name) {
movies[k] = leftArray[i];
i++;
}
else {
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

void MovieList::mergeSortWrapperDesc() {
mergeSortDesc(0, pos - 1);
}

void MovieList::mergeSortRatingDesc(int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;

mergeSortRatingDesc(left, mid);
mergeSortRatingDesc(mid + 1, right);

mergeRatingDesc(left, mid, right);
}
}

void MovieList::mergeRatingDesc(int left, int mid, int right) {
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
    
if (leftArray[i].rating > rightArray[j].rating) {
movies[k] = leftArray[i];
i++;
}
else {
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

void MovieList::mergeSortWrapperRatingDesc() {
mergeSortRatingDesc(0, pos - 1);
}
void MovieList::mergeSortRatingAsc(int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;

mergeSortRatingAsc(left, mid);
mergeSortRatingAsc(mid + 1, right);

mergeRatingAsc(left, mid, right);
}
}

void MovieList::mergeRatingAsc(int left, int mid, int right) {
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
if (leftArray[i].rating <= rightArray[j].rating) {
movies[k] = leftArray[i];
i++;
}
else {
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

void MovieList::mergeSortWrapperRatingAsc() {
mergeSortRatingAsc(0, pos - 1);
}

void MovieList::displayMoviesInRange() {
DWORD start = GetTickCount();
loadDataFromFile();
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

DWORD end = GetTickCount();
DWORD elapsedTime = end - start;
cout << "Time taken to display movies in range: " << elapsedTime << " ms" << endl;

cout << "Movies in range displayed successfully. Big O: O(n)" << endl;
}

void MovieList::searchMovie() {
DWORD start = GetTickCount();
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

DWORD end = GetTickCount();
DWORD elapsedTime = end - start;
cout << "Time taken to search movie: " << elapsedTime << " ms" << endl;
cout << "Movie search completed successfully. Big O: O(n)" << endl;
}

void MovieList::resizeArrays() {
DWORD start = GetTickCount();
int newCapacity = capacity * 2;

Movie* newMovies = new Movie[newCapacity];

for (int i = 0; i < capacity; i++) {
newMovies[i] = movies[i];
}

delete[] movies;

movies = newMovies;

capacity = newCapacity;

cout << "Array resized. New capacity: " << capacity << endl;

DWORD end = GetTickCount(); // Stop measuring time
DWORD elapsedTime = end - start; // Calculate elapsed time
cout << "Time taken to resize arrays: " << elapsedTime << " ms" << endl;

cout << "Array resized successfully. Big O: O(n)" << endl;
}
