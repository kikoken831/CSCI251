
// g++ Point2D.cpp Point3D.cpp Line2D.cpp Line3D.cpp fn_template_testcase.cpp

#include <iostream>
#include <utility>
#include <vector>
#include <math.h>
#include <string>
#include <algorithm>
#include <typeinfo>

#include "MyTemplates.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

using namespace std;

// ---------------------------------------------------------

int main ()
{
    cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.precision (3);

    Point2D pt2D_a (1, 24);
    Point2D pt2D_b (23, -3);
    
    Point2D pt2D_c (4, 17);
    Point2D pt2D_d (-5, -28);

    Point2D pt2D_e (-21, -9);
    Point2D pt2D_f (-27, -13);
    
    Point2D pt2D_g (19, -26);
    Point2D pt2D_h (-22, 8);

    Line2D line2D_1 (pt2D_e, pt2D_f);
    Line2D line2D_2 (pt2D_g, pt2D_h);

// ---------------------------------------------------------

    Point3D pt3D_a (12, 3, 14);
    Point3D pt3D_b (15, 3, -22);
    
    Point3D pt3D_c (16, 17, 10);
    Point3D pt3D_d (23, 26, 16);
    
    Point3D pt3D_e (-5, 25, 23);
    Point3D pt3D_f (4, 0, 5);
    
    Point3D pt3D_g (-9, -11, 25);
    Point3D pt3D_h (-3, 7, 23);

    Line3D line3D_1 (pt3D_e, pt3D_f);
    Line3D line3D_2 (pt3D_g, pt3D_h);

// ---------------------------------------------------------
    
    Point2D p2Dtemp;
    Point3D p3Dtemp;

    Line2D  l2Dtemp;
    Line3D  l3Dtemp;

    double dtemp;

// ---------------------------------------------------------
// Test scalar_difference for Point2D ...
// ---------------------------------------------------------
 
    cout << endl;
    cout << "scalar_difference betw. ";
    cout << "[" << pt2D_a.getX() << ", " << pt2D_a.getY() << "], distFrOrigin : " << pt2D_a.getScalarValue() << " and ";
    cout << "[" << pt2D_b.getX() << ", " << pt2D_b.getY() << "], distFrOrigin : " << pt2D_b.getScalarValue() << " is " << endl;
        
    dtemp = scalar_difference (pt2D_a, pt2D_b); // 0.826
    cout << dtemp << endl;

// ---------------------------------------------------------
// Test scalar_difference for Point3D ...
// ---------------------------------------------------------

    cout << endl;
    cout << "scalar_difference betw. ";     // 8.114
    cout << "[" << pt3D_a.getX() << ", " << pt3D_a.getY() << ", " << pt3D_a.getZ() << "], distFrOrigin : " << pt3D_a.getScalarValue() << " and ";
    cout << "[" << pt3D_b.getX() << ", " << pt3D_b.getY() << ", " << pt3D_b.getZ() << "], distFrOrigin : " << pt3D_b.getScalarValue() << " is " << endl;
        
    dtemp = scalar_difference (pt3D_a, pt3D_b);
    cout << dtemp << endl;

// ---------------------------------------------------------
// Test scalar_difference for Line2D ...
// ---------------------------------------------------------
    
    cout << endl;
    cout << "scalar_difference betw. ";
    cout << "Line2D [" << line2D_1.getPt1().getX() << ", " << line2D_1.getPt1().getY() << "] to ";
    cout <<        "[" << line2D_2.getPt2().getX() << ", " << line2D_2.getPt2().getY() << "] is " << endl;

    dtemp = scalar_difference (line2D_1, line2D_2); // 46.052
    cout << dtemp << endl;

// ---------------------------------------------------------
// Test scalar_difference for Line3D ...
// ---------------------------------------------------------

    cout << endl;
    cout << "scalar_difference betw. ";
    cout << "Line3D [" << line3D_1.getPt1().getX() << ", " << line3D_1.getPt1().getY() << "] to ";
    cout <<        "[" << line3D_2.getPt2().getX() << ", " << line3D_2.getPt2().getY() << "] is " << endl;

    dtemp = scalar_difference (line3D_1, line3D_2); // 13.015
    cout << dtemp << endl;

// ---------------------------------------------------------
// Test equals for Point2D
// ---------------------------------------------------------
     
    cout << endl;
    cout << "equals (" << endl;
    cout << "[" << pt2D_c.getX() << ", " << pt2D_c.getY() << "], distFrOrigin : " << pt2D_c.getScalarValue() << "," << endl;
    cout << "[" << pt2D_c.getX() << ", " << pt2D_c.getY() << "], distFrOrigin : " << pt2D_c.getScalarValue() << " ) returns " << endl;
    cout << boolalpha;
    cout << equals (pt2D_c, pt2D_c) << endl;
    cout << noboolalpha;

// ---------------------------------------------------------
// Test equals for Point3D
// ---------------------------------------------------------

    cout << endl;
    cout << "equals (" << endl;
    cout << "[" << pt3D_d.getX() << ", " << pt3D_d.getY() << ", " << pt3D_d.getZ() << "], distFrOrigin : " << pt3D_d.getScalarValue() << "," << endl;
    cout << "[" << pt3D_d.getX() << ", " << pt3D_d.getY() << ", " << pt3D_d.getZ() << "], distFrOrigin : " << pt3D_d.getScalarValue() << " ) returns " << endl;
    cout << boolalpha;
    cout << equals (pt3D_d, pt3D_d) << endl;
    cout << noboolalpha;

// ---------------------------------------------------------
// Test equals for Line2D
// ---------------------------------------------------------

    cout << endl;
    cout << "equals (" << endl;
    cout << "Line2D [" << line2D_1.getPt1().getX() << ", " << line2D_1.getPt1().getY() << "] to ";
    cout <<        "[" << line2D_1.getPt2().getX() << ", " << line2D_1.getPt2().getY() << "], length : " << line2D_1.getScalarValue() << " AND" << endl;
    cout << "Line2D [" << line2D_1.getPt1().getX() << ", " << line2D_1.getPt1().getY() << "] to ";
    cout <<        "[" << line2D_1.getPt2().getX() << ", " << line2D_1.getPt2().getY() << "], length : " << line2D_1.getScalarValue() << " ) returns " << endl;
    cout << boolalpha;
    cout << equals (line2D_1, line2D_1) << endl;
    cout << noboolalpha;

// ---------------------------------------------------------
// Test equals for Line3D
// ---------------------------------------------------------

    cout << endl;
    cout << "equals (" << endl;
    cout << "Line3D [" << line3D_1.getPt1().getX() << ", " << line3D_1.getPt1().getY() << ", " << line3D_1.getPt1().getZ() << "] to ";
    cout <<        "[" << line3D_1.getPt2().getX() << ", " << line3D_1.getPt2().getY() << ", " << line3D_1.getPt2().getZ() << "], length : " << line3D_1.getScalarValue() << " AND" << endl;
    cout << "Line3D [" << line3D_1.getPt1().getX() << ", " << line3D_1.getPt1().getY() << ", " << line3D_1.getPt1().getZ() << "] to ";
    cout <<        "[" << line3D_1.getPt2().getX() << ", " << line3D_1.getPt2().getY() << ", " << line3D_1.getPt2().getZ() << "], length : " << line3D_1.getScalarValue() << " returns" << endl;
    cout << boolalpha;
    cout << equals (line3D_1, line3D_1) << endl;
    cout << noboolalpha;

    return 0;
}


