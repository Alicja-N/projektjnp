using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;

class Film{
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(Review& r);
    bool RemoveReview(Review& r);
    bool ViewReviews();
};
class Review{
public:
    int rank;
    string text;
    string autor;
};

class user{
public:
    string login;
    string name;
    bool IsAuthenticated;
    bool IsAdmin;
};

