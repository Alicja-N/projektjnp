#include <iostream>
#include <cassert>
#include "swetrki.h"
#include <gtest/gtest.h>


TEST(UserTest, Initialization) {
    User u{"admin", "Admin"};
    EXPECT_EQ(u.getLogin(), "admin");
    EXPECT_FALSE(u.checkAdmin());
}

TEST(UserTest, LoginFunctionality) {
    User u{"user1", "Kowalski"};
    EXPECT_FALSE(u.isUserAuthenticated());
    u.loginUser( );
    EXPECT_TRUE(u.isUserAuthenticated());
}


TEST_F(VectorStorageTest, RegistersAndFindsUser) {
    User u{"anowak", "secure_pass"};
    EXPECT_TRUE(storage.registerUser(u));

    User* found = storage.findUser("anowak");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->login, "anowak");
}

TEST_F(VectorStorageTest, ReturnsNullptrForNonExistentUser) {
    EXPECT_EQ(storage.findUser("ghost"), nullptr);
}

// Testy filmów
TEST_F(VectorStorageTest, AddsAndRetrievesFilms) {
    Film f{"Interstellar", 2014};
    EXPECT_TRUE(storage.addFilm(f));

    auto allFilms = storage.getAllFilms();
    ASSERT_EQ(allFilms.size(), 1);
    EXPECT_EQ(allFilms[0].title, "Interstellar");
}

// Testy recenzji
TEST_F(VectorStorageTest, ManagesReviewsCorrectly) {
    Review r1{"Gladiator", "krytyk1", "9/10"};
    Review r2{"Gladiator", "krytyk2", "5/10"};
    
    storage.addReview(r1);
    storage.addReview(r2);

    // Sprawdzenie licznika
    EXPECT_EQ(storage.getReviewsCount("Gladiator"), 2);
    EXPECT_EQ(storage.getReviewsCount("Inny Film"), 0);

    // Sprawdzenie pobierania listingu
    auto reviews = storage.getReviewsForFilm("Gladiator");
    ASSERT_EQ(reviews.size(), 2);
    EXPECT_EQ(reviews[0].author, "krytyk1");

    // Test usuwania
    EXPECT_TRUE(storage.removeReview("Gladiator", "krytyk1"));
    EXPECT_EQ(storage.getReviewsCount("Gladiator"), 1);

    // Ponowne usunięcie tego samego elementu
    EXPECT_FALSE(storage.removeReview("Gladiator", "krytyk1"));
}