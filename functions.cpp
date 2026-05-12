#include <swetrki.h>
using std::string;
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
        for(int i=0;i<Reviews.size();i++){
            cout<<Reviews[i].autor<<" "<<Reviews[i].rank<<" "<<Reviews[i].text<<endl;
        }
        return true;
    };