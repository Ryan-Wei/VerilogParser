# A Simple Implement of Parser for Verilog Using Lex/YACC

**COSC320- Concepts of Programming Languages**

**PROJECT4 _Spring 2023**



## Scope

As a modern programming language, Verilog has a rich and intricate syntax. Since a finished Verilog parser would need thousands of lines of code, this project will merely implement the most frequently used syntax that are essential for describing digital circuits, and generate the input Verilog text file's Abstract Syntax Tree (AST).

Here are some of the most frequently used Verilog syntax elements supported by this project:

1. Module Declaration:

   ```verilog
   module module_name (input_list, output_list);
       // Module body
   endmodule
   ```

   Modules are the building blocks of Verilog designs. They encapsulate a set of logic and define input and output ports.

2. Data Types:
   Verilog supports various data types, including:

   - `wire`: Represents a continuous signal or interconnect.
   - `reg`: Represents a storage element or a variable as a register.
   - `integer`, `real`, `time`, and other predefined data types.

3. Port Declarations:
   Ports define the interface of a module and specify its inputs and outputs. They can be declared as `input`s, `output`s, or bidirectional.

   ```verilog
   module module_name (input wire a, output reg b, inout wire [7:0] c);
   ```

4. Assignments:
   Assignments are used to assign values to signals or variables.

   - Blocking assignment (`=`): Executes in sequence.
   - Non-blocking assignment (`<=`): Executes concurrently.

   ```verilog
   a = b;
   c <= d;
   ```

5. Operators:
   Verilog provides various operators for performing arithmetic, bitwise, logical, and comparison operations. Some commonly used operators include `+`, `-`, `*`, `/`, `%`, `&`, `|`, `^`, `!`, `~`, `==`, `!=`, `>`, `<`, `>=`, `<=`, `&&`, `||`, etc.

6. Behavioral Statements:
   Verilog supports behavioral constructs to describe the behavior of circuits.

   - If-else statement:

     ```verilog
     if (condition)
         // Statements
     else
         // Statements
     ```

   - Case statement:

     ```verilog
     case (expression)
         value1: // Statements
         value2: // Statements
         default: // Statements
     endcase
     ```

7. Procedural Blocks:
   Procedural blocks define a sequence of statements executed sequentially or concurrently.

   - Always block:

     ```verilog
     always @(posedge clk)
         // Statements
     ```

   - Initial block:

     ```verilog
     initial
         // Statements
     ```

8. Hierarchical Instantiation:
   Verilog allows hierarchical instantiation of modules within other modules.

   ```verilog
   module top_module;
       module sub_module_1 (inputs, outputs);
       module sub_module_2 (inputs, outputs);
       // ...
   endmodule
   ```

9. Comments:
   Verilog supports both single-line and multi-line comments for adding notes and explanations to the code.

   ```verilog
   // This is a single-line comment
   /* This is a
      multi-line comment */
   ```



## Usage

Build the project:

```makefile
make build
```

Run the project:

```makefile
make run
[input text]
[ctrl + d]
```

Run the default test file:

```makefile
make runtest
```

Run a custom test file:

````shell
cd bin
./verilog < [path of the input file]
````

Delete the generated files:

```makefile
make clean
```

Clean ,build and run:

```makefile
make all
```

