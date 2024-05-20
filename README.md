# Sable

Rigorous runtime performance analysis for c++ code.

This project was based off of [Stabilizer](https://people.cs.umass.edu/~emery/pubs/stabilizer-asplos13.pdf) ([Github](https://github.com/ccurtsinger/stabilizer/tree/master)). 

## Idea

Sable aims to get an accurate assessment of a function's runtime in the presence of noise and factors like memory location in both the stack and heap, which can bias a function's performance evaluation. 

To do this, multiple samples of the function are taken, with randomized stack and heap paddings created before function execution.

This method aims to approximate the true runtime of the function, regardless of noise and memory location.

## Usage

Sable works by comparing the runtime of two functions by performing a student's t-test on both functions runtimes.  This necessitates three conditions:

1. Samples must be random
2. The sample must approximate a normal distribution
3. Total population >> # of samples (10n)

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
sable::TestResult result = sable::compare_runtime(
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

> For more examples, see tests: `test/wait.cpp` and `test/calc_test.cpp`.

### Further examples

For further usage examples, see `tests/` directory.

Make any of the tests using `make [TestName]`