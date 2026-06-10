
#include "swetrki.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstddef>   
#include <string>    

#include "swetrki.h"
#include <QInputDialog>
#include <QMessageBox>

#include "swetrki.h"
#include <QInputDialog>
#include <QMessageBox>

void WczytajFilmyZPliku(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    
    if (!plik.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku: " << nazwaPliku << std::endl;
        return;
    }

    std::string linia;
    // Czytamy plik linijka po linijce
    while (std::getline(plik, linia)) {
        if (linia.empty()) continue; // Pomijaj puste linie

        std::stringstream ss(linia);
        std::string tytul;
        std::string slowaKluczowe;

        // Rozdzielamy tekst za pomocą średnika ';'
        if (std::getline(ss, tytul, ';') && std::getline(ss, slowaKluczowe)) {
            Film f;
            f.title = tytul;
            f.keywords = slowaKluczowe;
            
            // Zapisujemy wczytany film do bazy danych
            storage.SaveFilm(f);
        }
    }

    plik.close();
}

bool Film::AddReview(const std::string& loggedInUser) {
    bool okRank, okText;

    // 1. Pobranie oceny (1-5)
    int rank = QInputDialog::getInt(nullptr, "Dodaj recenzję", 
                                    "Podaj ocenę w skali 1-5:", 
                                    5, 1, 5, 1, &okRank);
    if (!okRank) return false; 

    // 2. Pobranie treści recenzji
    QString qText = QInputDialog::getMultiLineText(nullptr, "Dodaj recenzję", 
                                                   "Napisz treść recenzji:", 
                                                   "", &okText);
    if (!okText || qText.isEmpty()) return false;

    // 3. Automatyczne przypisanie autora (zamiast QInputDialog)
    std::string author = loggedInUser;
    if (author.empty()) {
        author = "Anonim"; // Zabezpieczenie, gdyby funkcja została wywołana bez podania usera (np. w testach)
    }

    // 4. Przepisanie danych do struktury recenzji
    Review r;
    r.rating = rank;
    r.text = qText.toStdString();
    r.author = author; // Przypisanie automatycznego autora
    r.filmtitle = this->title;

    // 5. Zapis i komunikat
    bool success = storage.SaveReview(r);
    if (success) {
        QMessageBox::information(nullptr, "Sukces", "Recenzja została pomyślnie zapisana!");
    } else {
        QMessageBox::warning(nullptr, "Błąd", "Nie udało się zapisać recenzji.");
    }

    return success;
}
bool Film::RemoveReview(Review& r){
        return storage.DeleteReview(this->title, r.author);
};
bool Film::ViewReviews() {
    std::vector<Review> reviews = storage.getReviewsForFilm(this->title);
    if (reviews.empty()) {
        QMessageBox::information(nullptr, "Recenzje", "Ten film nie posiada jeszcze żadnych recenzji.");
        return true;
    }

    QString allReviewsText = QString("<h3>Recenzje dla filmu: %1</h3><hr>")
                             .arg(QString::fromStdString(this->title));

    for (const auto& r : reviews) {
        allReviewsText += QString("<p><b>Autor:</b> %1<br>"
                                  "<b>Ocena:</b> %2/5<br>"
                                  "<b>Treść:</b> %3</p><hr>")
                          .arg(QString::fromStdString(r.author))
                          .arg(r.rating)
                          .arg(QString::fromStdString(r.text));
    }

    QMessageBox::information(nullptr, "Lista Recenzji", allReviewsText);
    return true;
}
int Film::getReviewsCount() const {
    return storage.getReviewsCount(this->title);
};
bool VectorStorage::SaveReview(const Review& r) {
            ReviewsBase.push_back(r);
            return true;
}

bool VectorStorage::DeleteReview(const std::string& filmTitle, const std::string& author) {
    for (auto it = ReviewsBase.begin(); it != ReviewsBase.end(); ++it) {
        if (it->filmtitle == filmTitle && it->author == author) {
            ReviewsBase.erase(it);
            return true; // Usunięto pomyślnie
        }
    }
    return false; // Nie znaleziono takiej recenzji
}

std::vector<Review> VectorStorage::getReviewsForFilm(const std::string& filmTitle) {
    std::vector<Review> filmReviews;
    for (const auto& r : ReviewsBase) {
        if (r.filmtitle == filmTitle) {
            filmReviews.push_back(r);
        }
    }
    return filmReviews;
}

int VectorStorage::getReviewsCount(const std::string& filmTitle) const {
    int count = 0;
    for (const auto& r : ReviewsBase) {
        if (r.filmtitle == filmTitle) count++;
    }
    return count;
}

bool VectorStorage::SaveFilm(const Film& f) {
    FilmsBase.push_back(f);
    return true;
}

std::vector<Film> VectorStorage::getAllFilms() {
    return FilmsBase;
}


User* VectorStorage::findUser(const std::string& login) {
    for (auto& a : Admins) {
        if (a.getLogin() == login) return &a; 
    }
    for (auto& lu : loggedUsers) {
        if (lu.getLogin() == login) return &lu;
    }
    Viewer* defaultViewer = new Viewer();
    defaultViewer->setLogin("Gość_" + login); 
    return defaultViewer;
}