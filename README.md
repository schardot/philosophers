# Philosophers 🧑‍🏫

The **Philosophers** project is a simulation of the dining philosophers problem using multithreading in **C**. The goal of the project is to demonstrate the application of synchronization techniques and avoid deadlocks while simulating multiple philosophers sharing limited resources (e.g., forks) in a dining setting.

## 📜 Problem Statement
In this project, philosophers sit at a table and eat spaghetti. Each philosopher needs two forks to eat, and there are only a limited number of forks available. Philosophers must alternate between thinking and eating, while ensuring that no deadlocks or starvation occur.

The simulation involves managing multiple threads, each representing a philosopher, and applying synchronization mechanisms to prevent race conditions.

## 🛠️ Features
- **Multithreading**: Each philosopher is implemented as a separate thread.
- **Mutexes**: Used to ensure synchronization and prevent deadlocks when accessing shared resources (forks).
- **Deadlock Prevention**: Implements techniques to avoid deadlocks during the simulation.
- **Fork Handling**: Philosophers pick up and put down forks as needed to eat.

## 🧑‍💻 How It Works
- Philosophers alternate between thinking and eating.
- Eating requires two forks, and philosophers can only eat when both forks are available.
- If a philosopher cannot get both forks, they will continue thinking until they can.
- The program manages synchronization using **mutexes** to ensure only one philosopher can pick up a fork at a time.

## 🧑‍🏫 Usage
1. Clone the repository:

   ```bash
   git clone https://github.com/schardot/philosophers.git
   cd philosophers
   ```
2. The project uses **Makefile** for easy compilation. To compile the program, run:

  ```bash
  make
  ```
3. Run the simulation with:

  ```bash
  ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
  ```

**number_of_philosophers**: Number of philosophers in the simulation.
**time_to_die**: Time in milliseconds before a philosopher dies of starvation.
**time_to_eat**: Time in milliseconds a philosopher spends eating.
**time_to_sleep**: Time in milliseconds a philosopher spends sleeping.
**number_of_times_each_philosopher_must_eat**: Optional. How many times each philosopher must eat before the simulation ends.

Example:

  ```bash
  ./philo 5 800 200 200 7
  ```

This will start the simulation with 5 philosophers, where each philosopher must eat 7 times, with time to die set to 800 ms, and time to eat/sleep set to 200 ms.

## ⚙️ Compilation
The project uses Makefile for easy compilation. To compile the program, run:

  ```bash
  make
  ```
To clean up the compiled files:

  ```bash
  make clean
  ```

To remove the compiled executable:

  ```bash
  make fclean
  ```

## 📝 Project Requirements

**Multithreading**: Using **pthreads** to create threads for each philosopher.
**Mutexes**: Synchronizing the access to shared resources (forks) using mutexes.
**Deadlock Avoidance**: The solution should ensure that philosophers won't be stuck waiting for each other forever.
**Starvation Prevention**: No philosopher should be left hungry forever; each philosopher must eat a minimum number of times.

## 🔧 Built With

* **C Programming Language**
* **pthreads** for multithreading
* **Mutexes** for synchronization
  
## 💡 Key Concepts

* **Threading**: Managing multiple processes (philosophers) that interact concurrently.
* **Mutexes**: Used to control access to shared resources.
* **Deadlock**: Preventing situations where philosophers wait indefinitely for forks.
* **Starvation**: Ensuring that all philosophers get a chance to eat.
  
## 🏆 Project Objectives

* Understanding how to manage concurrency and synchronization in a multithreaded environment.
* Implementing a solution to the classical dining philosophers problem while preventing deadlocks and starvation.
* Working with system-level programming techniques such as threads, mutexes, and semaphores in C.

## 📊 Example Output
Example of how the simulation output might look:

```c
Philosopher 1 is thinking
Philosopher 2 is eating
Philosopher 3 is sleeping
...
Philosopher 1 is eating
Philosopher 2 is sleeping
...
```

Each philosopher's activity (thinking, eating, sleeping) is logged to the console as the simulation runs.

## 💬 Contributions
Feel free to open an issue or submit a pull request if you have suggestions or improvements for this project!
