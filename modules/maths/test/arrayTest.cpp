#include <cxxtest/TestDrive.h>

#include <openma/maths.h>

CXXTEST_SUITE(ArrayTest)
{
  CXXTEST_TEST(assignment)
  {
    ma::maths::Vector a(10);
    a.values() << -1.0 , -1.0 , -1.0 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.5 ,  0.5 ,  0.5 , 
                   0.5 ,  0.5 ,  0.5 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.65,  0.65,  0.65, 
                   0.45,  0.45,  0.45, 
                   1.0 ,  1.0 ,  1.0 , 
                   0.0 ,  0.0 ,  0.0 , 
                  -0.4 , -0.4 , -0.4;
    a.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    ma::maths::Vector b = a;
    for (int i = 0 ; i < 30 ; ++i)
      TS_ASSERT_EQUALS(a.values().data()[i], b.values().data()[i]);
    for (int i = 0 ; i < 10 ; ++i)
      TS_ASSERT_EQUALS(a.residuals().data()[i], b.residuals().data()[i]);
  };
  
  CXXTEST_TEST(norm)
  {
    ma::maths::Vector a(10);
    a.values() << -1.0 , -1.0 , -1.0 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.5 ,  0.5 ,  0.5 , 
                   0.5 ,  0.5 ,  0.5 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.65,  0.65,  0.65, 
                   0.45,  0.45,  0.45, 
                   1.0 ,  1.0 ,  1.0 , 
                   0.0 ,  0.0 ,  0.0 , 
                  -0.4 , -0.4 , -0.4;
    a.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    
    ma::maths::Scalar b = a.norm();

    TS_ASSERT_DELTA(b.values().coeff(0), 0.0, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(1), 1.732050807568877, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(2), 0.866025403784439, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(3), 0.866025403784439, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(4), 1.732050807568877, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(5), 1.12583302491977, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(6), 0.779422863405995, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(7), 1.732050807568877, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(8), 0.0, 1e-15);
    TS_ASSERT_DELTA(b.values().coeff(9), 0.0, 1e-15);

    TS_ASSERT_EQUALS(b.residuals().coeff(0), -1.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(1), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(2), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(3), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(4), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(5), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(6), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(7), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(8), 0.0);
    TS_ASSERT_EQUALS(b.residuals().coeff(9), -1.0);
  };
  
  CXXTEST_TEST(mean)
  {  
    ma::maths::Scalar a(10), b(10);
    ma::maths::Position c(10);
    a.values() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    a.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    b.values() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    b.residuals().setConstant(10,-1.0);
    c.values() << -1.0 , -1.0 , -1.0 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.5 ,  0.5 ,  0.5 , 
                   0.5 ,  0.5 ,  0.5 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.65,  0.65,  0.65, 
                   0.45,  0.45,  0.45, 
                   1.0 ,  1.0 ,  1.0 , 
                   0.0 ,  0.0 ,  0.0 , 
                  -0.4 , -0.4 , -0.4;
    c.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    
    ma::maths::Scalar a_ = a.mean();
    ma::maths::Scalar b_ = b.mean();
    ma::maths::Position c_ = c.mean();

    TS_ASSERT_EQUALS(a_.values().coeff(0), 0.6375);
    TS_ASSERT_EQUALS(a_.residuals().coeff(0), 0.0);
    TS_ASSERT_EQUALS(a_.values().rows(), 1);
    TS_ASSERT_EQUALS(a_.residuals().rows(), 1);
    
    TS_ASSERT_EQUALS(b_.values().coeff(0), 0.0);
    TS_ASSERT_EQUALS(b_.residuals().coeff(0), -1.0);
    TS_ASSERT_EQUALS(b_.values().rows(), 1);
    TS_ASSERT_EQUALS(b_.residuals().rows(), 1);
    
    TS_ASSERT_EQUALS(c_.values().coeff(0,0), 0.6375);
    TS_ASSERT_EQUALS(c_.values().coeff(0,1), 0.6375);
    TS_ASSERT_EQUALS(c_.values().coeff(0,2), 0.6375);
    TS_ASSERT_EQUALS(c_.residuals().coeff(0), 0.0);
    TS_ASSERT_EQUALS(c_.values().rows(), 1);
    TS_ASSERT_EQUALS(c_.residuals().rows(), 1);
  };

  CXXTEST_TEST(scaledDifference)
  {
    ma::maths::Scalar a(10), b(10);
    a.values().setRandom();
    a.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    b.values().setRandom();
    b.residuals() <<  0.5, 0.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0,  0.0;
    
    ma::maths::Scalar c = 0.5 * (a - b);

    TS_ASSERT_EQUALS(c.residuals().coeff(0), -1.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(9), -1.0);
    for (int i = 1 ; i < 9 ; ++i)
      TS_ASSERT_EQUALS(c.values().coeff(i), (a.values().coeff(i) - b.values().coeff(i)) / 2.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(0), -1.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(1), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(2), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(3), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(4), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(5), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(6), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(7), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(8), 0.0);
    TS_ASSERT_EQUALS(c.residuals().coeff(9), -1.0);
  };
  
  CXXTEST_TEST(normalized)
  {
    ma::maths::Vector a(10);
    a.values().setRandom();
    a.values().row(9) << 0.0, 0.0, 0.0;
    a.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    ma::maths::Vector b(10);
    b.values().setRandom();
    b.residuals() << 1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, 0.4;
    ma::maths::Vector c = a.normalized();
    ma::maths::Vector d = (b-a).normalized();

    Eigen::Matrix<double,Eigen::Dynamic,1> norm = c.values().matrix().rowwise().norm();
    for (int i = 1 ; i < 9 ; ++i)
      TS_ASSERT_DELTA(norm.coeff(i), 1.0, 1e-16);
    TS_ASSERT_DELTA(norm.coeff(0), 0.0, 1e-16);
    TS_ASSERT_DELTA(norm.coeff(9), 0.0, 1e-16);
    
    norm = d.values().matrix().rowwise().norm();
    for (int i = 1 ; i < 9 ; ++i)
      TS_ASSERT_DELTA(norm.coeff(i), 1.0, 1e-15);
    TS_ASSERT_DELTA(norm.coeff(0), 0.0, 1e-16);
    TS_ASSERT_DELTA(norm.coeff(9), 0.0, 1e-16);
  };

  CXXTEST_TEST(cross)
  {
    ma::maths::Vector a(4), b(4);
    a.values() << 1.0, 0.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 1.0,
                  0.0, 0.0, 0.0;
    a.residuals() << 1.0, 0.5, 0.5, -1.0;
    b.values() << 0.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  1.0, 0.0, 0.0,
                  0.0, 0.0, 0.0;
    b.residuals() << 1.0, 0.5, 0.5, 1.0;
    ma::maths::Vector c = a.cross(b);

    const ma::maths::Vector::Values& cv = c.values();
    const ma::maths::Vector::Residuals& cr = c.residuals();

    TS_ASSERT_DELTA(cv.coeff(0,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(0,1), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(0,2), 1.0, 1e-15);

    TS_ASSERT_DELTA(cv.coeff(1,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(1,1), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(1,2), 0.0, 1e-15);

    TS_ASSERT_DELTA(cv.coeff(2,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(2,1), 1.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(2,2), 0.0, 1e-15);

    TS_ASSERT_DELTA(cv.coeff(3,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(3,1), 0.0, 1e-15);
    TS_ASSERT_DELTA(cv.coeff(3,2), 0.0, 1e-15);

    TS_ASSERT_EQUALS(cr.coeff(0), 0.0);
    TS_ASSERT_EQUALS(cr.coeff(1), 0.0);
    TS_ASSERT_EQUALS(cr.coeff(2), 0.0);
    TS_ASSERT_EQUALS(cr.coeff(3), -1.0);
  };

  CXXTEST_TEST(crossBis)
  {
    ma::maths::Vector a(4), b(4), c(4);
    a.values().setZero();
    a.residuals().setZero();
    b.values() << 0.0, 0.4, 0.0,
                  0.0, 2.0, 0.0,
                  0.9, 0.0, 0.0,
                  0.0, 0.0, 0.0;
    b.residuals() << 1.0, 0.5, 0.5, 1.0;
    c.values() << 2.0, 0.0, 0.0,
                  0.0, 3.0, 0.0,
                  0.0, 0.0, 1.5,
                  0.0, 0.0, 0.0;
    c.residuals() << 1.0, 0.5, 0.5, -1.0;
    ma::maths::Vector d = (c-a).normalized().cross((b-a).normalized());

    const ma::maths::Vector::Values& dv = d.values();
    const ma::maths::Vector::Residuals& dr = d.residuals();

    TS_ASSERT_DELTA(dv.coeff(0,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(0,1), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(0,2), 1.0, 1e-15);

    TS_ASSERT_DELTA(dv.coeff(1,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(1,1), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(1,2), 0.0, 1e-15);

    TS_ASSERT_DELTA(dv.coeff(2,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(2,1), 1.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(2,2), 0.0, 1e-15);

    TS_ASSERT_DELTA(dv.coeff(3,0), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(3,1), 0.0, 1e-15);
    TS_ASSERT_DELTA(dv.coeff(3,2), 0.0, 1e-15);

    TS_ASSERT_EQUALS(dr.coeff(0), 0.0);
    TS_ASSERT_EQUALS(dr.coeff(1), 0.0);
    TS_ASSERT_EQUALS(dr.coeff(2), 0.0);
    TS_ASSERT_EQUALS(dr.coeff(3), -1.0);
  };
  
  CXXTEST_TEST(operatorDouble)
  {
    ma::maths::Position c(10);
    c.values() << -1.0 , -1.0 , -1.0 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.5 ,  0.5 ,  0.5 , 
                   0.5 ,  0.5 ,  0.5 , 
                   1.0 ,  1.0 ,  1.0 , 
                   0.65,  0.65,  0.65, 
                   0.45,  0.45,  0.45, 
                   1.0 ,  1.0 ,  1.0 , 
                   0.0 ,  0.0 ,  0.0 , 
                  -0.4 , -0.4 , -0.4;
    c.residuals() << -1.0, 1.0, 0.5, 0.5, 1.0, 0.65, 0.45, 1.0, 0.0, -0.4;
    double norm = 0.0;
    
    norm = c.mean().norm();
    TS_ASSERT_DELTA(norm, 1.104182389825159, 1e-15);
    
    c.residuals().setConstant(-1.0);
    norm = c.mean().norm();
    TS_ASSERT_DELTA(norm, 0.0, 1e-15);
  };
  
  CXXTEST_TEST(replicate)
  {
    ma::maths::Position a(2);
    a.values() << -1.0 , -1.0 , -1.0 , 
                   1.0 ,  1.0 ,  1.0;
    a.residuals() << -1.0, 1.0;
    
    ma::maths::Position b = a.replicate(3);
    const ma::maths::Position::Values& bv = b.values();
    const ma::maths::Position::Residuals& br = b.residuals();
    TS_ASSERT_EQUALS(b.rows(), 6);
    
    TS_ASSERT_DELTA(bv.coeff(0,0),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(0,1),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(0,2),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(1,0),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(1,1),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(1,2),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(2,0),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(2,1),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(2,2),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(3,0),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(3,1),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(3,2),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(4,0),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(4,1),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(4,2),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(5,0),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(5,1),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(5,2),   1.0, 1e-15);
    
    TS_ASSERT_DELTA(br.coeff(0), -1.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(1),  1.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(2), -1.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(3),  1.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(4), -1.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(5),  1.0, 1e-15);
  };
  
  CXXTEST_TEST(replicateBis)
  {
    ma::maths::Position::Values av(2,3);
    av << -1.0 , -1.0 , -1.0 , 
           1.0 ,  1.0 ,  1.0;
           
    ma::maths::Position b = ma::maths::Position(av,ma::maths::Position::Residuals::Zero(av.rows())).replicate(3);
    const ma::maths::Position::Values& bv = b.values();
    const ma::maths::Position::Residuals& br = b.residuals();
    TS_ASSERT_EQUALS(b.rows(), 6);
    
    TS_ASSERT_DELTA(bv.coeff(0,0),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(0,1),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(0,2),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(1,0),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(1,1),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(1,2),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(2,0),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(2,1),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(2,2),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(3,0),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(3,1),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(3,2),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(4,0),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(4,1),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(4,2),  -1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(5,0),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(5,1),   1.0, 1e-15);
    TS_ASSERT_DELTA(bv.coeff(5,2),   1.0, 1e-15);
    
    TS_ASSERT_DELTA(br.coeff(0), 0.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(1), 0.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(2), 0.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(3), 0.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(4), 0.0, 1e-15);
    TS_ASSERT_DELTA(br.coeff(5), 0.0, 1e-15);
  };
};

CXXTEST_SUITE_REGISTRATION(ArrayTest)
CXXTEST_TEST_REGISTRATION(ArrayTest, assignment)
CXXTEST_TEST_REGISTRATION(ArrayTest, norm)
CXXTEST_TEST_REGISTRATION(ArrayTest, mean)
CXXTEST_TEST_REGISTRATION(ArrayTest, scaledDifference)
CXXTEST_TEST_REGISTRATION(ArrayTest, normalized)
CXXTEST_TEST_REGISTRATION(ArrayTest, cross)
CXXTEST_TEST_REGISTRATION(ArrayTest, crossBis)
CXXTEST_TEST_REGISTRATION(ArrayTest, operatorDouble)
CXXTEST_TEST_REGISTRATION(ArrayTest, replicate)
CXXTEST_TEST_REGISTRATION(ArrayTest, replicateBis)