gcc main.c grafo.c UF.c -o prog -lm
./prog
./tsp_plot.py exemplos/in/pr1002.tsp exemplos/mst/pr1002.mst exemplos/opt/pr1002.opt.tour
./tsp_plot.py exemplos/in/pr1002.tsp exemplos/out/pr1002.mst exemplos/out/pr1002.tour