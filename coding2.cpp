/*
Coding Assignment 2 - C++ Template

Reads relation R from input.txt (in the current working directory).

File format:
    n m
    a b
    a b
    ...
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <stdexcept>

using namespace std;

using Pair = pair<int,int>;
using Relation = set<Pair>;

// =========================
// Step 0: Input + Validation
// =========================

pair<int, Relation> read_input(const string& filename = "input.txt") {
    // Build path: directory_of_this_cpp_file + filename
    string file_path;

    {
        // __FILE__ is the path to this source file at compile time
        string src_path = __FILE__;
        size_t pos = src_path.find_last_of("/\\");
        string src_dir = (pos == string::npos) ? string(".") : src_path.substr(0, pos);
        file_path = src_dir + "/" + filename;
    }

    ifstream fin(file_path.c_str());
    if (!fin.is_open()) {
        throw runtime_error("File '" + filename + "' not found next to the .cpp file. Expected at: " + file_path);
    }

    int n, m;
    if (!(fin >> n >> m)) {
        throw runtime_error("First line must contain two integers: n m");
    }

    // Constraints
    if (!(1 <= n && n <= 150)) {
        throw runtime_error("Constraint violated: 1 ≤ n ≤ 150");
    }
    if (!(0 <= m && m <= n * n)) {
        throw runtime_error("Constraint violated: 0 ≤ m ≤ n^2");
    }

    Relation R;
    for (int i = 0; i < m; i++) {
        int a, b;
        if (!(fin >> a >> b)) {
            throw runtime_error("Each relation pair must contain two integers.");
        }
        if (!(0 <= a && a < n && 0 <= b && b < n)) {
            throw runtime_error("Relation elements must satisfy 0 ≤ a,b < n");
        }
        R.insert(std::make_pair(a, b));
    }

    return std::make_pair(n, R);
}

// =========================
// Step 1: Relation Property Checkers
// =========================

bool is_reflexive(int n, const Relation& R) {
    /*
    Returns True iff (x,x) ∈ R for every x in D.
    */
    for (int x = 0; x < n; x++) {
         if (R.find({x, x}) == R.end()) return false;
    }
    return true;
}

bool is_symmetric(const Relation& R) {
    /*
    Returns True iff for every (a,b) in R, (b,a) is also in R.
    */
    for (const auto& p : R) {
        int a = p.first;
        int b = p.second;
        if (R.find({b, a}) == R.end()) return false;
    }
    return true;
}

bool is_transitive(int n, const Relation& R) {
    /*
    Returns True iff whenever (a,b) ∈ R and (b,c) ∈ R, then (a,c) ∈ R.

    IMPORTANT:
    Must be checked on original R only (not closure).

    TEMPLATE NOTE:
    Placeholder ALWAYS returns True. Replace with real logic.
    */
    for (const auto& ab : R) {
        int a = ab.first;
        int b = ab.second;
        
        // Look for all pairs starting with b
        for (const auto& bc : R) {
            if (bc.first == b) {
                int c = bc.second;
                // Check if (a,c) is in R
                if (R.find({a, c}) == R.end()) {
                    return false;
                }
            }
        }
    }
    return true;
}

// =========================
// Step 2: Transitive Closure
// =========================

Relation transitive_closure(int n, const Relation& R) {
    /*
    Returns R+, the transitive closure of R.

    TEMPLATE NOTE:
    Placeholder returns R unchanged, so |R+| == |R|.
    Replace with Warshall or DFS/BFS.
    */
    (void)n; // placeholder
    // TODO: Implement transitive closure (Warshall or DFS/BFS)
    Relation R_plus = R;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (R_plus.find({i, k}) != R_plus.end()) {
                for (int j = 0; j < n; j++) {
                    if (R_plus.find({k, j}) != R_plus.end()) {
                        R_plus.insert({i, j});
                    }
                }
            }
        }
    }
    
    return R_plus;
}

// =========================
// Step 3: Main + Output
// =========================

int main() {
    try {
        pair<int, Relation> result = read_input("input.txt");
        int n = result.first;
        Relation R = result.second;

        bool reflexive = is_reflexive(n, R);
        bool symmetric = is_symmetric(R);
        bool transitive = is_transitive(n, R);

        Relation R_plus = transitive_closure(n, R);

        cout << "Reflexive = " << (reflexive ? "True" : "False") << "\n";
        cout << "Symmetric = " << (symmetric ? "True" : "False") << "\n";
        cout << "Transitive = " << (transitive ? "True" : "False") << "\n";
        cout << "|R+| = " << R_plus.size() << "\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}