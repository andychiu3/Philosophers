<h1 align="center"> Philosophers </h1>

## How to use

Open the terminal and get the repo from git
```bash
git clone <URL> philosophers
```

Change Dir to project file && compile the project by Makefile
```bash
cd philosophers && make
```

run the executable
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philo_eat]
```

**Parameters**

`number_of_philosophers:` Number of philosophers (and forks)

`time_to_die:` Time in milliseconds - if a philosopher doesn't start eating within this time since last meal, they die

`time_to_eat:` Time in milliseconds it takes for a philosopher to eat

`time_to_sleep:` Time in milliseconds a philosopher spends sleeping

`number_of_times_each_philo_eat (optional):` Program stops when all philosophers have eaten at least this many times

## Notes

This is a 42 project with specific formatting requirements and limited function access, so it may not represent the optimal or most concise solution.
