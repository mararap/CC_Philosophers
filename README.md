*This project has been created as part of the 42 curriculum by marapovi.*

# Philosophers

## Description

`Philosophers` is the Circle 03 concurrency project from 42.
The goal is to simulate the dining philosophers problem using POSIX threads and mutexes while respecting the subject's timing and synchronization constraints.

In this implementation, each philosopher is represented by one thread, and the simulation is supervised by a dedicated monitor thread. Each fork is protected by its own mutex, and additional mutexes protect console output, the global stop flag, and meal-related shared state. The program stops when one philosopher dies or, if the optional argument is provided, when every philosopher has eaten the required number of meals.

This version focuses on:

- avoiding data races on shared state,
- preventing circular-wait deadlock through parity-based fork ordering,
- reducing startup contention with a staggered launch for even-numbered philosophers,
- handling edge cases such as a single philosopher,
- cleaning up allocated memory and initialized mutexes on both success and failure paths.

## Technical Overview

The mandatory program is located in `philo/` and builds the executable `philo`.

High-level behavior:

- each philosopher loops through taking forks, eating, sleeping, and thinking,
- fork acquisition order depends on philosopher parity to break the circular wait condition,
- the monitor thread periodically checks whether a philosopher exceeded `time_to_die`,
- all status messages are serialized through a print mutex,
- meal timestamps and meal counters are protected by a dedicated mutex,
- the simulation end flag is protected by its own mutex.

Implementation details reflected in the code:

- time values are converted to microseconds internally for finer control,
- custom waiting uses short `usleep` intervals so threads can react quickly when the simulation ends,
- for an odd number of philosophers, thinking time is adjusted to reduce repeated fork collisions,
- when there is only one philosopher, the program correctly handles the single-fork starvation case.

## Instructions

### Requirements

- `cc`
- `make`
- POSIX threads support

### Compilation

From the project root:

```bash
cd philo
make
```

This produces the executable:

```bash
./philo/philo
```

### Available Make Commands

Inside `philo/`, the following Make targets are available:

- `make` or `make all`: build the `philo` executable,
- `make clean`: remove object files,
- `make fclean`: remove object files and the executable,
- `make re`: rebuild the project from scratch.

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example without meal limit:

```bash
./philo 5 800 200 200
```

Example with meal limit:

```bash
./philo 5 800 200 200 7
```

Argument meanings:

- `number_of_philosophers`: number of philosophers and forks,
- `time_to_die`: maximum time in milliseconds a philosopher may go without starting to eat,
- `time_to_eat`: eating duration in milliseconds,
- `time_to_sleep`: sleeping duration in milliseconds,
- `number_of_times_each_philosopher_must_eat`: optional stop condition.

### Output

The program prints state changes in the format required by the subject:

```text
timestamp philosopher_id has taken a fork
timestamp philosopher_id is eating
timestamp philosopher_id is sleeping
timestamp philosopher_id is thinking
timestamp philosopher_id died
```

## Project Structure

```text
philo/
├── actions.c
├── cleanup.c
├── init.c
├── main.c
├── monitor.c
├── threads.c
├── utils.c
├── philo.h
└── Makefile
```

## Resources

References used for the topic:

- The 42 project subject for `Philosophers`
- `man pthread_create`
- `man pthread_join`
- `man pthread_mutex_init`
- `man gettimeofday`
- `man usleep`
- POSIX Threads Programming documentation
- https://howardhinnant.github.io/dining_philosophers.html#Polite
- Other explanations of the dining philosophers problem and common deadlock-prevention strategies

AI usage:

- AI was used as a support tool for explanation, review, and small code-optimization discussions.
- This README was drafted with AI assistance and then adjusted manually to match the final implementation.
