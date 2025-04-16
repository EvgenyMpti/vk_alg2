#pragma once

#include <vector>
#include <optional>
#include <queue>
#include <algorithm>
#include <limits>

// ����������� ��� ���� ��������� ������
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    ~TreeNode() {
        delete left;
        delete right;
    }
};

TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i);

// �������������� ��������� ������ �� �������
TreeNode* buildTree(const std::vector<std::optional<int>>& arr);

// �������� �� �������������� ��������� ������
bool isSymmetric(TreeNode* root);

// ����� ����������� �������
int minDepth(TreeNode* root);

// ����� ������������ ������������ � ������������� ���������
// ��������� TreeNode* ��������� ������ ������
long long maxMinProduct(TreeNode* root);

// ��������� ���� ��������
bool isSameTree(TreeNode* p, TreeNode* q);

// �������� �� ������ � ���������� ��� �
bool isSubtree(TreeNode* root, TreeNode* subRoot);

int dfsMirror(TreeNode* left, TreeNode* right);

// ���������� ����
int countMirrorNodes(TreeNode* root);
