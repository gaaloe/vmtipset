#include "MiniCppUnit.hxx"
#include "manager_code.h"

class upperLeftIndented : public TestFixture<upperLeftIndented>
{
  void setUp() {
  }
  void tearDown() {
  }
public:
  TEST_FIXTURE( upperLeftIndented )
  {
    TEST_CASE( callStar );
  }
  void callStar()
  {
    e_team c[32] = {rus, uru, esp, irn, fra, aus, nga, cro,
		    srb, bra, swe, mex, eng, bel, col, jpn,
		    irn, uru, cro, aus, mex, bra, jpn, bel,
		    uru, cro, bra, jpn, uru, bra, cro, bra };
    e_person dotp[32];
    const int siz = whoMatchesBest(c, dotp, 2);
    ASSERT(siz == 1);
    ASSERT(dotp[0] == STMIBO);
  }
};
REGISTER_FIXTURE( upperLeftIndented );

