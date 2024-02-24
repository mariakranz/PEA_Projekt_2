
# Implementacja i analiza efektywności algorytmu Tabu Search dla problemu komiwojażera

Zadanie polegało na zaimplementowaniu algorytmu Tabu Search rozwiązującego problem komiwojażera i zbadaniu jego wyników dla trzech rozmiarów grafów (z plików ftv55.xml, ftv170.xml, rgb358.xml).

Zaimplementowane zostały trzy definicje sąsiedztwa: _swap_, _reverse_, _insert_.

Kryterium stopu to czas działania algorytmu podawany w sekundach.

Wyniki testów:

| Plik   | Liczba wierzchołków | Czas [s] |  Najlepsza znaleziona ścieżka (o minimalnym koszcie) / Ścieżka optymalna|
| -------|---------------------|----------|-------------------------------------------------------------------------|
| ftv55  |         56          |   120    |                             1608 / 1608                                 |
| ftv170 |        171          |   240    |                             3350 / 2755                                 |
| rbg358 |        358          |   360    |                             1326 / 1163                                 |
