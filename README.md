# Sales taxes problem
Basic sales tax is applicable at a rate of 10% on all goods, except books, food, and medical products that are exempt. Import duty is an additional sales tax applicable on all imported goods at a rate of 5%, with no exemptions.

When I purchase items I receive a receipt which lists the name of all the items and their price (including tax), finishing with the total cost of the items, and the total amounts of sales taxes paid. The rounding rules for sales tax are that for a tax rate of n%, a shelf price of p contains (np/100 rounded up to the nearest 0.05) amount of sales tax.

```
INPUT:

Input 1:
2 book at 12.49
1 music CD at 14.99
1 chocolate bar at 0.85

OUTPUT

Output 1:
2 book: 24.98
1 music CD: 16.49
1 chocolate bar: 0.85
Sales Taxes: 1.50
Total: 42.32
```

# Solution

## Intro
The project started with the test design in the `ApplicationTest` class (TDD), afterwards the other classes were designed and in the end it was done the refactory.

## Final Architecture
- The `ShoppingNote` class contains the input string and the product category (generic, medicine, food and book). Metaphorically it represents the note on paper of a shopping list.
- The `ShoppingSheetList`class collects all the notes of the shopping list.
- The `InputProvider` class is for the inputs. It can generate `ShoppingNote` in a hard coded way or by parsifying the input files. 
  In case of input file option:
  - For the product categories it parsifies in a key-value map the input vocabulary file that contains the matches between product and category -> `chocolate-FOOD`.
  - For the product list it parsifies in a dedicated list the string's file -> `2 book at 12.49`.
- `GenericProduct`is the class that represents the generic product subject to taxation. Each product contains a `Tax` object that provides tax calculation and rounding.
- `Book`, `Food` and `Medicine` are subclasses of `GenericProduct` that, for now, do not have particular functionalities with respect to the parent class if not the fact of being exempted from basic sales taxation.
- `Basket` is the class that collects the list of purchased products: it is a shopping cart.
- `Receipt` is the class that calculates and prints the final receipt for the products in the cart.
- `Application` is the class that decides which source to take the inputs from, fills the `Basket` with products from the shopping list and generates the `Receipt`.
- `ApplicationTest` is the class that performs unit tests on other classes, creates an application and performs functional tests on it for different types of input. It performs a looped series of repeated tests for different inputs (hard coded, correct input files, wrong input files, wrong category vocabulary files, etc.) without recompiling.
-The *input* folder contains input files and classes to manage that input.
-The *products* folder contains classes to manage the products.
-The *test* folder contains the class used for testing the project.
-The *src* folder contains application and other classes.

## Input format
As far as input is concerned, the application decides whether to use a coded hard source or the input files. 

If the input is hard coded the hypothesis is that for each string you know the category of the product.

If the input is from file the hypothesis is to have:
- a file (*InputNotes1.txt*) that provides a list of strings for the products (`"1 imported milk at 1.99"`)  
- a file (*CategoryVocabulary.txt*) with the list of all known products and their respective categories (`"milk FOOD"`).

Incorrectly formatted products and categories are discarded.

In the input folder there are some examples for these input files used in the tests. 

## Output format
Console printing was used for the output, in case of failure atest an assert is displayed

```
Assertion failed: ( int (p->GetTaxesValue()*100) == int (testTax*100) ), file ..\src\test\ApplicationTest.cpp, line 187
```

In case the test passes the receipt for that input is printed. Below an example of input from file and output for the first 4 tests on the Application.

INPUT FILE:

```
Test 1: inputNotes1.txt and categoryVocabulary.txt
Test 2: inputNotes2.txt and categoryVocabulary.txt
Test 3: inputNotes3.txt and categoryVocabulary.txt
Test 4: inputNotes4.txt and categoryVocabulary.txt`
```

OUTPUT:
```
Test 1:
2 book: 24.98
1 music CD: 16.49
1 chocolate bar: 0.85
Sales Taxes: 1.50
Total: 42.32

Test 2:
1 imported box of chocolates: 10.50
1 imported bottle of perfume: 54.65
Sales Taxes: 7.65
Total: 65.15

Test 3:
1 imported bottle of perfume: 32.19
1 bottle of perfume: 20.89
1 packet of headache pills: 9.75
3 box of imported chocolates: 35.55
Sales Taxes: 7.90
Total: 98.38

Test 4:
1 imported shirt: 32.19
1 milk: 1.00
1 pill: 2.00
3 aspirin: 6.30
Sales Taxes: 4.20
Total: 41.49
```

## Compile and Run
```
OS: `Win 10 Pro`
IDE: `Eclipse`
TOOLCHAIN: `MINGW GCC` 
DEBUGGER: `gdb`
```
