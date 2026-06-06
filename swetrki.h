
#ifndef SWETRKI_H
#define SWETRKI_H



#include <string>
#include <vector>
#include <cstddef>   

//enum class Rank { FATALNY = 1, SLABY = 2, SREDNI = 3, DOBRY = 4,REWELACYJNY = 5};
class Review{
public:
    int id;
    int rating;
    std::string text;
    std::string author;
    std::string filmtitle;
};

class Film{
public:
    int id;
    std::string title;
    std::string keywords;
    bool AddReview();
    bool RemoveReview(Review& r);
    bool ViewReviews();
    int getReviewsCount() const;
};
class User {
protected:
    std::string login;
    std::string name;
public:
    virtual ~User() = default; // idk to trzeba dac do klasy abstrakcyjnej z jakiegos powodu
    
    std::string getLogin() const { return login; }// getter- odczytuje ukryty login uzytkowanika
    void setLogin(std::string l) { login = l; }// setter - zmiana loginu

    // funkcja wirtualna- powoduje ze to jest klasa abstrakcyjna
    virtual std::string getRole() const = 0; 
};
class Viewer : public User {
public:
    std::string getRole() const override {
        return "Viewer"; 
    }
};
class LoggedUser : public User {
private:
    std::string password;
public:
    std::string getRole() const override{ 
        return "LoggedUser"; 
    }
    bool changePassword(std::string newPassword) {
        password = newPassword;
        return true;
    }
};

// Administrator
class Admin : public User {
public:
    std::string getRole() const override { return "Admin"; }
};
class VectorStorage {
    public:
        std::vector<Review> ReviewsBase;
        std::vector<Film> FilmsBase;
        std::vector<LoggedUser> loggedUsers; 
        std::vector<Admin> Admins;       
        bool SaveReview(const Review& r);
        bool DeleteReview(const std::string& filmTitle, const std::string& author);
        std::vector<Review> getReviewsForFilm(const std::string& filmTitle);
        int getReviewsCount(const std::string& filmTitle) const;
        bool SaveFilm(const Film& f);
        std::vector<Film> getAllFilms();
        User* findUser(const std::string& login);
};

extern VectorStorage storage;
#endif