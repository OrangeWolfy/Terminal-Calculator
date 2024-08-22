# Terminal Calculator

Calculator written in C to use directly in the terminal as a command to evaluate operations that include additions, subtractions, multiplications, divisions, modulus and parenthesis with operand precedence of PEMDAS to solve operation without the need to open the calculator.
</br><br>

## Requirements
This project requieres the C language and the (*GCC*) C compiler pre-intalled.\
*Check online the installation process for your current os*

## Installation and setup

### Step 1: Copy repository
```
git clone https://github.com/OrangeWolfy/Terminal-Calculator.git
```

### Step 2: Use the Makefile
A Makefile was created with all the steps for a bash terminal or build manually if desired:
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

## Usage
Once your done setting up the command you should know how to use it.

### Operators
You can make as many operations as long as it only includes:
* Decimal or Hexadecimal numbers.
* Additions: `calc 1+1` will result in 2.
* Subtraction: `calc 1-1` will result in 0.
* Multiplication: `calc 2*2` or `calc 2x2` will result in 4.
* Division: `calc 10/2` will result in 5.
* Modulus: `calc 2%10` will result in 2.
* Exponentiation: `calc 2^4` will result in 16.
* Parenthesis: `calc (1+2)*3` will result in 9.
* More may be added.

### Multiple operations
As said you can make multiple operations and it will evaluate the operation as expected in a calculator for example:\
`calc 10+20-30*40/50%60+2^4` will result in 22 and `calc (10+20-30)*40/50%60+2^4` will result in 16.

### Simultaneous operations
This calculator can also be used to make several operations in the same line by separating them with spaces so taking the previous example:\
`calc 10+20-30*40/50%60+2^4 (10+20-30)*40/50%60+2^4` will result in 22 and 16 for each operation.
</br><br>

### Important notes
* In some terminals some characters may be reserved so type the backslash `\` to work.
* **Blank spaces** can't be used for the same operation: `calc 1 + 1` will not give the expected result.

## Output
The expected results will be printed in the following style to the terminal:\
*calc (OPERATIONS)*\
*(RESULTS)*
```
➜  ~ calc 1+1 2-2 3*3 4/4
1+1 = 2.0
2-2 = 0.0
3*3 = 9.0
4/4 = 1.0
➜  ~ calc 10+20-30*40/50%60+2^4
10+20-30*40/50%60+2^4 = 22.0
```
