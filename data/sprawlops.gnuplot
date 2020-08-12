set yrange [0:100000]
set xlabel "Dice"
set ylabel "Number of occurrences"
set style line 1 lw 5
set terminal png

set title "Difficulty 1"
set output "Difficulty1.png"
plot 'results100k.csv' every ::0::9 using 1:3 with linespoints title "Success",\
 'results100k.csv' every ::0::9 using 1:4 with linespoints title "Failure",\
 'results100k.csv' every ::0::9 using 1:5 with linespoints title "Wound",\
 'results100k.csv' every ::0::9 using 1:6 with linespoints title "Death"
set title "Difficulty 2"
set output "Difficulty2.png"
plot 'results100k.csv' every ::10::19 using 1:3 with linespoints title "Success",\
 'results100k.csv' every ::10::19 using 1:4 with linespoints title "Failure",\
 'results100k.csv' every ::10::19 using 1:5 with linespoints title "Wound",\
 'results100k.csv' every ::10::19 using 1:6 with linespoints title "Death"
set title "Difficulty 3"
set output "Difficulty3.png"
plot 'results100k.csv' every ::20::29 using 1:3 with linespoints title "Success",\
 'results100k.csv' every ::20::29 using 1:4 with linespoints title "Failure",\
 'results100k.csv' every ::20::29 using 1:5 with linespoints title "Wound",\
 'results100k.csv' every ::20::29 using 1:6 with linespoints title "Death"
set title "Difficulty 4"
set output "Difficulty4.png"
plot 'results100k.csv' every ::30::39 using 1:3 with linespoints title "Success",\
 'results100k.csv' every ::30::39 using 1:4 with linespoints title "Failure",\
 'results100k.csv' every ::30::39 using 1:5 with linespoints title "Wound",\
 'results100k.csv' every ::30::39 using 1:6 with linespoints title "Death"
set title "Difficulty 5"
set output "Difficulty5.png"
plot 'results100k.csv' every ::40::49 using 1:3 with linespoints title "Success",\
 'results100k.csv' every ::40::49 using 1:4 with linespoints title "Failure",\
 'results100k.csv' every ::40::49 using 1:5 with linespoints title "Wound",\
 'results100k.csv' every ::40::49 using 1:6 with linespoints title "Death"

set title "Difficulty 1 with 1 armor"
set output "Difficulty1a1.png"
plot 'results100ka1.csv' every ::0::9 using 1:3 with linespoints title "Success",\
 'results100ka1.csv' every ::0::9 using 1:4 with linespoints title "Failure",\
 'results100ka1.csv' every ::0::9 using 1:5 with linespoints title "Wound",\
 'results100ka1.csv' every ::0::9 using 1:6 with linespoints title "Death"
set title "Difficulty 2 with 1 armor"
set output "Difficulty2a1.png"
plot 'results100ka1.csv' every ::10::19 using 1:3 with linespoints title "Success",\
 'results100ka1.csv' every ::10::19 using 1:4 with linespoints title "Failure",\
 'results100ka1.csv' every ::10::19 using 1:5 with linespoints title "Wound",\
 'results100ka1.csv' every ::10::19 using 1:6 with linespoints title "Death"
set title "Difficulty 3 with 1 armor"
set output "Difficulty3a1.png"
plot 'results100ka1.csv' every ::20::29 using 1:3 with linespoints title "Success",\
 'results100ka1.csv' every ::20::29 using 1:4 with linespoints title "Failure",\
 'results100ka1.csv' every ::20::29 using 1:5 with linespoints title "Wound",\
 'results100ka1.csv' every ::20::29 using 1:6 with linespoints title "Death"
set title "Difficulty 4 with 1 armor"
set output "Difficulty4a1.png"
plot 'results100ka1.csv' every ::30::39 using 1:3 with linespoints title "Success",\
 'results100ka1.csv' every ::30::39 using 1:4 with linespoints title "Failure",\
 'results100ka1.csv' every ::30::39 using 1:5 with linespoints title "Wound",\
 'results100ka1.csv' every ::30::39 using 1:6 with linespoints title "Death"
set title "Difficulty 5 with 1 armor"
set output "Difficulty5a1.png"
plot 'results100ka1.csv' every ::40::49 using 1:3 with linespoints title "Success",\
 'results100ka1.csv' every ::40::49 using 1:4 with linespoints title "Failure",\
 'results100ka1.csv' every ::40::49 using 1:5 with linespoints title "Wound",\
 'results100ka1.csv' every ::40::49 using 1:6 with linespoints title "Death"

set title "Difficulty 1 with 1 reroll"
set output "Difficulty1r1.png"
plot 'results100kr1.csv' every ::0::9 using 1:3 with linespoints title "Success",\
 'results100kr1.csv' every ::0::9 using 1:4 with linespoints title "Failure",\
 'results100kr1.csv' every ::0::9 using 1:5 with linespoints title "Wound",\
 'results100kr1.csv' every ::0::9 using 1:6 with linespoints title "Death"
set title "Difficulty 2 with 1 reroll"
set output "Difficulty2r1.png"
plot 'results100kr1.csv' every ::10::19 using 1:3 with linespoints title "Success",\
 'results100kr1.csv' every ::10::19 using 1:4 with linespoints title "Failure",\
 'results100kr1.csv' every ::10::19 using 1:5 with linespoints title "Wound",\
 'results100kr1.csv' every ::10::19 using 1:6 with linespoints title "Death"
set title "Difficulty 3 with 1 reroll"
set output "Difficulty3r1.png"
plot 'results100kr1.csv' every ::20::29 using 1:3 with linespoints title "Success",\
 'results100kr1.csv' every ::20::29 using 1:4 with linespoints title "Failure",\
 'results100kr1.csv' every ::20::29 using 1:5 with linespoints title "Wound",\
 'results100kr1.csv' every ::20::29 using 1:6 with linespoints title "Death"
set title "Difficulty 4 with 1 reroll"
set output "Difficulty4r1.png"
plot 'results100kr1.csv' every ::30::39 using 1:3 with linespoints title "Success",\
 'results100kr1.csv' every ::30::39 using 1:4 with linespoints title "Failure",\
 'results100kr1.csv' every ::30::39 using 1:5 with linespoints title "Wound",\
 'results100kr1.csv' every ::30::39 using 1:6 with linespoints title "Death"
set title "Difficulty 5 with 1 reroll"
set output "Difficulty5r1.png"
plot 'results100kr1.csv' every ::40::49 using 1:3 with linespoints title "Success",\
 'results100kr1.csv' every ::40::49 using 1:4 with linespoints title "Failure",\
 'results100kr1.csv' every ::40::49 using 1:5 with linespoints title "Wound",\
 'results100kr1.csv' every ::40::49 using 1:6 with linespoints title "Death"

set title "Difficulty 1"
set output "Difficulty1scomp.png"
plot 'results100k.csv' every ::0::9 using 1:3 with linespoints title "Success (plain)",\
 'results100ka1.csv' every ::0::9 using 1:3 with linespoints title "Success (1 armor)",\
 'results100kr1.csv' every ::0::9 using 1:3 with linespoints title "Success (1 reroll)",\
 'results100k.csv' every ::0::9 using 1:($5+$6) with linespoints title "Wound/Death (plain)",\
 'results100ka1.csv' every ::0::9 using 1:($5+$6) with linespoints title "Wound/Death (1 armor)",\
 'results100kr1.csv' every ::0::9 using 1:($5+$6) with linespoints title "Wound/Death (1 reroll)"
set title "Difficulty 2"
set output "Difficulty2scomp.png"
plot 'results100k.csv' every ::10::19 using 1:3 with linespoints title "Success (plain)",\
 'results100ka1.csv' every ::10::19 using 1:3 with linespoints title "Success (1 armor)",\
 'results100kr1.csv' every ::10::19 using 1:3 with linespoints title "Success (1 reroll)",\
 'results100k.csv' every ::10::19 using 1:($5+$6) with linespoints title "Wound/Death (plain)",\
 'results100ka1.csv' every ::10::19 using 1:($5+$6) with linespoints title "Wound/Death (1 armor)",\
 'results100kr1.csv' every ::10::19 using 1:($5+$6) with linespoints title "Wound/Death (1 reroll)"
set title "Difficulty 3"
set output "Difficulty3scomp.png"
plot 'results100k.csv' every ::20::29 using 1:3 with linespoints title "Success (plain)",\
 'results100ka1.csv' every ::20::29 using 1:3 with linespoints title "Success (1 armor)",\
 'results100kr1.csv' every ::20::29 using 1:3 with linespoints title "Success (1 reroll)",\
 'results100k.csv' every ::20::29 using 1:($5+$6) with linespoints title "Wound/Death (plain)",\
 'results100ka1.csv' every ::20::29 using 1:($5+$6) with linespoints title "Wound/Death (1 armor)",\
 'results100kr1.csv' every ::20::29 using 1:($5+$6) with linespoints title "Wound/Death (1 reroll)"
set title "Difficulty 4"
set output "Difficulty4scomp.png"
plot 'results100k.csv' every ::30::39 using 1:3 with linespoints title "Success (plain)",\
 'results100ka1.csv' every ::30::39 using 1:3 with linespoints title "Success (1 armor)",\
 'results100kr1.csv' every ::30::39 using 1:3 with linespoints title "Success (1 reroll)",\
 'results100k.csv' every ::30::39 using 1:($5+$6) with linespoints title "Wound/Death (plain)",\
 'results100ka1.csv' every ::30::39 using 1:($5+$6) with linespoints title "Wound/Death (1 armor)",\
 'results100kr1.csv' every ::30::39 using 1:($5+$6) with linespoints title "Wound/Death (1 reroll)"
set title "Difficulty 5"
set output "Difficulty5scomp.png"
plot 'results100k.csv' every ::40::49 using 1:3 with linespoints title "Success (plain)",\
 'results100ka1.csv' every ::40::49 using 1:3 with linespoints title "Success (1 armor)",\
 'results100kr1.csv' every ::40::49 using 1:3 with linespoints title "Success (1 reroll)",\
 'results100k.csv' every ::40::49 using 1:($5+$6) with linespoints title "Wound/Death (plain)",\
 'results100ka1.csv' every ::40::49 using 1:($5+$6) with linespoints title "Wound/Death (1 armor)",\
 'results100kr1.csv' every ::40::49 using 1:($5+$6) with linespoints title "Wound/Death (1 reroll)"
