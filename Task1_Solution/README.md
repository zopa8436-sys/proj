Task 1 solution (Итоговое задание)

g++ -std=c++17 -O2 main.cpp VectorTask1.cpp -o task1
Build (g++ on Linux):

```bash
cd Task1_Solution
g++ -std=c++17 -O2 main.cpp VectorTask1.cpp -o task1
./task1
```

The program now runs without manual input: it randomly chooses `n` in [12..30] and a random interval `a b` (with `a<=b`), saves the generated vector to `vector_before.bin`, performs the requested operations, prints results, and finally restores the vector from the binary file.
