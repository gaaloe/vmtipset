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
    TEST_CASE( stmibo );
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
  void stmibo()
  {
    e_team c[32] = {rus, uru, esp, irn, fra, aus, nga, cro,
		    srb, bra, swe, mex, eng, bel, col, jpn,
		    irn, uru, cro, aus, mex, bra, jpn, bel,
		    uru, cro, bra, jpn, uru, bra, cro, bra };
    const int score = personMatch(STMIBO, c, 2);
    ASSERT(score == 295 + scoreFromGroups[STMIBO]);
  }
};
REGISTER_FIXTURE( upperLeftIndented );

class exactLeftIndented : public TestFixture<exactLeftIndented>
{
  void setUp() {
  }
  void tearDown() {
  }
public:
  TEST_FIXTURE( exactLeftIndented )
  {
    TEST_CASE( stmibo );
  }
  void stmibo()
  {
    e_team c[32] =
      {rus, uru, por, esp, fra, aus, cro, arg, bra, sui, ger, mex, bel, eng, col, pol,
       rus, por, fra, cro, bra, ger, bel, eng,
       fra, cro, bra, eng,
       bra, eng,
       cro,
       bra};
    const int score = personMatch(STMIBO, c, 2);
    ASSERT(score == 520 + scoreFromGroups[STMIBO]);
    e_person dotp[32];
    const int siz = whoMatchesBest(c, dotp, 2);
    ASSERT(siz == 1);
    ASSERT(dotp[0] == STMIBO);
  }
};
REGISTER_FIXTURE( exactLeftIndented );
