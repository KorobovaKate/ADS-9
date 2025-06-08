// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
public:
    struct Uzel {
        char simvol;
        std::vector<Uzel*> childUzel;
        
        Uzel(char val) : simvol(val) {}
        ~Uzel() {
            for (Uzel* child : childUzel) {
                delete child;
            }
        }
    };

private:
    Uzel* root;
    int kol_perestanovok;
    
    void buildTree(Uzel* parent, const std::vector<char>& elements);
    int factorial(int n) const;
    
public:
    explicit PMTree(const std::vector<char>& elements);
    ~PMTree();
    
    int getKolPerestanovok() const { return kol_perestanovok; }
    Uzel* getRoot() const { return root; }
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
