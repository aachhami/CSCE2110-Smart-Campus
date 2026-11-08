Smart Campus Navigation and Facility Analytics System | CSCE 2110 Milestone 1

This C++ console program loads campus records, looks up facilities by ID,
explores building connections, and maintains a department hierarchy in memory.

Build on Linux / UNT CELL from the project root:
    g++ -std=c++17 -Wall -Wextra -Wpedantic Main.cpp -o campus
Run with the instructor data:
    ./campus
Run with a different data directory:
    ./campus testdata/validation
Run the missing-file scenario:
    ./campus testdata/missing
Use 10 to exit. The program also accepts 0 per UI-7.

Main.cpp coordinates startup and the interactive menu. Input.h handles text
normalization, field splitting, file warnings and summaries. Facilities.h,
HashTable.h, CampusGraph.h and DepartmentTree.h implement the four modules.
data/ contains the unchanged instructor files. testdata/validation/ contains
additional inputs. design_document.txt describes implementation choices.
test_results.txt records local test runs. CONTRIBUTIONS.txt is the team record.

Quick live demo: start with the instructor data. Use 1 to list facilities and
2 to search for f004, 004 and F999. Use 3 and 4 to inspect the graph, then 5
from Library and Observatory. Use 6 to add Design under University, 7 to find
it, and 8 and 9 to compare the two displays. Enter text at the menu to show
recovery. Exit and restart with testdata/validation to show collision and
duplicate diagnostics. Restart with testdata/missing to create a root.
