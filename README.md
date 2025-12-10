# Operating-Systems

## Lab №1

### Description
The goal of this lab was to implement three console applications that interact with each other using processes:
- **Main** — the main program that manages execution.
- **Creator** — a utility that generates a binary file with employee records.
- **Reporter** — a utility that creates a formatted text report based on the binary file.

### Employee record structure:
```c++
struct employee {
    int    num;        // employee ID
    char   name[10];   // employee name
    double hours;      // worked hours
};
```

## Lab №2

### Description
This laboratory work is dedicated to studying multithreaded programming. It is necessary to implement a console process with three threads: `main`, `min_max`, and `average`.

### Main Thread
- Creates an array of integers (size and elements are entered from the console)
- Creates `min_max` and `average` threads
- Waits for the created threads to complete
- Replaces the minimum and maximum elements of the array with the average value
- Outputs the modified array to the console
- Terminates the program

### Min_max Thread
- Finds the minimum and maximum elements of the array
- Outputs the found values to the console
- Pauses for **7 milliseconds** after each element comparison

### Average Thread
- Calculates the arithmetic mean of the array elements
- Outputs the result to the console
- Pauses for **12 milliseconds** after each summation operation

### C++20 Version
- Uses modern C++20 standard features
- More secure and expressive code

### C++98 Version
- Corresponds to practices before the introduction of the standard thread library
- Demonstrates low-level thread management

## Lab3

### Description
It was required to develop a multithreaded console application consisting of a main thread (`main`) and several worker threads (`marker`).  
The main thread controls the execution of the `marker` threads, while the `marker` threads mark elements of a shared array with their identifiers in a concurrent environment.

The thread execution must be strictly synchronized according to the given logic:
- simultaneous start of all threads,
- waiting until all marker threads become blocked,
- sequential termination of threads by user command,
- correct cleanup of the array after each thread finishes.

### The main thread:
  - requests the array size and the number of threads,
  - starts the `marker` threads,
  - synchronously controls their execution,
  - terminates selected threads and displays the array state.

### The `marker` threads:
  - generate random indices,
  - attempt to mark array elements with their ID,
  - notify the main thread if they cannot continue work,
  - correctly clear their data upon termination.
