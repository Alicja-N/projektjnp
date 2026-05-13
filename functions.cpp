#include "swetrki.h"
#include <iostream>
using namespace std;
bool Film::AddReview(Review& r){
        Reviews.push_back(r);
        return true;
};
bool Film::RemoveReview(Review& r){
    for(int i=0;i<Reviews.size();i++){
        if(Reviews[i].autor==r.autor){
            Reviews.erase(Reviews.begin()+i);
            return true;
        }
    }
    return false;
};
bool Film::ViewReviews(){
    if (Reviews.empty()) {
        cout << "Brak recenzji dla filmu: " << title << endl;
        return false;
    }
    for (const auto& r : Reviews) {
        cout << "Autor: " << r.autor 
             << " | Ocena: " << static_cast<int>(r.rating) 
             << " | Tresc: " << r.text << endl;
    }
    return true;
}