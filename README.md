# Shortest Path Flight Program
This program uses data from https://openflights.org/data.html to print an itinerary of flights to take in order to get from one airport to another.

## Usage
Using our program requires usage of the command line. To use the program, simply clone the repo and run make. After successfully compiling the program, run ./shortestpathflight.
```
make
./shortestpathflight
```
Upon running the executable, you will be prompted for an intermediate airport destination to be considered for your trip itinerary. Respond with Y if you wish to input one, and N if you do not care for a specific intermediate destination.
Afterwards, simply enter the IATA codes of your desired start, end, and optional intermediate airports.  
The program will print an itinerary for you to follow, as well as different airlines you can take from one airport to another if there are multiple options available.

![Image of program](https://media.discordapp.net/attachments/574865675907235862/787200465989140520/unknown.png "Landmark process")

The program has error handling for different cases, such as if you enter an airport that cannot be found, or if no route can be found between two airports.

![Image of error for no airport found](https://media.discordapp.net/attachments/574865675907235862/787202039242948608/unknown.png "No ending airport found")

![Image of error for no route](https://cdn.discordapp.com/attachments/574865675907235862/787201391809921024/unknown.png "No route found")

