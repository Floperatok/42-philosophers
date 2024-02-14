# <div align="center">⚙️ philosophers (a [42](https://42perpignan.fr/) project) ⚙️</div>
## 📑 Introduction
School 42's `philosophers` project about introduction of the basics of process threading, how to work on the same memory space. How to deals with dataraces by using mutexes.\
The goal of this project is to write a program in C that create a given number of thread in the same process, and each threads will have to follow a routine during which they will have to do some tasks, like locking / unlocking mutexes and wait some time.\
The threads are called `philo`, each philos must eat from time to time to not starve, for eating, they must have a `fork` in each hands. Forks are represented by mutexes, there are as many forks as philos. To be able to eat, the philos have to share the forks, alternating meals between them.

Routine to be performed by philos:
- Take a fork: The philo/thread locks a mutex/fork.
- Eat: Once the philo/thread locked two mutexes/forks, it can eat, and wait a given amount of time.
- Sleep: Once the philo/thread finish eating, he now fall asleep, waiting a given amount of time.
- Think: Once the philo/thread wakes up, he now thinks, waiting for forks/mutexes to be available.

If a philo don't eat for a too long time, he dies. The goal of this project is to program such philos, and make sure they don't die.

Subject : <a href=asset/en.subject.pdf>en.philosophers_subject.pdf<a/>
### My grade
[![nsalles's 42 Philosophers Score](https://badge42.coday.fr/api/v2/clshyl91d071301p436jjiyqr/project/3433377)](https://github.com/Coday-meric/badge42)
## Usage
Download `philosophers` and enter the repo:
```sh
git clone https://github.com/Floperatok/42-philosophers.git && cd 42-philosophers
```
There are two folder `philo` and `philo_bonus`, the `philo` folder is the classic program with thread as philos. The `philo_bonus` is the bonus folder where philos are not longer represented with threads but with process, and forks are no longer represented with mutexes but with semaphores. Go inside of the folder of your choice, then compile :
```sh
make && make clean
```
You can now execute the program with the necessary arguments:
```sh
./philo 5 800 200 200
```
*Note: if you choose the bonus folder, the program name is `philo_bonus`*\
The first argument is the number of philos.\
The second arguement is the time in millisecond it takes for a philo to starve to death.\
The third arguement is the time in millisecond it takes for a philo to eat.\
The fourth arguement is the time in millisecond it takes for a philo to sleep.\
It is possible to enter a fifth argument which is the number of times the philo must eat before the program stops, the program does not stop by default.