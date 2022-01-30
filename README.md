# parallel-maharaja

### Compiling
```
cmake .
```

```
make
```
### Run
```
./parallel-maharaja 8 4
```
Where 8 - size deck(NxN), 4 - parallel processes


## MPI

### Compiling
```
mpic++ main.cpp chessboard.cpp -o a.out
```

### Run
```
mpiexec -n 2 ./a.out
