#include <iostream>
#include <limits>
#include <gtest/gtest.h>

#include "allocator.hpp"

class AllocatorTest : public ::testing::Test
{
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(AllocatorTest, test_usual)
{
    Allocator allocator;
    ASSERT_NO_THROW(allocator.makeAllocator(256));
    ASSERT_NE(allocator.alloc(100), nullptr);
    ASSERT_NE(allocator.alloc(100), nullptr);
    ASSERT_EQ(allocator.alloc(100), nullptr);
    ASSERT_NO_THROW(allocator.makeAllocator(16));
    char* ptr1 = allocator.alloc(16);
    ASSERT_NE(ptr1, nullptr);
    ASSERT_EQ(allocator.alloc(1), nullptr);
    allocator.reset();
    char* ptr2 = allocator.alloc(8);
    ASSERT_NE(ptr2, nullptr);
    char* ptr3 = allocator.alloc(8);
    ASSERT_NE(ptr3, nullptr);
    ASSERT_EQ(ptr1, ptr2);
    ASSERT_NE(ptr1, ptr3);
}

TEST_F(AllocatorTest, test_bad_alloc)
{
    Allocator allocator;
    ASSERT_THROW(allocator.makeAllocator(-1), std::bad_alloc);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
