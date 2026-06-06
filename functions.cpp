#include "swetrki.h"
#include <iostream>
using namespace std;
VectorStorage storage;
bool Film::AddReview(){
        int rank;
        string author;
        string text;    
        cout<< "Podaj ocenę w skali 1-5"<< endl;
        cin>> rank;
        cout << "Napisz treść renezji:"<< endl;
        cin.ignore();
        getline(cin, text);
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