//
// Created by Szef on 07.12.2023.
//

#ifndef PEA_PROJEKT2_TEST_H
#define PEA_PROJEKT2_TEST_H


class Test {
public:
    //rozmiar tabu zalezny od rozmiaru instancji (7*tabu.size)
    static void generateFile_BestSolutionInTime_ftv55(int numberOfInstances, int time);
    static void generateFile_BestSolutionInTime_ftv170(int numberOfInstances, int time);
    static void generateFile_BestSolutionInTime_rbg358(int numberOfInstances, int time);

    //rozmiar tabu niezalezny od instancji (wartosc stala: 500)
    static void generateFile_BestSolutionInTime_ftv55v2(int numberOfInstances, int time);
    static void generateFile_BestSolutionInTime_ftv170v2(int numberOfInstances, int time);
    static void generateFile_BestSolutionInTime_rbg358v2(int numberOfInstances, int time);
};


#endif //PEA_PROJEKT2_TEST_H
