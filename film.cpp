#include <vector>
#include <swetrki.h>
using  std::vector;
using std::string;
class Film{
    string title;
    string keywords;
    vector<Review> Reviews;
    bool AddReview(Review& r);
    bool RemoveReview(Review& r);
    bool ViewReviews();
};