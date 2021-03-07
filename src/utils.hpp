#include <vector>
#include <random>
#include <algorithm>

template <typename T>
inline void initialize_random_array(T *array, int n, T min_val = 0, T max_val = 10, bool sum_to_one = true, bool norm_one = false) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> dist(min_val, max_val);
    for (int i = 0; i < n; i++) {
        array[i] = (T)dist(engine);
    }

    if (sum_to_one) {
        T sum = 0;
        for (int i = 0; i < n; i++) {
            sum += array[i];
        }
        for (int i = 0; i < n; i++) {
            array[i] /= sum;
        }
    } else if (norm_one) {
        T sum = 0;
        for (int i = 0; i < n; i++) {
            sum += array[i] * array[i];
        }
        for (int i = 0; i < n; i++) {
            array[i] /= sqrt((double)sum);
        }
    }
}

template <typename T>
inline void initialize_random_array(std::vector<T> &array, T min_val = 0, T max_val = 10, bool sum_to_one = true, bool norm_one = false) {
    initialize_random_array(array.data(), array.size(), min_val, max_val, sum_to_one, norm_one);
}

inline void initialize_random_array(int *array, int n, int min_val = 0, int max_val = 10) {
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (max_val - min_val)) + min_val;
    }
}

inline void initialize_random_array(std::vector<int> &array, int min_val = 0, int max_val = 10) {
    initialize_random_array(array.data(), array.size(), min_val, max_val);
}

template <typename I, typename O>
inline O mean(I *a, int n, int skip = 0) {
    O sum = 0;
    int fixed_size = n - skip;
    if (fixed_size <= 0)
        return (O)0;
    for (int i = skip; i < n; i++) {
        sum += (O)a[i];
    }
    return sum / fixed_size;
}

template <typename I, typename O>
inline O st_dev(I *a, int n, int skip = 0) {
    O sum = 0;
    O sum_sq = 0;
    int fixed_size = n - skip;
    if (fixed_size <= 0)
        return (O)0;
    for (int i = skip; i < n; i++) {
        sum += (O)a[i];
        sum_sq += (O)a[i] * (O)a[i];
    }
    O diff = sum_sq - (sum * sum / fixed_size);
    return diff >= 0 ? std::sqrt(diff / fixed_size) : (O)0;
}