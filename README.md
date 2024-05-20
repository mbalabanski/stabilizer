# Sable

Runtime performance analysis for c++ code.

This project was based off of [Stabilizer](https://people.cs.umass.edu/~emery/pubs/stabilizer-asplos13.pdf) ([Github](https://github.com/ccurtsinger/stabilizer/tree/master)). 

## Idea

Sable aims to get an accurate assessment of a function's runtime in the presence of noise and factors like memory location in both the stack and heap, which can bias a function's performance evaluation. 

To do this, multiple samples of the function are taken, with randomized stack and heap paddings created before function execution.

This method aims to approximate the true runtime of the function, regardless of noise and memory location.

## Usage

Sable works by comparing the runtime of two functions by performing a student's t-test on both functions runtimes.  This necessitates three conditions:

1. Samples must be random
2. The sample must approximate a normal distribution
3. Each sample is independent of one another

These are important to keep in mind during usage, especially when setting parameters such as number of trials, which can satistfy condition #2, to be greater than 30, by the [ Central Limit Theorem](https://en.wikipedia.org/wiki/Central_limit_theorem)

### Adding Sable to a project

Clone this repository and make using:

```sh
$ git clone https://github.com/MaxiBal/sable.git
$ cd sable
$ mkdir build && cd build
$ cmake ..
$ make sable_lib
```

From this, add the object built into linking and add `include/` to targeted include directories.

Finally, add:

```cpp
#include <sable.hpp>
```

### `sable::compare_runtime`

To compare the runtime of two functions, use `sable::compare_runtime`.

```cpp
sable::TestResult sable::compare_runtime(
    void() function1, 
    void() function2, 
    float significance_level, 
    size_t number_of_trials
);
```
> #### Notes on Usage:
> _significance_level_ - determines when null hypothesis should be rejected.  Usually 0.01, 0.05 or 0.10.
>
> _number_of_trials_ - should at least be greater than 30


This returns a `sable::TestResult` struct, which contains 5 parameters: the runtime data for functions 1 and 2, the probability for the functions to have the same runtime, the student's t-test test statistic, and a summary of the hypotheses.

The hypotheses are summarized by the bitflags in the enum `sable::HypothesisTest`, where 0 means a failure to reject the null hypothesis, and a flag is set for the alternate hypotheses: Not Equal, Greater Than, and Less Than.

To print results of a test to stdout, use `sable::output_test_result`.

#### Example Usage

```cpp
void run_func()
{
    std::this_thread::sleep_for(std::chrono::microseconds(10));
}

void run_func2()
{
    std::this_thread::sleep_for(std::chrono::microseconds(14));
}

int main()
{
    auto test_results = sable::compare_runtime(
        run_func, 
        run_func2, 
        0.05, // signficance level
        100 // # of trials
    );

    sable::output_test_result(test_results);

    return 0;
}
```

> For more examples, see tests: `test/wait.cpp`, `test/calc_test.cpp`, and `test/confusion_matrix.cpp`.

### `sable::watch_function`

Sable watch function compares the functions current runtime, to its previous runtime.

```cpp
std::optional<TestResult> watch_function(
    const std::string& identifier, 
    void() func, 
    size_t trials,
    float alpha
);
```
> #### Notes on Usage
> _identifier_ - must be unique for each call
>
> _alpha_ - significance level - determines when null hypothesis should be rejected.  Usually 0.01, 0.05 or 0.10.
>
> _trials_ - should at least be greater than 30
>
> **Returns** - an option of `sable::TestResult`

This function saves runtime data to a created file `./sable/[identifier].csv`.  This makes it necessary to have a unique identifier for each `watch_function` call.  

In the event that no data file or `sable` directory exists, this function will create the file and path and write headings and runtime data to it.

This function will run a student's t-test (like [`compare_runtime`](#sablecompare_runtime)) to determine if there is a difference in runtime from the previous execution.



#### Returns

This function returns `nullopt` when there is no existing data file (`sable/[identifier].csv`), or if it is unable to read from the file.  Otherwise, it returns the results of the student's t-test.

#### Usage

```cpp
void run_func()
{
    const size_t duration = 40; // change between compilations
    std::this_thread::sleep_for(std::chrono::microseconds(duration));
}

int main()
{
    auto test_results = sable::watch_function("WaitFunction", run_func, trials, 0.05);

    if (test_results)
        sable::output_test_result(test_results.value());

    return 0;
}
```

### Further examples

For further usage examples, see `tests/` directory.

Make any of the tests using `make [TestName]`