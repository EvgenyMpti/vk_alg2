#include "sort.h"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#include <vector>
#include <stdexcept>

// Êîïèðîâàíèå ëèñòîâ
long long copyTime(int n, int x, int y) {
    if (n <= 0) return 0;
    if (n == 1) return 0;

    // x - âðåìÿ áîëåå áûñòðîãî ïðèíòåðà
    if (x > y) std::swap(x, y);

    long long first_copy_time = x; // íà ïåðâóþ êîïèþ
    int copies_needed = n - 1; // ñêîëüêî êîïèé íóæíî ñäåëàòü

    long long left = 0;

    long long right = static_cast<long long>(copies_needed) * x;
    long long min_time_for_rest = right;

    while (left <= right) {
        long long mid_time = left + (right - left) / 2;

        long long copies_made = (mid_time / x) + (mid_time / y);

        if (copies_made >= copies_needed) {
            min_time_for_rest = mid_time;
            right = mid_time - 1;
        }
        else
            left = mid_time + 1;
    }

    return first_copy_time + min_time_for_rest;
}

// Íàêîðìèòü æèâîòíûõ
int feedAnimals(std::vector<int>& animals, std::vector<int>& food) {
    if (animals.empty() || food.empty())
        return 0;

    // Ñîðòèðóåì îáà ìàññèâà
    std::sort(animals.begin(), animals.end());
    std::sort(food.begin(), food.end());

    int fed_count = 0;
    int food_idx = 0;

    for (int animal_appetite : animals) {
        while (food_idx < food.size() && food[food_idx] < animal_appetite)
            food_idx++; // ïîðöèÿ ìàëà, áåðåì ñëåäóþùóþ

        if (food_idx < food.size()) {
            fed_count++;
            food_idx++;
        }
        else
            break;
    }

    return fed_count;
}


// Íàéòè ðàçíèöó ìåæäó äâóõ ñòðîê
char findTheDifference(const std::string& a, const std::string& b) {
    if (b.length() != a.length() + 1) {
        return '\0';
    }

    char result_char_code = 0;

    // XOR
    for (char c : a) {
        result_char_code ^= c;
    }

    for (char c : b) {
        result_char_code ^= c;
    }

    return result_char_code;
}

// Ñóììà äâóõ ýëåìåíòîâ ìàññèâà
std::vector<int> twoSum(const std::vector<int>& data, int target) {
    std::unordered_map<int, int> cache; // ýëåìåíò, èíäåêñ

    for (int i = 0; i < data.size(); ++i) {
        int current_val = data[i];
        int complement = target - current_val;

        // Èùåì â êåøå
        auto it = cache.find(complement);
        if (it != cache.end()) {
            return { it->second, i };
        }

        cache[current_val] = i;
    }

    return {};
}

// Ñîðòèðîâêà Øåëëà
void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return;

    // Îïðåäåëÿåì ìàêñèìàëüíûé øàã (2^k - 1) < n
    int gap = 1;
    while (gap * 2 + 1 < n)
        gap = gap * 2 + 1;


    while (gap >= 1) {
        // Âûïîëíÿåì ñîðòèðîâêó âñòàâêàìè äëÿ ýëåìåíòîâ ñ øàãîì gap
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp; // Âñòàâëÿåì temp íà ïðàâèëüíîå ìåñòî
        }
        // ïåðåõîäèì ê ïðåäûäóùåìó øàãó
        gap = (gap - 1) / 2;
    }
}


// Ìàññèâ àíàãðàìì
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> anagram_groups;

    for (const std::string& s : strs) {
        std::string sorted_s = s;
        std::sort(sorted_s.begin(), sorted_s.end());
        anagram_groups[sorted_s].push_back(s);
    }

    std::vector<std::vector<std::string>> result;
    result.reserve(anagram_groups.size());

    for (auto const& [key, val] : anagram_groups) {
        result.push_back(val);
    }

    return result;
}

// Íàéòè êîðåíü ÷èñëà
int integerSqrt(int target) {
    if (target < 0) 
        throw std::invalid_argument("êîðåíü íå îïðåäåëåí");

    if (target == 0 || target == 1) 
        return target;

    long long left = 0;
    // â òåîðèè äîñòàòî÷íî äî target/2 + 1
    long long right = target;
    int result = 0;

    while (left <= right) {
        long long mid_ll = left + (right - left) / 2;
        if (mid_ll > std::numeric_limits<int>::max()) {
            mid_ll = std::numeric_limits<int>::max();
        }
        int mid = static_cast<int>(mid_ll);

        long long square = static_cast<long long>(mid) * mid;

        if (square == target) {
            return mid;
        }
        else if (square < target) {
            result = mid; // êàíäèäàò íà îòâåò
            left = static_cast<long long>(mid) + 1; // áîëüøèé êîðåíü
        }
        else {
            right = static_cast<long long>(mid) - 1; // òî÷íî ìåíüøå
        }
    }

    return result;
}