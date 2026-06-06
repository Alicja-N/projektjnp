using namespace std;
#include "swetrki.h"
#include <iostream>
bool Film::AddReview(){
        int rank;
        string author;
        string text;    
        cout<< "Podaj ocenę w skali 1-5"<< endl;
        cin>> rank;
        cout << "Napisz treść renezji:"<< endl;
        cin>> text;
        cout<< "Podaj autora recenzji:"<< endl;
        cin>> author;
        Review r;
            r.rating = rank;
            r.text = text;
            r.author = author;
            r.filmtitle = this->title;
        return storage.SaveReview(r);
};
bool Film::RemoveReview(Review& r){
        return storage.DeleteReview(this->title, r.author);
};
bool Film::ViewReviews(){
    vector<Review> Reviews = storage.getReviewsForFilm(this->title);
    if (Reviews.empty()) {
        cout << "Brak recenzji dla filmu: " << title << endl;
        return false;
    }
    for (const auto& r : Reviews) {
        cout << "Autor: " << r.author;
        cout << " | Ocena: " << r.rating<< endl; 
        cout << " | Tresc: " << r.text << endl;
    }
    return true;
};
int Film::getReviewsCount() const {
    return storage.getReviewsCount(this->title);
};
bool VectorStorage::SaveReview(const Review& r) {
            ReviewsBase.push_back(r);
            return true;
}

bool VectorStorage::DeleteReview(const string& filmTitle, const string& author) {
    for (auto it = ReviewsBase.begin(); it != ReviewsBase.end(); ++it) {
        if (it->filmtitle == filmTitle && it->author == author) {
            ReviewsBase.erase(it);
            return true; // Usunięto pomyślnie
        }
    }
    return false; // Nie znaleziono takiej recenzji
}

vector<Review> VectorStorage::getReviewsForFilm(const string& filmTitle) {
    vector<Review> filmReviews;
    for (const auto& r : ReviewsBase) {
        if (r.filmtitle == filmTitle) {
            filmReviews.push_back(r);
        }
    }
    return filmReviews;
}

int VectorStorage::getReviewsCount(const string& filmTitle) const {
    int count = 0;
    for (const auto& r : ReviewsBase) {
        if (r.filmtitle == filmTitle) count++;
    }
    return count;
}

bool VectorStorage::SaveFilm(const Film& f) {
    FilmsBase.push_back(f);
    return true;
}

vector<Film> VectorStorage::getAllFilms() {
    return FilmsBase;
}


User* VectorStorage::findUser(const string& login) {
    for (auto& a : Admins) {
        if (a.getLogin() == login) return &a; 
    }
    for (auto& lu : loggedUsers) {
        if (lu.getLogin() == login) return &lu;
    }
    Viewer* defaultViewer = new Viewer();
    defaultViewer->setLogin("Gość_" + login); 
    return defaultViewer;
}