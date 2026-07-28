#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// --- Global Constants and Structures ---
const int MAXN = 200005;
// Max number of unique values is N (initial) + Q (updates), approx 400000.
const int MAX_COMPRESSED = 2 * MAXN + 5;

// Update structure: idx (1-based), old_val (raw), new_val (raw)
struct Update {
    int idx;
    int old_val;
    int new_val;
};

// Query structure: L, R (1-based), T (time/update index), id (original query index)
struct Query {
    int L, R, T, id;
};

// --- Global State Variables ---
int N, Q;
int S; // Block size for Mo's Algorithm
int A[MAXN]; // The current state of the array (stores compressed values)
int Count[MAX_COMPRESSED]; // Frequency counter for compressed values
int distinct_count;  // Running count of distinct elements

vector<Update> updates;
vector<Query> queries;
vector<string> results;
vector<int> coordinate_map; // Stores unique raw values for compression


// --- Helper Functions for Coordinate Compression ---
// Maps a raw value to its compressed index (1-based)
int compress_value(int val) {
    return lower_bound(coordinate_map.begin(), coordinate_map.end(), val) - coordinate_map.begin() + 1;
}

// --- Mo's Core Logic ---

int get_block(int x) {
    return x / S;
}

bool compareQueries(const Query& qa, const Query& qb) {
    int block_L_a = get_block(qa.L);
    int block_L_b = get_block(qb.L);
    if (block_L_a != block_L_b) {
        return block_L_a < block_L_b;
    }

    int block_R_a = get_block(qa.R);
    int block_R_b = get_block(qb.R);
    if (block_R_a != block_R_b) {
        // Snake order optimization
        if (block_L_a % 2 == 0) return block_R_a < block_R_b;
        return block_R_a > block_R_b;
    }

    return qa.T < qb.T;
}

// Adds element at index 'i' to the current range
void Add(int i) {
    int val = A[i];
    Count[val]++;
    if (Count[val] == 1) {
        distinct_count++;
    }
}

// Removes element at index 'i' from the current range
void Remove(int i) {
    int val = A[i];
    Count[val]--;
    if (Count[val] == 0) {
        distinct_count--;
    }
}

// Adjusts distinct count during time transition (Apply or Undo)
// k: index, old_comp: compressed value before change, new_comp: compressed value after change
void AdjustTime(int k, int old_comp, int new_comp, int currentL, int currentR) {
    // Crucial check: only adjust if the index k is in the current Mo's range
    if (currentL <= k && k <= currentR) {
        // 1. Remove old value
        Count[old_comp]--;
        if (Count[old_comp] == 0) {
            distinct_count--;
        }

        // 2. Add new value
        Count[new_comp]++;
        if (Count[new_comp] == 1) {
            distinct_count++;
        }
    }
    // Update the array state A[k]
    A[k] = new_comp;
}

// --- Main Solve Function ---

void solve() {
    // 1. Read input and collect all unique values
    cin >> N >> Q;
    vector<int> current_A_raw(N + 1); // Tracks the RAW values for recording subsequent 'old_val' in updates
    for (int i = 1; i <= N; ++i) {
        cin >> current_A_raw[i];
        coordinate_map.push_back(current_A_raw[i]);
    }

    int query_idx_counter = 0;
    int update_idx_counter = 0;

    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;
        if (type == 1) { // Update: 1 k u
            int k, u;
            cin >> k >> u;
            // Store RAW values in the update struct
            updates.push_back({ k, current_A_raw[k], u });
            coordinate_map.push_back(u);
            current_A_raw[k] = u; // Update the tracking array for future updates
            update_idx_counter++;
        }
        else { // Query: 2 a b
            int a, b;
            cin >> a >> b;
            queries.push_back({ a, b, update_idx_counter, query_idx_counter++ });
        }
    }

    // 2. Coordinate Compression
    sort(coordinate_map.begin(), coordinate_map.end());
    coordinate_map.erase(unique(coordinate_map.begin(), coordinate_map.end()), coordinate_map.end());

    // Compress initial array values (from the final state of current_A_raw after all updates were tracked)
    // IMPORTANT: The A array must be initialized to the state just before the *first* query.
    // We must rebuild the initial state array manually.
    vector<int> initial_array_state(N + 1);
    for (int i = 1; i <= N; ++i) initial_array_state[i] = A[i] = compress_value(current_A_raw[i]);

    // Apply updates in reverse to find the true initial state (T=0)
    for (int t = updates.size() - 1; t >= 0; --t) {
        int k = updates[t].idx;
        initial_array_state[k] = updates[t].old_val;
    }

    // Now, A[i] holds the compressed value of the array state at T=0
    for (int i = 1; i <= N; ++i) {
        A[i] = compress_value(initial_array_state[i]);
    }

    // Compress update values (using the global compressed map)
    for (auto& upd : updates) {
        upd.old_val = compress_value(upd.old_val);
        upd.new_val = compress_value(upd.new_val);
    }

    // 3. Mo's Setup and Sorting
    S = max(1, (int)pow(N, 2.0 / 3.0));
    sort(queries.begin(), queries.end(), compareQueries);
    results.resize(query_idx_counter);

    // 4. Mo's Processing
    int currL = 1, currR = 0, currT = 0;

    for (const auto& q : queries) {

        // A. Move Time Pointer (T)
        while (currT < q.T) {
            // Apply Update: A[k] changes from old_val to new_val
            const auto& upd = updates[currT];
            AdjustTime(upd.idx, upd.old_val, upd.new_val, currL, currR);
            currT++;
        }
        while (currT > q.T) {
            // Undo Update: A[k] changes from new_val back to old_val
            currT--;
            const auto& upd = updates[currT];
            // Swap: current value (A[k]) is new_val, target value is old_val
            AdjustTime(upd.idx, upd.new_val, upd.old_val, currL, currR);
        }

        // B. Move Range Pointers (R and L)
        while (currR < q.R) {
            currR++;
            Add(currR);
        }
        while (currR > q.R) {
            Remove(currR);
            currR--;
        }

        while (currL > q.L) {
            currL--;
            Add(currL);
        }
        while (currL < q.L) {
            Remove(currL);
            currL++;
        }

        // 5. Record Answer
        int range_size = q.R - q.L + 1;
        if (distinct_count == range_size) {
            results[q.id] = "YES";
        }
        else {
            results[q.id] = "NO";
        }
    }

    // 6. Output Results
    for (const auto& res : results) {
        cout << res << "\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}