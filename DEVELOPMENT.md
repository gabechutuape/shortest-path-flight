# Development Log

### Progress 12/4 (gfc2)
Today, I added the required data files for the project to work, those being the 
routes, airlines, and airports from OpenFlights. I also added the logic for parsing lines of data from
CSV files into our master logic file, which is called "assembler.cpp". Lastly, I added a TODO.md for 
project cohesion and I copied our project goals to our README.md so that our GitHub wouldn't look barren when you clicked on it.

### Progress 12/4 (dimitar3)
I created the assembler class and associated header and cpp files. I implemented the ctor, copy ctor, copy assignment and destructor
for this class. As well as creating the three instance variables for file names for our three data files.

### Progress 12/5 (dimitar3)
Created and implemented a function that calculates distance between two points on Earth using haversine formula.
Created a hash map that maps airline ids to airline names and a function that populates that map using airline_file_.
Created a map that maps airport ids to nodes and a hash map that maps airport codes to ids and 
a function that populates both using airport_file_.
Created structs for nodes and edges to be used in graph later. 

### Progress 12/8 (dimitar3)
Created and implemented a function that reads from route_file_ and populates a new hashmap "route_map_". This
is our adjacency list. Modified edge node to include more data for the route_map_, which maps airline id's to 
edges (routes).

### Progress 12/9 (dimitar3)
Created a function that finds edges between nodes. Implemented Dijkstra's algorithm to find shortest path between airports
using route_map_ as the adjacency list for the graph. This function returns a vector of strings containing info about which route is taken and how much distance between them. I created a helper function that populates this vector of strings. Using the shortest path algo, I implemented a landmark path function. Then I added to the delete function and created the copy function.  


### Progress 12/9 (rchaud9)
Made and implemented a Makefile.
This makefile basically used the original CS225 template (with some modifications) and includes the compilation for the test cases as well.
In testing it, a few issues with bugs came up, but it was nothing too severe that I had to change. There were some syntax issues, and a few functions that had one or two small things
such as a variable type that needed fixing. Also started looking into the test file but didn't get to actually making it.

### Progress 12/9 and 12/10 (gfc2)
Created the testfile, updated makefile.  
In order for our testfile to test the helper functions of the main code working properly, I found it easiest to
copy the private helper functions over to a new file, helper.cpp and helper.h. This is how tests work. It relies upon
consistency between assembler.cpp/assembler.h and helper.cpp/helper.h.  
Implemented 3 different tests for parsing CSV lines (basic values, values containing commas, sample airport data).  
Implemented 2 tests for using the Haversine formula for calculating distance (two points, and the same point).
I needed to figure out how to compare two doubles. I accomplished this using an error tolerance value.  
Implemented a test for checking if PopulateIdToMap properly took the first two values from a CSV line and put
them into an unordered_map.  
Currently, we have 9 assertions and 6 test cases. The next tests I would like to have are for shortest distance, and whether or not it actually works.

### Progress 12/10 (rchaud9)
Worked some more on the testfile. We have good tests, but we still need to test for the actual program, as in testing for 
shortest distance. 