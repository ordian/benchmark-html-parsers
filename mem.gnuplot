set title "html parsers benchmark"
set ylabel 'rss memory (mb)'
set datafile separator ";"
set style fill solid
set style histogram cluster gap 4
set tics font ",10"
set term png size 1920,1080
set output "result/mem.png"
plot "result/gumbo.csv" using ($4/1000000): xtic(1) with histogram ti "gumbo",\
     "result/html5ever_rc.csv" using ($4/1000000): xtic(1) with histogram ti "html5ever (rc)",\
     "result/html5ever_arena.csv" using ($4/1000000): xtic(1) with histogram ti "html5ever (arena)",\
     "result/myhtml.csv" using ($4/1000000): xtic(1) with histogram ti "myhtml",\
     "result/myhtml_single.csv" using ($4/1000000): xtic(1) with histogram ti "myhtml 1 thread"