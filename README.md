# Terminal Calculator

This is a calculator writen in C to use directly in the terminal as an alias with addition, subtraction, multiplication, division with no order of operations to solve simple operation without the need to open the calculator using C.
</br><br>

## Setup

### Step 1: Copy repository
This project requieres the C language and the a C compiler (*GCC*) intalled.
```
# install the requirements
sudo apt update && sudo apt upgrade -y
sudo apt-get install build-essential

# clone the repository and compile the source file to an executable
git clone https://github.com/OrangeWolfy/Terminal-Calculator.git
```

### Step 2: Use the Makefile
A Makefile was created with all the steps:
- Create the directory to hold the executable only if it hasn't been created `mkdir -p ~/.calculator/`
- Compile the C file `gcc calculator.c -o calc`
- Move the executable to the directory created `mv calc ~/.calculator/`
- Create the alias on `.bashrc` for use in all terminals only if it hasn't been created `grep -l calc=\"~/.calculator/calc\" ~/.bashrc || echo "alias calc=\"~/.calculator/calc\"" >> ~/.bashrc`

To build use the make file type
```
make
```
where you copied the repository.

### Step 3: Try it
```
calc 1+1
```

## Sintaxis
Once your done setting up the command you should know how to use it.

### Characters
You can make as many operations as long as the result is within the int size (-2,147,483,648 to 2,147,483,647) and only includes:
* Additions: `calc 1+1`
* Subtraction: `calc 1-1`
* Multiplication: `calc 2*2` or `calc 2x2`
* Division: `calc 4/2`
* More may be added
* **Blank spaces are not valid**: `calc 1 + 1` will not result give a result

### Multiple operations
As said you can make multiple operations and it will keep record of your result and may be combined like expected in a calculator
`calc 10+20-10*2/4` this will give 25 (*just remeber there is no order of operations*).
