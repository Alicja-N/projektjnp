#include <iostream>
#include <cassert>
#include "swetrki.h"
#include <gtest/gtest.h>


TEST(UserTest, Initialization) {
    User u("admin", "Admin");
    EXPECT_EQ(u.getLogin(), "admin");
    EXPECT_FALSE(u.checkAdmin());
}

TEST(UserTest, LoginFunctionality) {
    User u("user1", "Kowalski");
    EXPECT_FALSE(u.isUserAuthenticated());
    u.loginUser();
    EXPECT_TRUE(u.isUserAuthenticated());
}


TEST(FilmTest, AddReviewIncreasesCount) {
    Film f;
    f.title = "Diuna";
    
    // Na początku powinno być 0
    EXPECT_EQ(f.getReviewsCount(), 0);

    Review r1;
    r1.autor = "Ania";
    r1.text = "Mega film!";
    r1.rating = Rank::DOBRY;

    f.AddReview(r1);

    // Po dodaniu powinno być dokładnie 1
    EXPECT_EQ(f.getReviewsCount(), 1);
}