#include <iostream>
#include <vector>
#include <chrono>

const int N = 8192;

int main() {
    // Initialize matrices with sample data
    std::vector<std::vector<float>> A(N, std::vector<float>(N, 1.0f)); // Matrix A with all elements as 1.0f
    std::vector<std::vector<float>> B(N, std::vector<float>(N, 1.0f)); // Matrix B with all elements as 1.0f
    std::vector<std::vector<float>> C(N, std::vector<float>(N, 0.0f)); // Resultant Matrix C

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Matrix multiplication
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End the timer
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "Time taken for matrix multiplication: " << duration.count() << " seconds" << std::endl;

    // Optionally, print some elements of the result matrix for verification
    std::cout << "Some elements from the result matrix: " << std::endl;
    for(int i = 0; i < 10; ++i) {
        std::cout << C[i][i] << " "; // Diagonal elements, should all be N for this sample
    }
    std::cout << std::endl;

    return 0;
}
