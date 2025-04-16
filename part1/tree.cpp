#include "tree.h"
#include <vector>
#include <optional>
#include <queue>
#include <algorithm>
#include <stdexcept>


TreeNode* buildTreeRecOpt(const std::vector<std::optional<int>>& arr, size_t i) {
    if (i >= arr.size() || !arr[i].has_value()) {
        return nullptr; // ������ ��� ������ ��� �������� nullopt
    }

    TreeNode* root = new TreeNode(arr[i].value());
    root->left = buildTreeRecOpt(arr, 2 * i + 1);
    root->right = buildTreeRecOpt(arr, 2 * i + 2);
    return root;
}

// ��������� ���� ��������
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

int dfsMirror(TreeNode* left, TreeNode* right) {
    if (!left || !right) {
        return 0;
    }
    int count = (left->val == right->val) ? 1 : 0;
    count += dfsMirror(left->left, right->right);
    count += dfsMirror(left->right, right->left);
    return count;
}

// �������������� ��������� ������ �� �������
TreeNode* buildTreeOpt(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr[0].has_value()) {
        return nullptr; // ������ ������ ��� ������ null
    }
    return buildTreeRecOpt(arr, 0);
}

// �������� �� �������������� ��������� ������
bool isSymmetricOpt(TreeNode* root) {
    if (!root) {
        return true;
    }
    std::queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);

    while (!q.empty()) {
        TreeNode* t1 = q.front(); q.pop();
        TreeNode* t2 = q.front(); q.pop();

        if (!t1 && !t2) continue;
        if (!t1 || !t2) return false;
        if (t1->val != t2->val) return false;

        // ��������� � ������� � ���������� �������
        q.push(t1->left);
        q.push(t2->right);
        q.push(t1->right);
        q.push(t2->left);
    }
    return true;
}

// ����� ����������� �������
int minDepthOpt(TreeNode* root) {
    if (!root) {
        return 0;
    }
    std::queue<std::pair<TreeNode*, int>> q; // ���� � ��� �������
    q.push({ root, 1 });

    while (!q.empty()) {
        TreeNode* currentNode = q.front().first;
        int currentDepth = q.front().second;
        q.pop();

        // ���������, �������� �� ���� ������
        if (!currentNode->left && !currentNode->right) {
            return currentDepth;
        }

        // ��������� �������� ���� � �������
        if (currentNode->left) {
            q.push({ currentNode->left, currentDepth + 1 });
        }
        if (currentNode->right) {
            q.push({ currentNode->right, currentDepth + 1 });
        }
    }
    return 0;
}

// ����� ������������ ������������ � ������������� ���������
long long maxMinProductBST(TreeNode* root) {
    if (!root) {
        throw std::invalid_argument("������ �� ������ ���� ������");
    }

    // ����� ������������ ��������
    TreeNode* minNode = root;
    while (minNode->left) {
        minNode = minNode->left;
    }

    // ����� ������������� ��������
    TreeNode* maxNode = root;
    while (maxNode->right) {
        maxNode = maxNode->right;
    }

    return static_cast<long long>(minNode->val) * maxNode->val;
}

// �������� �� ������ � ���������� ��� �
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!subRoot) return true;
    if (!root) return false;
    if (isSameTree(root, subRoot)) {
        return true;
    }
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// ���������� ����
int countMirrorNodes(TreeNode* root) {
    if (!root) {
        return 0;
    }
    return dfsMirror(root->left, root->right);
}