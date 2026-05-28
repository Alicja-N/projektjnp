#include "swetrki.h"
#include <iostream>
using namespace std;

bool VectorStorage::addReview(const Review& r) {
            allReviews.push_back(r);
            return true;
}

bool VectorStorage::removeReview(const string& filmTitle, const string& author) {
    for (auto it = allReviews.begin(); it != allReviews.end(); ++it) {
        if (it->filmTitle == filmTitle && it->author == author) {
            allReviews.erase(it);
            return true; // Usunięto pomyślnie
        }
    }
    return false; // Nie znaleziono takiej recenzji
}

vector<Review> VectorStorage::getReviewsForFilm(const string& filmTitle) {
    vector<Review> filmReviews;
    for (const auto& r : allReviews) {
        if (r.filmTitle == filmTitle) {
            filmReviews.push_back(r);
        }
    }
    return filmReviews;
}

int VectorStorage::getReviewsCount(const string& filmTitle) const {
    int count = 0;
    for (const auto& r : allReviews) {
        if (r.filmTitle == filmTitle) count++;
    }
    return count;
}

bool VectorStorage::addFilm(const Film& f) {
    allFilms.push_back(f);
    return true;
}

vector<Film> VectorStorage::getAllFilms() {
    return allFilms;
}


bool VectorStorage::registerUser(const User& u) {
    allUsers.push_back(u);
    return true;
}

User* VectorStorage::findUser(const string& login) {
    for (auto& u : allUsers) {
        if (u.login == login) return &u;
    }
    return nullptr;
}
