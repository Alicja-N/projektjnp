#include <vector>
#include <swetrki.h>
using  std::vector;
using std::string;
class Film{
public:
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(){
        int rank;
        string author;
        string text;
        cout<< "Podaj ocenę w skali 1-5"<< endl;
        cin >> rank;
        cout << "Napisz treść renezji:"<< endl;
        cin>> text;
        cout<< "Podaj autora recenzji:"<< endl;
        cin>> author;
        Review r;
            r.rating = rank;
            r.text = text;
            r.author = author;
            Reviews.push_back(r);
        return true;
    };
    bool AddReview(const Review& r){
        Reviews.push_back(r);
        return true;
    }
    bool RemoveReview(Review& r){
        for(int i=0;i<Reviews.size();i++){
            if(Reviews[i].author==r.author){
                Reviews.erase(Reviews.begin()+i);
                return true;
            }
        }
        return false;
    };
    bool ViewReviews(){
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
    }
};