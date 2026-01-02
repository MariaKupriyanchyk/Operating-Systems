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

## Lab №4

### Description
This laboratory work is devoted to studying **interprocess synchronization** and communication between processes using shared system resources.
The goal of the lab is to implement a message-passing system between multiple processes through a **shared binary file**, where one process acts as a **Receiver** and several processes act as **Senders**.
Message exchange is organized as a **FIFO ring buffer**, ensuring that messages are received in the same order in which they were sent.

### Receiver Process
The **Receiver** process performs the following actions:

- Requests from the console:
  - the name of the binary file used for message transfer,
  - the maximum number of records (queue capacity) in the file.
- Creates a binary file for storing messages  
  (maximum message length is **20 characters**).
- Requests the number of **Sender** processes.
- Launches the specified number of Sender processes, passing the file name via command-line arguments.
- Waits until all Sender processes signal readiness.
- Cyclically processes user commands:
  - read the next message from the file,
  - terminate the Receiver process.

### Sender Process
Each **Sender** process performs the following actions:
- Opens the binary file whose name is received from the command line.
- Sends a readiness signal to the Receiver.
- Cyclically processes user commands:
  - send a message to the Receiver,
  - terminate the Sender process.

Messages are entered from the console.  
The length of a message must be **less than 20 characters**.

### Implementation Details
- Message transfer is implemented using a **ring (circular) FIFO queue** stored in a binary file.
- Process synchronization is achieved using:
  - a mutex,
  - two semaphores (for empty and full slots).
- Correct synchronization ensures:
  - safe concurrent access to the shared file,
  - correct message ordering,
  - blocking behavior when the queue is full or empty.
- Input validation is performed using regular expressions to prevent invalid values and uncontrolled process creation.

### Testing
Google Test is used to verify:
- correct message transmission,
- boundary conditions (empty and maximum-length messages),
- rejection of invalid input,
- robustness of the queue implementation.
