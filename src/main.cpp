// Copyright 2022 NNTU-CS
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "tree.h"

void demonstratePermutations() {
    std::cout << "=== Пример работы с деревом перестановок ===\n\n";

    std::vector<char> elements = {'1', '2', '3'};
    PMTree tree(elements);

    std::cout << "Все перестановки для {1,2,3}:\n";
    auto all_perms = getAllPerms(tree);
    for (const auto& perm : all_perms) {
        for (char c : perm) std::cout << c;
        std::cout << " ";
    }
    std::cout << "\n\n";

    std::cout << "Получение перестановок по номеру:\n";
    for (int i = 1; i <= 6; ++i) {
        auto perm1 = getPerm1(tree, i);
        auto perm2 = getPerm2(tree, i);
        std::cout << "Пер. #" << i << ": ";
        for (char c : perm1) std::cout << c;
        std::cout << " (метод1), ";
        for (char c : perm2) std::cout << c;
        std::cout << " (метод2)\n";
    }
    std::cout << "\n";
}

void runPerformanceExperiment() {
    std::cout << "=== Начало вычислительного эксперимента ===\n";

    std::ofstream data_file("result/experiment.csv");
    data_file << "n,getAllTime,getPerm1Time,getPerm2Time\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> elements(n);
        for (int i = 0; i < n; ++i) {
            elements[i] = 'a' + i;
        }

        auto start = std::chrono::high_resolution_clock::now();
        PMTree tree(elements);
        auto end = std::chrono::high_resolution_clock::now();
        auto build_time = std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count();

        int total_perms = tree.getKolPerestanovok();
        if (total_perms == 0) continue;

        start = std::chrono::high_resolution_clock::now();
        auto all_perms = getAllPerms(tree);
        end = std::chrono::high_resolution_clock::now();
        auto get_all_time = std::chrono::duration_cast
            <std::chrono::microseconds>(end - start).count();

        std::uniform_int_distribution<> dist(1, total_perms);
        const int num_tests = 100;
        std::vector<int> test_numbers(num_tests);
        for (int& num : test_numbers) {
            num = dist(gen);
        }

        start = std::chrono::high_resolution_clock::now();
        for (int num : test_numbers) {
            auto perm = getPerm1(tree, num);
        }
        end = std::chrono::high_resolution_clock::now();
        auto get1_time = std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count() / num_tests;

        start = std::chrono::high_resolution_clock::now();
        for (int num : test_numbers) {
            auto perm = getPerm2(tree, num);
        }
        end = std::chrono::high_resolution_clock::now();
        auto get2_time = std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count() / num_tests;

        data_file << n << "," << get_all_time << ","
                  << get1_time << "," << get2_time << "\n";

        std::cout << "n = " << n << ":\tgetAll = " << get_all_time << " μs,\t"
                  << "getPerm1 = " << get1_time << " μs,\t"
                  << "getPerm2 = " << get2_time << " μs\n";
    }

    data_file.close();
    std::cout << "\nРезультаты сохранены в result/experiment.csv\n";
    std::cout << "=== Эксперимент завершен ===\n\n";
}

int main() {
    demonstratePermutations();
    runPerformanceExperiment();
    return 0;
}
