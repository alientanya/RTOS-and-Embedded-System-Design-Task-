# Module 04.1 – Testing a State Machine

## Objective

Before improving your state machine, you must first verify its current behaviour.

In this module, your task is to evaluate your implementation by exercising every behaviour exposed by the supplied IMU driver.

The goal is **not** to modify the driver.

The goal is to understand and validate your state machine.

---

# Rules

- Do **not** modify `imu.c`.
- Do **not** modify `imu.h`.
- Test your state machine against every available driver test condition.
- Record your observations before making any improvements to your implementation.

---

# Deliverables

Submit the following files:

```
main.c
imu_manager.c
imu_manager.h
test.c
TEST_REPORT.md
```

---

# test.c

Create a separate test application that exercises your state machine.

Your test application should attempt to verify all behaviours exposed by the supplied driver.

The implementation of the test application is intentionally left open-ended.

---

# TEST_REPORT.md

Your report should include:

- Test name
- Test objective
- Expected behaviour
- Actual behaviour
- Result (PASS / FAIL)
- Any bugs or unexpected behaviour discovered
- Suggested improvements

---

# Evaluation

Your submission will be evaluated on:

- Completeness of testing.
- Ability to identify weaknesses in your own implementation.
- Quality of observations.
- Clarity of the report.
- Code quality of the test application.

---

# Notes

The supplied IMU driver is considered part of the test framework.

Your solution should adapt to the framework rather than modifying it.