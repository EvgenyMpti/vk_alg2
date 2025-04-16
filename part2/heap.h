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

// Ïðîâåðêà êîððåêòíîñòè êó÷è
bool isHeap(const std::vector<int>& arr, bool heapType = 1);

// Ïðîâåðêà íà ïîëíîå áèíàðíîå äåðåâî
bool isCompleteTree(TreeNode* root);

// Îáúåäèíåíèå îòñîðòèðîâàííûõ ìàññèâîâ
std::vector<int> mergeKSortedArrays(const std::vector<std::vector<int>>& arrays);

// K íàèìåíüøèé ýëåìåíò
std::optional<int> kthSmallest(TreeNode* root, int k);

// K íàèáîëüøèé ýëåìåíò
std::optional<int> kthLargest(TreeNode* root, int k);

// Âñïîìîãàòåëüíàÿ ôóíêöèÿ äëÿ ðàñ÷åòà âûñîò è balance factor
int calculateHaBF(TreeNode* node);

// Ðàñ÷åò Balance factor
void setBalanceFactors(TreeNode* root);

// Ïðåîáðàçîâàíèå â çåðêàëüíîå äåðåâî
TreeNode* invertTree(TreeNode* root);

// äëÿ òåñòîâ
TreeNode* buildTree(const std::vector<std::optional<int>>& arr);
TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i);
