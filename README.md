# MPI Ring Token

Exercício de Programação Paralela Avançada. Implementação de algorítimo de Ring Token em MPI

``` sh
mpicc -o bin/ring ring.c
mpirun --machinefile hosts mpi
mpirun --machinefile hosts -np 12 mpi
mpirun --machinefile hosts -np 12 --mca btl_tcp_if_include 10.20.221.0/24 mpi
```
