# AoC 2023 in (mostly) C

This repository stores the code used for my [2023 Advent of Code](https://adventofcode.com/2023/) submissions.

Unlike other people who develop elegant code in sane language, I develop extremely hacky code in a not-so-sane language (I mean, C is cool and all, but damn it's pretty hard to use).

My thought process is described day per day in [the journal](JOURNAL.md)

## Building

Building the code is simple, the same as how you usually would build a CMake project.

1. Make sure you're at the project's root directory
2. `cmake -B build/ -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"`
3. `cmake --build build/ --config Release --target all`
4. Done!

That's how it would've been done on Linux, on Windows etc. please read the docs for CMake.

## Testing

Still a to-do thing, see [the repo's todo list](TODO.md)

## Benchmarking

Also still a to-do thing, see [the repo's todo list](TODO.md)

## Acknowledgements

[Jan Oberpichler](https://github.com/thejan14)'s subdirectory `CMakeLists.txt` files directly inspired the ones in this repo. [Give his AoC 2023 repo some love!](https://github.com/thejan14/adventofcode2023)

[Christian Lundh](https://github.com/happycoder74)'s `foreach` method for including subdirectories dynamically in the main `CMakeLists.txt` also directly inspired the one used in this repo. [His AoC stuff is really awesome, btw, go check it out!](https://github.com/happycoder74/adventofcode)

Also honorable mention to [Gustav Louw](https://github.com/glouw) for his awesome [C Template Library (ctl)](https://github.com/glouw/ctl). I haven't had the need to use it (and am planning to remove the submodule eventually), but it still is cool indeed.
