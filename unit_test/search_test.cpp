#include <gtest/gtest.h>
#include <QString>
#include "search.h"

TEST(Search, searchBefore)
{
    Search s;

    QString text = "This is an example.";
    QString substing = "an";
    int index = 0;

    s.searchBefore (text, substing, &index);
    EXPECT_EQ(index, 8);
}

TEST(Search, searchAfter)
{
    Search s;

    QString text = "This is an example.";
    QString substing = "an";
    int index = 0;

    s.searchAfter (text, substing, &index);
    EXPECT_EQ(index, 10);
}
