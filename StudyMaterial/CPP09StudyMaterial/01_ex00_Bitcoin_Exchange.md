# CPP09 ex00 — Bitcoin Exchange

This document details the implementation of **ex00 (Bitcoin Exchange)**, explaining the header [BitcoinExchange.hpp](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.hpp), source file [BitcoinExchange.cpp](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp), and [main.cpp](file:///c:/42AD/staff-evaluation/cpp09/ex00/main.cpp).

---

## 1. Class Design (`ex00/BitcoinExchange.hpp`)

The class parses a database of historical Bitcoin exchange rates, processes an input query file, and prints the evaluated values on specific dates.

```cpp
class BitcoinExchange
{
private:
    std::map<std::string, float> _rates;
```
* **What it is for:** Maps date keys to database rate values.
* **Why it is needed:** Dates sorted chronologically as keys allow fast $O(\log n)$ search lookups. Since string sorting maps dates correctly (e.g. `"2011-01-03"` < `"2011-01-04"`), we can use string comparison to traverse dates.

---

## 2. Reading the Database (`ex00/BitcoinExchange.cpp`)

### [readDataFile](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp#L33-L57)
* **What it is for:** Loads the `data.csv` exchange rates database.
* **Why it is needed:** Provides the rate dictionary used for queries.
* **How it works:**
  1. Opens `data.csv` using `std::ifstream`.
  2. Discards the first header line (`date,exchange_rate`).
  3. Loops through lines:
     - Uses `std::stringstream` to parse the line.
     - Extracts the date string up to the comma: `getline(str, date, ',')`.
     - Extracts the remaining rate string: `getline(str, rate)`.
     - Converts the rate using `atof` and saves it: `_rates[date] = atof(rate.c_str())`.

---

## 3. Input Validations

### [isValidDate](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp#L80-L99) & [isValidDateValues](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp#L59-L78)
* **What it is for:** Verifies date string formatting and values.
* **How it works:**
  * Asserts string length is `10` and dashes are at indices 4 and 7 (`YYYY-MM-DD`).
  * Splits the string into year, month, and day integers.
  * Validates value limits:
    * Year is between `2009` and `2022`.
    * Month is between `1` and `12`.
    * Day is between `1` and `31`.
    * Handles leap-years (years 2012, 2016, 2020 allow 29 days in February, other years allow 28).
    * Handles 30-day months (April, June, September, November).

### [isValidValue](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp#L111-L125)
* **What it is for:** Validates the query float amount.
* **How it works:** Parses the value using `atof`. Asserts that the amount is positive (returns error if `< 0`) and not too large (returns error if `> 1000`).

---

## 4. Date Lookup and Query Calculations

If a query date does not exist in the database, the project guidelines state we must look up the rate of the **closest historical date** before it.

The codebase implements this using a custom string-decrementing recursion:

### [getDateAndPrint](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp#L157-L171)
* **What it is for:** Finds the rate on the target date (or previous date) and prints the result.
* **Why it is needed:** Performs the rate calculation and handles missing keys.
* **How it works:**
  1. Searches for the exact date in the map: `_rates.find(date)`.
  2. If found, computes the multiplication and prints it to the screen.
  3. If not found, and the date is greater than or equal to the database start date (`"2009-01-02"`):
     * Decrements the date by one day using `lowerBound`.
     * Recursively calls `getDateAndPrint` with the new date.

```
Lookup simulation for Date "2012-03-05" (missing):
  getDateAndPrint("2012-03-05") 
    │ (not found)
    └─► lowerBound("2012-03-05") ──► returns "2012-03-04"
          │
          ▼
  getDateAndPrint("2012-03-04")
    │ (not found)
    └─► lowerBound("2012-03-04") ──► returns "2012-03-03"
          │
          ▼
  getDateAndPrint("2012-03-03") ──► Found! (Prints result using 2012-03-03 rate)
```

### [lowerBound](file:///c:/42AD/staff-evaluation/cpp09/ex00/BitcoinExchange.cpp#L127-L155)
* **What it is for:** Decrements a date string by one day.
* **Why it is needed:** Backtracks the date search key.
* **How it works:**
  * Splits the string into integer variables `y`, `m`, and `d`.
  * If `d > 1`, decrements `d`.
  * If `d == 1` and `m > 1`, sets `d = 31` and decrements `m`.
  * If `d == 1`, `m == 1` and `y > 2008`, sets `d = 31`, `m = 12`, and decrements `y`.
  * Formats the integers back into a `"YYYY-MM-DD"` string using `std::setfill('0')`.
  * *Evaluation Note:* This algorithm assumes all months have 31 days during backtracking. While it successfully finds preceding keys in the map, it can traverse through invalid intermediate dates (like February 30th) if they are missing from the database. A standard alternative is using `std::map::lower_bound` which searches the tree elements directly in $O(\log n)$ time.

---

## 5. Main Execution Flow (`ex00/main.cpp`)

The `main` function instantiates the class, passing the input query file:

```cpp
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return (1);
    }
    BitcoinExchange exchange(argv[1]);
    return (0);
}
```
* The constructor loads `data.csv`, parses the input file, validates formatting on each row, and prints evaluated rates in real-time.

---

## Next Steps

Let's look at the implementation of **ex01: Reverse Polish Notation**.

👉 Proceed to [02_ex01_RPN.md](./02_ex01_RPN.md)
