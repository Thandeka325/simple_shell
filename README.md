# Project 0x16. C - Simple Shell
This project aims to create a simple UNIX command interpreter using basic C programming.

# Requirements
General

- Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
+ All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
* Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
+ Your shell should not have any memory leaks
- No more than 5 functions per file
* All your header files should be include guarded
+ Use system calls only when you need to (why?)
* Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see [Docker](https://github.com/moby/moby/blob/master/AUTHORS).

# More Info
Output
* Unless specified otherwise, your program must have the exact same output as `sh (/bin/sh)` as well as the exact same error output.
* The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]`.

Example of error with `sh`:

```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:

```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

List of allowed functions and system calls:

`access` (man 2 access), `chdir` (man 2 chdir), `close` (man 2 close), `closedir` (man 3 closedir)
`execve` (man 2 execve), `exit` (man 3 exit), `_exit` (man 2 _exit), `fflush` (man 3 fflush), `fork` (man 2 fork)
`free` (man 3 free), `getcwd` (man 3 getcwd), `getline` (man 3 getline), `getpid` (man 2 getpid)
`isatty` (man 3 isatty), `kill` (man 2 kill), `malloc` (man 3 malloc), `open` (man 2 open), `opendir` (man 3 opendir)
`perror` (man 3 perror), `read` (man 2 read), `readdir` (man 3 readdir), `signal` (man 2 signal), 
`lstat` (__lxstat) (man 2 lstat), `fstat` (__fxstat) (man 2 fstat), `strtok` (man 3 strtok), `wait` (man 2 wait)
`waitpid` (man 2 waitpid), `wait3` (man 2 wait3), `wait4` (man 2 wait4), `write` (man 2 write), `stat` (__xstat) (man 2 stat)

# Compilation

Your shell will be compiled this way:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

```

# Testing

Your shell should work like this in interactive mode:

```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

But also in non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```



