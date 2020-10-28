#/bin/bash
echo "Experimentos. Iniciados" >> output.txt
#compilar
gcc graph_generator.cc -lstdc++ -o generator
echo "Gerador de grafos compilado" >> output.txt
gcc serial_dijkstra.cc -lstdc++ -o serial
echo "Serial compilado" >> output.txt
gcc openmp_dijkstra.cc -lstdc++ -fopenmp -o parallel
echo "Paralelo compilado" >> output.txt
#gerar grafos
./generator 50 >50.txt
echo "Criado grafo com 50 vertices." >> output.txt
./generator 100 >100.txt
echo "Criado grafo com 100 vertices." >> output.txt
./generator 150 >150.txt
echo "Criado grafo com 150 vertices." >> output.txt
./generator 200 >200.txt
echo "Criado grafo com 200 vertices." >> output.txt
#execucao serial com 200 vertices
echo "Executando código serial" >> output.txt
for i in {1. .10}
do
    time ./serial 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
#execucao por numero de threads
echo "Executando código paralelo com 2 threads" >> output.txt
export OMP_NUM_THREADS=2
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando código paralelo com 3 threads" >> output.txt
export OMP_NUM_THREADS=3
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando código paralelo com 4 threads" >> output.txt
export OMP_NUM_THREADS=4
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando código paralelo com 5 threads" >> output.txt
export OMP_NUM_THREADS=5
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando código paralelo com 6 threads" >> output.txt
export OMP_NUM_THREADS=6
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando código paralelo com 7 threads" >> output.txt
export OMP_NUM_THREADS=7
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando código paralelo com 8 threads" >> output.txt
export OMP_NUM_THREADS=8
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
#execucao com carga dados diferente
echo "Executando codigo paralelo com grafos de 50 vertices" >> output.txt
for i in {1. .10}; do
    time ./parallel 50 <50.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando codigo paralelo com grafos de 100 vertices" >> output.txt
for i in {1. .10}; do
    time ./parallel 100 <100.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando codigo paralelo com grafos de 150 vertices" >> output.txt
for i in {1. .10}; do
    time ./parallel 150 <150.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Executando codigo paralelo com grafos de 200 vertices" >> output.txt
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
#execucao com clausula schedule
export OMP_NUM_THREADS=8
export OMP_SCHEDULE= static,200/8

echo "Executando com clausula schedule static,num_vertices/8" >> output.txt
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
export OMP_SCHEDULE= dynamic
echo "Executando com clausula schedule dynamic" >> output.txt
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1) 
    echo "$var" >> output.txt
done
export OMP_SCHEDULE= guided
echo "Executando com clausula schedule guided" >> output.txt
for i in {1. .10}; do
    time ./parallel 200 <200.txt
    var=$({ time; } 2>&1)
    echo "$var" >> output.txt
done
echo "Experimentos executados com sucesso!" >> output.txt
