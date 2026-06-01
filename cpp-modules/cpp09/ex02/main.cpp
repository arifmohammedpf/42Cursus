#include "PmergeMe.hpp"

void printVector(const std::vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i];
        if (i < arr.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

bool isValidNumber(const std::string &str)
{
    if (str.empty())
        return false;

    if (str.length() > 1 && str[0] <= '0')
        return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+')
    {
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }
    }

    long long num = std::atoll(str.c_str());

    if (num > INT_MAX || num < INT_MIN)
    {
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Error: No arguments provided" << std::endl;
            std::cerr << "Usage: " << argv[0] << " <num1> <num2> ... <numN>" << std::endl;
            return 1;
        }

        std::vector<int> vectorNumbers;
        std::deque<int> dequeNumbers;
        for (int i = 1; i < argc; ++i)
        {
            if (!isValidNumber(argv[i]))
            {
                std::cerr << "Error: Not a valid number: " << argv[i] << std::endl;
                return 1;
            }
            int num = std::atoi(argv[i]);
            vectorNumbers.push_back(num);
            dequeNumbers.push_back(num);
        }

        std::cout << "Before: ";
        printVector(vectorNumbers);

        PmergeMe fordSort;

        std::clock_t startVec = std::clock();
        fordSort.sort(vectorNumbers);
        std::clock_t endVec = std::clock();
        double timeVec = 1000000.0 * (endVec - startVec) / CLOCKS_PER_SEC;

        std::clock_t startDeque = std::clock();
        fordSort.dequeSort(dequeNumbers);
        std::clock_t endDeque = std::clock();
        double timeDeque = 1000000.0 * (endDeque - startDeque) / CLOCKS_PER_SEC;

        std::cout << "After:  ";
        printVector(vectorNumbers);

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Time to process a range of " << vectorNumbers.size()
                  << " elements with std::vector : " << timeVec << " us" << std::endl;
        std::cout << "Time to process a range of " << dequeNumbers.size()
                  << " elements with std::deque  : " << timeDeque << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
