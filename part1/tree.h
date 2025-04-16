#pragma once

#include <vector>
#include <optional>
#include <queue>
#include <algorithm>
#include <limits>

// Определение для узла бинарного дерева
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

// Восстановление бинарного дерева из массива
TreeNode* buildTree(const std::vector<std::optional<int>>& arr);

// Проверка на симметричность бинарного дерева
bool isSymmetric(TreeNode* root);

// Поиск минимальной глубины
int minDepth(TreeNode* root);

// Поиск произведения минимального и максимального элементов
// Принимает TreeNode* бинарного дерева ПОИСКА
long long maxMinProduct(TreeNode* root);

// Сравнение двух деревьев
bool isSameTree(TreeNode* p, TreeNode* q);

// Является ли дерево В поддеревом для А
bool isSubtree(TreeNode* root, TreeNode* subRoot);

int dfsMirror(TreeNode* left, TreeNode* right);

// Зеркальные узлы
int countMirrorNodes(TreeNode* root);
