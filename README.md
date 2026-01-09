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

## Lab №3

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

## Lab №5

### Description
This laboratory work is dedicated to studying **interprocess communication using named pipes** and controlled access of parallel processes to a shared file.
The goal of the lab is to implement a **client–server system** where multiple client processes access a shared binary file through **named channels**, while the server guarantees correct synchronization and data consistency.
The server coordinates access to file records, providing **exclusive access for modification** and **shared access for reading**, according to the specified rules.

### Data Structure
The binary file consists of records with the following structure:
```c++
struct employee {
    int    num;        // employee ID
    char   name[10];   // employee name
    double hours;      // worked hours
};
```

### Server Process
The **Server** process:
- Reads from the console:
  - binary file name,
  - employee data for file initialization.
- Creates a binary file with employee records.
- Displays the initial file contents.
- Requests and launches a specified number of **Client** processes.
- Handles client requests via **named pipes**:
  - modification requests lock the record exclusively,
  - read requests allow concurrent reading but block writers.
- After all clients finish, outputs the modified file contents.
- Terminates execution by console command.

### Client Process
Each **Client** process runs in a loop and allows the user to:
- modify a file record,
- read a file record,
- exit the program.
File access is performed using the employee **ID** as a key.

### Record Modification
- Requests record ID.
- Sends modification request to the server.
- Receives and displays current record.
- Requests new field values.
- Sends updated record to the server.
- Releases access to the record.

### Record Reading
- Requests record ID.
- Sends read request to the server.
- Receives and displays the record.

### Implementation Details
- Interprocess communication is implemented using **named pipes**.
- Access to file records follows the **reader–writer synchronization model**:
  - exclusive access for writing,
  - shared access for reading.
- Input validation prevents incorrect data entry.
- Data integrity is preserved during concurrent client execution.

### Testing
**Google Test** is used to verify:
- correctness of input validation (ID, name, hours),
- rejection of invalid input,
- correct reading and modification of records,
- stability of client–server interaction.
  
## Colloquium REST API

### Description
This laboratory work is devoted to studying the principles of **RESTful API design**, **client–server interaction**, and **backend application development**.
The goal of the lab is to implement a REST API for managing a list of tasks (To-Do List) that supports **CRUD operations** (Create, Read, Update, Delete) using standard HTTP methods and JSON data format.
The application follows a layered architecture and demonstrates interaction between controller, service, repository, and database layers.

### Task Resource
Each task is represented by the following structure:
```json
{
  "id": 1,
  "title": "Task title",
  "description": "Task description",
  "status": "todo"
}
```

### Task Fields
Each task contains the following fields:
- **id** — unique identifier of the task  
- **title** — task title (must not be empty)  
- **description** — task description (must not be empty)  
- **status** — task status (`todo`, `in_progress`, `done`)

### Database Interaction
- Persistence is implemented using **Spring Data JPA**
- During testing, an **H2 in-memory database** is used
- Task identifiers are generated automatically
- Database constraints ensure data integrity

### Caching
To improve application performance, caching is implemented:
- task retrieval by ID is cached
- cache is updated on task modification
- cache entries are removed on task deletion

### Testing
The application includes automated tests for all layers.

#### Repository Tests
- verify correct persistence of entities
- use in-memory database

#### Service Tests
- verify business logic
- use mocked repository

#### Controller Tests
- verify REST endpoints
- validate HTTP status codes
- test input validation and error handling

### Implementation Details
- REST API is implemented using **Spring Boot**
- JSON serialization and deserialization are handled by **Jackson**
- Validation is implemented via **Jakarta Bean Validation**
- Exception handling returns appropriate HTTP responses
- The application follows a layered architecture:
  - Controller
  - Service
  - Repository
  - Database

### Technologies Used
- Java 17
- Spring Boot
- Spring Web
- Spring Data JPA
- Spring Validation
- Spring Cache
- H2 Database
- JUnit 5
- Mockito
- Docker
