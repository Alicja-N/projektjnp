
#include "swetrki.h"
#include <iostream>
#include <cstddef>   
#include <string>    


bool Film::AddReview(){
        int rank;
        std::string author;
        std::string text;    
        std::cout<< "Podaj ocenę w skali 1-5"<< std::endl;
        std::cin>> rank;
        std::cout << "Napisz treść renezji:"<< std::endl;
        std::cin.ignore();
        std::getline(std::cin, text);
        std::cout<< "Podaj autora recenzji:"<< std::endl;
        std::cin>> author;
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
    std::vector<Review> Reviews = storage.getReviewsForFilm(this->title);
    if (Reviews.empty()) {
        std::cout << "Brak recenzji dla filmu: " << title << std::endl;
        return false;
    }
    for (const auto& r : Reviews) {
        std::cout << "Autor: " << r.author;
        std::cout << " | Ocena: " << r.rating<< std::endl; 
        std::cout << " | Tresc: " << r.text << std::endl;
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

bool VectorStorage::DeleteReview(const std::string& filmTitle, const std::string& author) {
    for (auto it = ReviewsBase.begin(); it != ReviewsBase.end(); ++it) {
        if (it->filmtitle == filmTitle && it->author == author) {
            ReviewsBase.erase(it);
            return true; // Usunięto pomyślnie
        }
    }
    return false; // Nie znaleziono takiej recenzji
}

std::vector<Review> VectorStorage::getReviewsForFilm(const std::string& filmTitle) {
    std::vector<Review> filmReviews;
    for (const auto& r : ReviewsBase) {
        if (r.filmtitle == filmTitle) {
            filmReviews.push_back(r);
        }
    }
    return filmReviews;
}

int VectorStorage::getReviewsCount(const std::string& filmTitle) const {
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

std::vector<Film> VectorStorage::getAllFilms() {
    return FilmsBase;
}


User* VectorStorage::findUser(const std::string& login) {
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