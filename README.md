# SHELL BASIC FOR YOUR COMPUTER :computer:

## DESCRIPTION

> **HSH** is our tool (command) that will help you to follow our navigation, hsh interprets what you put in the stdinput and tries to execute it depending on the command you have used. Remember to read our instructions and what commands can be used in hsh.


### EXAMPLES

Intended to be compiled with the follwing command:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

Once compiled, this shell program can be run in interactive mode by running:

```
./hsh
```

Or non-interactive mode, with commands such as:

```
echo -e "ls -a \npwd\n" | -/hsh
```

Alternatively, if a know desired command sequence exists, it can be indirectly run from file with:

```
cat {{file_name_here}} | . /hsh
```

### How to invoke hsh? :alien:

usage: **hsh** `[filename]`
To invoke hsh, compile all `.c` files in the repository and run the resulting executable:

```
gcc *.c -o hsh
./hsh
```

`"hsh"` can be used in both interactive and non-interactive modes. When invoked in non-interactive mode with no input from a terminal, it will execute received commands sequentially.

Example:

```
$ echo "echo 'hello'" | ./hsh
'hello'
$
```
If **hsh** is invoked with standard input connected to a terminal (determined by isatty(3)), an interactive shell is opened. When executing interactively, **hsh** displays the prompt $ when it is ready to read a command.

Example:

```
$~./hsh
$
```

Alternatively, if command line arguments are supplied upon invocation, **hsh** treats the first argument as a file from which to read commands. The supplied file should contain one command per line. hsh runs each of the commands contained in the file in order before exiting.

Example:

```
$ cat ruben
echo 'holberton'
$ ./hsh ruben
'holberton'
$
```

## Environment :sparkles:

When **"hsh"** is called, it copies the environment of the parent process in which it was executed. This environment is a collection of name-value pairs represented as strings in the format `NAME=VALUE`, describing various variables. Some important environmental variables include:

### HOME

The home directory of the current user and the default directory argument for the **cd** builtin command.

check out :eyes:

```
$ echo "echo $HOME" | ./hsh
/home/vagrant
```

### PWD

The current working directory as set by the **cd** command.

check out :eyes:

```
$ echo "echo $PWD" | ./hsh
/home/vagrant/holberton/simple_shell
```

### OLDPWD

The previous working directory as set by the cd command.

check out :eyes:

```
$ echo "echo $OLDPWD" | ./hsh
/home/vagrant/holberton/printf
```
### PATH

The shell searches for commands in a list of directories separated by colons. A null directory name in the path is indicated by two adjacent colons, an initial colon, or a trailing colon, and represents the current directory.

check out :eyes:

```
$ echo "echo $PATH" | ./hsh
/home/vagrant/.cargo/bin:/home/vagrant/.local/bin:/home/vagrant/.rbenv/plugins/ruby-build/bin:/home/vagrant/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/vagrant/.cargo/bin:/home/vagrant/workflow:/home/vagrant/.local/bin
```

## Command Execution :white_check_mark:

After receiving a command, **hsh** tokenizes it into words using `" "` as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. **hsh** then proceeds with the following actions:

+ If the first character of the command is neither a slash `(\)` nor dot `(.)`, the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
+ If the first character of the command is none of a slash `(\)`, dot `(.)`, nor builtin, shellby searches each element of the PATH environmental variable for a directory containing an executable file by that name.
+ If the first character of the command is a slash `(\)` or dot `(.)` or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

## Exit Status :wave:

> hsh returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

> If a command is not found, the return status is `8`; if a command is found but is not executable, the return status is `24`.

> All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

## Signals :ear:

While running in interactive mode, hsh ignores the keyboard input Ctrl+c. Alternatively, an input of end-of-file (Ctrl+d) will exit the program.

User hits `Ctrl+d` in the third line.

```
$ ./hsh
$ ^C
$ ^C
$
```

## Shellby Builtin Commands :file_folder:

### cd

+ Usage: `cd [DIRECTORY]`
+ Changes the current directory of the process to `DIRECTORY`.
+ If no argument is given, the command is interpreted as `cd $HOME`.
+ If the argument `-` is given, the command is interpreted as cd $OLDPWD and the pathname of the new working directory is printed to standad output.
+ If the argument, `--` is given, the command is interpreted as cd $OLDPWD but the pathname of the new working directory is not printed.
+ The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

Example:

```
$ ./hsh
$ pwd
/home/vagrant/holberton/simple_shell
$ cd ../
$ pwd
/home/vagrant/holberton
$ cd -
$ pwd
/home/vagrant/holberton/simple_shell

```

### exit

+ Usage: `exit [STATUS]`
+ Exits the shell.
+ The `STATUS` argument is the integer used to exit the shell.
+ If no argument is given, the command is interpreted as `exit 0`.

example:

```
$ ./hsh
$ exit
normal shell ~
```

## Authors :
+ Stefano Madueño
+ Mauricio Aguilar
+ Francisco Sono

