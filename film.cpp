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
    bool RemoveReview(Review& r);
    bool ViewReviews();
};