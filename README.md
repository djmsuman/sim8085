# sim8085

Text based Intel 8085 simulator in C++.

**Simulates instructions by changing memory, registers and flags accordingly.**

- _This simulator is basically made to be able to play with 8085 asm language._

- *This project is currently under heavy development.*

## Set up & running

1. Clone this repository

    `$ git clone https://github.com/djmsuman/sim8085.git`

2. Go to project root

  `$ cd sim8085`

3. Build the project

    `$ make`

4. Execute the program

    `$ make exec`

5. Build & run tests

    `$ make test`

## Limitations

- Only parse hex opcodes. (Will get a minimum assembler soon)

- Since you need to manually enter the opcodes in bytes there is no support for
    label. Currently you need to manually assign address and set `JMP`
    instruction accordingly.

- Does not provide any idea of execution time if the same program were running
    in a real Intel 8085.
