using namespace std;
#include <iostream>
#include <vector>
using std::vector;
using std::string;
enum class rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};
class Film{
public:
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(Review& r);
    bool RemoveReview(Review& r);
    bool ViewReviews();
};
class Review{
public:
    enum rank;
    string text;
    string autor;
};

class user{
public:
    string login;
    string name;
    bool IsAuthenticated;
    bool IsAdmin;
    user() : IsAuthenticated(false), IsAdmin(false) {}
};

