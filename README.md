# Server and client application for managing user accounts, currency exchange, and real-time currency data.


## Building the Application

### Using Git

1. Initialize a new Git repository:
    ```bash
    git init
    ```

2. Clone the repository:
    ```bash
    git clone https://github.com/pomietlo-x-surma/Exchange-Web-App.git
    ```

3. Navigate to the project directory:
    ```bash
    cd Exchange-Web-App
    ```

4. Create a `build` directory and navigate into it:
    ```bash
    mkdir build
    cd build
    ```

5. Generate the build files using CMake:
    ```bash
    cmake ..
    ```

6. Build the project:
    ```bash
    cmake --build .
    ```

### Using Visual Studio

1. Open Visual Studio.

2. Select "Clone a repository" and enter the repository URL:
    ```
    https://github.com/pomietlo-x-surma/Exchange-Web-App.git
    ```

3. After cloning, open the Solution Explorer and locate the `CMakeLists.txt` file.

4. Open `CMakeLists.txt` and save it with `Ctrl + S`.

5. If the project doesn't start building automatically, open the terminal with `Ctrl + `` and run the following commands:
    ```bash
    cd C:/path/to/Exchange-Web-App
    cd build
    cmake ..
    cmake --build .
    ```

6. Set `Exchange-Web-App.cpp` as the startup item by right-clicking on it in Solution Explorer and selecting "Set as Startup Item".
