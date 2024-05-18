# YADRO-Test-assignment

This is my implementation for a test assignment related to simulating the work of a computer club.

This project is divided into several parts (let's consider the main ones):

1. **Club class**:
    - This class encompasses the functionality of the most important club functions.

2. **Implementation of all functions**:
   - Important functions: Implementation of important functions is stored in files named `core`.
   - Helper functions: Implementation of helper functions resides in files named `helper`.
   - Additionally, there are other files such as `structures.cpp` for convenient project management

3. **Ability to test the program using Google Tests**:
   - You can verify the correctness of the program using Google Tests.

# Running the Project

### Step 1:
To correctly clone the project, use the following command:

```bash
git clone --recurse-submodules https://github.com/PletkaDaniil/YADRO-Test-assignment.git
```
### Step 2:
After the project and its submodules have been cloned, create a directory named build.

```bash
1. mkdir build
2. cd build
3. cmake ..
4. make 
(or 4. cmake --build .)
```

### Step 3: Running Google Tests or Specific Files

Now it depends on your preferences:

- If you want to run Google tests, use this command:
  
  ```bash
  # Command to run Google tests
  ./testing_club_work/test_club
  ```
- If you want to run Google tests, use this command:

  ```bash
  #  Command to run a specific file
  ./club_management ../input.txt
  ```