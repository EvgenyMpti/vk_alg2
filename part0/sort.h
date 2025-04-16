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

// Êîïèðîâàíèå ëèñòîâ
long long copyTime(int n, int x, int y);

// Íàêîðìèòü æèâîòíûõ
int feedAnimals(std::vector<int>& animals, std::vector<int>& food);

// Íàéòè ðàçíèöó ìåæäó äâóõ ñòðîê
char findTheDifference(const std::string& a, const std::string& b);

// Ñóììà äâóõ ýëåìåíòîâ ìàññèâà
std::vector<int> twoSum(const std::vector<int>& data, int target);

// Ñîðòèðîâêà Øåëëà
void shellSort(std::vector<int>& arr);

// Ìàññèâ àíàãðàìì
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs);

// Íàéòè êîðåíü ÷èñëà
int integerSqrt(int target);
