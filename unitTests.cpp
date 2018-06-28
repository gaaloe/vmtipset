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
    ASSERT(dotp[0] == MIBJ);
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

class whyVISTbad : public TestFixture<whyVISTbad>
{
  void setUp() {
  }
  void tearDown() {
  }
public:
  TEST_FIXTURE( whyVISTbad )
  {
    TEST_CASE( stmibo );
  }
  void stmibo()
  {
    e_team c[32] =
      {uru, rus, esp, por, fra, den, cro, arg, sui, bra, ger, swe, bel, eng, col, jpn, 
       por, esp, arg, den, sui, ger, bel, eng, 
       por, arg, ger, eng, 
       arg, ger, 
       por, 
       ger}; 

    ASSERT(253 == personMatch(TEST, c, 2));
  }
};
REGISTER_FIXTURE( whyVISTbad );

class whySTONY : public TestFixture<whySTONY>
{
  void setUp() {
  }
  void tearDown() {
  }
public:
  TEST_FIXTURE( whySTONY )
  {
    TEST_CASE( matchTheBest );
  }
  void matchTheBest()
  {
    e_team c[32] = {
      uru, rus, esp, por, fra, den, cro, arg, bra, sui, swe, mex, bel, eng, sen, col, 
      uru, rus, arg, den, bra, sui, col, eng, 
      rus, arg, bra, eng, 
      rus, bra, 
      eng, 
      bra 
    };
    ASSERT(517 == personMatch(STONY, c, 2));
    ASSERT(508 == personMatch(STJOKX, c, 2));
  }
};
REGISTER_FIXTURE( whySTONY );
