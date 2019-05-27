# lunacode
An extended version of Brainfsck.

### Spec
- `EOF` is a 0
- a newline is a linefeed (LF).

### Improvements
#### New commands
- `%`: similar to `exit()` (in Python) or `return 0` in C. Ends the program.
- `*`: returns the memory cell to zero, instead of typing `[-]` every time.
- `&`: print value of cell to `/dev/stderr` (instead of `stdout`).
- `^`: move to the very first cell in tape.
- `$`: output a newline.
- `#`: output debug information, e.g. all cell ids, values and chars. 

### FAQ
- **why is this written in shell?**
  - why not?
- **why does this have such an awful syntax?**
  - what awful syntax?
- **what's this useful for?**
  - I don't know.
- **What's Brainfsck?**
  - you've never heard of it?
