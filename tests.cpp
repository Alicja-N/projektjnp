
#include <gtest/gtest.h>
#include "swetrki.h"

// Test 1: Sprawdzenie, czy nowy film poprawnie zapisuje się w bazie
TEST(VectorStorageTest, SaveFilmCorrectly) {
    // Czyszczenie bazy przed testem (dobra praktyka)
    storage.FilmsBase.clear();

    Film f;
    f.title = "Incepcja";
    f.keywords = "sny,leo,bączek";

    bool success = storage.SaveFilm(f);

    EXPECT_TRUE(success);
    ASSERT_EQ(storage.FilmsBase.size(), 1);
    EXPECT_EQ(storage.FilmsBase[0].title, "Incepcja");
}

// Test 2: Sprawdzenie, czy wyszukiwanie istniejącego Admina działa
TEST(VectorStorageTest, FindExistingAdmin) {
    storage.Admins.clear();

    Admin a;
    a.setLogin("super_admin");
    storage.Admins.push_back(a);

    User* found = storage.findUser("super_admin");

    ASSERT_NE(found, nullptr);          // Sprawdzamy czy w ogóle coś znalazł
    EXPECT_EQ(found->getLogin(), "super_admin");
    std::string role = found->getRole();
    EXPECT_EQ(role, "Admin");
}

// Test 3: Sprawdzenie mechanizmu "Gościa" (Viewer) przy braku loginu
TEST(VectorStorageTest, ReturnsDefaultViewerWhenUserNotFound) {
    storage.Admins.clear();
    storage.loggedUsers.clear();

    // Szukamy loginu, którego na pewno nie ma w bazie
    User* found = storage.findUser("nieznany_gosc");

    ASSERT_NE(found, nullptr);          // Nie powinno zwrócić nullptr, tylko obiekt
    std::string guestRole = found->getRole();
    EXPECT_EQ(guestRole, "Viewer");
    EXPECT_EQ(found->getLogin(), "Gość_nieznany_gosc");

    // Ponieważ funkcja findUser tworzy w tym przypadku obiekt przez 'new', 
    // musimy posprzątać pamięć w teście, żeby uniknąć wycieków
    delete found;
}

// Test 4: Dodawanie i liczenie recenzji dla konkretnego filmu
TEST(VectorStorageTest, AddAndCountReviews) {
    storage.ReviewsBase.clear();

    Review r1;
    r1.filmtitle = "Shrek";
    r1.author = "Jan";
    r1.rating = 5;
    r1.text = "Klasyk!";

    Review r2;
    r2.filmtitle = "Shrek";
    r2.author = "Anna";
    r2.rating = 4;
    r2.text = "Dobry film.";

    Review r3;
    r3.filmtitle = "Inny Film";
    r3.author = "Jan";
    r3.rating = 2;

    storage.SaveReview(r1);
    storage.SaveReview(r2);
    storage.SaveReview(r3); // Ta recenzja jest do innego filmu

    // Sprawdzamy czy funkcja dobrze filtruje i zlicza recenzje tylko dla Shreka
    int shrekReviewsCount = storage.getReviewsCount("Shrek");
    EXPECT_EQ(shrekReviewsCount, 2);

    std::vector<Review> shrekReviews = storage.getReviewsForFilm("Shrek");
    ASSERT_EQ(shrekReviews.size(), 2);
    EXPECT_EQ(shrekReviews[0].author, "Jan");
    EXPECT_EQ(shrekReviews[1].author, "Anna");
}

// Test 5: Usuwanie recenzji z bazy danych
TEST(VectorStorageTest, DeleteReviewCorrectly) {
    storage.ReviewsBase.clear();

    Review r;
    r.filmtitle = "Matrix";
    r.author = "Neo";
    r.rating = 5;
    storage.SaveReview(r);

    // Próba usunięcia nieistniejącej recenzji (zły autor)
    bool deleteFailed = storage.DeleteReview("Matrix", "Trinitiy");
    EXPECT_FALSE(deleteFailed);
    EXPECT_EQ(storage.ReviewsBase.size(), 1); // Nadal powinna być 1 recenzja

    // Próba usunięcia poprawnej recenzji
    bool deleteSuccess = storage.DeleteReview("Matrix", "Neo");
    EXPECT_TRUE(deleteSuccess);
    EXPECT_TRUE(storage.ReviewsBase.empty()); // Baza powinna być pusta
}

// Główna funkcja uruchamiająca wszystkie testy GTest
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

