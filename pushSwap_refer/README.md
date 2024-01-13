# push_swap

Push_swap is a project in the 42 curriculum. It's a sorting algorithm that takes a list of numbers as input and sorts them using a set of operations performed on two stacks. The goal of the project is to find the smallest set of operations necessary to sort the list.

Here's what you need to know to understand Push_swap:

- Two Stacks: The algorithm uses two stacks, "A" and "B," to store and sort the input numbers.

- Available Operations: The algorithm uses a set of operations to manipulate the numbers in the stacks, including "sa" (swap the first two numbers in stack A), "ra" (rotate the first element on stack A), "pa" (pop the first number from stack B and push it onto stack A), and "pb" (pop the first number from stack A and push it onto stack B).

- Sorting Algorithm: The sorting algorithm works by continuously manipulating the numbers in the stacks until they are sorted in ascending order in stack A. For This Project I choose `"RADIX"` sort algorithm.

- Optimization: The goal of the project is to find the smallest set of operations necessary to sort the list, so optimization is a key component of the project.

- Implementation: The project is implemented in C and must be compiled using the 42 project standards.

- Testing: The program is tested using a set of provided test cases, as well as additional test cases created by the user.

Push_swap is a challenging project that requires a deep understanding of stack data structures and sorting algorithms. It's a great opportunity to improve coding skills and problem-solving abilities.





## Table of Contents
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Support](#support)
- [Acknowledgments](#acknowledgments)

## Getting Started

Installing the `push_swap` can be done in a few simple steps:

1. Download the project from the project's GitHub repo.

2. Open a terminal and navigate to the directory where the files were cloned.

3. Run the following command to compile the program:


````
make
````
This will create a `./push_swap` file in the directory, which is the compiled program that you can test.

## Usage

To test the code simply rum the program name on the terminal, followed by a sequence of numbers

````
./push_swap 3 2 1
````

<img width="466" alt="Screenshot 2023-01-29 at 12 22 03 PM" src="https://user-images.githubusercontent.com/59938530/215314603-68a27c9a-12ef-44a3-ab86-e39501542fd0.png">


## Support

Feel free to contact me on slack or via email

email - `tehuanmelo@gmail.com`

twitter - `@tehuanmelo`

slack - `tde-melo`

## Acknowledgments
I am extremely thankful to the @42AbuDhabi for providing me with endless opportunities and support. The resources, guidance, and education I have received have been invaluable. I am grateful for the investment the 42 Abu Dhabi has made in me and my collegues, we will strive to make the most of this gift. Thank you @42AbuDhabi for everything.
