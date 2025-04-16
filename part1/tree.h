#pragma once

#include <vector>
#include <optional>
#include <queue>
#include <algorithm>
#include <limits>

// Îïðåäåëåíèå äëÿ óçëà áèíàðíîãî äåðåâà
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

// Âîññòàíîâëåíèå áèíàðíîãî äåðåâà èç ìàññèâà
TreeNode* buildTree(const std::vector<std::optional<int>>& arr);

// Ïðîâåðêà íà ñèììåòðè÷íîñòü áèíàðíîãî äåðåâà
bool isSymmetric(TreeNode* root);

// Ïîèñê ìèíèìàëüíîé ãëóáèíû
int minDepth(TreeNode* root);

// Ïîèñê ïðîèçâåäåíèÿ ìèíèìàëüíîãî è ìàêñèìàëüíîãî ýëåìåíòîâ
// Ïðèíèìàåò TreeNode* áèíàðíîãî äåðåâà ÏÎÈÑÊÀ
long long maxMinProduct(TreeNode* root);

// Ñðàâíåíèå äâóõ äåðåâüåâ
bool isSameTree(TreeNode* p, TreeNode* q);

// ßâëÿåòñÿ ëè äåðåâî Â ïîääåðåâîì äëÿ À
bool isSubtree(TreeNode* root, TreeNode* subRoot);

int dfsMirror(TreeNode* left, TreeNode* right);

// Çåðêàëüíûå óçëû
int countMirrorNodes(TreeNode* root);
