#include "gtest/gtest.h"
#include "heap.h" 
#include <vector>
#include <optional>
#include <string>
#include <algorithm>

class HeapTest : public ::testing::Test {
protected:
    void TearDown() override {}

    void checkBalanceFactors(TreeNode* node, std::vector<int>& factors) {
        if (!node) return;
        checkBalanceFactors(node->left, factors);
        factors.push_back(node->balance_factor);
        checkBalanceFactors(node->right, factors);
    }
};

// Сравнение двух деревьев
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

TEST_F(HeapTest, IsHeapTest) {
    EXPECT_TRUE(isHeap({ 21, 19, 18, 11, 12, 15, 16, 9, 8, 10 }, 1));
    EXPECT_FALSE(isHeap({ 10, 20, 15, 18, 25 }, 1));
    EXPECT_TRUE(isHeap({ 1, 2, 3, 4, 5 }, 0));
    EXPECT_FALSE(isHeap({ 5, 4, 3, 2, 1 }, 0));
    EXPECT_TRUE(isHeap({ 10 }, 1));
    EXPECT_TRUE(isHeap({}, 1));
}

TEST_F(HeapTest, IsCompleteTreeTest) {
    // Полное дерево: [1, 2, 3, 4, 5, 6]
    std::vector<std::optional<int>> complete_arr = { 1, 2, 3, 4, 5, 6 };
    TreeNode* complete_root = buildTree(complete_arr);
    EXPECT_TRUE(isCompleteTree(complete_root));
    delete complete_root;

    // Неполное дерево: [1, 2, 3, 4, std::nullopt, 6]
    std::vector<std::optional<int>> incomplete_arr = { 1, 2, 3, 4, std::nullopt, 6 };
    TreeNode* incomplete_root = buildTree(incomplete_arr);
    EXPECT_FALSE(isCompleteTree(incomplete_root));
    delete incomplete_root;

    // Неполное: [1, 2, 3, null, 5]
    std::vector<std::optional<int>> incomplete_arr2 = { 1, 2, 3, std::nullopt, 5 };
    TreeNode* incomplete_root2 = buildTree(incomplete_arr2);
    EXPECT_FALSE(isCompleteTree(incomplete_root2));
    delete incomplete_root2;


    EXPECT_TRUE(isCompleteTree(nullptr));
}

TEST_F(HeapTest, MergeKSortedArraysTest) {
    std::vector<std::vector<int>> arrays1 = { {1, 3, 5, 7}, {2, 4, 6}, {0, 8, 9, 11} };
    std::vector<int> expected1 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
    EXPECT_EQ(mergeKSortedArrays(arrays1), expected1);

    std::vector<std::vector<int>> arrays2 = { {1, 4, 5}, {1, 3, 4}, {2, 6} };
    std::vector<int> expected2 = { 1, 1, 2, 3, 4, 4, 5, 6 };
    EXPECT_EQ(mergeKSortedArrays(arrays2), expected2);

    std::vector<std::vector<int>> arrays3 = { {}, {1, 2}, {} };
    std::vector<int> expected3 = { 1, 2 };
    EXPECT_EQ(mergeKSortedArrays(arrays3), expected3);

    std::vector<std::vector<int>> arrays4 = {};
    std::vector<int> expected4 = {};
    EXPECT_EQ(mergeKSortedArrays(arrays4), expected4);
}

TEST_F(HeapTest, KthSmallestLargest) {
    std::vector<std::optional<int>> bst_arr = { 16, 10, 22, 6, 12, 18, 24, 2, 8, 11, 13, 17, 21, 23, 27 };
    TreeNode* bst_root = buildTree(bst_arr);

    EXPECT_EQ(kthSmallest(bst_root, 1).value_or(-1), 2);
    EXPECT_EQ(kthSmallest(bst_root, 3).value_or(-1), 8);
    EXPECT_EQ(kthSmallest(bst_root, 8).value_or(-1), 16); // Корень
    EXPECT_EQ(kthSmallest(bst_root, 15).value_or(-1), 27);
    EXPECT_FALSE(kthSmallest(bst_root, 0).has_value());
    EXPECT_FALSE(kthSmallest(bst_root, 16).has_value());

    EXPECT_EQ(kthLargest(bst_root, 1).value_or(-1), 27);
    EXPECT_EQ(kthLargest(bst_root, 3).value_or(-1), 23);
    EXPECT_EQ(kthLargest(bst_root, 8).value_or(-1), 16); // Корень
    EXPECT_EQ(kthLargest(bst_root, 15).value_or(-1), 2);
    EXPECT_FALSE(kthLargest(bst_root, 0).has_value());
    EXPECT_FALSE(kthLargest(bst_root, 16).has_value());

    delete bst_root;
    EXPECT_FALSE(kthSmallest(nullptr, 1).has_value());
    EXPECT_FALSE(kthLargest(nullptr, 1).has_value());
}


TEST_F(HeapTest, SetBalanceFactorsTest) {
    std::vector<std::optional<int>> bf_arr = { 9, 3, 8, 16, 7, std::nullopt, 11, 21 };
    TreeNode* bf_root = buildTree(bf_arr);

    setBalanceFactors(bf_root);

    std::vector<int> expected_factors = { 0, 1, 1, 0, 1, -1, 0 };
    std::vector<int> actual_factors;
    checkBalanceFactors(bf_root, actual_factors);

    EXPECT_EQ(actual_factors, expected_factors);

    delete bf_root;
}

TEST_F(HeapTest, InvertTreeTest) {
    std::vector<std::optional<int>> orig_arr = { 4, 2, 7, 1, 3, 6, 9 };
    TreeNode* orig_root = buildTree(orig_arr);

    std::vector<std::optional<int>> inv_arr = { 4, 7, 2, 9, 6, 3, 1 };
    TreeNode* expected_inv_root = buildTree(inv_arr);

    TreeNode* actual_inv_root = invertTree(orig_root);

    EXPECT_TRUE(isSameTree(actual_inv_root, expected_inv_root));
    EXPECT_EQ(actual_inv_root, orig_root);

    delete actual_inv_root;
    delete expected_inv_root;

    EXPECT_EQ(invertTree(nullptr), nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
