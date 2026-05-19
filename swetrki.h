using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;
//enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};
int rank;
string author;
string text;
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
    };;
    bool RemoveReview(Review& r);
    bool ViewReviews();
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

