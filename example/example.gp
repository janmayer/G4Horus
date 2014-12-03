reset

set terminal pdf enhanced font 'Calibri'
set key top right
set key spacing 1.1

set title "Full energy and single escape peak efficiency"

set style line  1 lt 1 lw 2 lc rgb '#E41A1C' # red
set style line  2 lt 1 lw 2 lc rgb '#377EB8' # blue
set style line  3 lt 1 lw 2 lc rgb '#4DAF4A' # green
set style line  4 lt 1 lw 2 lc rgb '#984EA3' # purple
set style line  5 lt 1 lw 2 lc rgb '#FF7F00' # orange
set style line  6 lt 1 lw 2 lc rgb '#FFFF33' # yellow
set style line  7 lt 1 lw 2 lc rgb '#A65628' # brown
set style line  8 lt 1 lw 2 lc rgb '#F781BF' # pink

set style line 11 lt 2 lw 1.5 lc rgb '#E41A1C' # red
set style line 12 lt 2 lw 2 lc rgb '#377EB8' # blue
set style line 13 lt 2 lw 2 lc rgb '#4DAF4A' # green
set style line 14 lt 2 lw 2 lc rgb '#984EA3' # purple
set style line 15 lt 2 lw 2 lc rgb '#FF7F00' # orange
set style line 16 lt 2 lw 2 lc rgb '#FFFF33' # yellow
set style line 17 lt 2 lw 2 lc rgb '#A65628' # brown
set style line 18 lt 2 lw 2 lc rgb '#F781BF' # pink


set style line 111 lc rgb '#808080' lt 1
set border 3 back ls 111
set tics nomirror
set style line 112 lc rgb '#808080' lt 0 lw 1
set grid back ls 112

set ylabel 'absolute efficiency [%]'
set xlabel 'γ-ray energy [keV]'

set xrange [0:11000]
set yrange [0:*]

set output "example.pdf"

plot \
	'226Ra.dat'  u 1:6:7 with yerrorbars ls 1 title '^{226}Ra', \
	'56Co.dat'    u 1:6:7 with yerrorbars ls 2 title '^{56}Co', \
	'27Al-pg.dat' u 1:6:7 with yerrorbars ls 3 title '^{27}Al(p,γ)', \
	'16O.dat'     u 1:6:7 with yerrorbars ls 4 title '^{19}F(p,α)^{16}O', \
	'12C.dat'     u 1:6:7 with yerrorbars ls 5 title '^{12}C(p,p′γ)', \
	'Simulation.dat' u 1:($2*100) with steps ls 7 title 'Simulation', \
	'226Ra.dat'   u 1:11:12 with yerrorbars ls 11 notitle, \
	'56Co.dat'    u 1:11:12 with yerrorbars ls 12 notitle, \
	'27Al-pg.dat' u 1:11:12 with yerrorbars ls 13 notitle, \
	'16O.dat'     u 1:11:12 with yerrorbars ls 14 notitle, \
	'12C.dat'     u 1:11:12 with yerrorbars ls 15 notitle, \
	'Simulation.dat' u 1:($3*100) with steps ls 17 notitle

unset output
