# 					Parser of Verilog Using Lex/YACC



<img src="D:\A\exchange\courses\prog\project\parser\README.assets\image-20230516003259035.png" alt="image-20230516003259035" style="zoom:57%;" />

​															**Department of Electrical Engineering and Computer Science**

​																		**COSC320- Concepts of Programming Languages**

​																							  **PROJECT4 _Spring 2023**

​																			**Parsing of input languages using lex/ yacc**

























> Tao Wei (100063849)
>
> Available at: [Ryan-Wei/parser: a simple verilog parser (github.com)](https://github.com/Ryan-Wei/parser)



## 1. Introduction

#### 1.1 Motivation

In this course project, I will construct a **parser of Verilog** using YACC and an associated lexer using Flex for the following reasons:

- I would want to select a project that relates to compiling because I will transfer the credits from this course to *fundamentals of compiling* in my home school; 
- Verilog is a programming language that I am extremely familiar with because I once used it to design a pipeline CPU based on MIPS instruction set.

#### 1.2 Problem Description

The primary objective of this project is to develop a Verilog parser capable of analyzing Verilog code and constructing a hierarchical representation of the code's structure. The parser should utilize the lex/yacc (Flex/Bison) toolset, which enables the generation of efficient and accurate parsers from lexical and grammatical specifications. The Verilog parser should be able to handle a broad range of Verilog constructs, including module declarations, ports, statements, expressions, and control structures. By implementing a robust Verilog parser, we can lay the foundation for various language processing tasks such as code generation, optimization, and static analysis.

#### 1.3 Domain Introduction

In the field of digital design and hardware description languages, Verilog stands as a widely adopted and standardized language for modeling and simulating digital systems. As Verilog designs grow in complexity, the need for efficient tools to analyze, validate, and transform Verilog code becomes crucial. Parsing, a fundamental process in language processing, plays a key role in understanding and interpreting the structure and syntax of programming languages. In this project, I aim to implement a Verilog parser using lex/yacc, also known as Flex/Bison, to facilitate the analysis and manipulation of Verilog code.

#### 1.4 Project Scope

The project will focus on the design and implementation of a Verilog parser using the lex/yacc system. The parser will take its input from Verilog source code files and generate an abstract syntax tree (AST) in `json` format representing the hierarchical structure of the code. The parser will handle the tokenization of Verilog constructs, enforcing the language's syntax rules and identifying any syntactic errors. While semantic analysis and detailed error handling are important aspects of Verilog parsing, they may not be the primary focus of this project, which primarily aims to construct a functional Verilog parser.

#### 1.5 Expected Deliverables

The main deliverable of this project will be a Verilog parser implemented using lex/yacc. Along with the parser implementation, a comprehensive project report will be provided, encompassing the problem statement, detailed notes on the parser description, flow chart illustrating the program implementation, program codes with line-by-line comments, screenshots of the parser's results, a concluding analysis, and a list of references used.



## 2. Notes

#### 2.1 Verilog

Verilog is a hardware description language (HDL) widely used in the design, simulation, and verification of digital electronic systems. It provides a concise and structured way to describe the behavior and structure of digital circuits at various levels of abstraction. Verilog is particularly popular in the field of electronic design automation (EDA) and is an industry-standard language for digital circuit design.

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

#### 2.2 Lexer

The lexer (lexical analyzer) in Verilog is responsible for breaking down the input Verilog source code into a sequence of tokens or lexemes. Its main function is to scan the input characters and identify the different components of the code, such as keywords, identifiers, operators, numbers, and punctuation symbols. The lexer serves as the initial phase in the Verilog compilation process and plays a crucial role in preparing the code for further analysis by the parser.

Here are some key functions and features of the lexer in Verilog:

1. **Tokenization**: The lexer scans the input Verilog code character by character and identifies the individual tokens or lexemes. It recognizes keywords (e.g., `module`, `input`, `output`), identifiers (module names, signal names), operators (arithmetic, bitwise), numbers (integer, real), punctuation symbols (brackets, semicolons), and other language elements.
2. **Skipping Whitespace and Comments**: The lexer ignores whitespace characters (spaces, tabs, newlines) and discards them as they do not affect the code's structure. It also handles comments (single-line or multi-line) and removes them from the token stream.
3. **Token Attributes**: Each token identified by the lexer may have associated attributes. For example, a number token may include attributes like its value and data type, while an identifier token may include attributes like its name and scope.
7. **Interface with Parser**: The lexer provides a stream of tokens to the parser, which is responsible for syntactic analysis. The parser uses the tokens to build the abstract syntax tree (AST) representing the structure of the Verilog code.

The lexer's primary role is to break down the Verilog source code into meaningful tokens, allowing subsequent stages of the compilation process to operate on well-defined language components. It provides the foundation for the parser to analyze the code's syntax and structure, facilitating the understanding and manipulation of the Verilog design.

#### 2.3 Parser

The parser in Verilog is a crucial component of the compilation process that analyzes the syntax and structure of the Verilog code. Its primary function is to parse the sequence of tokens generated by the lexer and construct a parse tree or an abstract syntax tree (AST) representing the hierarchical structure of the code.

Here are key functions and features of the Verilog parser:

1. **Grammar Rules**: The parser follows a set of grammar rules specific to the Verilog language. These rules define the syntax and structure of valid Verilog code, including module declarations, port definitions, statements, expressions, and control structures.
2. **Syntactic Analysis**: The parser analyzes the sequence of tokens to ensure they conform to the Verilog grammar rules. It verifies the correctness of the code's syntax, identifying any syntax errors or violations. If an error is found, the parser may generate appropriate error messages or diagnostics.
3. **AST Construction**: As the parser processes the tokens, it constructs an AST that represents the hierarchical structure of the Verilog code. The AST represents the relationships between different language constructs, such as modules, ports, statements, and expressions, and serves as an intermediate representation that can be further utilized for analysis, optimization, or code generation.
7. **Interface with Other Compilation Stages**: Once the parsing is complete, the parser provides the resulting parse tree or AST to subsequent stages of the compilation process, such as semantic analysis, optimization, or code generation. These stages utilize the parsed structure to perform further analysis or transformations.

Overall, the Verilog parser plays a vital role in understanding the structure and syntax of Verilog code. It ensures that the code is valid, constructs a representation of the code's hierarchy, and facilitates subsequent stages in the compilation pipeline.

#### 2.4 Lex/YACC

Lex and Yacc (or Flex and Bison) are widely used tools for creating lexical analyzers (lexers) and parsers, respectively. They are commonly used in the field of compiler construction to process and analyze programming languages.

Lex (or Flex) is a lexical analyzer generator that helps in creating lexical analyzers. A lexical analyzer, also known as a lexer or scanner, takes input source code and breaks it down into a stream of tokens. Lex helps in defining regular expressions that specify the patterns for different tokens in the input language. It generates a C or C++ code file that implements the lexer based on the provided regular expressions.

Yacc (or Bison) is a parser generator that aids in creating parsers. A parser is responsible for analyzing the syntax of a language by recognizing the hierarchical structure of the input code. Yacc uses a grammar specification, typically written in a language similar to BNF (Backus-Naur Form), to define the rules and syntax of the input language. It generates a C or C++ code file that implements the parser based on the provided grammar. Yacc (or Bison) is capable of generating both LALR (Look-Ahead LR) and LR (Canonical LR) parsers. Both LALR and LR parsers are effective for parsing programming languages and other context-free languages. 







## 3. Flow Chart

<img src="D:\A\exchange\courses\prog\project\parser\README.assets\flowchart.png" alt="flowchart" style="zoom:38%;" />

Here's a breakdown of each step:

1. **Read Verilog File**: The Verilog source code is opened and read by the lexer line by line. The file content is loaded into the program's processing buffer.

2. **Lexical Analysis**: The Verilog source code is processed by the lexer (generated using lex) to identify individual language tokens, such as keywords, identifiers, operators, numbers, and punctuation symbols.
3. **EOF Lexed**: If the curser reaches the End-of-File, the lexing operation is successful; otherwise, it is unsuccessful.

4. **Syntactic Analysis**: The tokens are passed to the parser (generated using yacc), which verifies the correctness of the code's syntax and constructs a parse tree or abstract syntax tree (AST) representing the code's structure.
5. **Start Symbol Parsed**: The parsing procedure is successful if the Start Symbol can be correctly parsed; otherwise, it fails.

6. **AST Generation**: The parser constructs a hierarchical representation of the code's structure using Abstract Syntax Tree (AST). This tree captures the relationships and dependencies between different language constructs, aiding further analysis.

7. **End**: The flow chart concludes, indicating the completion of the Verilog parser implementation.



## 4. Code

Available at: [Ryan-Wei/parser: a simple verilog parser (github.com)](https://github.com/Ryan-Wei/parser)

#### 4.1 Environment

- Software
  - Windows Subsystem for Linux (WSL) 1.2.5.0 / Ubuntu 20.04
  - bison (GNU Bison) 3.5.1
  - flex 2.6.4
  - gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
  - GNU Make 4.2.1 Built for x86_64-pc-linux-gnu
  - git 2.40.1

- Hardware
  - Processor	Intel(R) Core(TM) i5-1035G4 CPU @ 1.10GHz   1.50 GHz
  - Installed RAM	16.0 GB

#### 4.2 Directory

```shell
.
├── .gitattributes
├── .makefile.swp
├── .verilogParser.y.swp
├── .vscode
│   ├── c_cpp_properties.json
│   ├── launch.json
│   └── settings.json
├── README.assets
│   ├── flowchart.png
│   └── image-20230516003259035.png
├── README.md
├── bin
│   └── verilogParser
├── calculator.l
├── calculator.y
├── directory_tree.txt
├── lex.yy.c
├── makefile
├── python
│   ├── parser.out
│   └── parser.py
├── src
│   ├── ALU.v
│   ├── verilogParser
│   ├── verilogParser.l
│   └── verilogParser.y
├── test.v
├── y.tab.c
└── y.tab.h

104 directories, 163 files

```

#### 4.3 Usage

Build the project:

```makefile
make build
```

Run the project:

```makefile
make run
make runtest
```

Delete the generated files:

```makefile
make clean
```





// description of bison and grammar (unambiguous) and specific grammar









## 5. Result







## 6. Conclusion

In this project, I set out to implement a Verilog parser using lex/yacc, with the goal of analyzing and interpreting Verilog source code. Through the implementation process, I have achieved several key objectives and gained valuable insights into the intricacies of Verilog parsing.

First, I successfully designed and implemented a Verilog lexer using Flex, which allowed us to tokenize the Verilog source code into individual language elements. This lexical analysis served as the initial step in the parsing process, enabling us to break down the code into meaningful tokens such as keywords, identifiers, operators, and numbers.

Next, using yacc, I constructed a Verilog parser that validated the syntax of the Verilog code and generated a hierarchical representation of its structure in the form of an abstract syntax tree (AST) in `json` format. The parser's syntactic analysis provided a deeper understanding of the Verilog code's organization, capturing the relationships and dependencies between various language constructs such as modules, ports, statements, and expressions.

Furthermore, the implementation of the Verilog parser allowed us to explore semantic analysis to enforce Verilog-specific constraints and rules. This involved checking for proper scoping, type compatibility, and adherence to Verilog language rules beyond the syntactic level. Through semantic analysis, I ensured that the parsed Verilog code was not only syntactically correct but also semantically sound.

Throughout the project, I encountered and addressed various challenges, such as handling complex Verilog constructs, managing errors, and designing an efficient and robust parser using an unambiguous grammar. These challenges provided valuable learning opportunities and fostered a deeper understanding of the Verilog language and parsing techniques.

In conclusion, the Verilog parser implementation using Lex/YACC has proven to be a valuable tool for analyzing and processing Verilog code. By breaking down the Verilog source code into its constituent elements, validating its syntax, and constructing an AST, the parser provides a foundation for subsequent language processing tasks such as optimization, code generation, and static analysis.

While my implementation focused on the core aspects of Verilog parsing, there is ample room for further enhancements and extensions. Future work may involve incorporating more advanced semantic analysis, error recovery mechanisms, or optimizations to improve the performance and accuracy of the parser.

Overall, this project has not only deepened my understanding of Verilog parsing but also equipped us with practical knowledge and skills in building parsers for other programming languages. The Verilog parser serves as a stepping stone for further exploration in the field of digital design and language processing, contributing to the development of more sophisticated tools and methodologies for working with Verilog designs.



## 7. Reference

1. Verilog-2005 Standard, IEEE Standard for Verilog Hardware Description Language, IEEE Std 1364-2005.
2. [Flex: The Fast Lexical Analyzer.](https://github.com/westes/flex)
3. [Bison: The Yacc-compatible Parser Generator.](https://www.gnu.org/software/bison/)
4. [Verilog HDL Quick Reference Guide.](https://www.asic-world.com/verilog/veritut.html)
5. [chipsalliance/verible: Verible is a suite of SystemVerilog developer tools, including a parser, style-linter, formatter and language server (github.com)](https://github.com/chipsalliance/verible)
6. Brown, S., & Vranesic, Z. (2008). Fundamentals of Digital Logic with Verilog Design (3rd ed.).
7. Sutherland, S., & Mills, D. (2007). Verilog and SystemVerilog Gotchas: 101 Common Coding Errors and How to Avoid Them.
8. Patterson, D. A., & Hennessy, J. L. (2020). Computer Organization and Design: The Hardware Software Interface [RISC-V Edition].
9. 唐朔飞. (2019). 计算机组成原理（第2版）.
10. Cooper, D., & Torczon, L. (2011). Engineering a Compiler. Morgan Kaufmann.
11. Aho, A. V., Lam, M. S., Sethi, R., & Ullman, J. D. (2006). Compilers: Principles, Techniques, and Tools. Pearson Education.
12. Levin, D., & Arora, S. (2009). An Introduction to Lex & Yacc. O'Reilly Media.



