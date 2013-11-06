#include "pictureGA.h"
#include <fstream>
#include <string>

#include <iostream>
#include <cstdlib>
using namespace std;

pictureGA::pictureGA() {
  numIndividuals = 0;
  generation = NULL;
  /*!
    1. get the target picture with the default filename "picture.in"
    2. allocate the initial population and then randomize them.
  */

  /*! Notes:
     1. Need to input the value for numIndividuals somewhere!
     2. Need to find the max and min allowed values for the genome
     from somewhere! Should it be from reading the target picture, or
     raw possible greyscale values, assuming a single byte per pixel?
  */
  input_target_picture();

  cout << "\nHow many individuals would you like to have within the generation?\n";
  cin >> numIndividuals;

  generation = new individual[numIndividuals];
  for( int i=0; i<numIndividuals; i++ ) {
    generation[i].allocate_genome( nRows * nCols );
    generation[i].randomize_genome();
    generation[i].set_max_min_values(currentMax, currentMin); //!< This will set the mac and the min values for the individual of the generation
  }
}

pictureGA::~pictureGA() {
  if( targetPicture ) {
    for( int i=0; i<nRows; i++ )
      if( targetPicture[i] ) delete [] targetPicture[i];
    delete [] targetPicture;
  }
  if( generation ) delete [] generation;
}

void
pictureGA::go() {
  int numGeneration = 0;
  double fitnessDifference = 0;
  do {
    /*! Inside the do-while loop
      1. assess fitness of each individual, set the global
      differences between everyone to fitnessDifference (this
      measures convergence)
      2. roulettify to select the two top parents
      3. generate next population
      4. mutate the new population
    */
    numGeneration ++;
  } while ( numGeneration < 100 && fitnessDifference > 0.1 );
}

/***********************************************************
 *  PRIVATE MEMBER FUNCTIONS
 ***********************************************************/
void
pictureGA::input_target_picture() {

  ifstream inFile;

  string filename;
  cout << "Please enter your input file:\n";
  cin >> filename;
  inFile.open( filename.c_str());

  if( inFile.fail() ) {
    cout << "Error opening " << filename << endl;
    exit(1);
  }

  /*!
    1. Open the file after asking the user for the filename. There are
    several error-checking going on.
    2. Read the size of the image (number of rows and columns ) as
    the first two numbers in this file.
    3. Allocate the rows
    4. For each row, create the columns and then read the values int them
  */
  inFile >> nRows;
  inFile >> nCols;

  targetPicture = new int*[nRows];
  if( !targetPicture ) {
    cout << "Error allocating targetPicture!\n";
    exit(2);
  }

  for( int i=0; i<nRows; i++ ) {
    targetPicture[i] = new int[nCols];
    for( int j=0; j<nCols; j++ )  {
      inFile >> targetPicture[i][j];
      if(targetPicture[i][j]>currentMax) currentMax = targetPicture[i][j];
      if(targetPicture[i][j]<currentMin) currentMin = targetPicture[i][j];
    }
  }

  inFile.close();
}

void
pictureGA::calculate_fitnesses() {
  /// You must implement this function
}

void
pictureGA::roulettify() {

  double* rouletteValues = new double[numIndividuals];
  double rouletteSoFar(0);
  // calculate fitnesses
  // use fitness (0 - 255) to find percent on roulette
  // find the sum and divide each fitness by that sum
  calculate_fitnesses();

  // find the total fitness before dividing.
  double totalFitness = 0;
  for( int i =0; i<numIndividuals; i++ )
    totalFitness+=generation[i].get_my_fitness();

  for( int i =0; i<numIndividuals; i++ )
    rouletteValues[i] = 0.0;

  for( int i =0; i<numIndividuals; i++ ) {
    rouletteSoFar += generation[i].get_my_fitness()/totalFitness;
    rouletteValues[i] = rouletteSoFar;
  }

  // Once the roulette values are in place, find the parent indices
  parent1 = 0;
  parent2 = 0;

  // To find P1 and P2, we need to generate two random numbers from 0
  // to 100. Because the total of all the candidates' fitness is 100%,
  // picking somewhere in the range would give the parents. A nuance
  // is that the parents have to be different, so the indices must be
  // checked to be different.

}

void
pictureGA::spawn() {

  unsigned int child1(0), child2(1);       // children indices
  unsigned int p1(parent1), p2(parent2);   // parent indices
  unsigned int crossover(0);
  unsigned int i(0);

  /// You must implement this function; the given variables are suggestions
}

void
pictureGA::irradiate() {

  /// For every individual except the elite parents
  /// 1. see if they are to be mutated (their chance < mutationRate)
  /// 2. if so, completely randomize the values in their genetic sequence.

}
