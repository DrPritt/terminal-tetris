# terminal-tetris

A simple and fun Tetris clone for your terminal, built with C++ and ncurses. 

Creators: Ron S. and Oliver K.

# Features

- Classic Tetris gameplay in your terminal
- Colorful ncurses graphics
- Hold and preview blocks
- Score tracking
- Difficulty increase

# Dependencies

The code uses c++ standard and ncurses library.

To download ncurses on Debian/Ubuntu run the following code in your terminal:

```bash
sudo apt-get install libncurses5-dev
```

# Compiling and running the game

1. Clone this repository and enter the directory:

```bash
git clone https://github.com/DrPritt/terminal-tetris.git
cd terminal-tetris
 ```

2. Go into /terminal-tetris and create a /obj directory:

```bash
mkdir obj
```

3. Then compile all the files into one main executable:

```bash
make all
```

You should see a "main" file in the project root.

4. After compiling all the files you can run the executable by doing:

NB! It is highly recommended to run this in a regular terminal (not in some text editor for example VS Code)!

```bash
make run
```

The game screen should appear!

# Controls

- **a**: Move left
- **d**: Move right
- **w**: Rotate block
- **s**: Speed up drop
- **e**: Hold current block
- **space**: Hard drop
- **h**: Toggle help
- **q**: Quit


# Command-Line Flags

The executable has also two flags:
   1. -h / --help => This shows you the controls for the game.
   2. -v / --version => Shows you the version.

# Optional: Install Globally

To play Tetris from anywhere, move the executable:

```bash
sudo mv main /usr/local/bin/tetris
```

Now you can start the game by running:

```bash
tetris
```

Enjoy playing Tetris in your terminal!