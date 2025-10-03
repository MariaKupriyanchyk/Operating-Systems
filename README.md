# Operating-Systems

## Lab №1
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
