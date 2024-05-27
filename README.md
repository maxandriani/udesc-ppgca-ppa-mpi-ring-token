# MPI Ring Token

Exercício de Programação Paralela Avançada. Implementação de algorítimo de Ring Token em MPI

## Enunciado

O trabalho requer a execução de uma aplicação comunicante usando MPI_Send/MPI_Recv. A implementação deve seguir o modelo SPMD. O objetivo é realizar a comunicação seguindo uma lógica de anel, guiado pelos identificadores de cada processo. Ou seja, o processo 0 deve enviar o token para o processo 1, ... Quando o token retornar para o processo 0, a execução é finalizada. Cada processo deve informar uma mensagem ao receber o token.

O código deverá ser implementado na infraestrutura experimental do LabP2D.

## Getting Started

``` sh
## build
make build
```

``` sh
## clean
make clean
```

``` sh
## run
make run
```

## Help

``` sh
mpicc -o bin/ring ring.c
mpirun --machinefile hosts mpi
mpirun --machinefile hosts -np 12 mpi
mpirun --machinefile hosts -np 12 --mca btl_tcp_if_include 10.20.221.0/24 mpi
```
