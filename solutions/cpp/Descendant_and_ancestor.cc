// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "./BST_prototype.h"

using std::unique_ptr;

bool SearchTarget(const unique_ptr<BSTNode<int>>&,
                  const unique_ptr<BSTNode<int>>&);

// @include
bool PairIncludesAncestorAndDescendantOfM(
    const unique_ptr<BSTNode<int>>& possible_anc_or_desc_0,
    const unique_ptr<BSTNode<int>>& possible_anc_or_desc_1,
    const unique_ptr<BSTNode<int>>& middle) {
  auto *search_0 = possible_anc_or_desc_0.get();
  auto *search_1 = possible_anc_or_desc_1.get();

  // Perform interleaved searching from possible_anc_or_desc_0 and 
  // possible_anc_or_desc_1 for middle.
  while (search_0 != possible_anc_or_desc_1.get() &&
         search_0 != middle.get() &&
         search_1 != possible_anc_or_desc_0.get() && 
         search_1 != middle.get() &&
         (search_0 || search_1)) {
    if (search_0) {
      search_0 = search_0->data > middle->data ?
                 search_0->left.get() : search_0->right.get();
    }
    if (search_1) {
      search_1 = search_1->data > middle->data ?
                 search_1->left.get() : search_1->right.get();
    }
  }

  // If both searches were unsuccessful, or we got from 
  // possible_anc_or_desc_0 to possible_anc_or_desc_1 without seeing middle, 
  // or from possible_anc_or_desc_1 to possible_anc_or_desc_0 without seeing 
  // middle, middle cannot lie between possible_anc_or_desc_0 and 
  // possible_anc_or_desc_1.
  if ((search_0 != middle.get() && search_1 != middle.get()) ||
      search_0 == possible_anc_or_desc_1.get() || 
      search_1 == possible_anc_or_desc_0.get()) {
    return false;
  }

  // If we get here, we already know one of possible_anc_or_desc_0 or 
  // possible_anc_or_desc_1 has a path to middle. Check if middle has a path 
  // to possible_anc_or_desc_1 or to possible_anc_or_desc_0.
  return search_0 == middle.get() ?
         SearchTarget(middle, possible_anc_or_desc_1) :
         SearchTarget(middle, possible_anc_or_desc_0);
}

bool SearchTarget(const unique_ptr<BSTNode<int>>& from,
                  const unique_ptr<BSTNode<int>>& target) {
  auto *iter = from.get();
  while (iter && iter != target.get()) {
    iter = iter->data > target->data ? iter->left.get() : iter->right.get();
  }
  return iter == target.get();
}
// @exclude

void SmallTest() {
  auto root = unique_ptr<BSTNode<int>>(new BSTNode<int>{5});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{4});
  assert(!PairIncludesAncestorAndDescendantOfM(root, root->left, root->left->right));

  // Example of the first figure of BST chapter.
  root = unique_ptr<BSTNode<int>>(new BSTNode<int>{19});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{7});
  root->left->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{3});
  root->left->left->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->left->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{5});
  root->left->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{11});
  root->left->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{17});
  root->left->right->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{13});
  root->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{43});
  root->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{23});
  root->right->left->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{37});
  root->right->left->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{29});
  root->right->left->right->left->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{31});
  root->right->left->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{41});
  root->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{47});
  root->right->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{53});

  assert(!PairIncludesAncestorAndDescendantOfM(root->right, root->left,
                                         root->right->left));
  assert(PairIncludesAncestorAndDescendantOfM(root, root->right->left->right->left->right,
                                         root->right->left));
}

int main(int argc, char* argv[]) {
  SmallTest();
  //      3
  //    2   5
  //  1    4 6
  auto root = unique_ptr<BSTNode<int>>(new BSTNode<int>{3});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{1});
  root->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{5});
  root->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{4});
  root->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{6});
  assert(PairIncludesAncestorAndDescendantOfM(root, root->right->right, root->right));
  assert(PairIncludesAncestorAndDescendantOfM(root->right->right, root, root->right));
  assert(!PairIncludesAncestorAndDescendantOfM(root, root->right,
                                         root->right->right));
  assert(!PairIncludesAncestorAndDescendantOfM(root->right, root,
                                         root->right->right));
  assert(!PairIncludesAncestorAndDescendantOfM(root->right->left, root->right->right,
                                         root->right));
  assert(!PairIncludesAncestorAndDescendantOfM(root->right->left, root->left->left,
                                         root->right));
  return 0;
}
