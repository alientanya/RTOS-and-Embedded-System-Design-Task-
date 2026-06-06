# Module 00 - Development Environment Setup

## Purpose

Before we can build embedded systems, RTOS applications, or firmware, we need a professional development environment.

This module introduces the basic tools used throughout the rest of the curriculum.

The goal is not to learn Linux itself.

The goal is to learn the software development workflow used by professional engineers.

By the end of this module, learners should be able to:

* Navigate a Linux environment
* Create and edit source files
* Compile C programs
* Run executables
* Understand the role of Git
* Understand the role of CMake
* Understand the role of GDB
* Understand the overall development workflow

---

## Why Are We Doing This?

Many beginners start directly with microcontrollers.

This often leads to confusion because they are learning:

* Programming
* Toolchains
* Debugging
* Hardware
* RTOS concepts

all at the same time.

In this curriculum we separate these topics.

We first learn the software workflow on a PC.

Once the workflow is understood, we can later move to STM32, ESP32, or other embedded platforms without changing our development habits.

---

## The Development Workflow

Every project in this curriculum follows the same pattern:

Write Code
↓
Build Code
↓
Run Code
↓
Debug Code
↓
Track Changes

The tools introduced in this module support this workflow.

---

## Tools Introduced

### WSL (Windows Subsystem for Linux)

Provides a Linux development environment inside Windows.

Why?

Many professional software and embedded development tools are designed around Linux workflows.

---

### GCC

The compiler.

Converts C source code into executable machine code.

Source Code
↓
GCC
↓
Executable Program

---

### Git

Version control system.

Tracks changes to a project over time and allows collaboration between multiple developers.

---

### CMake

Build system generator.

Helps organize and build larger projects without manually writing long compiler commands.

---

### GDB

Debugger.

Allows inspection of program execution, variables, and program state.

---

## Learning Outcomes

After completing this module, learners should be able to:

* Install WSL
* Install development tools
* Create a workspace
* Create a C source file
* Compile a program using GCC
* Run the resulting executable
* Create and clone a Git repository
* Commit and push changes to GitHub

---

## Success Criteria

A learner has completed this module when they can:

1. Open a Linux terminal.
2. Create a source file.
3. Compile the source file.
4. Run the resulting executable.
5. Push a file to a GitHub repository.

These skills will be used throughout every future module.
