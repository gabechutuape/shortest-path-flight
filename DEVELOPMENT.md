# Development Log

### Progress Fall Break
None.

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
shortest distance. Shortest distance would need implementation for PopulateAirportMapAndCodeToID so started work on that. Cleaned up the overall code a bit as well, added a few comments. 

### Progress 12/11 (dimitar3)
Bug Fixes: Added a check in shortest path function, changed to using relative file paths in test cases, made some functions public as necessary, moved structs to top of file to fix errors.

### Progress 12/11 (gfc2)
Bug Fix: I found out that we were parsing latitudes and longitudes when populating our map containing airport locations as INTEGERS and not DOUBLES. This has been rectified.  
Made a test case for PopulateAirportMapAndCodeToID. The test has two test nodes, with manually assigned information of airports, builds a map containing those nodes and 
an unordered map containing each airport ID and code. It then compares this information to the logic used in our PopulateAirportMapAndCodeToID function. Again, in this case
I copied the code of the function and not the actual function itself because I couldn't figure out how to pass an input file as an argument, since that isn't how the
function is used in our program anyways. I figure as long as the code is the same, the test is still valid.

### Progress 12/11 (rchaud9)
Made some new test cases. Wanted to test out the PopulateRouteMap. Made a simple test case that reads and makes a simple edge that takes and reads the input 
from a file and uses the same logic that the normal code would. Took a bit of bugfixing. Still not sure why it only works if 2+ lines are present. Similar to the above approach,
I used a copy of the code of the function and not the real function itself. It seemed to work for our purpose.

### Progress 12/11 (dimitar3)
Implemented the output of the information to the user, as well as input validation.
Created all the necessary functions in main.cpp to get the project to run.
Fixed some bugs in assembler.cpp.
Added error enum in assembler to help with error outputs in command line.

### Progress 12/11 (gfc2)
Implemented the test cases for FindShortestPath and FindLandMarkPath.  
In order to accomplish testing these, I wanted to prove that they could produce a double-ended queue of airport IDs that represent the path that you take from point A to point B.  
However, our project code would return text for the user to see in the form of a trip itinerary. So, I copied over the entirety of assembler.cpp/assembler.h into helper.cpp/helper.h and
renamed the Assembler class and all references to it to TestAssembler. Next, I had to produce 3 datasets for the TestAssembler constructor to use: an airports data file, an airlines
data file, and a routes data file. In order to do this, I needed to produce a graph that I would test things on. I settled on 4 nodes: ORD (O'Hare Int'l Airport), NRT (Narita Int'l Airport),
PVG (Shanghai Pudong Int'l Airport), and MNL (Manila Ninoy Aquino Airport). I chose these four because it's faster to get from O'Hare to Manila by stopping in Narita, versus stopping in Shanghai.
Therefore, I needed to grab the airport data from airports.dat from OpenFlights for these four airports and put them into my dataset. Then, I took the airlines that serviced these locations
(US, Japan, China, Philippines), and put them into my airline dataset. Lastly, knowing what airlines could take you from US->Japan or US->China and then Japan->Philippines or China->Philippines,
I was able to find all the routes that would be detected within routes.dat as valid, and copied those into my dataset. This was a lot of work on my end, and there may have been an easier way to
verify that we could successfully implement Dijkstra's algorithm, such as cooking down our code from assembler.cpp to a very basic version and making a very basic dataset. In terms of reusability
with testing other airports, it's very difficult to try new tests. You would need to do what I did entirely.
In terms of testing FindLandMarkPath, I simply wanted to see if it properly determined a path through ORD -> PVG -> MNL if it was given PVG as the required intermediate destination, as opposed to NRT.
FindLandMarkPath simply runs FindShortestPath twice, and I wanted the test case to produce a double-ended queue of those airport IDs produced by FindShortestPath.  
In the end, the code is slightly changed when copying from assembler.cpp/assembler.h to helper.cpp/helper.h, but in my opinion, it performs a successful test, and that's all I wanted.

## Progress 12/12 (FINAL) (rchaud9)
Recorded and finalized the presentation of our project. Overall went well. 