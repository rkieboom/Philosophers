## Dining Philosophers

### Description
This is a C program that simulates the "Dining Philosophers" problem, a classic problem in synchronization. The program starts by creating five philosopher threads, each of which alternates between thinking and eating. At the center of the table, there is a bowl of noodles and five chopsticks, each of which is shared by two neighboring philosophers.

The philosophers will think for a random amount of time and then pick up their left chopstick and then their right chopstick. After that, they will eat for a random amount of time before putting down their chopsticks and returning to thinking. The goal is to avoid deadlocks and starvation by implementing a synchronization strategy for the philosophers to pick up and put down their chopsticks.

### Build and Run
You can build the program by running the following command in the program's directory:
```
make
```
And run the program as follows ([] is optional):
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
