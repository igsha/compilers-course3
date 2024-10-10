# Number parser

This document describe a number parser.

## Regex description

Number is a `/[0-9]+(\.[0-9]*)?([eE][-+]?[0-9]+)?/`.

## Syntax diagram

```
           [0-9]         [0-9]                 [0-9]
          +-----+       +-----+       +--------------------+
          |     |       |     |       |                    v
        +---+<--+     +---+<--+       |                  +---+
0 ----->| 1 |-------->| 2 |---------> 3 -------> 4 ----->| 5 |---+
  [0-9] +---+   [.]   +---+   [eE]    ^   [-+]     [0-9] +---+   |
          |                           |                    ^     |
          +---------------------------+                    +-----+
                    [eE]                                    [0-9]
```

Acceptance states:
* 1
* 2
* 5

Additional error state is 6.
It is possible to move into the 6th state from any state.

## State transition table

| state/symbol | [0-9] | [.] | [eE] | [-+] | * |
+--------------+-------+-----+------+------+---+
|      0       |   1   |  6  |  6   |  6   | 6 |
|      1       |   1   |  2  |  3   |  6   | 6 |
|      2       |   2   |  6  |  3   |  6   | 6 |
|      3       |   5   |  6  |  6   |  4   | 6 |
|      4       |   5   |  6  |  6   |  6   | 6 |
|      5       |   5   |  6  |  6   |  6   | 6 |
|      6       |   6   |  6  |  6   |  6   | 6 |

## Action table

Description:
* `i` is a integer accumulator for a number;
* `f` is a fraction accumulator for a number;
* `o` is an order accumulator for a number;
* `isf` is a fraction flag;
* `po` is a positive order flag;
* `s` stands for the input symbol.

| state/symbol |     [0-9]    |   [.]   |   [eE]  |      [-+]     | * |
+--------------+--------------+---------+---------+---------------+---+
|      0       |              |         |         |               |   |
|      1       | i += s + '0' |         |         |               |   |
|      2       | f += s + '0' | isf = 1 |         |               |   |
|      3       |              |         | isf = 1 |               |   |
|      4       |              |         |         |               |   |
|      5       | o += s + '0' |         |         | po = s == '+' |   |
|      6       |              |         |         |               |   |

The first step is a transition, the next is an action.
