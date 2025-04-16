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

// Проверка корректности кучи
bool isHeap(const std::vector<int>& arr, bool heapType = 1);

// Проверка на полное бинарное дерево
bool isCompleteTree(TreeNode* root);

// Объединение отсортированных массивов
std::vector<int> mergeKSortedArrays(const std::vector<std::vector<int>>& arrays);

// K наименьший элемент
std::optional<int> kthSmallest(TreeNode* root, int k);

// K наибольший элемент
std::optional<int> kthLargest(TreeNode* root, int k);

// Вспомогательная функция для расчета высот и balance factor
int calculateHaBF(TreeNode* node);

// Расчет Balance factor
void setBalanceFactors(TreeNode* root);

// Преобразование в зеркальное дерево
TreeNode* invertTree(TreeNode* root);

// для тестов
TreeNode* buildTree(const std::vector<std::optional<int>>& arr);
TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i);
