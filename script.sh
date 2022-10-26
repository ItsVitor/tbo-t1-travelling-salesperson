gcc main.c grafo.c UF.c -o prog -lm
time ./prog
./tsp_plot.py exemplos/in/d18512.tsp exemplos/mst/d18512.mst exemplos/tour/d18512.tour
./tsp_plot.py exemplos/in/d18512.tsp exemplos/out/d18512.mst exemplos/out/d18512.tour