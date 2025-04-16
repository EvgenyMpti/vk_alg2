#include "gtest/gtest.h"
#include "tree.h"
#include <vector>
#include <optional>
#include <limits>
#include <stdexcept>

class TreeTest : public ::testing::Test {
};

TEST_F(TreeTest, BuildTreeBasic) {
    std::vector<std::optional<int>> arr = { 8, 9, 11, 7, 16, 3, 1 };
    TreeNode* root = buildTree(arr);

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val, 8);
    ASSERT_NE(root->left, nullptr);
    EXPECT_EQ(root->left->val, 9);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->val, 11);
    ASSERT_NE(root->left->left, nullptr);
    EXPECT_EQ(root->left->left->val, 7);

    delete root;
}

TEST_F(TreeTest, BuildTreeWithNulls) {
    // Äåðåâî: 1 -> (null, 2 -> (3, null))
    std::vector<std::optional<int>> arr = { 1, std::nullopt, 2, std::nullopt, std::nullopt, 3, std::nullopt };
    TreeNode* root = buildTree(arr);

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->val, 1);
    EXPECT_EQ(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->right->val, 2);
    ASSERT_NE(root->right->left, nullptr);
    EXPECT_EQ(root->right->left->val, 3);
    EXPECT_EQ(root->right->right, nullptr);

    delete root;
}

TEST_F(TreeTest, IsSymmetric) {
    // Ñèììåòðè÷íîå
    std::vector<std::optional<int>> sym_arr = { 3, 8, 8, 9, 6, 6, 9 };
    TreeNode* sym_root = buildTree(sym_arr);
    EXPECT_TRUE(isSymmetric(sym_root));
    delete sym_root;

    // Àñèììåòðè÷íîå
    std::vector<std::optional<int>> asym_arr = { 3, 8, 7, 9, 6, std::nullopt, 9 };
    TreeNode* asym_root = buildTree(asym_arr);
    EXPECT_FALSE(isSymmetric(asym_root));
    delete asym_root;

    // + àñèììåòðè÷íîå
    std::vector<std::optional<int>> asym_arr2 = { 1, 2, 2, std::nullopt, 3, std::nullopt, 3 };
    TreeNode* asym_root2 = buildTree(asym_arr2);
    EXPECT_FALSE(isSymmetric(asym_root2));
    delete asym_root2;

    EXPECT_TRUE(isSymmetric(nullptr));
}

TEST_F(TreeTest, MinDepth) {
    // 8 -> (9->(7, null)), (2->(11->(6,null), 9))
    TreeNode* depth_root = new TreeNode(8);
    depth_root->left = new TreeNode(9);
    depth_root->right = new TreeNode(2);
    depth_root->left->left = new TreeNode(7);
    depth_root->right->left = new TreeNode(11);
    depth_root->right->right = new TreeNode(9); // Ëèñò
    depth_root->right->left->left = new TreeNode(6); // Ëèñò

    EXPECT_EQ(minDepth(depth_root), 3);
    delete depth_root;

    TreeNode* simple_root = new TreeNode(1);
    simple_root->left = new TreeNode(2); // Ëèñò
    EXPECT_EQ(minDepth(simple_root), 2);
    delete simple_root;

    EXPECT_EQ(minDepth(nullptr), 0);
}

TEST_F(TreeTest, MaxMinProductBST) {
    // 8 -> (3 -> (1, 6 -> (4, 7))), (10 -> (null, 14 -> (13, null)))
    TreeNode* bst_root = new TreeNode(8);
    bst_root->left = new TreeNode(3);
    bst_root->right = new TreeNode(10);
    bst_root->left->left = new TreeNode(1);
    bst_root->left->right = new TreeNode(6);
    bst_root->left->right->left = new TreeNode(4);
    bst_root->left->right->right = new TreeNode(7);
    bst_root->right->right = new TreeNode(14);
    bst_root->right->right->left = new TreeNode(13);

    EXPECT_EQ(maxMinProduct(bst_root), 14);
    delete bst_root;

    TreeNode* single_node_bst = new TreeNode(5);
    EXPECT_EQ(maxMinProduct(single_node_bst), 25);
    delete single_node_bst;

    EXPECT_THROW(maxMinProduct(nullptr), std::invalid_argument);
}

TEST_F(TreeTest, IsSameTreeUnchanged) {
    std::vector<std::optional<int>> arr1 = { 1, 2, 3 };
    std::vector<std::optional<int>> arr2 = { 1, 2, 3 };
    std::vector<std::optional<int>> arr3 = { 1, 2, 4 };
    TreeNode* t1 = buildTree(arr1);
    TreeNode* t2 = buildTree(arr2);
    TreeNode* t3 = buildTree(arr3);

    EXPECT_TRUE(isSameTree(t1, t2));
    EXPECT_FALSE(isSameTree(t1, t3));

    delete t1;
    delete t2;
    delete t3;
}

TEST_F(TreeTest, IsSubtreeUnchanged) {
    std::vector<std::optional<int>> arrA = { 3, 4, 5, 1, 2, std::nullopt, std::nullopt, std::nullopt, std::nullopt, 0 };
    std::vector<std::optional<int>> arrC = { 4, 1, 2, std::nullopt, std::nullopt, 0 };
    TreeNode* rootA = buildTree(arrA);
    TreeNode* rootC = buildTree(arrC);

    EXPECT_TRUE(isSubtree(rootA, rootC));

    delete rootA;
    delete rootC;
}

TEST_F(TreeTest, CountMirrorNodesUnchanged) {
    std::vector<std::optional<int>> mirror_arr = { 3, 8, 8, 9, 6, 6, 9 };
    TreeNode* mirror_root = buildTree(mirror_arr);
    // (8,8), (9,9), (6,6) -> 3
    EXPECT_EQ(countMirrorNodes(mirror_root), 3);
    delete mirror_root;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}