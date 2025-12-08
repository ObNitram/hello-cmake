#include <gtest/gtest.h>

#include "helloword/helloword.hpp"

TEST(DummyTest, BasicAssertions)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, Addition)
{
    EXPECT_EQ(1 + 1, 2);
    EXPECT_EQ(2 + 2, 4);
}

TEST(HelloTest, get_greeting)
{
    EXPECT_EQ(hello::get_greeting("Alice"), "Hello, Alice!");
    EXPECT_EQ(hello::get_greeting(), "Hello, World!");
}
