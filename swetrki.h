using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;

class Film{
public:
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(Review& r);
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

