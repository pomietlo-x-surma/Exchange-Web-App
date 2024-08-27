## Server and client application for managing user accounts, currency exchange, and real-time currency data.


## Application Overview

The application consists of both server-side and client-side components. 

- **Client-Side**: We used React to build the client-side of the application.

- **Server-Side**: The server was developed in C++ using the Boost library.

- **Additional**: Python was employed to read and fetch the current exchange rates and charts.


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


## Running the React Application
### To start the React application, open a terminal in the project directory and run:

```bash
npm run dev
```
### This will start the development server for the React app.


## Application Screenshots and Descriptions

1. **Login Screen**  
   On the login screen, you can log in by entering your email and password or create a new account:
   
   ![Login Screen](https://i.imgur.com/i8P12rD.png)

2. **Registration Form**  
   During registration, you need to enter your email, username, and password twice. The password must meet the following requirements: at least 8 characters, at least one lowercase and uppercase letter, a special character, and a number:
   
   ![Registration Form](https://i.imgur.com/N503WMR.png)

3. **User Dashboard**  
   In the user menu, you can check the current exchange rate and view its graph over time. On the right side, you can also exchange currency and check your account balance:
   
   ![User Dashboard](https://i.imgur.com/R3f700t.png)

