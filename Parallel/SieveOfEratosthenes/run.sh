#PBS -l nodes=1:ppn=12
echo "******************** Run with 1 processor ********************"
mpirun -np 1 ./Parallel/SieveOfEratosthenes/a.out
echo "******************** Run with 2 processor ********************"
mpirun -np 2 ./Parallel/SieveOfEratosthenes/a.out
echo "******************** Run with 4 processor ********************"
mpirun -np 4 ./Parallel/SieveOfEratosthenes/a.out
echo "******************** Run with 8 processor ********************"
mpirun -np 8 ./Parallel/SieveOfEratosthenes/a.out
echo "******************** Run with 10 processor ********************"
mpirun -np 10 ./Parallel/SieveOfEratosthenes/a.out
echo "******************** Run with 12 processor ********************"
mpirun -np 12 ./Parallel/SieveOfEratosthenes/a.out
