// Copyright 2022 NNTU-CS

#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
static void rekursivnySborPerestanovok(const PMTree::Uzel* uzel,
                                     std::vector<char>& tekushaya,
                                     std::vector<std::vector<char>>& rezultat) {
    tekushaya.push_back(uzel->simvol);
    
    if (uzel->potomki.empty()) {
        rezultat.push_back(tekushaya);
    } else {
        for (const auto& potomok : uzel->potomki) {
            rekursivnySborPerestanovok(potomok, tekushaya, rezultat);
        }
    }
    
    tekushaya.pop_back();
}

PMTree::PMTree(const std::vector<char>& elementi) : koren(nullptr), vsego_perestanovok(0) {
    if (elementi.empty()) return;
    
    vsego_perestanovok = vichislitFactorial(elementi.size());
    koren = new Uzel('\0');
    
    for (char simvol : elementi) {
        std::vector<char> ostavshiesya = elementi;
        ostavshiesya.erase(std::remove(ostavshiesya.begin(), ostavshiesya.end(), simvol), ostavshiesya.end());
        
        Uzel* novyUzel = new Uzel(simvol);
        stroitDerevo(novyUzel, ostavshiesya);
        koren->potomki.push_back(novyUzel);
    }
}

PMTree::~PMTree() {
    delete koren;
}

void PMTree::stroitDerevo(Uzel* roditel, const std::vector<char>& elementi) {
    if (elementi.empty()) return;
    
    for (char simvol : elementi) {
        std::vector<char> ostavshiesya = elementi;
        ostavshiesya.erase(std::remove(ostavshiesya.begin(), ostavshiesya.end(), simvol), ostavshiesya.end());
        
        Uzel* novyUzel = new Uzel(simvol);
        stroitDerevo(novyUzel, ostavshiesya);
        roditel->potomki.push_back(novyUzel);
    }
}

int PMTree::vichislitFactorial(int n) const {
    return (n <= 1) ? 1 : n * vichislitFactorial(n - 1);
}

std::vector<std::vector<char>> getAllPerms(const PMTree& derevo) {
    std::vector<std::vector<char>> rezultat;
    if (!derevo.poluchitVsegoPerestanovok()) return rezultat;
    
    std::vector<char> tekushaya;
    for (const auto& potomok : derevo.poluchitKoren()->potomki) {
        rekursivnySborPerestanovok(potomok, tekushaya, rezultat);
    }
    return rezultat;
}

static void poiskPerestanovki(const PMTree::Uzel* uzel, int& ostalos, std::vector<char>& rezultat) {
    if (ostalos < 0) return;
    
    rezultat.push_back(uzel->simvol);
    
    if (uzel->potomki.empty()) {
        ostalos--;
    } else {
        for (const auto& potomok : uzel->potomki) {
            poiskPerestanovki(potomok, ostalos, rezultat);
            if (ostalos < 0) break;
        }
    }
    
    if (ostalos >= 0) {
        rezultat.pop_back();
    }
}

std::vector<char> getPerm1(const PMTree& derevo, int nomer) {
    std::vector<char> rezultat;
    if (nomer < 1 || nomer > derevo.poluchitVsegoPerestanovok()) return rezultat;
    
    int ostalos = nomer - 1;
    for (const auto& potomok : derevo.poluchitKoren()->potomki) {
        poiskPerestanovki(potomok, ostalos, rezultat);
        if (ostalos < 0) break;
    }
    return rezultat;
}

std::vector<char> getPerm2(const PMTree& derevo, int nomer) {
    std::vector<char> rezultat;
    const int vsego = derevo.poluchitVsegoPerestanovok();
    
    if (nomer < 1 || nomer > vsego) return rezultat;
    
    int ostalos = nomer - 1;
    const PMTree::Uzel* tekushiy = derevo.poluchitKoren();
    
    while (!tekushiy->potomki.empty()) {
        int kolichestvo_potomkov = tekushiy->potomki.size();
        int razmer_poddereva = vsego / kolichestvo_potomkov;
        int indeks = ostalos / razmer_poddereva;
        ostalos = ostalos % razmer_poddereva;
        
        tekushiy = tekushiy->potomki[indeks];
        rezultat.push_back(tekushiy->simvol);
    }
    
    return rezultat;
}
