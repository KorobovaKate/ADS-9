// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 private:
  struct Node {
    char simvol;
    std::vector<Node*> childUzel;
        
    Node(char sim) : simvol(sim) {}
    ~Node() {
      for (Node* child : childUzel) {
        delete child;
      }
    }
  };

  Node* root;
  int kol_perestanovok;

  void building(Node* parent, const std::vector<char>& komponents);
  int factorials(int n) const;

 public:
  explicit PMTree(const std::vector<char>& komponents);
  ~PMTree();

  int getKolPerestanovki() const { return kol_perestanovok; }
  Node* getRoot() const { return root; }
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
