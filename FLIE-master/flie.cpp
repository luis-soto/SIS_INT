// FLIE - Fuzzy Logic Inference Engine
// FLIE was developed by Joao Alberto Fabro, nowadays(2018) Associate Professor at UTFPR-Federal University of Technology - Parana - Brazil
// FLIE is a simple library that implements fuzzy concepts (Fuzzy Sets) in form of triangular or trapezoidal Fuzzy Sets(or Categories).
// Several of these "Categories/Fuzzy Sets" can then be agregated in "Linguistic Variables".
// Linguistic Variables can then be used to define "Rules" associating "Fuzzy Sets" with each other.
// The following source codes compose the Library:
//  - fuzfier.h and fuzzfier.cpp (source code for class "fuzzy_set"(also called fuzzyset or trapezoid_category), that are classes that represent fuzzy concepts - near, far, large, small...)
//  - lingvar.h and lingvar.cpp (source code for class "linguisticvariable", that aggregates 2 or more fuzzy_sets in one coherent "concept", such as "Distance")
//  - rule.h and rule.cpp (source code for class "rule": each "rule" relates one (or two or three) input fuzzy_set's with one output fuzzy set. For example, "if Distance is Near then Action_in_the_Break is Hard" -> rule.definerule( "Far","Hard");
//  - fuzzy_control.h and fuzzy_control.cpp (source code for a Mamdani type fuzzy logic controller - aggregates linguistic variables, rules and a defuzzyfication method in order to perform fuzzy inference)
//  - flie.h and flie.cpp (example code that creates a PD Fuzzy controller)
// These "Rules" can then be aggregated into a "Fuzzy Controller". The code for the "simplest" fuzzy control system is depicted bellow:
/* Simple Example of use (save this excerpt and compile it together with the library) - the easyest way is to just save this
code with the name "flie.cpp" */
// Joao Alberto Fabro, fabro@utfpr.edu.br, 05/2018
// ----------------------------------------------------------------------------------------------------
#define DOS
// ----------------------------------------------------------------------------------------------------
#include "flie.h"
#include <iostream>
#include <stdio.h>
// ----------------------------------------------------------------------------------------------------
static const float pi = 3.1415;
// ----------------------------------------------------------------------------------------------------
fuzzy_control fc1;
fuzzy_control fc2;
// ----------------------------------------------------------------------------------------------------
fuzzy_set fsNear, fsHalf, fsFar;
fuzzy_set fsLowSpeed, fsAverageSpeed, fsHighSpeed;
// ----------------------------------------------------------------------------------------------------
linguisticvariable leftSensor, centerSensor, rightSensor, leftEngine, rightEngine;
// ----------------------------------------------------------------------------------------------------
rule infrule[2];
// ----------------------------------------------------------------------------------------------------
int main()
{
    fsNear.setname("Near");
    fsNear.setrange(1.0, 15.0);
    fsNear.setval(1.0, 1.0, 11.0, 15.0);

    fsHalf.setname("Half");
    fsHalf.setrange(11.0, 30.0);
    fsHalf.setval(11.0, 15.0, 26.0, 30.0);

    fsFar.setname("Far");
    fsFar.setrange(26.0, 40.0);
    fsFar.setval(26.0, 30.0, 40.0, 40.0);

    leftSensor.setname("Left Sensor");
    leftSensor.includecategory(&fsNear);
    leftSensor.includecategory(&fsHalf);
    leftSensor.includecategory(&fsFar);

    centerSensor.setname("Center Sensor");
    centerSensor.includecategory(&fsNear);
    centerSensor.includecategory(&fsHalf);
    centerSensor.includecategory(&fsFar);

    rightSensor.setname("Right Sensor");
    rightSensor.includecategory(&fsNear);
    rightSensor.includecategory(&fsHalf);
    rightSensor.includecategory(&fsFar);

    fsLowSpeed.setname("Low Speed");
    fsLowSpeed.setrange(0, pi/3 + pi/15);
    fsLowSpeed.setval(0, 0, pi/3 - pi/15, pi/3 + pi/15);

    fsAverageSpeed.setname("Average Speed");
    fsAverageSpeed.setrange(pi/3 - pi/15, 2*pi/3 + pi/15);
    fsAverageSpeed.setval(pi/3 - pi/15 , pi/3 + pi/15, 2*pi/3 - pi/15, 2*pi/3 + pi/15);

    fsHighSpeed.setname("High Speed");
    fsHighSpeed.setrange(2*pi/3 - pi/15, pi);
    fsHighSpeed.setval(2*pi/3 - pi/15, 2*pi/3 + pi/15, pi, pi);

    leftEngine.setname("Left Engine");
    leftEngine.includecategory(&fsLowSpeed);
    leftEngine.includecategory(&fsAverageSpeed);
    leftEngine.includecategory(&fsHighSpeed);

    rightEngine.setname("Right Engine");
    rightEngine.includecategory(&fsLowSpeed);
    rightEngine.includecategory(&fsAverageSpeed);
    rightEngine.includecategory(&fsHighSpeed);

    fc1.definevars(leftSensor, centerSensor, rightSensor, rightEngine);
    fc2.definevars(leftSensor, centerSensor, rightSensor, leftEngine);

    fc1.set_defuzz(CENTROID);
    fc2.set_defuzz(CENTROID);

    // Right engine rules
    fc1.insert_rule("Near", "Near", "Near", "Low Speed");
    fc1.insert_rule("Near", "Near", "Half", "Low Speed");
    fc1.insert_rule("Near", "Near", "Far", "Low Speed");
    fc1.insert_rule("Near", "Half", "Near", "Low Speed");
    fc1.insert_rule("Near", "Half", "Half", "Low Speed");
    fc1.insert_rule("Near", "Half", "Far", "Low Speed");
    fc1.insert_rule("Near", "Far", "Near", "Low Speed");
    fc1.insert_rule("Near", "Far", "Half", "Average Speed");
    fc1.insert_rule("Near", "Far", "Far", "Average Speed");
    fc1.insert_rule("Half", "Near", "Near", "High Speed");
    fc1.insert_rule("Half", "Near", "Half", "Low Speed");
    fc1.insert_rule("Half", "Near", "Far", "Low Speed");
    fc1.insert_rule("Half", "Half", "Near", "High Speed");
    fc1.insert_rule("Half", "Half", "Half", "Average Speed");
    fc1.insert_rule("Half", "Half", "Far", "Average Speed");
    fc1.insert_rule("Half", "Far", "Near", "High Speed");
    fc1.insert_rule("Half", "Far", "Half", "Average Speed");
    fc1.insert_rule("Half", "Far", "Far", "Average Speed");
    fc1.insert_rule("Far", "Near", "Near", "High Speed");
    fc1.insert_rule("Far", "Near", "Half", "High Speed");
    fc1.insert_rule("Far", "Near", "Far", "Low Speed");
    fc1.insert_rule("Far", "Half", "Near", "High Speed");
    fc1.insert_rule("Far", "Half", "Half", "High Speed");
    fc1.insert_rule("Far", "Half", "Far", "Average Speed");
    fc1.insert_rule("Far", "Far", "Near", "High Speed");
    fc1.insert_rule("Far", "Far", "Half", "High Speed");
    fc1.insert_rule("Far", "Far", "Far", "High Speed");

    // Left engine rules
    fc2.insert_rule("Near", "Near", "Near", "High Speed");
    fc2.insert_rule("Near", "Near", "Half", "High Speed");
    fc2.insert_rule("Near", "Near", "Far", "High Speed");
    fc2.insert_rule("Near", "Half", "Near", "High Speed");
    fc2.insert_rule("Near", "Half", "Half", "High Speed");
    fc2.insert_rule("Near", "Half", "Far", "High Speed");
    fc2.insert_rule("Near", "Far", "Near", "High Speed");
    fc2.insert_rule("Near", "Far", "Half", "High Speed");
    fc2.insert_rule("Near", "Far", "Far", "High Speed");
    fc2.insert_rule("Half", "Near", "Near", "Low Speed");
    fc2.insert_rule("Half", "Near", "Half", "High Speed");
    fc2.insert_rule("Half", "Near", "Far", "High Speed");
    fc2.insert_rule("Half", "Half", "Near", "Low Speed");
    fc2.insert_rule("Half", "Half", "Half", "Average Speed");
    fc2.insert_rule("Half", "Half", "Far", "High Speed");
    fc2.insert_rule("Half", "Far", "Near", "Average Speed");
    fc2.insert_rule("Half", "Far", "Half", "Average Speed");
    fc2.insert_rule("Half", "Far", "Far", "High Speed");
    fc2.insert_rule("Far", "Near", "Near", "Low Speed");
    fc2.insert_rule("Far", "Near", "Half", "Low Speed");
    fc2.insert_rule("Far", "Near", "Far", "High Speed");
    fc2.insert_rule("Far", "Half", "Near", "Average Speed");
    fc2.insert_rule("Far", "Half", "Half", "Average Speed");
    fc2.insert_rule("Far", "Half", "Far", "High Speed");
    fc2.insert_rule("Far", "Far", "Near", "Low Speed");
    fc2.insert_rule("Far", "Far", "Half", "Average Speed");
    fc2.insert_rule("Far", "Far", "Far", "High Speed");

    // Variables for Input and Output
    float distLeft, distCenter, distRight;
    float rightEngine, leftEngine;
    char ch = 'y';
    bool cont;

    do
    {
        std::cout << endl << "Enter values:" << endl;
        std::cout << "left sensor value = ";
        std::cin >> distLeft;
        std::cout << "central sensor value = ";
        std::cin >> distCenter;
        std::cout << "right sensor value = ";
        std::cin >> distRight;
        std::cout << endl;

        rightEngine = fc1.make_inference(distLeft, distCenter, distRight);
        leftEngine = fc2.make_inference(distLeft, distCenter, distRight);

        std::cout << "For:" << endl
                  << "Left sensor = " << distLeft << endl
                  << "Central sensor = " << distCenter << endl
                  << "Right sensor = " << distRight << endl
                  << "The defuzyfied Output is:" << endl
                  << "Left engine = " << leftEngine << endl
                  << "Right engine = " << rightEngine << endl;

        std::cout << "Continue(y/n)? ";
        std::cin >> ch;
        cont = (ch == 'y');
    }
    while(cont);

    return 0;
}
// ----------------------------------------------------------------------------------------------------