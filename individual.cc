#include "individual.h"
#include <cstdlib> // for "NULL", "exit()"

individual::individual() {
  myGenome = NULL;
  numGenes = 0;
  myFitness = 0.0;
  maxValue = 0;
  minValue = 0;
}

individual::individual( const unsigned int nGenes,
			const int max,
			const int min ) {
  allocate_genome( nGenes );
  myFitness = 0.0;
  maxValue = max;
  minValue = min;
}

individual::~individual() {
  if( myGenome ) delete myGenome;
}

int
individual::operator [] ( const unsigned int index ) const {
  if( !myGenome ) return 0;
  if( index > numGenes ) return 0;
  return myGenome[index];
}

double
individual::get_my_fitness() const {
  return myFitness;
}

void
individual::set_max_min_values( const int max, const int min ) {
  if( max < min ) return;
  maxValue = max;
  minValue = min;
}

void
individual::set_value( const int value, const unsigned int index ) {
  if( index >= numGenes ) return;
  myGenome[index] = value;
}

void
individual::set_genome( int* input, const unsigned int nGenes ) {
  if( nGenes != numGenes ) return;
  if( nGenes < 0 ) return;
  for( int i=0; i<nGenes; i++ ) myGenome[i] = input[i];
}

void
individual::allocate_genome( const unsigned int nGenes ) {
  /// if the genome has already been allocated, skip because we want to
  /// prevent memory leaks.
  if( myGenome ) return;

  /// Allocate space for the genome now
  myGenome = new int[nGenes];

  /// if failed, something is REALLY wrong, so bail out of the entire
  /// program.
  if( !myGenome ) exit(-1);

  /// Assign the numGenes used later to nGenes.
  numGenes = nGenes;
}

void
individual::randomize_genome() {

  /// If there is no genome space allocated, do not do anything.
  if( !myGenome ) return;

  /// find the random number, divide it by RAND_MAX (defined in
  /// cstdlib) to find the range, multiply it by the difference
  /// between max and min values and then add it to minValue to get
  /// the correct scaled range.
  for( int i=0; i< numGenes; i++ ) {
    myGenome[i] = static_cast<int>(((rand()*1.0)/RAND_MAX)*(maxValue - minValue) + minValue);
  }
}

#include <cmath>
void
individual::calculate_fitness( int ** targetPicture,
			       const unsigned int nRows,
			       const unsigned int nCols ) {
  /// if the genome is not defined, then skip this step.
  if( !myGenome ) return;

  double difference = 0.0;
  myFitness = difference;
}

/// precondition: none, as whether the genome exists or not is checked
///               inside the function.
///
/// postcondition: given mRate probability, an element in the genome will
///                be changed to a randomly allowed value.
void
individual::mutate( double const mRate ) {

  // Check to make sure that the genome exists before trying to
  // manipulate it. Perhaps add a debug statement?
  if( !myGenome ) return;

  for( int i=0; i<numGenes; i++ ) {
    double random = ((rand() *1.0)/RAND_MAX);
    if( random < mRate ) {
      myGenome[i] = static_cast<int>((random * (maxValue - minValue)) + minValue);
    }

  }

}
