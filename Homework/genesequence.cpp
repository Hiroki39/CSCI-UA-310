/*
    genesequence.cpp
    Jun 24, 2020
    Hongyi Zheng
    Use DP tables to find highest gene sequence alignment score and number of
    aligments that will result in highest score in a short time
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // Receive inputs
    string seq1, seq2;
    cin >> seq1 >> seq2;

    // Initalize two DP tables
    vector<vector<int>> scores(seq1.size() + 1,
                               vector<int>(seq2.size() + 1, 0));
    vector<vector<int>> num_of_alignments(seq1.size() + 1,
                                          vector<int>(seq2.size() + 1, 0));

    // Setting base cases
    for (size_t i = 0; i < seq1.size() + 1; ++i) {
        scores[i][0] = -i;
        num_of_alignments[i][0] = 1;
    }
    for (size_t j = 0; j < seq2.size() + 1; ++j) {
        scores[0][j] = -j;
        num_of_alignments[0][j] = 1;
    }

    // Iterate throught DP tables
    for (size_t i = 1; i < seq1.size() + 1; ++i) {
        for (size_t j = 1; j < seq2.size() + 1; ++j) {
            int solution1 = scores[i - 1][j] - 1;
            int solution2 = scores[i][j - 1] - 1;
            int solution3;
            if (seq1[i - 1] == seq2[j - 1]) {
                solution3 = scores[i - 1][j - 1] + 2;
            } else {
                solution3 = scores[i - 1][j - 1] - 1;
            }
            scores[i][j] = max(max(solution1, solution2), solution3);

            // Add number of aligments according to the score
            if (scores[i][j] == solution1)
                num_of_alignments[i][j] =
                    (num_of_alignments[i][j] + num_of_alignments[i - 1][j]) %
                    1000000009;
            if (scores[i][j] == solution2)
                num_of_alignments[i][j] =
                    (num_of_alignments[i][j] + num_of_alignments[i][j - 1]) %
                    1000000009;
            if (scores[i][j] == solution3)
                num_of_alignments[i][j] = (num_of_alignments[i][j] +
                                           num_of_alignments[i - 1][j - 1]) %
                                          1000000009;
        }
    }

    // Output results
    cout << scores[seq1.size()][seq2.size()] << endl;
    cout << num_of_alignments[seq1.size()][seq2.size()] << endl;
}
