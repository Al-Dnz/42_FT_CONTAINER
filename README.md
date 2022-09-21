# FT_CONTAINERS

https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf

## CHECK UP

To compare the std and ft librairies with my personal tests:
```
make
diff <(./ft_prog) <(./std_prog)
```

To watch them:
```
./ft_prog
```

Check leaks with
```
valgrind ./ft_prog
```

Compare time with:
```
./time_test.sh
```

Test with other testers at:
```
./test.sh
```


