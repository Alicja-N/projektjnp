#include <string>
#include <vector>
using std::vector;
using std::string;
//enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};
class Review{
public:
    int id;
    int rating;
    string text;
    string author;
    string filmtitle;
};

class Film{
public:
    int id;
    string title;
    string keywords;
    bool AddReview();
    bool RemoveReview(Review& r);
    bool ViewReviews();
    int getReviewsCount() const;
};
class User {
protected:
    string login;
    string name;
public:
    virtual ~User() = default; // idk to trzeba dac do klasy abstrakcyjnej z jakiegos powodu
    
    string getLogin() const { return login; }// getter- odczytuje ukryty login uzytkowanika
    void setLogin(string l) { login = l; }// setter - zmiana loginu

    // funkcja wirtualna- powoduje ze to jest klasa abstrakcyjna
    virtual string getRole() const = 0; 
};
class Viewer : public User {
public:
    string getRole() const {
        return "Viewer"; 
    }
};
class LoggedUser : public User {
private:
    string password;
public:
    string getRole() const { 
        return "LoggedUser"; 
    }
    bool changePassword(string newPassword) {
        password = newPassword;
        return true;
    }
};

// Administrator
class Admin : public User {
public:
    string getRole() const { return "Admin"; }
};
class VectorStorage {
    public:
        vector<Review> ReviewsBase;
        vector<Film> FilmsBase;
        vector<LoggedUser> loggedUsers; 
        vector<Admin> Admins;       
        bool SaveReview(const Review& r);
        bool DeleteReview(const string& filmTitle, const string& author);
        vector<Review> getReviewsForFilm(const string& filmTitle);
        int getReviewsCount(const string& filmTitle) const;
        bool SaveFilm(const Film& f);
        vector<Film> getAllFilms();
        User* findUser(const string& login);
};

extern VectorStorage storage;