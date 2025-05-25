# terminal-tetris

Creators: Ron S. and Oliver K.


# dependencies

The code uses c++ standard and ncurses library.

To download ncurses on Debian run the following code in your terminal:

```bash
sudo apt-get install libncurses5-dev
```

# compiling and running the game

1. Go into /terminal-tetris and create a /obj directory:

```bash
mkdir obj
```

2. Then compile all the files into one main executable:

```bash
make all
```

You should see a "main" file in the project root.

3. After compiling all the files you can run the executable by doing:

NB! It is highly recommended to run this in a regular terminal (not in some text editor for example VS Code)!

```bash
make run
```

The game screen should appear!

# good to know

1. The executable has also two flags:
   1. -h / --help => This shows you the controls for the game.

While in /terminal-tetris:

```bash
./main -h
```

   2. -v / --version => Shows you the version.

While in /terminal-tetris:

```bash
./main -v
```