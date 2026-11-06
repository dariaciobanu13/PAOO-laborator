# Laborator 04 - Effective C++, Items 4, 5, 6

```bash
cmake -B build
cmake --build build
./build/Laborator_04      # correct versions
./build/demo_greseli      # lists the demos with bad classes
./build/demo_greseli neinit  # or: ordine | fiasco | shallow
```

Code that must not build has its own target:

```bash
cmake --build build --target eroare_const_in_corp          # item 4
cmake --build build --target eroare_atribuire_referinta    # item 5
cmake --build build --target eroare_copie_privata          # item 6, C++98
cmake --build build --target eroare_link_friend            # item 6, C++98, link error
cmake --build build --target eroare_copie_uncopyable       # item 6, Uncopyable
cmake --build build --target eroare_copie_delete           # item 6, = delete
```

| Item | Classes | Bad version |
|---|---|---|
| 4 | `JucatorLista`, `Contract`, `Teren`, `ligaNationala()` | `neinit`, `ordine`, `fiasco` |
| 5 | `Scor`, `Arbitru`, `Transfer`, `Rezerva`, `Antrenor` | `shallow` |
| 6 | `Stadion98`, `StadionUncopyable`, `StadionModern` | `eroare_copie_*` |
