*This project has been created as part of the 42 curriculum by marapovi.*

# Philosophers

Implementation of the Dining Philosophers problem for 42 Vienna CommonCore.

## Description

This project implements the classic Dining Philosophers problem using POSIX threads and mutexes in C.

A number of philosophers sit at a round table with a bowl of spaghetti in the center. Each philosopher alternates between eating, sleeping, and thinking. There is one fork between each pair of adjacent philosophers. To eat, a philosopher needs to hold both the fork to his left and the fork to his right in his hands. If a philosopher has not started eating within `time_to_die` milliseconds since the start of their last meal or the start of the simulation, they die and the simulation ends.

Key implementation details:
- Each philosopher runs as a separate thread
- Fork access is protected by individual mutexes (one per fork)
- A dedicated monitor thread detects death and meal-count stop conditions
- Deadlock is prevented by always locking forks in memory-address order
- Even-numbered philosophers are staggered at startup to prevent starvation

## Instructions

### Requirements

- `cc` (clang or gcc)
- POSIX threads (`-lpthread`, linked automatically via Makefile)

### Build

```
make
```

### Run

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers` — number of philosophers and forks (≥ 1)
- `time_to_die` — milliseconds before a philosopher starves
- `time_to_eat` — milliseconds a philosopher spends eating
- `time_to_sleep` — milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional) — simulation stops when all philosophers have eaten this many times

**Examples:**
```
./philo 5 800 200 200          # 5 philosophers, no one should die
./philo 4 310 200 100          # someone will die
./philo 1 800 200 200          # single philosopher edge case
./philo 5 800 200 200 7        # stops after each philosopher eats 7 times
```

### Project Structure

```
include/    philo.h (structs, typedefs, prototypes)
src/        main.c      argument parsing and program entry
            init.c      initialization chain (dinner, forks, philosophers)
            threads.c   thread creation, joining, sim-over check
            actions.c   philosopher actions (take/drop forks, eat, sleep, think)
            monitor.c   death detection and meal-count monitoring
            cleanup.c   resource freeing and mutex destruction
            utils.c     shared helpers (time, print, atoui)
```

### Testing for data races

```
valgrind --tool=helgrind ./philo 5 800 200 200 3
valgrind --tool=drd ./philo 5 800 200 200 3
```

### Testing for memory leaks

```
valgrind --leak-check=full ./philo 5 800 200 200 3
```

## Resources

### References

- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- `man pthread_create`, `man pthread_mutex_init`, `man gettimeofday`, `man usleep`

### AI Usage

GitHub Copilot was used throughout this project as a guided tutor, not as a code generator. Specifically:

- **Concept clarification**: threading, mutex semantics, deadlock conditions, and POSIX API behavior were explained through a question-and-answer format
- **Design reasoning**: struct layout, file architecture, and Norm-compliant function splitting were worked out through guided questions before any code was written
- **Code review**: each function was reviewed for correctness after being written by hand — the AI identified bugs and asked questions to guide fixes rather than rewriting code directly
- **Evaluation preparation**: mock evaluation questions were used to verify understanding of all major design decisions

All code in this repository was written by the author and can be fully explained and justified.