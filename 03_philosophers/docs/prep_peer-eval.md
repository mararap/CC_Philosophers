Let me read the subject and your own code to give you concrete guidance on what to look for.    

Read [](file:///home/marapovi/CommonCore_gh/03_philosophers/docs/subject.md#1-1), lines 1 to 150

Read [](file:///home/marapovi/CommonCore_gh/03_philosophers/include/philo.h)

Read [](file:///home/marapovi/CommonCore_gh/03_philosophers/src/threads.c)

Read [](file:///home/marapovi/CommonCore_gh/03_philosophers/src/init.c)

Read [](file:///home/marapovi/CommonCore_gh/03_philosophers/docs/subject.md#150-150), lines 150 to 250

Read [](file:///home/marapovi/CommonCore_gh/03_philosophers/src/monitor.c)

Here's a practical checklist for your evaluation, with concrete things to look for in the code:

---

## Quick Prep Checklist (30 min)

### 1. Initial Setup
```bash
git clone <their-repo> /tmp/philo_eval
cd /tmp/philo_eval/philo
make
```
- Verify it compiles with `-Wall -Wextra -Werror`
- Check Makefile has `NAME`, `all`, `clean`, `fclean`, `re` rules
- Run `norminette` on all `.c` and `.h` files

### 2. Global Variables Check
```bash
grep -rn "^[a-zA-Z].*;" src/ include/ | grep -v "static\|typedef\|#\|//\|{\|}"
```
Or just read their header file and `.c` files — any variable declared outside a function that isn't `static` is a global. **If they use a global for shared resources → grade is 0.**

---

### 3. How to Verify: One Thread Per Philosopher

Look for `pthread_create` calls. The correct pattern is a loop that creates exactly `number_of_philosophers` threads:

```c
// GOOD: one thread per philosopher
for (i = 0; i < num_philos; i++)
    pthread_create(&philos[i].tid, NULL, routine, &philos[i]);
```

**Red flags:**
- Extra threads beyond `num_philos` (a separate monitor thread is okay and common, but each philosopher must be its own thread)
- Philosopher logic running in the main thread instead of a dedicated thread
- Fewer `pthread_create` calls than the number of philosophers

**What to ask:** "Show me where you create the threads. How many threads are created?"

---

### 4. How to Verify: One Fork Per Philosopher

There should be an array of **exactly `number_of_philosophers` mutexes** representing forks. Look in their struct/init code:

```c
// GOOD: N forks for N philosophers
pthread_mutex_t *forks; // array of size number_of_philosophers
// init:
forks = malloc(sizeof(pthread_mutex_t) * num_philos);
for (i = 0; i < num_philos; i++)
    pthread_mutex_init(&forks[i], NULL);
```

Each philosopher picks up fork `i` (their own) and fork `(i + 1) % num_philos` (their neighbor's). This models the circular table.

**Red flags:**
- More or fewer mutexes than philosophers
- Forks not represented as mutexes at all

---

### 5. How to Verify: Mutex Per Fork Used to Protect Access

When a philosopher eats, they should:
1. `pthread_mutex_lock(&forks[left])` 
2. `pthread_mutex_lock(&forks[right])`
3. Eat
4. `pthread_mutex_unlock(&forks[left])`
5. `pthread_mutex_unlock(&forks[right])`

**What to look for:** The fork mutexes are locked/unlocked around eating, not just checked with a boolean flag without a mutex. A bare `if (fork_available[i])` without mutex protection is a **data race**.

---

### 6. How to Verify: Output Not Mixed Up

There should be a **print mutex** — a single mutex locked before every `printf` call and unlocked after:

```c
pthread_mutex_lock(&data->print_mutex);
printf("%lld %zu is eating\n", timestamp, philo->id);
pthread_mutex_unlock(&data->print_mutex);
```

**Red flag:** `printf` calls without mutex protection → messages can interleave.

---

### 7. How to Verify: Death Check + Mutex Preventing Die-While-Eating Race

There should be a **monitor** (often in the main thread or a dedicated thread) that periodically checks:
```c
if (current_time - philo->last_meal_time > time_to_die)
    // philosopher died
```

The key: `last_meal_time` must be protected by a mutex, because the philosopher thread writes it (when eating) and the monitor thread reads it. Look for a mutex around both the read and write of `last_meal_time`.

**Red flag:** No mutex protecting `last_meal_time` → data race between monitor and philosopher threads.

---

### 8. Data Race Check

Run their program with helgrind or DRD:
```bash
valgrind --tool=helgrind ./philo 5 800 200 200
valgrind --tool=drd ./philo 5 800 200 200
```
**Any data race → evaluation stops, grade is 0.**

### 9. Memory Leak Check
```bash
valgrind --leak-check=full ./philo 5 800 200 200 7
```
Use the meal-count argument so the program terminates naturally.

---

### 10. Required Tests

| Test | Expected Result |
|------|----------------|
| `./philo 1 800 200 200` | Philosopher takes 1 fork, can't eat, **dies** |
| `./philo 5 800 200 200` | **No one dies** |
| `./philo 5 800 200 200 7` | **No one dies**, stops after 7 meals each |
| `./philo 4 410 200 200` | **No one dies** |
| `./philo 4 310 200 100` | **Someone dies** |
| `./philo 2 800 200 200` | **No one dies**, death delay < 10ms |

For the `1 philosopher` test, verify the output shows only "has taken a fork" then "died" ~800ms later — never "is eating".

For the `2 philosophers` test, check timestamps carefully: death should be reported within 10ms of `time_to_die`.

---

### Summary: Questions to Ask Your Peer

1. "Show me your philosopher struct and where threads are created" → verify 1 thread per philo
2. "Show me your fork array and initialization" → verify 1 mutex per fork
3. "Walk me through what happens when a philosopher eats" → verify mutex lock/unlock around forks
4. "How do you protect your print output?" → verify print mutex
5. "How does your monitor detect death? How do you prevent a race between dying and eating?" → verify `last_meal_time` mutex
6. "Do you use any global variables?" → instant check