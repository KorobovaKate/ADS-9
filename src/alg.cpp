// Copyright 2022 NNTU-CS

#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include "tree.h"
#include <algorithm>

static void rekursivnySborPerestanovok(const PMTree::Uzel* uzel,
                                      std::vector<char>& current,
                                      std::vector<std::vector<char>>& result) {
    current.push_back(uzel->simvol);

    if (uzel->childUzel.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : uzel->childUzel) {
            rekursivnySborPerestanovok(child, current, result);
        }
    }

    current.pop_back();
}

PMTree::PMTree(const std::vector<char>& elements)
  : root(nullptr), kol_perestanovok(0) {
    if (elements.empty()) return;

    kol_perestanovok = factorial(elements.size());
    root = new Uzel('\0'); // Фиктивный корень

    for (char elem : elements) {
        std::vector<char> ostavshiesya = elements;
        ostavshiesya.erase(std::remove(ostavshiesya.begin(),
          ostavshiesya.end(), elem), ostavshiesya.end());

        Uzel* child = new Uzel(elem);
        buildTree(child, ostavshiesya);
        root->childUzel.push_back(child);
    }
}

PMTree::~PMTree() {
    delete root;
}

void PMTree::buildTree(Uzel* parent, const std::vector<char>& elements) {
    if (elements.empty()) return;

    for (char elem : elements) {
        std::vector<char> ostavshiesya = elements;
        ostavshiesya.erase(std::remove(ostavshiesya.begin(),
          ostavshiesya.end(), elem), ostavshiesya.end());

        Uzel* child = new Uzel(elem);
        buildTree(child, ostavshiesya);
        parent->childUzel.push_back(child);
    }
}

int PMTree::factorial(int n) const {
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.getKolPerestanovok()) return result;

    std::vector<char> current;
    for (const auto& child : tree.getRoot()->childUzel) {
        rekursivnySborPerestanovok(child, current, result);
    }
    return result;
}

static void poiskPerestanovki(const PMTree::Uzel* uzel,
  int& ostalos, std::vector<char>& rezultat) {
    if (ostalos < 0) return;

    rezultat.push_back(uzel->simvol);

    if (uzel->childUzel.empty()) {
        ostalos--;
    } else {
        for (const auto& child : uzel->childUzel) {
            poiskPerestanovki(child, ostalos, rezultat);
            if (ostalos < 0) break;
        }
    }

    if (ostalos >= 0) {
        rezultat.pop_back();
    }
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<char> rezultat;
    if (num < 1 || num > tree.getKolPerestanovok()) return rezultat;

    int ostalos = num - 1;
    for (const auto& child : tree.getRoot()->childUzel) {
        poiskPerestanovki(child, ostalos, rezultat);
        if (ostalos < 0) break;
    }
    return rezultat;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> rezultat;
    if (num < 1 || num > tree.getKolPerestanovok()) return rezultat;

    int ostalos = num - 1;
    const PMTree::Uzel* tekushiy = tree.getRoot();

    while (!tekushiy->childUzel.empty()) {
        int razmer_podder = tree.factorial(tekushiy->childUzel.size() - 1);
        int index = ostalos / razmer_podder;
        ostalos = ostalos % razmer_podder;

        tekushiy = tekushiy->childUzel[index];
        rezultat.push_back(tekushiy->simvol);
    }

    return rezultat;
}
