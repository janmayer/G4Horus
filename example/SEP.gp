reset

set terminal pdf enhanced font 'Calibri'
set key top left
set key spacing 1.1

set title "Single escape peak efficiency with and without active hit rejection (veto)"

set style line 1 lt 1 lw 2 lc rgb '#A6CEE3' # light blue
set style line 2 lt 1 lw 2 lc rgb '#1F78B4' # dark blue
set style line 3 lt 1 lw 2 lc rgb '#B2DF8A' # light green
set style line 4 lt 1 lw 2 lc rgb '#33A02C' # dark green
set style line 5 lt 1 lw 2 lc rgb '#FB9A99' # light red
set style line 6 lt 1 lw 2 lc rgb '#E31A1C' # dark red
set style line 7 lt 1 lw 2 lc rgb '#FDBF6F' # light orange
set style line 8 lt 1 lw 2 lc rgb '#FF7F00' # dark orange

set style line 11 lt 2 lw 2 lc rgb '#A6CEE3' # light blue
set style line 12 lt 2 lw 2 lc rgb '#1F78B4' # dark blue
set style line 15 lt 2 lw 2 lc rgb '#FB9A99' # light red
set style line 16 lt 2 lw 2 lc rgb '#E31A1C' # dark red


set style line 111 lc rgb '#808080' lt 1
set border 3 back ls 111
set tics nomirror
set style line 112 lc rgb '#808080' lt 0 lw 1
set grid back ls 112

set ylabel 'absolute efficiency [%]'
set xlabel 'γ-ray energy [keV]'

set xrange [0:10000]
set mxtics 4
set yrange [0:0.03]
set ytics 0.01
set mytics 4

set output "SEP.pdf"

plot \
	'226Ra.dat'   u 1:11:12 with yerrorbars ls  1 notitle, \
	'56Co.dat'    u 1:11:12 with yerrorbars ls 11 notitle, \
	'27Al-pg.dat' u 1:11:12 with yerrorbars ls  7 notitle, \
	'16O.dat'     u 1:11:12 with yerrorbars ls  5 notitle, \
	'12C.dat'     u 1:11:12 with yerrorbars ls 15 notitle, \
	'Simulation.dat' u 1:($3*100) with steps ls 3 notitle, \
	'226Ra_veto.dat'   u 1:11:12 with yerrorbars ls  2 title '^{226}Ra', \
	'56Co_veto.dat'    u 1:11:12 with yerrorbars ls 12 title '^{56}Co', \
	'27Al-pg_veto.dat' u 1:11:12 with yerrorbars ls  8 title '^{27}Al(p,γ)', \
	'16O_veto.dat'     u 1:11:12 with yerrorbars ls  6 title '^{19}F(p,α)^{16}O', \
	'12C_veto.dat'     u 1:11:12 with yerrorbars ls 16 title '^{12}C(p,p′γ)', \
	'Simulation_veto.dat' u 1:($3*100) with steps ls 4 title 'Simulation'

unset output
