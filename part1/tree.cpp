#include "tree.h"
#include <vector>
#include <optional>
#include <queue>
#include <algorithm>
#include <stdexcept>


TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i) {
    if (i >= arr.size() || !arr[i].has_value()) {
        return nullptr; // Èíäåêñ âíå ãðàíèö èëè çíà÷åíèå nullopt
    }

    TreeNode* root = new TreeNode(arr[i].value());
    root->left = buildTreeRec(arr, 2 * i + 1);
    root->right = buildTreeRec(arr, 2 * i + 2);
    return root;
}

// Ñðàâíåíèå äâóõ äåðåâüåâ
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

// Âîññòàíîâëåíèå áèíàðíîãî äåðåâà èç ìàññèâà
TreeNode* buildTree(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr[0].has_value()) {
        return nullptr; // Ïóñòîé ìàññèâ èëè êîðåíü null
    }
    return buildTreeRec(arr, 0);
}

// Ïðîâåðêà íà ñèììåòðè÷íîñòü áèíàðíîãî äåðåâà
bool isSymmetric(TreeNode* root) {
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

        // Äîáàâëÿåì â î÷åðåäü â çåðêàëüíîì ïîðÿäêå
        q.push(t1->left);
        q.push(t2->right);
        q.push(t1->right);
        q.push(t2->left);
    }
    return true;
}

// Ïîèñê ìèíèìàëüíîé ãëóáèíû
int minDepth(TreeNode* root) {
    if (!root) {
        return 0;
    }
    std::queue<std::pair<TreeNode*, int>> q; // óçåë è åãî ãëóáèíà
    q.push({ root, 1 });

    while (!q.empty()) {
        TreeNode* currentNode = q.front().first;
        int currentDepth = q.front().second;
        q.pop();

        // Ïðîâåðÿåì, ÿâëÿåòñÿ ëè óçåë ëèñòîì
        if (!currentNode->left && !currentNode->right) {
            return currentDepth;
        }

        // Äîáàâëÿåì äî÷åðíèå óçëû â î÷åðåäü
        if (currentNode->left) {
            q.push({ currentNode->left, currentDepth + 1 });
        }
        if (currentNode->right) {
            q.push({ currentNode->right, currentDepth + 1 });
        }
    }
    return 0;
}

// Ïîèñê ïðîèçâåäåíèÿ ìèíèìàëüíîãî è ìàêñèìàëüíîãî ýëåìåíòîâ
long long maxMinProduct(TreeNode* root) {
    if (!root) {
        throw std::invalid_argument("Äåðåâî íå äîëæíî áûòü ïóñòûì");
    }

    // Ïîèñê ìèíèìàëüíîãî ýëåìåíòà
    TreeNode* minNode = root;
    while (minNode->left) {
        minNode = minNode->left;
    }

    // Ïîèñê ìàêñèìàëüíîãî ýëåìåíòà
    TreeNode* maxNode = root;
    while (maxNode->right) {
        maxNode = maxNode->right;
    }

    return static_cast<long long>(minNode->val) * maxNode->val;
}

// ßâëÿåòñÿ ëè äåðåâî Â ïîääåðåâîì äëÿ À
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!subRoot) return true;
    if (!root) return false;
    if (isSameTree(root, subRoot)) {
        return true;
    }
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// Çåðêàëüíûå óçëû
int countMirrorNodes(TreeNode* root) {
    if (!root) {
        return 0;
    }
    return dfsMirror(root->left, root->right);
}