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
fuzzy_control rightEngineController;
fuzzy_control leftEngineController;
// ----------------------------------------------------------------------------------------------------
fuzzy_set fsNear, fsHalf, fsFar;
fuzzy_set fsLowSpeed, fsMediumSpeed, fsHighSpeed;
// ----------------------------------------------------------------------------------------------------
linguisticvariable leftSensor, centerSensor, rightSensor, leftEngine, rightEngine;
// ----------------------------------------------------------------------------------------------------
rule infrule[2];
// ----------------------------------------------------------------------------------------------------
void configFuzzy(void)
{
    fsNear.setname("Near");
    fsNear.setrange(1.0, 32.0);
    fsNear.setval(1.0, 1.0, 28.0, 32.0);

    fsFar.setname("Far");
    fsFar.setrange(28.0, 40.0);
    fsFar.setval(28.0, 32.0, 40.0, 40.0);

    leftSensor.setname("Left Sensor");
    leftSensor.includecategory(&fsNear);
    leftSensor.includecategory(&fsFar);

    centerSensor.setname("Center Sensor");
    centerSensor.includecategory(&fsNear);
    centerSensor.includecategory(&fsFar);

    rightSensor.setname("Right Sensor");
    rightSensor.includecategory(&fsNear);
    rightSensor.includecategory(&fsFar);

    fsLowSpeed.setname("Low Speed");
    fsLowSpeed.setrange(-pi/2, pi/10);
    fsLowSpeed.setval(-pi/2, -pi/2, -pi/10, pi/10);

    fsMediumSpeed.setname("Medium Speed");
    fsMediumSpeed.setrange(-pi/10, pi/2 + pi/10);
    fsMediumSpeed.setval(-pi/10, pi/10, pi/2 - pi/10, pi/2 + pi/10);

    fsHighSpeed.setname("High Speed");
    fsHighSpeed.setrange(pi/2 - pi/10, pi);
    fsHighSpeed.setval(pi/2 - pi/10, pi/2 + pi/10, pi, pi);

    leftEngine.setname("Left Engine");
    leftEngine.includecategory(&fsLowSpeed);
    leftEngine.includecategory(&fsMediumSpeed);
    leftEngine.includecategory(&fsHighSpeed);

    rightEngine.setname("Right Engine");
    rightEngine.includecategory(&fsLowSpeed);
    rightEngine.includecategory(&fsMediumSpeed);
    rightEngine.includecategory(&fsHighSpeed);

    rightEngineController.definevars(leftSensor, centerSensor, rightSensor, rightEngine);
    leftEngineController.definevars(leftSensor, centerSensor, rightSensor, leftEngine);

    rightEngineController.set_defuzz(CENTROID);
    leftEngineController.set_defuzz(CENTROID);

    // Right engine rules
    rightEngineController.insert_rule("Near", "Near", "Far", "Low Speed");
    rightEngineController.insert_rule("Near", "Far", "Far", "Medium Speed");
    rightEngineController.insert_rule("Far", "Near", "Near", "High Speed");
    rightEngineController.insert_rule("Far", "Far", "Near", "High Speed");
    rightEngineController.insert_rule("Far", "Far", "Far", "High Speed");
    rightEngineController.insert_rule("Near", "Near", "Near", "Low Speed");

    // Left engine rules
    leftEngineController.insert_rule("Near", "Near", "Far", "High Speed");
    leftEngineController.insert_rule("Near", "Far", "Far", "High Speed");
    leftEngineController.insert_rule("Far", "Near", "Near", "Low Speed");
    leftEngineController.insert_rule("Far", "Far", "Near", "Medium Speed");
    leftEngineController.insert_rule("Far", "Far", "Far", "High Speed");
    leftEngineController.insert_rule("Near", "Near", "Near", "High Speed");
}

float rightMotorInference(float distLeft, float distCenter, float distRight){
    return rightEngineController.make_inference(distLeft, distCenter, distRight);
}

float leftMotorInference(float distLeft, float distCenter, float distRight){
    return leftEngineController.make_inference(distLeft, distCenter, distRight);
}
// ----------------------------------------------------------------------------------------------------
