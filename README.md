Gerar arquivos com lista de adjacencias.

compile

gcc graph_generator.cc -lstdc++ -o generator

run

./generator num_vertex > lst.txt

OPENMP

Obter custo do menor caminho de todos os vertices para todos os vertices

compile

gcc serial_dijkstra.cc -lstdc++ -o serial

run

./serial num_vertex < lst.txt

Obter custo do menor caminho de todos os vertices para todos os vertices com execucao paralela

compile

gcc openmp_dijkstra -lstdc++ -fopenmp -o parallel

run

./parallel num_vertex < lst.txt


experimentos

compile

chmod +x script.sh

run

./script.sh

MPI
//mpirun --machinefile cluster.txt mpi num_vetex < lst.txt
//mpic++ mpi_dijkstra.cc -o mpi

