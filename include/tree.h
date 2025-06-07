// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 private:
    struct Uzel {
        char simvol;
        std::vector<Uzel*> potomki;
        
        Uzel(char sim) : simvol(sim) {}
        ~Uzel() {
            for (Uzel* potomok : potomki) {
                delete potomok;
            }
        }
    };

    Uzel* koren;
    int vsego_perestanovok;

    void stroitDerevo(Uzel* roditel, const std::vector<char>& elementi);
    int vichislitFactorial(int n) const;

 public:
    explicit PMTree(const std::vector<char>& elementi);
    ~PMTree();

    int poluchitVsegoPerestanovok() const { return vsego_perestanovok; }
    Uzel* poluchitKoren() const { return koren; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& derevo);
std::vector<char> getPerm1(const PMTree& derevo, int nomer);
std::vector<char> getPerm2(const PMTree& derevo, int nomer);

#endif  // INCLUDE_TREE_H_
