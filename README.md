# Terminal Calculator

Calculator written in C to use directly in the terminal as a command to evaluate operations that include additions, subtractions, multiplications, divisions, modulus and parenthesis with operand precedence of PMMDAS to solve operation without the need to open the calculator.
</br><br>

## Requirements
This project requieres the C language and the (*GCC*) C compiler pre-intalled.
*Check online the installation process for your current os*

## Installation and setup

### Step 1: Copy repository
```
git clone https://github.com/OrangeWolfy/Terminal-Calculator.git
```

### Step 2: Use the Makefile
A Makefile was created with all the steps or build manually if desired:
- Create the directory to hold the executable `mkdir -p ~/.calculator/`.
- Compile the C file `gcc calculator.c -o calc`.
- Move the executable to the directory created `mv calc ~/.calculator/`.
- Create the alias on `.bashrc` for use in all terminals only if it hasn't been added previously `grep -l calc=\"~/.calculator/calc\" ~/.bashrc || echo "alias calc=\"~/.calculator/calc\"" >> ~/.bashrc`.

To build use the proyect just type
```
make
```
where you copied the repository.

### Step 3: Try it
```
calc 1+1
```
(*If the command is not recognized the setting for an alias may be different on your os or terminal*)

## Sintaxis
Once your done setting up the command you should know how to use it.

### Characters
You can make as many operations as long as it only includes:
* Numbers
* Additions: `calc 1+1` will result in 2.
* Subtraction: `calc 1-1` will result in 0.
* Multiplication: `calc 2*2` or `calc 2x2` will result in 4.
* Division: `calc 10/2` will result in 5.
* Modulus: `calc 2%10` will result in 2.
* Parenthesis: `calc (1+2)*3` will result in 9.
* More may be added.

### Important notes
* In some terminals the parenthesis may be reserved so `\(` and `\)` will be needed to work.
* **Blank spaces** are not valid: `calc 1 + 1` will not result give a result.


### Multiple operations
As said you can make multiple operations and it will evaluate the operation as expected in a calculator for example:\
`calc 10+20-30*40/50%60` will result in 6 and `calc (10+20-30)*40/50%60` will result in 0.
