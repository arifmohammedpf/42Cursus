#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <climits>
#include <ctime>
#include <iomanip>
#include <utility>
#include <cstddef>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe &object);
    PmergeMe &operator=(const PmergeMe &rhs);
    ~PmergeMe();

    void sort(std::vector<int>& arr);
    void dequeSort(std::deque<int>& arr);

private:
    std::vector<std::pair<int, int> > makePairs(const std::vector<int>& arr, bool& hasLeftover, int& leftover);
    void sortPairs(std::vector<std::pair<int, int> >& pairs);
    std::vector<int> buildMainChain(const std::vector<std::pair<int, int> >& pairs);
    std::vector<int> buildPendingChain(const std::vector<std::pair<int, int> >& pairs);
    std::vector<size_t> generateJacobsthal(size_t n);
    void binaryInsert(std::vector<int>& arr, int value);

    std::deque<std::pair<int, int> > makeDequePairs(const std::deque<int>& arr, bool& hasLeftover, int& leftover);
    void sortDequePairs(std::deque<std::pair<int, int> >& pairs);
    std::deque<int> buildDequeMainChain(const std::deque<std::pair<int, int> >& pairs);
    std::deque<int> buildDequePendingChain(const std::deque<std::pair<int, int> >& pairs);
    std::deque<size_t> generateDequeJacobsthal(size_t n);
    void dequeBinaryInsert(std::deque<int>& arr, int value);
};

#endif
