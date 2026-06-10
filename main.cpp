
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QMessageBox>
#include <QInputDialog>

#include "swetrki.h"


VectorStorage storage;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    
    Admin admin1;
    admin1.setLogin("admin");
    storage.Admins.push_back(admin); 

    LoggedUser user1;
    user1.setLogin("user1");
    storage.loggedUsers.push_back(user1);

    storage.getAllFilms();

    
    QWidget mainWindow;
    mainWindow.setWindowTitle("Knitted Sweaters - Recenzje Filmowe");
    mainWindow.resize(600, 500);

    QStackedWidget *stackedWidget = new QStackedWidget(&mainWindow);
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);
    mainLayout->addWidget(stackedWidget);

    
    static User* currentUser = nullptr;
    static std::string userRole = "Viewer";

    //widok logowania
    QWidget *loginPage = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(loginPage);

    loginLayout->addWidget(new QLabel("<h2>Logowanie</h2>"));
    
    QLineEdit *loginInput = new QLineEdit();
    loginInput->setPlaceholderText("Login");
    loginLayout->addWidget(loginInput);

    QLineEdit *passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Hasło");
    passwordInput->setEchoMode(QLineEdit::Password);
    loginLayout->addWidget(passwordInput);

    QPushButton *loginButton = new QPushButton("Zaloguj się");
    loginLayout->addWidget(loginButton);
    stackedWidget->addWidget(loginPage);

    //ekran główny
    QWidget *appPage = new QWidget();
    QVBoxLayout *appLayout = new QVBoxLayout(appPage);

    QLabel *welcomeLabel = new QLabel();
    appLayout->addWidget(welcomeLabel);

    // wyszukiwanie
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Wyszukaj tytuł lub słowa kluczowe...");
    QPushButton *searchButton = new QPushButton("Szukaj");
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);
    appLayout->addLayout(searchLayout);

    // Lista filmów
    QListWidget *filmListWidget = new QListWidget();
    appLayout->addWidget(new QLabel("<h3>Lista filmów:</h3>"));
    appLayout->addWidget(filmListWidget);

    // Przyciski akcji na dole
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QPushButton *addFilmButton = new QPushButton("Dodaj film");
    QPushButton *viewReviewsButton = new QPushButton("Wyświetl recenzje");
    QPushButton *addReviewButton = new QPushButton("Dodaj recenzję");
    QPushButton *deleteReviewButton = new QPushButton("Usuń recenzję");
    QPushButton *logoutButton = new QPushButton("Wyloguj");

    buttonsLayout->addWidget(addFilmButton);
    buttonsLayout->addWidget(viewReviewsButton);
    buttonsLayout->addWidget(addReviewButton);
    buttonsLayout->addWidget(deleteReviewButton);
    buttonsLayout->addWidget(logoutButton);
    appLayout->addLayout(buttonsLayout);

    stackedWidget->addWidget(appPage);

    //odswiezanie listy filmów
    auto refreshFilmList = [&](const std::string &filter = "") {
        filmListWidget->clear();
        for (size_t i = 0; i < storage.FilmsBase.size(); ++i) {
            const auto &film = storage.FilmsBase[i];
            if (filter.empty() || 
                film.title.find(filter) != std::string::npos || 
                film.keywords.find(filter) != std::string::npos) {
                
                QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(film.title));
                item->setData(Qt::UserRole, QVariant::fromValue(i)); 
                filmListWidget->addItem(item);
            }
        }
    };

    

    // klikniecie zaloguj sie
    QObject::connect(loginButton, &QPushButton::clicked, [&]() {
        std::string login = loginInput->text().toStdString();
      

        currentUser = storage.findUser(login);
        if (currentUser != nullptr) {
            userRole = currentUser->getRole();
            welcomeLabel->setText(QString("<h3>Zalogowano jako: <b>%1</b> (Rola: %2)</h3>")
                                  .arg(QString::fromStdString(currentUser->getLogin()))
                                  .arg(QString::fromStdString(userRole)));
            
            loginInput->clear();
            passwordInput->clear();
            refreshFilmList();
            stackedWidget->setCurrentWidget(appPage);
        } else {
            QMessageBox::warning(&mainWindow, "Błąd", "Nie znaleziono użytkownika!");
        }
    });

    // wyszukiwanie
    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        refreshFilmList(searchInput->text().toStdString());
    });

    // klikniecie na film
    QObject::connect(filmListWidget, &QListWidget::itemClicked, [&](QListWidgetItem *item) {
        size_t index = item->data(Qt::UserRole).toUInt();
        std::string info = "Tytuł: " + storage.FilmsBase[index].title + "\nSłowa kluczowe: " + storage.FilmsBase[index].keywords;
        QMessageBox::information(&mainWindow, "Informacje o filmie", QString::fromStdString(info));
    });

    // Dodawanie nowego filmu 
    QObject::connect(addFilmButton, &QPushButton::clicked, [&]() {
        if (userRole == "Viewer") {
            QMessageBox::critical(&mainWindow, "Brak uprawnień", "Twój status to Viewer. Możesz tylko wyświetlać dane!");
            return;
        }

        bool okTitle, okKeywords;
        QString title = QInputDialog::getText(&mainWindow, "Dodaj film", "Podaj tytuł filmu:", QLineEdit::Normal, "", &okTitle);
        if (!okTitle || title.isEmpty()) return;

        QString keywords = QInputDialog::getText(&mainWindow, "Dodaj film", "Podaj słowa kluczowe (po przecinku):", QLineEdit::Normal, "", &okKeywords);
        if (!okKeywords) return;

        Film f;
        f.title = title.toStdString();
        f.keywords = keywords.toStdString();
        storage.SaveFilm(f);

        refreshFilmList();
        QMessageBox::information(&mainWindow, "Sukces", "Film został dodany do bazy.");
    });

    // Wyświetlanie recenzji 
    QObject::connect(viewReviewsButton, &QPushButton::clicked, [&]() {
        QListWidgetItem *selected = filmListWidget->currentItem();
        if (!selected) {
            QMessageBox::warning(&mainWindow, "Błąd", "Wybierz film z listy!");
            return;
        }
        size_t index = selected->data(Qt::UserRole).toUInt();
        
        storage.FilmsBase[index].ViewReviews(); 
        
    });

    // Dodawanie recenzj
    QObject::connect(addReviewButton, &QPushButton::clicked, [&]() {
        if (userRole == "Viewer") {
            QMessageBox::critical(&mainWindow, "Brak uprawnień", "Możesz tylko wyświetlać recenzje!");
            return;
        }
        QListWidgetItem *selected = filmListWidget->currentItem();
        if (!selected) {
            QMessageBox::warning(&mainWindow, "Błąd", "Wybierz film z listy!");
            return;
        }
        size_t index = selected->data(Qt::UserRole).toUInt();

        std::string authorLogin = "";
        if (currentUser != nullptr) {
            authorLogin = currentUser->getLogin();
        }

        storage.FilmsBase[index].AddReview(authorLogin);
    });

    // Usuwanie recenzji
    QObject::connect(deleteReviewButton, &QPushButton::clicked, [&]() {
        if (userRole == "Viewer" || userRole == "LoggedUser") {
            QMessageBox::critical(&mainWindow, "Brak uprawnień", "Możesz tylko wyświetlać recenzje!");
            return;
        }
        QListWidgetItem *selected = filmListWidget->currentItem();
        if (!selected) {
            QMessageBox::warning(&mainWindow, "Błąd", "Wybierz film z listy!");
            return;
        }
        size_t index = selected->data(Qt::UserRole).toUInt();

        std::vector<Review> currentReviews = storage.getReviewsForFilm(storage.FilmsBase[index].title);
        if (currentReviews.empty()) {
            QMessageBox::information(&mainWindow, "Info", "Brak recenzji do usunięcia.");
            return;
        }

        QStringList items;
        for (size_t i = 0; i < currentReviews.size(); ++i) {
            items << QString("Indeks %1: %2 (Autor: %3, Ocena: %4)")
                     .arg(i)
                     .arg(QString::fromStdString(currentReviews[i].text))
                     .arg(QString::fromStdString(currentReviews[i].author))
                     .arg(currentReviews[i].rating);
        }

        bool ok;
        QString item = QInputDialog::getItem(&mainWindow, "Usuń recenzję", "Wybierz recenzję do usunięcia:", items, 0, false, &ok);
        if (ok && !item.isEmpty()) {
            int rindex = items.indexOf(item);
            if (rindex >= 0 && rindex < static_cast<int>(currentReviews.size())) {
                Review r = currentReviews[rindex];
                storage.FilmsBase[index].RemoveReview(r);
                QMessageBox::information(&mainWindow, "Sukces", "Recenzja usunięta.");
            }
        }
    });

    // wylogowanie
    QObject::connect(logoutButton, &QPushButton::clicked, [&]() {
        currentUser = nullptr;
        userRole = "Viewer";
        searchInput->clear();
        stackedWidget->setCurrentWidget(loginPage);
    });

    // Uruchomienie okna
    mainWindow.show();
    return app.exec();
}
