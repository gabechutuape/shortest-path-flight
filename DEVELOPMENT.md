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