# CS 225 Data Structures
## Project Goals (rchaud9 - gfc2 - dimitar3)

## Dataset
- Our dataset of interest is the OpenFlights open source dataset of flight routes and
airports, from ​ https://openflights.org/data.html​.  
##Abstract Goal
- Our goal, at an abstract level of explanation, is to use this dataset of flight routes
and airports to discover shortest paths between airports.  
##Traversal and Algorithms
- Our chosen traversal for this project is the breadth first search. This is because it
has greater efficacy in finding the shortest path between vertices compared to the
depth first search. This idea presents itself as applicable to our project
specifications, so we chose it.
- Our chosen algorithms are Dijkstra’s algorithm and the Landmark Path algorithm.
	- We chose Dijkstra’s algorithm because, in searching for algorithms that
	would be appropriate for our goal of finding shortest paths between
	airports, our group members showed more familiarity with Dijkstra’s
	algorithm as opposed to the alternative Floyd-Warshall algorithm. We find
	its considerably low complexity favorable for our goal.
	- We chose the Landmark Path algorithm because, upon inspection, it
	provides functionality that accomplishes our goal. Additionally, it provides
	an interesting perspective on the data in the form of requiring an
	intermediary airport of travel in between getting from one airport to
	another. This could be abstracted into the idea of stopping in a country to
	visit a relative while making a business trip.
