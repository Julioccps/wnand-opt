# W'nAND-Opt

This project is a C implementation for analyzing and optimizing boolean logic circuits built using NAND gates. It can determine the truth signature of a given circuit and attempt to match it to common logic gates (NOT, NAND, AND, NOR, OR, XNOR, XOR).

## The "What" and "NAND"

The name **W'nAND-Opt** (pronounced "What an Optimizer") comes from its purpose: this project is designed to be a submodule for a compiler of a new esoteric programming language currently in development.

This esoteric language relies on **NAND** as its *only* arithmetic operator. The goal of `wnandopt` is to provide the compiler with the intelligence to recognize high-level patterns (like addition, XOR, etc.) within the raw NAND-based circuits, enabling significant optimizations in the generated code.

## Project Structure

- `include/`: Contains header files with data structure definitions and function prototypes.
- `src/`: Contains the source code implementation.
- `Makefile`: Provides build instructions for the project.

## Building the Project

To build the executable, navigate to the project root directory and run `make`:

```bash
make
```

This will create an executable named `wnandopt` in the project root.

## Running the Example

After building, you can run the example:

```bash
./wnandopt
```

The example currently constructs a simple XOR circuit and attempts to optimize/identify it.

## Future Enhancements (TODO)

- **CLI Interaction:** Implement a command-line interface for more interactive use, allowing users to define circuits, display their structure, and save/load circuit states to/from files (e.g., `.bin`, `.dat`).
- **Circuit Visualization:** Add functionality to visualize the circuit structure.
- **Improved Optimization:** Enhance the `optimize_circuit` function to identify more complex logic patterns or provide more detailed optimization reports.
