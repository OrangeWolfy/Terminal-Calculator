# Terminal Calculator

This is a calculator writen in C to use directly in the terminal as an alias with addition, subtraction, multiplication, division but no order of operations to solve simple operation without the need to open the calculator using C.
</br><br>

## Setup

### Step 1: Installation
This project requieres the C language and the a C compiler (*GCC*) intalled.
```
# install the requirements
sudo apt update && sudo apt upgrade -y
sudo apt-get install build-essential

# clone the repository and compile the source file to an executable
git clone https://github.com/OrangeWolfy/Terminal-Calculator.git
gcc calculator.c -o calc
```
I recommend you should move this project to a file close to the $HOME file to make the path short if you haven't already.
```
mkdir ~/.calculator
cp calculator.c ~/.calculator
cp calc ~/.calculator
```

### Step 2: Configure the command/alias
To use the executable as a command you will need to configure the `~/.bashrc` file as follows.
```
alias calc="~/.calculator/calc
```
The alias name can be change if needed by just changing the `alias NewName=`.

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
`calc 10+20-10*2/4` this will give 25 (*just remeber there is no order of operations at the moment*).

## More
I know not many people or none at all will see this but thank you if you are, this was a project I decided to do when I wanted to know the result to an operation so simple opening the calculator will be a waste of time and too lazy to solve it myself so I made this to solve that and just have some more practice making a new type of project experimenting with arguments when executed as a command and documenting a github project for the first time so feel free to modify it as much as you want.
