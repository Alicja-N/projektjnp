using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;
//enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};
class Review{
public:
    int rating;
    string text;
    string author;
};

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
        cin>> rank;
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
    };;
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
    int getReviewsCount() const {
        return Reviews.size();
    }
};

class User{
public:
    string login;
    string name;
    bool isAuthenticated;
    bool isAdmin;
    bool isUserAuthenticated() const {
        return isAuthenticated;
    }
    void loginUser();
    bool checkAdmin() const;
    string getLogin() const;
};

