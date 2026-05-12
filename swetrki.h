using namespace std;
#include <iostream>
#include <vector>
using std::vector;

class Film{
public:
    char* title;
    char* keywords;
    vector<Review> Reviews;
    bool AddReview(Review& r);
};
class Review{
public:
    int rank;
    char* text;
    char* autor;
};
class user{
public:
    char* login;
    char* name;
    bool IsAuthenticated;
    bool IsAdmin;
};

