#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <optional>
#include <functional>
#include <stdexcept>
#include <tuple>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int balance_factor;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr), balance_factor(0) {}
    ~TreeNode() {
        delete left;
        delete right;
    }
};

// �������� ������������ ����
bool isHeap(const std::vector<int>& arr, bool heapType = 1);

// �������� �� ������ �������� ������
bool isCompleteTree(TreeNode* root);

// ����������� ��������������� ��������
std::vector<int> mergeKSortedArrays(const std::vector<std::vector<int>>& arrays);

// K ���������� �������
std::optional<int> kthSmallest(TreeNode* root, int k);

// K ���������� �������
std::optional<int> kthLargest(TreeNode* root, int k);

// ��������������� ������� ��� ������� ����� � balance factor
int calculateHaBF(TreeNode* node);

// ������ Balance factor
void setBalanceFactors(TreeNode* root);

// �������������� � ���������� ������
TreeNode* invertTree(TreeNode* root);

// ��� ������
TreeNode* buildTree(const std::vector<std::optional<int>>& arr);
TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i);
