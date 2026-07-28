#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

#define pb push_back

// The main string and the number of patterns
string s;
int n, nodeIndex = 1, patternFound[500005];

// Adjacency list for the trie nodes
vector<int> trieAdjList[500005];

// Structure for each node in the trie
struct TrieNode {
    int failureLink, child[26] = {}, occurrences = 0;
    vector<int> patternIndices;
} trie[500005];

// Function to insert a pattern into the trie
void insertPattern(string pattern, int index)
{
    int node = 1;
    for (int i = 0; i < pattern.size(); i++) {
        if (trie[node].child[pattern[i] - 'a'] == 0)
            trie[node].child[pattern[i] - 'a'] = ++nodeIndex;
        node = trie[node].child[pattern[i] - 'a'];
    }
    trie[node].patternIndices.pb(index);
}

// Function to build the failure links for the Aho-Corasick
// algorithm
void buildFailureLinks()
{
    // Initialize a queue for BFS traversal
    queue<int> nodeQueue;

    // Start from the root node
    int node = 1;

    // Set failure link of root node to itself
    trie[1].failureLink = 1;

    // Push all child nodes of the root to the queue
    for (int i = 0; i < 26; i++) {
        if (trie[node].child[i])
            trie[trie[node].child[i]].failureLink = node,
            nodeQueue.push(trie[node].child[i]);
        else
            trie[node].child[i]
            = 1; // If child node doesn't exist, point
        // to root
    }

    // Perform BFS traversal to set failure links
    while (!nodeQueue.empty()) {
        node = nodeQueue.front();
        nodeQueue.pop();
        for (int i = 0; i < 26; i++) {
            if (trie[node].child[i])
                trie[trie[node].child[i]].failureLink
                = trie[trie[node].failureLink].child[i],
                nodeQueue.push(trie[node].child[i]);
            else
                trie[node].child[i]
                = trie[trie[node].failureLink].child[i];
        }
    }
    // Create adjacency list based on failure links
    for (int i = 2; i <= nodeIndex; i++)
        trieAdjList[trie[i].failureLink].pb(i);
}

// Function to run the Aho-Corasick algorithm on the main
// string
void runAhoCorasick(string s)
{
    // Start from the root node
    for (int i = 0, node = 1; i < s.size(); i++) {
        // Traverse the trie based on characters in the main
        // string
        node = trie[node].child[s[i] - 'a'];
        // Increment occurrences at each node
        trie[node].occurrences++;
    }
}

// DFS function to propagate the occurrences down the trie
int dfs(int u)
{
    // Initialize total occurrences at current node
    int totalOccurrences = trie[u].occurrences;

    // Traverse child nodes recursively
    for (int v : trieAdjList[u])
        totalOccurrences += dfs(v);

    // Propagate occurrences to pattern indices
    for (int patternIndex : trie[u].patternIndices)
        patternFound[patternIndex] = totalOccurrences;

    // Return total occurrences
    return totalOccurrences;
}

// Main function
int main()
{
    string s; cin >> s;
    int n; cin >> n;
    vector<string> patterns(n);
    // Input and insert patterns into trie
    for (int i = 0; i < n; i++) {
        cin >> patterns[i];
        insertPattern(patterns[i], i);
    }

    // Build failure links for Aho-Corasick algorithm
    buildFailureLinks();

    // Run Aho-Corasick algorithm on main string
    runAhoCorasick(s);

    // Propagate occurrences down the trie using DFS
    dfs(1);

    // Output pattern matches
    for (int i = 0; i < n; i++)
        cout << (patternFound[i] ? "YES" : "NO") << '\n';
}