set title "html parsers benchmark"
set ylabel 'rss memory (mb)'
set yrange [0:]

set datafile separator ";"

set style data histogram
set style fill solid

set term png size 1920,1080
set output "result/mem.png"

plot "result/gumbo.csv"           using ($5/1000000): xtic(1) ti "gumbo",\
     "result/html5ever_rc.csv"    using ($5/1000000)          ti "html5ever (rc)",\
     "result/html5ever_arena.csv" using ($5/1000000)          ti "html5ever (arena)",\
     "result/myhtml.csv"          using ($5/1000000)          ti "myhtml",\
     "result/myhtml_single.csv"   using ($5/1000000)          ti "myhtml 1 thread"
