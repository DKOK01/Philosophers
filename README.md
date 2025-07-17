# Philosophers

A C implementation of the classic "Dining Philosophers" problem, showcasing multi-threading, synchronization, and deadlock prevention using mutexes.

## 📋 Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Examples](#examples)
- [Rules](#rules)

## 🎯 About

This project is a solution to the famous "Dining Philosophers" problem, a classic synchronization problem in computer science. The implementation uses threads and mutexes to simulate philosophers sitting around a table, alternating between thinking, eating, and sleeping while avoiding deadlocks and race conditions.

## 🤔 The Problem

The Dining Philosophers problem consists of:
- N philosophers sitting around a circular table
- Each philosopher alternates between thinking, eating, and sleeping
- There are N forks (one between each pair of adjacent philosophers)
- A philosopher needs both left and right forks to eat
- The challenge is to design a protocol that prevents deadlock and starvation

## ✨ Features

- **Multi-threaded simulation** with one thread per philosopher
- **Deadlock prevention** using proper mutex ordering
- **Race condition prevention** with synchronized access to shared resources
- **Real-time monitoring** of philosopher states
- **Configurable parameters** for different simulation scenarios
- **Memory leak prevention** with proper cleanup

## 🛠️ Installation

### Prerequisites
- GCC compiler
- Make
- POSIX-compliant system (Linux/macOS)

### Build
```bash
cd philo
make
```

### Clean
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything
```

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't eaten
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) Simulation stops when all philosophers have eaten at least this many times

### Output Format
```
[timestamp_ms] [philosopher_id] [action]
```

Actions:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

## 📁 Project Structure

```
philo/
├── main.c              # Entry point and argument parsing
├── philo.h             # Header file with structures and prototypes
├── philo_actions.c     # Philosopher actions (eat, sleep, think)
├── philo_checks.c      # State checking functions
├── philo_cleanup.c     # Memory and resource cleanup
├── philo_forks.c       # Fork handling and synchronization
├── philo_init.c        # Initialization functions
├── philo_monitor.c     # Death monitoring thread
├── philo_simulation.c  # Main simulation logic
├── philo_utils.c       # Utility functions
└── Makefile           # Build configuration
```

## 🔧 Implementation Details

### Data Structures

- **`t_data`**: Contains global simulation parameters and shared resources
- **`t_philo`**: Individual philosopher structure with thread and state information

### Synchronization

- **Fork mutexes**: Prevent multiple philosophers from using the same fork
- **Print mutex**: Ensures atomic printing of status messages
- **Meal mutex**: Protects access to meal-related variables
- **Dead lock mutex**: Synchronizes access to the death flag

### Deadlock Prevention

The implementation uses fork ordering to prevent deadlocks:
- Odd-numbered philosophers take left fork first, then right fork
- Even-numbered philosophers take right fork first, then left fork

## 📖 Examples

### Basic simulation with 4 philosophers
```bash
./philo 4 800 200 200
```

### Simulation with mandatory eating count
```bash
./philo 5 800 200 200 7
```

### Quick death scenario
```bash
./philo 4 310 200 100
```

## 📋 Rules

1. **No philosopher should die** (unless specified by parameters)
2. **No data races** - all shared data must be protected by mutexes
3. **No deadlocks** - philosophers must be able to continue eating
4. **Status messages** must be printed in the correct format
5. **Timing accuracy** - actions must respect the specified time limits
6. **Clean termination** - all resources must be properly cleaned up

## ⚠️ Important Notes

- The simulation runs until a philosopher dies or all philosophers have eaten the required number of times
- Timestamps are in milliseconds from the start of the simulation
- The program handles edge cases like single philosopher scenarios
- Memory leaks are prevented through proper cleanup procedures

## 🏆 42 School Project

This project is part of the 42 School curriculum, focusing on:
- Thread management and synchronization
- Mutex usage and deadlock prevention
- Process lifecycle management
- Resource sharing and protection
- System programming concepts

---

*Made with ❤️ by aysadeq*
