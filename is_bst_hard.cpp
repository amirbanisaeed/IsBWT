#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#include <queue>
#endif

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using namespace std;

struct Node
{
    long long int key;
    int depth;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void PreOrderTraverse(vector<Node>& tree, int index, queue<long long int>& q, int& cnt)
{

    if (index == -1)
    {
        return;
    }

    q.push(cnt);
    tree[index].depth = cnt;
    cnt++;
    //cout << "Pre " << tree[index].key << endl;
   // cout << cnt << endl;
    PreOrderTraverse(tree, tree[index].left, q, cnt);
    PreOrderTraverse(tree, tree[index].right, q, cnt);
}

void InOrderTraverse(const vector<Node>& tree, int index, queue<long long int>& q, queue<long long int>& d, bool& Isbst)
{
    if (index == -1)
    {
        return;
    }

    InOrderTraverse(tree, tree[index].left, q, d, Isbst);
    if (q.front() > tree[index].key)
    {
        Isbst = false;
        return;
    }
    else if (q.front() == tree[index].key)
    {
        if (tree[index].depth < d.front())
        {
            Isbst = false;
            return;
        }

    }

    q.pop();
    q.push(tree[index].key);

    d.pop();
    d.push(tree[index].depth);

    //cout << key[index];
    InOrderTraverse(tree, tree[index].right, q, d, Isbst);
}
/*
void InOrderTraverse(const vector<Node> &tree, int index, queue<long long int> &q, bool &Isbst, bool &iAmRight)
{
  if (index == -1)
  {

    return;
  }

  //ComingFromRight = false;
  InOrderTraverse(tree, tree[index].left, q, Isbst, iAmRight);
  if (iAmRight)
  {
    if (q.front() > tree[index].key)
    {
      Isbst = false;
      return;
    }
    iAmRight = false;
  }
  else
  {
    if (q.front() >= tree[index].key)
    {
      Isbst = false;
      return;
    }
  }

  q.pop();
  q.push(tree[index].key);


  iAmRight = true;

  //cout << key[index];
  InOrderTraverse(tree, tree[index].right, q, Isbst, iAmRight);
  if (tree[index].right == -1)
  {
    iAmRight = false;
  }
}
*/
bool IsBinarySearchTree(vector<Node>& tree)
{
    // Implement correct algorithm here
    if (tree.size() == 0)
    {
        return true;
    }

    queue<long long int> q, d;
    queue<long long int> ref;
    int cnt = 0;
    q.push(INT32_MIN);
    d.push(0);

    PreOrderTraverse(tree, 0, ref, cnt);

    bool isBST = true;
    bool ComingLeft = false;
    InOrderTraverse(tree, 0, q, d, isBST);
    //InOrderTraverse(tree, 0, q, isBST, ComingLeft);
    return isBST;
}
/*
int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
*/
int main(int argc, char** argv)
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 16 * 1024 * 1024; // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif

    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i)
    {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree))
    {
        cout << "CORRECT" << endl;
    }
    else
    {
        cout << "INCORRECT" << endl;
    }

    return 0;
}
