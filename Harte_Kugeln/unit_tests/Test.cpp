#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "test_MatVec.h"
#include "test_Kugel.h"
#include "test_CollisionPair.h"
#include "test_Box.h"


void runSuite(int argc, char const *argv[]){
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<>  > lis(xmlfile.out);

	cute::makeRunner(lis,argc,argv)(make_suite_MatVec(), "MatVec");
	cute::makeRunner(lis,argc,argv)(make_suite_Kugel(), "Kugel");
	cute::makeRunner(lis,argc,argv)(make_suite_CollisionPair(), "CollisionPair");
	cute::makeRunner(lis,argc,argv)(make_suite_Box(), "Box");

}

int main(int argc, char const *argv[]){
    runSuite(argc,argv);
}



