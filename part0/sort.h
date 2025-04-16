#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#include <vector>
#include <optional>

// Копирование листов
long long copyTime(int n, int x, int y);

// Накормить животных
int feedAnimals(std::vector<int>& animals, std::vector<int>& food);

// Найти разницу между двух строк
char findTheDifference(const std::string& a, const std::string& b);

// Сумма двух элементов массива
std::vector<int> twoSum(const std::vector<int>& data, int target);

// Сортировка Шелла
void shellSort(std::vector<int>& arr);

// Массив анаграмм
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs);

// Найти корень числа
int integerSqrt(int target);
