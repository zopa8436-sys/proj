Task 1 solution (Итоговое задание)

Build (g++ on Linux):

```bash
cd Task1_Solution
g++ -std=c++17 -O2 main.cpp VectorTask1.cpp -o task1
./task1
```

The program asks for `n` (12..30) and interval `a b`. It saves the generated vector to `vector_before.bin` before performing the requested operations, prints results, and finally restores the vector from the binary file.
