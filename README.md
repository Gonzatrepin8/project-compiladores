# Taller y Diseño de Software

This repository has a Makefile that you can use to compile our compiler. You can run this Makefile script with the command:

```bash
make
```

This command will create an executable file `c-tds` in the root directory. This is the compiler program.

If you run this program with no arguments it receives an input where you can type your program, or you can pass as argument a file path. Example:

```bash
./c-tds program.ctds
```
This check whether the input program is parsed successfully or not.

### Running Tests

To run the parser tests simply use:

```bash
make test
```
