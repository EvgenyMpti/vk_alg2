#include "heap.h"
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <optional>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <tuple>

TreeNode* buildTreeRec(const std::vector<std::optional<int>>& arr, size_t i) {
    if (i >= arr.size() || !arr[i].has_value())
        return nullptr;

    TreeNode* node = new TreeNode(arr[i].value());
    node->left = buildTreeRec(arr, 2 * i + 1);
    node->right = buildTreeRec(arr, 2 * i + 2);
    return node;
}

TreeNode* buildTree(const std::vector<std::optional<int>>& arr) {
    if (arr.empty() || !arr[0].has_value())
        return nullptr;

    return buildTreeRec(arr, 0);
}

// Ïðîâåðêà êîððåêòíîñòè êó÷è
bool isHeap(const std::vector<int>& arr, bool isMaxheap) {
    size_t n = arr.size();
    if (n <= 1)
        return true;

    std::function<bool(int, int)> compare;
    if (isMaxheap)
        compare = std::greater_equal<int>();
    else
        compare = std::less_equal<int>();

    // Ïðîâåðÿåì òîëüêî âíóòðåííèå óçëû
    for (size_t i = 0; i <= (n / 2) - 1; ++i) {
        size_t leftChildIdx = 2 * i + 1;
        size_t rightChildIdx = 2 * i + 2;

        if (leftChildIdx < n && !compare(arr[i], arr[leftChildIdx]))
            return false;

        if (rightChildIdx < n && !compare(arr[i], arr[rightChildIdx]))
            return false;
    }
    return true;
}

// Ïðîâåðêà íà ïîëíîå áèíàðíîå äåðåâî
bool isCompleteTree(TreeNode* root) {
    if (!root)
        return true;

    std::queue<TreeNode*> q;
    q.push(root);
    bool nullEncountered = false; // âñòðåòèëñÿ ëè óæå null óçåë

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current == nullptr) {
            nullEncountered = true;
        }
        else {
            if (nullEncountered)
                return false;

            q.push(current->left);
            q.push(current->right);
        }
    }
    return true;
}

// Îáúåäèíåíèå îòñîðòèðîâàííûõ ìàññèâîâ
std::vector<int> mergeKSortedArrays(const std::vector<std::vector<int>>& arrays) {
    // çíà÷åíèå, èíäåêñ_ìàññèâà, èíäåêñ_ýëåìåíòà
    using Element = std::tuple<int, size_t, size_t>;

    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> minHeap;

    for (size_t i = 0; i < arrays.size(); ++i) {
        if (!arrays[i].empty())
            minHeap.push({ arrays[i][0], i, 0 });
    }

    std::vector<int> result;

    // Èçâëå÷åíèå ìèíèìàëüíûõ ýëåìåíòîâ èç êó÷è
    while (!minHeap.empty()) {
        auto [value, arrayIdx, elementIdx] = minHeap.top();
        minHeap.pop();

        result.push_back(value);

        // Åñëè â òåêóùåì ìàññèâå åñòü ñëåäóþùèé ýëåìåíò, äîáàâëÿåì åãî â êó÷ó
        size_t nextElementIdx = elementIdx + 1;
        if (nextElementIdx < arrays[arrayIdx].size()) {
            minHeap.push({ arrays[arrayIdx][nextElementIdx], arrayIdx, nextElementIdx });
        }
    }

    return result;
}

// K íàèìåíüøèé ýëåìåíò
std::optional<int> kthSmallest(TreeNode* root, int k) {
    if (k <= 0) return std::nullopt;

    std::stack<TreeNode*> s;
    TreeNode* current = root;
    int count = 0;

    while (current || !s.empty()) {
        // Èäåì âëåâî äî óïîðà, äîáàâëÿÿ óçëû â ñòåê
        while (current) {
            s.push(current);
            current = current->left;
        }

        // Äîñòàåì óçåë èç ñòåêà
        current = s.top();
        s.pop();

        count++;
        if (count == k)
            return current->val;

        // Ïåðåõîäèì ê ïðàâîìó ïîääåðåâó
        current = current->right;
    }

    return std::nullopt;
}

// K íàèáîëüøèé ýëåìåíò
std::optional<int> kthLargest(TreeNode* root, int k) {
    if (k <= 0) return std::nullopt;

    std::stack<TreeNode*> s;
    TreeNode* current = root;
    int count = 0;

    while (current || !s.empty()) {
        // Èäåì âïðàâî äî óïîðà, äîáàâëÿÿ óçëû â ñòåê
        while (current) {
            s.push(current);
            current = current->right;
        }

        // Äîñòàåì óçåë èç ñòåêà
        current = s.top();
        s.pop();

        count++;
        if (count == k)
            return current->val;

        // Ïåðåõîäèì ê ëåâîìó ïîääåðåâó
        current = current->left;
    }
    return std::nullopt;
}

int calculateHaBF(TreeNode* node) {
    if (!node)
        return -1;

    int leftHeight = calculateHaBF(node->left);
    int rightHeight = calculateHaBF(node->right);

    // Ðàññ÷èòûâàåì è ñîõðàíÿåì balance factor
    node->balance_factor = leftHeight - rightHeight;

    // Âîçâðàùàåì âûñîòó òåêóùåãî óçëà
    return 1 + std::max(leftHeight, rightHeight);
}

// Ðàñ÷åò Balance factor
void setBalanceFactors(TreeNode* root) {
    calculateHaBF(root);
}

// Ïðåîáðàçîâàíèå â çåðêàëüíîå äåðåâî
TreeNode* invertTree(TreeNode* root) {
    if (!root)
        return nullptr;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        // Îáìåí ëåâîãî è ïðàâîãî ïîòîìêîâ
        std::swap(current->left, current->right);

        if (current->left)
            q.push(current->left);

        if (current->right)
            q.push(current->right);
    }
    return root;
}