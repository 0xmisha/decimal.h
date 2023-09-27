# decimal: A Comprehensive Review

## Introduction
The `decimal` project revolves around implementing a new data type, named `decimal`, in the C programming language. This type, while not part of the native C language standard, holds paramount importance, especially in applications like financial calculations where floating point inaccuracies can yield catastrophic results. This venture delves into challenges such as handling financial data, comprehending various data type representations, and instilling robust structured programming concepts.

## Installation
````
git clone https://github.com/0xmisha/decimal.h.git
cd decimal.h/src
make
````

## Requirements

- Gcc
- Make
- check.h (for tests)

## Core Features
1. **Decimal Data Type**: Capable of representing extremely large numbers, ranging from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335, it addresses the need for high precision in both integral and fractional values.
   
2. **Binary Representation**: The unique architecture consists of a 96-bit integer number, a scaling factor determining the position of a floating decimal point, and a 1-bit sign to distinguish between positive and negative values. A meticulous breakdown of how the binary representation is structured is provided, including the significance of each bit and its role.

3. **Decimal Arithmetic**: Essential arithmetic operations like addition, subtraction, multiplication, and division are supported. Special attention is given to potential errors like overflow, underflow, or division by zero, ensuring the library's robustness.
   
4. **Comparison**: Incorporates fundamental comparison functions, enabling evaluations like less than, greater than, equality, and their respective derivatives.
   
5. **Conversion and Parsing**: Bridges the gap between integers, floating-point numbers, and the `decimal` type through a set of conversion functions. This flexibility ensures seamless integration and interoperability between different data types.
   
6. **Additional Utility Functions**: Additional tools, such as `floor`, `round`, `truncate`, and `negate`, offer extended functionality, enhancing the library's overall utility.

## Technical Specifications
1. **C11 Standard**: The codebase strictly adheres to the C11 standard and is tailored for the gcc compiler.
   
2. **Structured Programming**: Emphasis on organized, modular, and readable code is evident, advocating for the principles of structured programming.
   
3. **Google Coding Style**: By aligning with the Google coding style, the library ensures maintainability, readability, and adherence to widely accepted best practices.
   
4. **Static Library**: The deliverable is in the form of a static library, simplifying integration into other projects.
   
5. **Testing and Coverage**: Employing the Check library, a comprehensive suite of unit tests assures the reliability of the library. A minimum of 80% code coverage, verified via `gcov`, speaks volumes about the depth of testing.
   
6. **Build Automation**: The provided `Makefile` automates various tasks like compilation, testing, and generating coverage reports.

## Conclusion
The `s21_decimal` project is a commendable attempt to bring high-precision arithmetic to the C language. By addressing the intricacies of financial computations and upholding stringent coding standards, it stands as a valuable addition to any developer's toolkit.