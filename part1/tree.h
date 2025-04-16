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

TreeNode* buildTreeRecOpt(const std::vector<std::optional<int>>& arr, size_t i);

// �������������� ��������� ������ �� �������
TreeNode* buildTreeOpt(const std::vector<std::optional<int>>& arr);

// �������� �� �������������� ��������� ������
bool isSymmetricOpt(TreeNode* root);

// ����� ����������� �������
int minDepthOpt(TreeNode* root);

// ����� ������������ ������������ � ������������� ���������
// ��������� TreeNode* ��������� ������ ������
long long maxMinProductBST(TreeNode* root);

// ��������� ���� ��������
bool isSameTree(TreeNode* p, TreeNode* q);

// �������� �� ������ � ���������� ��� �
bool isSubtree(TreeNode* root, TreeNode* subRoot);

int dfsMirror(TreeNode* left, TreeNode* right);

// ���������� ����
int countMirrorNodes(TreeNode* root);
