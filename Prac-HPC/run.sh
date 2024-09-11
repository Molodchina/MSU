ARGC=$#
EXP_ARGC=1

rm *.err
module load SpectrumMPI

if [ $ARGC -eq $EXP_ARGC ]; then 
	mpixlc mpi_heat-3d.c -o mpi_heat-3d -D$1
	echo "[+] Execute mpi_heat-3d.c with $1"
else 
	mpixlc mpi_heat-3d.c -o mpi_heat-3d
	echo "[+] Execute mpi_heat-3d.c by default"
fi;

bsub < tasks
