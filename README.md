# Student Directory Tree

## Overview
This C program, crafted for the COMP2421 course, serves as a management system for school classes. It utilizes a Binary Search Tree (BST) to store and manage student information efficiently, allowing the school secretary to perform various operations such as insertion, updating, listing, searching, and deletion of student records.

## Repository Contents
- `StudentDirectoryTree.c`: The main C program source file that contains all the functions to manipulate the BST and manage student records.
- `Project 3 Spring 2023.pdf`: Project requirements and detailed specifications document.

## Features
- Insert new student records with complete details into the BST.
- Find and update existing student information using the unique student ID.
- List all students in lexicographic order based on their names.
- Search and list students from a specific city in lexicographic name order.
- List students by class, also in lexicographic name order.
- Delete student records based on the student ID.
- Save all student records into `students.data`.
- Automatically load student records from `students.data` if the file exists.
- An interactive menu for easy operation of the program.

## How It Works
The program performs the following operations:
1. Reads student data from `students.data` upon startup (if available).
2. Provides an interactive menu for the user to select an operation.
3. Processes user input and performs the requested action on the BST.
4. Writes updated student data back to `students.data` as necessary.
5. Exits and saves data when the user finishes.

## Usage
First, compile the program using a C compiler.

## Contribution
As an individual academic project, contributions are intended for peer review and instructional enhancement purposes only.
