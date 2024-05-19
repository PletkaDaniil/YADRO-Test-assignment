# YADRO-Test-assignment

This is my implementation for a test assignment related to simulating the work of a computer club.

This project is divided into several parts:

1. **Club class**:
    - This class encompasses the functionality of the most important computer club functions.

2. **Implementation of all functions**:
   - Important functions: Implementation of important functions is stored in files named `core`.
   - Helper functions: Implementation of helper functions resides in files named `helper`.
   - Additionally, there are other files such as `structures.h` for convenient project management

3. **Ability to test the program using Google Tests**:
   - You can verify the correctness of the program using Google Tests.

# Building and Running the Project

### Step 1:
To correctly clone the project, use the following command:

```bash
git clone --recurse-submodules https://github.com/PletkaDaniil/YADRO-Test-assignment.git
```
### Step 2:
After the project have been cloned, create a directory:

```bash
mkdir build
```
```bash
cd build
```
Configure the project using CMake:
```bash
cmake ..
```
***Build*** the project:
```bash
make
```
or
```bash 
cmake --build .
```

### Step 3: Running Google Tests or Specific Files

Now it depends on your preferences:

- If you want to run Google tests, use this command:
  
  ```bash
  # Command to run Google tests
  ./testing_club_work/test_club
  ```
- If you want to run a specific file (e.g. `input.txt`) through the terminal, use this command:

  ```bash
  #  Command to run a specific file
  ./club_management ../input.txt
  ```

# Some explanations about the task

**1.** About `ID 4` I have implemented my program so that anyone can leave the computer club, both a person at the table and a person in queque.

**2.** About `ID 3` I have implemented my program so that any client in queue (no matter where they stand) who is waiting and understands that the queue has reached its limit (the number of tables is less than the length of the queue) - the client leaves.

**3.**  **Google Tests**: 
   + `15 tests` are provided to check the correctness of the file.

   + `10 tests` for various types of events in the club. For example, what will happen if a client changes his\her table after 1 minute?
