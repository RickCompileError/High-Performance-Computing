#PBS -l nodes=1:ppn=12
for ((i=1;i<=12;i=i+1))
do
	echo "******************** Run with $i processor ********************"
	mpirun -np $i ./Parallel/Matrix/a.out
done
