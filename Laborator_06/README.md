# Laborator 06 - Effective C++, Items 13, 14

```bash
cmake -B build
cmake --build build
./build/Laborator_06                   # correct versions
./build/demo_greseli                   # lists the demos with bad classes
./build/demo_greseli leak              # or: copiere
```

| Item | Classes | Bad version |
|---|---|---|
| 13 | `Contract` + `creeazaContract()`, `std::unique_ptr`, `std::shared_ptr` | `leak`: manual `delete` skipped by return / exception |
| 14 | `CheieUnica`, `CheieComuna`, `ListaJucatori`, `CheieTransferabila` on a `Vestiar` | `copiere`: `CheieGresita`, unlocked twice |

## Item 13 - use objects to manage resources
The resource goes into a managing object right away (RAII); its destructor releases it however the block is left.

- `std::unique_ptr`: one owner, no copy, `std::move` transfers it (replaces `std::auto_ptr`, removed in C++17)
- `std::shared_ptr`: reference counted, the last copy deletes the object
- `Contract::inViata()` counts live contracts, so a leak is visible even without the sanitizer

## Item 14 - copying behavior in resource-managing classes
`Vestiar` plays the mutex, `incuie` / `descuie` are its C style API. What should copying a key do?

| Option | Class | How |
|---|---|---|
| prohibit copying | `CheieUnica` | copy functions `= delete` |
| reference counting | `CheieComuna` | `std::shared_ptr<Vestiar>` with `descuie` as deleter |
| deep copy | `ListaJucatori` | new array in the copy, copy and swap in `operator=` |
| transfer ownership | `CheieTransferabila` | move-only, the source is left with `nullptr` |
