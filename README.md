# Urban
An optimising Brainfsck transpiler with multiple extensions. It quickly
translates Brainfsck source file into C code, which can then be compiled
with GCC, TCC or (best) Clang.

### spec
- `EOF` is a 0
- a newline is a linefeed (LF).

### extensions
- `%`: equals `exit()` in C. Ends the program on the exit code in the
  current memory cell.
- `*`: returns the memory cell to zero, instead of typing `[-]` every time.
- `&`: print value of cell to `/dev/stderr` (instead of `stdout`).
- `^`: move to the very first cell in tape.
- `$`: output a newline.
- `;`: **comments**!
- '{': equals `[<]`
- '}': equals `[>]`

### optimisations
- compresses commands (e.g. `+++++` compiles to just one increment
  instruction).
- converts `[-]` to a simple nilifying instruction. (Provides a 
  significant speed boost for certain programs.)
- converts `[<]`/`[>]` to a single `memrchr()`/`memchr()` instruction.
  (Provides a significant speed boost to certain programs.

### known issues
- the source isn't commented.
- the source won't be commented.
- the source is messy.
- OK, the source is *really* messy.
- I would like to say I'd clean it up sometime, but I
  most likely won't.

### FAQ
- **why is this written in C?**
  - why not?
- **why does Brainfsck have such an awful syntax?**
  - what awful syntax?
- **what's this useful for?**
  - I don't know.
- **What's Brainfsck?**
  - you've never heard of it?

### license
This project, and all it's including documentations and code,
is licensed under the BSD 2-Clause License. See the LICENSE.md for more
information.
