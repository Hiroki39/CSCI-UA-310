/*
    smellCosmos.cpp
    Jun 12, 2020
    Hongyi Zheng
    Delete some unnecesary codes and functions to speed up I/O process and
    simplify code, use a helper function to avoid slicing and save time.
*/

#include <iostream>
#include <vector>
using namespace std;

/*
 * Complete the 'smellCosmos' function below.
 *
 * The function is expected to return a LONG_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. LONG_INTEGER_ARRAY a
 *  2. LONG_INTEGER_ARRAY b
 */

void mod(vector<long>& polynomial) {
    for (size_t i = 0; i < polynomial.size(); ++i) {
        polynomial[i] = (polynomial[i] % 1000000009 + 1000000009) % 1000000009;
    }
}

// prevent slicing, which takes up much time
vector<long> karatsuba(const vector<long>& a, const vector<long>& b, int start,
                       int end) {
    vector<long> result(2 * (end - start) + 1, 0);

    if (end - start < 32) {  // base case
        for (int i = 0; i < end - start + 1; ++i) {
            for (int j = 0; j < end - start + 1; ++j) {
                result[i + j] +=
                    ((a[start + i] * b[start + j]) % 1000000009 + 1000000009) %
                    1000000009;
            }
        }
        mod(result);
        return result;
    }

    int mid =
        (start + end) / 2;  // calculate the mid index to divide polynomial

    vector<long> fmid, gmid;
    for (int i = 0; i < (end - start + 1) / 2; ++i) {
        fmid.push_back(a[start + i] + a[mid + 1 + i]);
        gmid.push_back(b[start + i] + b[mid + 1 + i]);
    }
    if ((end - start) % 2 == 0) {
        fmid.push_back(a[mid]);
        gmid.push_back(b[mid]);
    }
    mod(fmid);
    mod(gmid);

    // calculate fmid * gmid, flo * glo, fhi* ghi
    vector<long> fmid_gmid = karatsuba(fmid, gmid, 0, fmid.size() - 1);
    vector<long> flo_glo = karatsuba(a, b, start, mid);
    vector<long> fhi_ghi = karatsuba(a, b, mid + 1, end);

    for (size_t i = 0; i < flo_glo.size(); ++i) {
        result[i] += flo_glo[i];     // add flo * glo to the result
        fmid_gmid[i] -= flo_glo[i];  // subtract flo * glo from fmid * gmid
    }

    int hi_start = (mid - start + 1) * 2;  // calculate n in x^n
    for (size_t i = 0; i < fhi_ghi.size(); ++i) {
        result[i + hi_start] += fhi_ghi[i];  // add fhi * ghi to the result
        fmid_gmid[i] -= fhi_ghi[i];  // subtract fhi * ghi from fmid * gmid
    }

    int mid_start = mid - start + 1;  // calculate 2/n in x^(2/n)
    for (size_t i = 0; i < fmid_gmid.size(); ++i) {
        result[i + mid_start] +=
            fmid_gmid[i];  // add fhi * glo + flo* ghi to the result
    }
    mod(result);
    return result;
}

// call karatsuba() to calculate the result, do modulo opertion before
// returning the vector
vector<long> smellCosmos(const vector<long>& a, const vector<long>& b) {
    return karatsuba(a, b, 0, a.size() - 1);
}

int main() {
    int n;
    cin >> n;

    vector<long> a, b;
    long a_i, b_i;

    for (int i = 0; i < n + 1; i++) {
        cin >> a_i;
        a.push_back(a_i);
    }
    for (int i = 0; i < n + 1; i++) {
        cin >> b_i;
        b.push_back(b_i);
    }

    vector<long> result = smellCosmos(a, b);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}
