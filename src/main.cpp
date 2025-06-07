// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

void demonstratePermutations() {
    cout << "=== Пример работы с деревом перестановок ===\n\n";
    
    vector<char> elements = {'1', '2', '3'};
    PMTree tree(elements);
    
    cout << "Все перестановки для {1,2,3}:\n";
    auto all_perms = getAllPerms(tree);
    for (const auto& perm : all_perms) {
        for (char c : perm) cout << c;
        cout << " ";
    }
    cout << "\n\n";
    
    cout << "Получение перестановок по номеру:\n";
    for (int i = 1; i <= 6; ++i) {
        auto perm1 = getPerm1(tree, i);
        auto perm2 = getPerm2(tree, i);
        cout << "Пер. #" << i << ": ";
        for (char c : perm1) cout << c;
        cout << " (метод1), ";
        for (char c : perm2) cout << c;
        cout << " (метод2)\n";
    }
    cout << "\n";
}

void runPerformanceExperiment() {
    cout << "=== Начало вычислительного эксперимента ===\n";
    
    ofstream data_file("result/experiment.csv");
    data_file << "n,getAllTime,getPerm1Time,getPerm2Time\n";
    
    random_device rd;
    mt19937 gen(rd());
    
    for (int n = 1; n <= 10; ++n) {
        // Создаем входные данные
        vector<char> elements(n);
        for (int i = 0; i < n; ++i) {
            elements[i] = 'a' + i;
        }
        
        auto start = chrono::high_resolution_clock::now();
        PMTree tree(elements);
        auto end = chrono::high_resolution_clock::now();
        auto build_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        
        int total_perms = tree.getTotalPermutations();
        if (total_perms == 0) continue;
        
        // Тестируем getAllPerms()
        start = chrono::high_resolution_clock::now();
        auto all_perms = getAllPerms(tree);
        end = chrono::high_resolution_clock::now();
        auto get_all_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        
        // Тестируем getPerm1() и getPerm2() на случайных номерах
        uniform_int_distribution<> dist(1, total_perms);
        const int num_tests = 100;
        vector<int> test_numbers(num_tests);
        for (int& num : test_numbers) {
            num = dist(gen);
        }
        
        start = chrono::high_resolution_clock::now();
        for (int num : test_numbers) {
            auto perm = getPerm1(tree, num);
        }
        end = chrono::high_resolution_clock::now();
        auto get1_time = chrono::duration_cast<chrono::microseconds>(end - start).count() / num_tests;
        
        start = chrono::high_resolution_clock::now();
        for (int num : test_numbers) {
            auto perm = getPerm2(tree, num);
        }
        end = chrono::high_resolution_clock::now();
        auto get2_time = chrono::duration_cast<chrono::microseconds>(end - start).count() / num_tests;
        
        data_file << n << "," << get_all_time << "," << get1_time << "," << get2_time << "\n";
        
        cout << "n = " << n << ":\tgetAll = " << get_all_time << " μs,\t"
             << "getPerm1 = " << get1_time << " μs,\t"
             << "getPerm2 = " << get2_time << " μs\n";
    }
    
    data_file.close();
    cout << "\nРезультаты эксперимента сохранены в result/experiment.csv\n";
    cout << "=== Эксперимент завершен ===\n\n";
}

int main() {
    demonstratePermutations();
    
    runPerformanceExperiment();
    
    return 0;
}
