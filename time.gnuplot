set title "html parsers benchmark"
set ylabel 'parse time (s)'
set yrange [0:]

set datafile separator ";"

set style fill solid 1.0 border 0
set style histogram errorbars gap 2 lw 2
set style data histogram

set term png size 1920, 1080
set output "result/time.png"

plot "result/gumbo.csv"           using 3:4: xtic(1) ti "gumbo",\
     "result/html5ever_rc.csv"    using 3:4          ti "html5ever (rc)",\
     "result/html5ever_arena.csv" using 3:4          ti "html5ever (arena)",\
     "result/myhtml.csv"          using 3:4          ti "myhtml",\
     "result/myhtml_single.csv"   using 3:4          ti "myhtml 1 thread"
