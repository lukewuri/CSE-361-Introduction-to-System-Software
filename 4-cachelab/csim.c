//Name: Luke Wuri
//WUSTL Key: lwuri
//WUSTL ID: 445002

#include "cachelab.h"
#include <stdlib.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h>

  typedef enum {
    false,
    true
  }
bool;

FILE * tracefile;

int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;

//trace codes
char instr;

//initializing B and S to calculate later on
int B = 1;
int S = 1;

int s = 0; //2^s is number of sets, S
int E = 0; //Number of lines per set
int b = 0; //2^b is block size, B
char * t = ""; //trace file name

//Optional Inputs
bool h = false;
bool v = false;

//how many total reads, hits+miss so far,
int p = 0;

//struct to represent our individual cache line
struct cacheline {
  unsigned long long tag; //tag for the each line, very large to hold as much as we need potentially
  int update; //used to compare to p to see how often the line was changed
  bool occupied; // if a line is occupied or not
};
struct cacheline * sim;

void dataload(char * thing) {
  unsigned long long actualaddress = 0;
  p += 1;
  int lru = p;
  int incr = -1;
  sscanf(thing + 0, "%llx", & actualaddress); //get our address as an unsigned long long
  unsigned long long tag = actualaddress / B; //we are only interested in comparing tags
  int index = E * (tag & (S - 1)); //points to the first line


  for (int iter = 0; iter < E; iter++) //iterate through the line of our cache to see if our we have hits with the address we passed in
  {
    if (sim[index + iter].occupied == true) //we will only have hits potentially if the line is occupied
    {
      if (!(sim[index + iter].update >= lru)) //if the least recently used is less than the time of the current index
      {
        lru = sim[index + iter].update;
        incr = iter;
      }
      if (sim[index + iter].tag == tag) //if tags match, then we have a hit and we can exit the method
      {
        sim[index + iter].update = p;
        hit_count++;
        return;
      }

    }
    if (sim[index + iter].occupied == false) //line is unoccupied, leave the for loop
    {
      incr = iter;
      lru = p;
      break;
    }
  }
  if (!(lru == p)) { //if the least recently used is not equal to the pointer
    eviction_count++;
  }
  sim[index + incr].update = p; //align the timing
  sim[index + incr].occupied = true;
  sim[index + incr].tag = tag;
  miss_count++; //miss if we do not have a hit
}

void datastore(char * thing) {
  dataload(thing);
}

void datamodify(char * thing) {
  dataload(thing);
  datastore(thing);
}

int main(int argc, char * argv[]) {

  //https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
  //Reference for getting command line input
  //Gets command prompt input
  //Input style:         ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>
  int arg;
  while ((arg = getopt(argc, argv, "s:E:b:t:hv")) != -1)
    switch (arg) {
    case 's':
      s = atoi(optarg);
      break;
    case 'E':
      E = atoi(optarg);
      break;
    case 'b':
      b = atoi(optarg);
      break;
    case 't':
      t = optarg;
      break;
    case 'h':
      h = atoi(optarg);
      break;
    case 'v':
      v = atoi(optarg);
      break;
    default:
      printf("Error with input");
      break;
    }

  for (int y = 0; y < b; y++) {
    B *= 2;
  }

  for (int r = 0; r < s; r++) {
    S *= 2;
  }

  int cachesize = sizeof(struct cacheline) * S * E;

  tracefile = fopen(t, "r"); //open our trace file using read only
  //the following section saves the ENTIRE trace file into the big array.
  char thing[1000]; //line by line
  char big[3000000][1000]; //contains our entire file
  int i = 0;
  while (fgets(thing, 1000, tracefile) != NULL) {
    strcpy(big[i], thing);
    ++i;
  }
  fclose(tracefile); //close file
  sim = (struct cacheline * ) calloc(10, cachesize); //allocate memory and clear 

  for (int x = 0; x < 300000; x++) {
    char address2[1000] = {
      0
    }; //address2 contains what we will pass into our methods, and also
    if (big[x][0] == ' ') //Ignore I, instructions
    {
      instr = big[x][1]; //get the letter for our switch statement
      char * address = strchr(big[x] + 2, ' '); //remove the Letter from the trace line
      int k = 0;
      while (address[k] != ',') { //remove everything after the comma from the traceline
        address2[k] = address[k];
        k++;
      }

      //Switch statement to do the various methods as described in the lab handout
      switch (instr) {
      case 'M':
        datamodify(address2);
        break;
      case 'L':
        dataload(address2);
        break;
      case 'S':
        datastore(address2);
        break;
      default:
        break;
      }
    }
  }
  printSummary(hit_count, miss_count, eviction_count);
  return 0;
}
