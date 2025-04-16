#include "gtest/gtest.h"
#include "sort.h"
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

// функция для проверки анаграмм
bool compareAnagramGroups(std::vector<std::vector<std::string>> result,
    std::vector<std::vector<std::string>> expected) {
    if (result.size() != expected.size()) return false;

    for (auto& group : result) std::sort(group.begin(), group.end());
    for (auto& group : expected) std::sort(group.begin(), group.end());

    auto sort_key = [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
        if (a.empty() && b.empty()) return false;
        if (a.empty()) return true;
        if (b.empty()) return false;
        return a[0] < b[0];
        };
    std::sort(result.begin(), result.end(), sort_key);
    std::sort(expected.begin(), expected.end(), sort_key);

    return result == expected;
}


TEST(SortHashAlgorithmsTest, CopyTimeTest) {
    // min(x,y) + min_t | (t/x + t/y >= n-1)
    EXPECT_EQ(copyTime(5, 1, 2), 4);
    EXPECT_EQ(copyTime(4, 1, 1), 3);
    EXPECT_EQ(copyTime(1, 10, 100), 0);
    EXPECT_EQ(copyTime(2, 10, 100), 20); 
    EXPECT_EQ(copyTime(10, 3, 5), 21);
}

TEST(SortHashAlgorithmsTest, FeedAnimalsTest) {
    std::vector<int> animals1 = { 3, 4, 7 };
    std::vector<int> food1 = { 8, 1, 2 };
    EXPECT_EQ(feedAnimals(animals1, food1), 1);

    std::vector<int> animals2 = { 3, 8, 1, 4 };
    std::vector<int> food2 = { 1, 1, 2 };

    EXPECT_EQ(feedAnimals(animals2, food2), 1);

    std::vector<int> animals3 = { 1, 2, 2 };
    std::vector<int> food3 = { 7, 1 };

    EXPECT_EQ(feedAnimals(animals3, food3), 2);

    std::vector<int> animals4 = { 8, 2, 3, 2 };
    std::vector<int> food4 = { 1, 4, 3, 8 };

    EXPECT_EQ(feedAnimals(animals4, food4), 3);

    std::vector<int> animals5 = {};
    std::vector<int> food5 = { 1, 2 };
    EXPECT_EQ(feedAnimals(animals5, food5), 0);
}

TEST(SortHashAlgorithmsTest, FindTheDifferenceTest) {
    EXPECT_EQ(findTheDifference("uio", "oeiu"), 'e');
    EXPECT_EQ(findTheDifference("fe", "efo"), 'o');
    EXPECT_EQ(findTheDifference("bbb", "bbbb"), 'b');
    EXPECT_EQ(findTheDifference("", "a"), 'a');

    EXPECT_EQ(findTheDifference("ab", "ab"), '\0');
    EXPECT_EQ(findTheDifference("abc", "ab"), '\0');
}

TEST(SortHashAlgorithmsTest, TwoSumTest) {
    std::vector<int> result1 = twoSum({ 2, 7, 11, 15 }, 9);

    std::sort(result1.begin(), result1.end());
    EXPECT_EQ(result1, (std::vector<int>{0, 1}));

    std::vector<int> result2 = twoSum({ 3, 2, 4 }, 6);
    std::sort(result2.begin(), result2.end());
    EXPECT_EQ(result2, (std::vector<int>{1, 2}));

    std::vector<int> result3 = twoSum({ 3, 3 }, 6);
    std::sort(result3.begin(), result3.end());
    EXPECT_EQ(result3, (std::vector<int>{0, 1}));

    std::vector<int> result4 = twoSum({ 1, 2, 3, 4 }, 10);
    EXPECT_EQ(result4, (std::vector<int>{}));
}

TEST(SortHashAlgorithmsTest, ShellSortTest) {
    std::vector<int> arr1 = { 12, 3, 7, 8, 16, 24, 19, 11, 9, 88, 72, 63 };
    std::vector<int> sorted_arr1 = { 3, 7, 8, 9, 11, 12, 16, 19, 24, 63, 72, 88 };
    shellSort(arr1);
    EXPECT_EQ(arr1, sorted_arr1);

    std::vector<int> arr2 = { 5, 1, 4, 2, 8 };
    std::vector<int> sorted_arr2 = { 1, 2, 4, 5, 8 };
    shellSort(arr2);
    EXPECT_EQ(arr2, sorted_arr2);

    std::vector<int> arr3 = { 1 };
    std::vector<int> sorted_arr3 = { 1 };
    shellSort(arr3);
    EXPECT_EQ(arr3, sorted_arr3);

    std::vector<int> arr4 = {};
    std::vector<int> sorted_arr4 = {};
    shellSort(arr4);
    EXPECT_EQ(arr4, sorted_arr4);
}

TEST(SortHashAlgorithmsTest, GroupAnagramsTest) {
    std::vector<std::string> strs1 = { "eat","tea","tan","ate","nat","bat" };
    std::vector<std::vector<std::string>> expected1 = { {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"} };
    std::vector<std::vector<std::string>> result1 = groupAnagrams(strs1);
    EXPECT_TRUE(compareAnagramGroups(result1, expected1));

    std::vector<std::string> strs2 = { "won","now","aaa","ooo","ooo" };
    std::vector<std::vector<std::string>> expected2 = { {"aaa"}, {"ooo", "ooo"}, {"won", "now"} };
    std::vector<std::vector<std::string>> result2 = groupAnagrams(strs2);
    EXPECT_TRUE(compareAnagramGroups(result2, expected2));

    std::vector<std::string> strs3 = { "a" };
    std::vector<std::vector<std::string>> expected3 = { {"a"} };
    std::vector<std::vector<std::string>> result3 = groupAnagrams(strs3);
    EXPECT_TRUE(compareAnagramGroups(result3, expected3));

    std::vector<std::string> strs4 = {};
    std::vector<std::vector<std::string>> expected4 = {};
    std::vector<std::vector<std::string>> result4 = groupAnagrams(strs4);
    EXPECT_TRUE(compareAnagramGroups(result4, expected4));
}

TEST(SortHashAlgorithmsTest, IntegerSqrtTest) {
    EXPECT_EQ(integerSqrt(0), 0);
    EXPECT_EQ(integerSqrt(1), 1);
    EXPECT_EQ(integerSqrt(2), 1);
    EXPECT_EQ(integerSqrt(3), 1);
    EXPECT_EQ(integerSqrt(4), 2);
    EXPECT_EQ(integerSqrt(8), 2);
    EXPECT_EQ(integerSqrt(9), 3);
    EXPECT_EQ(integerSqrt(15), 3);
    EXPECT_EQ(integerSqrt(16), 4);
    EXPECT_EQ(integerSqrt(2147395600), 46340);
    EXPECT_EQ(integerSqrt(2147483647), 46340);

    EXPECT_THROW(integerSqrt(-1), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
