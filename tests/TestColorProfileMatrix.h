#ifndef TESTCOLORPROFILEMATRIX_H_
#define TESTCOLORPROFILEMATRIX_H_

#include "cpptest.h"
#include <utility>
#include <string>
#include <ostream>
#include <sstream>

#include "file_io/FastaParser.h"
#include "file_io/FastaMult.h"
#include "file_io/FastaRefID.h"
#include "file_io/FastaWriter.h"		// for writing FASTA files
#include "file_io/FastaFlowParser.h"

#include "graphs/ReferenceMap.h"
#include "graphs/CanonicalAntibodyGraph.h"
#include "graphs/CreateProfile.h"

using namespace std;

class TestColorProfileMatrix : public Test::Suite {
public:
    TestColorProfileMatrix();
    virtual ~TestColorProfileMatrix();

protected:
    virtual void setup();      		// setup resources...
    virtual void tear_down(); 		// remove resources...
    
    void test_cp_matrix_scores_1();
    void test_cp_matrix_scores_2();
    
    void test_cp_matrix_partition_1();
    
    CanonicalAntibodyGraph *cab;
};

#endif
