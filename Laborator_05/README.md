# Laborator 05 - Effective C++, Items 10, 11, 12

```bash
cmake -B build
cmake --build build
./build/Laborator_05                   # correct versions
./build/demo_greseli                   # lists the demos with bad classes
./build/demo_greseli void              # or: autoatribuire | copiere
```

| Item | Classes | Bad version |
|---|---|---|
| 10 | `Scor` (`operator=`, `operator+=`, `operator=(int)` return `*this`) | `void`: `ScorVoid`, `a = b = c` does not compile |
| 11 | `EchipaTestIdentitate`, `EchipaOrdine`, `EchipaSwap` (+ move assignment) | `autoatribuire`: `EchipaGresita`, heap-use-after-free |
| 12 | `Jucator`, `Capitan` | `copiere`: `CapitanGresit`, base part not copied |

## Item 10 - return a reference to `*this`
`a = b = c` is parsed as `a = (b = c)`, so `b = c` has to give back `b`.
The same rule holds for `+=`, `-=` and `operator=` from other types.

## Item 11 - assignment to self
Self-assignment is often hidden: `a[i] = a[j]` with `i == j`, `*p1 = *p2` with `p1 == p2`.
Deleting first and then copying reads freed memory when `this == &rhs`.

- identity test: handles `a = a`, but not an exception from `new`
- careful ordering: copy first, delete after
- copy and swap: copy into a temporary, swap, the temporary takes the old data away

## Item 12 - copy all parts
A derived class copy constructor must call `Base(rhs)`, and its `operator=` must call `Base::operator=(rhs)`.
Otherwise the base part is default constructed (copy constructor) or left unchanged (`operator=`).
When a member is added, both copying functions must be updated.
