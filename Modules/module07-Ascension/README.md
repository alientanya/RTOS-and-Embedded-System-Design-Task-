# Module 07 - RTOS Firmware Integration Project

## Objective

Until this point, every module has focused on learning one concept at a time.

- Tasks
- Queues
- State Machines
- Mutexes
- Semaphores
- Software Timers

Real embedded firmware, however, is never written one concept at a time.

Everything works together.

This project marks the beginning of writing firmware the way it is developed in industry.

The objective is not simply to make the program work.

The objective is to design firmware that is modular, scalable, reusable, and easy to integrate into larger systems.

This project is expected to represent the engineering practices that will be followed in future RoboCup projects.

---

# Why This Project Exists

When I originally built the firmware for our robot, I eventually arrived at a very similar architecture.

At that time, however, I was mostly solving immediate problems.

I knew I wanted cleaner code, better modularity, and reusable software, but I did not yet have a clear direction for how everything should fit together.

This project is the result of everything learned from those experiences.

Unlike me, you now know exactly why you are building it.

The architecture you design here is not just another assignment.

It is intended to become part of the software architecture that will eventually run on our robots.

Take this project seriously.

Good engineering decisions made today will save weeks or months of development effort in future projects.

---

# Project Goal

Design a complete RTOS based firmware application capable of:

- Acquiring sensor data
- Processing the acquired information
- Estimating robot state
- Communicating with external systems
- Logging important system events
- Operating reliably under an RTOS

The exact implementation is left to you.

Your engineering decisions will be reviewed.

---

# Engineering Philosophy

Before writing any code, ask yourself:

> If another engineer joins the project one year from now,
> will they be able to understand and extend my work?

Also ask yourself:

- Can this module be reused in another robot?
- Can it work with different hardware?
- Can another communication protocol replace the current one?
- Can another developer understand my interfaces without reading the implementation?
- If a sensor changes tomorrow, how much of my application breaks?

If the answer is "everything", your design is probably too tightly coupled.

---

# Design Principles

The following principles should guide every design decision.

- Single Responsibility Principle
- Separation of Concerns
- Platform Independence
- Modular Design
- Scalability
- Reusability
- Readability
- Maintainability
- Loose Coupling
- Clear Interfaces

These principles are often more important than the specific APIs used.

---

# Final Note

When I first built firmware like this, I was solving problems one at a time without realizing I was slowly building an architecture.

You have the advantage of seeing the destination before beginning the journey.

Use that advantage.

You have reached the end of this course.

But this is not the end.

It is the point where learning becomes engineering.

The concepts are no longer separate lessons.

They are now tools.

Use them wisely.

Welcome to **Ascension**.