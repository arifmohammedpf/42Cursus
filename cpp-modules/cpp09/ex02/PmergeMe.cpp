#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &object)
{
    *this = object;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
    if (this != &rhs)
    {
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::sort(std::vector<int> &arr)
{
    if (arr.size() <= 1)
    {
        return;
    }

    bool hasLeftover = false;
    int leftover = 0;
    std::vector<std::pair<int, int> > pairs = makePairs(arr, hasLeftover, leftover);

    if (pairs.empty())
    {
        return;
    }

    sortPairs(pairs);

    std::vector<int> mainChain = buildMainChain(pairs);
    std::vector<int> pendingChain = buildPendingChain(pairs);
    std::vector<size_t> jacobsthal = generateJacobsthal(pendingChain.size());

    for (size_t i = 0; i < jacobsthal.size(); i++)
    {
        size_t index = jacobsthal[i];
        if (index < pendingChain.size())
        {
            binaryInsert(mainChain, pendingChain[index]);
        }
    }

    if (hasLeftover)
    {
        binaryInsert(mainChain, leftover);
    }

    arr = mainChain;
}

std::vector<std::pair<int, int> > PmergeMe::makePairs(const std::vector<int> &arr, bool &hasLeftover, int &leftover)
{
    std::vector<std::pair<int, int> > pairs;
    size_t size = arr.size();

    if (size % 2 == 1)
    {
        hasLeftover = true;
        leftover = arr[size - 1];
        size--;
    }

    for (size_t i = 0; i < size; i += 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        if (a > b)
        {
            pairs.push_back(std::make_pair(a, b));
        }
        else
        {
            pairs.push_back(std::make_pair(b, a));
        }
    }

    return pairs;
}

void PmergeMe::sortPairs(std::vector<std::pair<int, int> > &pairs)
{
    for (size_t i = 1; i < pairs.size(); i++)
    {
        std::pair<int, int> key = pairs[i];
        int j = i - 1;

        while (j >= 0 && pairs[j].first > key.first)
        {
            pairs[j + 1] = pairs[j];
            j--;
        }
        pairs[j + 1] = key;
    }
}

std::vector<int> PmergeMe::buildMainChain(const std::vector<std::pair<int, int> > &pairs)
{
    std::vector<int> mainChain;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].first);
    }

    return mainChain;
}

std::vector<int> PmergeMe::buildPendingChain(const std::vector<std::pair<int, int> > &pairs)
{
    std::vector<int> pendingChain;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        pendingChain.push_back(pairs[i].second);
    }

    return pendingChain;
}

std::vector<size_t> PmergeMe::generateJacobsthal(size_t n)
{
    if (n == 0)
    {
        return std::vector<size_t>();
    }

    std::vector<size_t> jacobsthalNumbers;
    jacobsthalNumbers.push_back(0);
    jacobsthalNumbers.push_back(1);

    while (true)
    {
        size_t size = jacobsthalNumbers.size();
        size_t next = jacobsthalNumbers[size - 1] + 2 * jacobsthalNumbers[size - 2];
        if (next >= n)
        {
            break;
        }
        jacobsthalNumbers.push_back(next);
    }

    std::vector<size_t> insertionOrder;
    std::vector<bool> inserted(n, false);

    for (size_t i = 2; i < jacobsthalNumbers.size(); i++)
    {
        size_t jacobsthal = jacobsthalNumbers[i];
        size_t prevJacobsthal = jacobsthalNumbers[i - 1];

        for (size_t j = jacobsthal; j > prevJacobsthal; j--)
        {
            if (j - 1 < n && !inserted[j - 1])
            {
                insertionOrder.push_back(j - 1);
                inserted[j - 1] = true;
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        if (!inserted[i])
        {
            insertionOrder.push_back(i);
        }
    }

    return insertionOrder;
}

void PmergeMe::binaryInsert(std::vector<int> &arr, int value)
{
    int left = 0;
    int right = arr.size();

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    arr.insert(arr.begin() + left, value);
}

void PmergeMe::dequeSort(std::deque<int> &arr)
{
    if (arr.size() <= 1)
    {
        return;
    }

    bool hasLeftover = false;
    int leftover = 0;
    std::deque<std::pair<int, int> > pairs = makeDequePairs(arr, hasLeftover, leftover);

    if (pairs.empty())
    {
        return;
    }

    sortDequePairs(pairs);

    std::deque<int> mainChain = buildDequeMainChain(pairs);
    std::deque<int> pendingChain = buildDequePendingChain(pairs);
    std::deque<size_t> jacobsthal = generateDequeJacobsthal(pendingChain.size());

    for (size_t i = 0; i < jacobsthal.size(); i++)
    {
        size_t index = jacobsthal[i];
        if (index < pendingChain.size())
        {
            dequeBinaryInsert(mainChain, pendingChain[index]);
        }
    }

    if (hasLeftover)
    {
        dequeBinaryInsert(mainChain, leftover);
    }

    arr = mainChain;
}

std::deque<std::pair<int, int> > PmergeMe::makeDequePairs(const std::deque<int> &arr, bool &hasLeftover, int &leftover)
{
    std::deque<std::pair<int, int> > pairs;
    size_t size = arr.size();

    if (size % 2 == 1)
    {
        hasLeftover = true;
        leftover = arr[size - 1];
        size--;
    }

    for (size_t i = 0; i < size; i += 2)
    {
        int a = arr[i];
        int b = arr[i + 1];
        if (a > b)
        {
            pairs.push_back(std::make_pair(a, b));
        }
        else
        {
            pairs.push_back(std::make_pair(b, a));
        }
    }

    return pairs;
}

void PmergeMe::sortDequePairs(std::deque<std::pair<int, int> > &pairs)
{
    for (size_t i = 1; i < pairs.size(); i++)
    {
        std::pair<int, int> key = pairs[i];
        int j = i - 1;

        while (j >= 0 && pairs[j].first > key.first)
        {
            pairs[j + 1] = pairs[j];
            j--;
        }
        pairs[j + 1] = key;
    }
}

std::deque<int> PmergeMe::buildDequeMainChain(const std::deque<std::pair<int, int> > &pairs)
{
    std::deque<int> mainChain;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].first);
    }

    return mainChain;
}

std::deque<int> PmergeMe::buildDequePendingChain(const std::deque<std::pair<int, int> > &pairs)
{
    std::deque<int> pendingChain;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        pendingChain.push_back(pairs[i].second);
    }

    return pendingChain;
}

std::deque<size_t> PmergeMe::generateDequeJacobsthal(size_t n)
{
    if (n == 0)
    {
        return std::deque<size_t>();
    }

    std::deque<size_t> jacobsthalNumbers;
    jacobsthalNumbers.push_back(0);
    jacobsthalNumbers.push_back(1);

    while (true)
    {
        size_t size = jacobsthalNumbers.size();
        size_t next = jacobsthalNumbers[size - 1] + 2 * jacobsthalNumbers[size - 2];
        if (next >= n)
        {
            break;
        }
        jacobsthalNumbers.push_back(next);
    }

    std::deque<size_t> insertionOrder;
    std::deque<bool> inserted(n, false);

    for (size_t i = 2; i < jacobsthalNumbers.size(); i++)
    {
        size_t jacobsthal = jacobsthalNumbers[i];
        size_t prevJacobsthal = jacobsthalNumbers[i - 1];

        for (size_t j = jacobsthal; j > prevJacobsthal; j--)
        {
            if (j - 1 < n && !inserted[j - 1])
            {
                insertionOrder.push_back(j - 1);
                inserted[j - 1] = true;
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        if (!inserted[i])
        {
            insertionOrder.push_back(i);
        }
    }

    return insertionOrder;
}

void PmergeMe::dequeBinaryInsert(std::deque<int> &arr, int value)
{
    int left = 0;
    int right = arr.size();

    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    arr.insert(arr.begin() + left, value);
}