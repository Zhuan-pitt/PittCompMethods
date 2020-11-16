#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <QApplication>
#include <QWidget>
#include <random>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>




SoTranslation *earthTranslation=NULL;
SoTranslation *venusTranslation=NULL;
SoTranslation *jupiterTranslation=NULL;
SoTranslation *marsTranslation=NULL;
SoTranslation *conTranslation=NULL;
SoTranslation *mercuryTranslation=NULL;
double tPhi=0.0;
void callback(void *, SoSensor *) {
  static const double R_e=11663;
  static const double R_v=8378;
  static const double R_j=58315;

  static const double R_m=4665;
  static const double R_ma=23326;
  
  earthTranslation->translation.setValue(R_e*cos(tPhi),0, R_e*sin(tPhi));
  venusTranslation->translation.setValue(R_v*cos(tPhi*1.62),0, R_v*sin(tPhi*1.62));
  jupiterTranslation->translation.setValue(R_j*cos(tPhi*0.084),0, R_j*sin(tPhi*0.084));
  mercuryTranslation->translation.setValue(R_m*cos(tPhi*4.15),0, R_m*sin(tPhi*4.15));
  marsTranslation->translation.setValue(R_ma*cos(tPhi*0.5),0, R_ma*sin(tPhi*0.5));
  // conTranslation->translation.setValue(R_j*cos(tPhi*0.084),2000, R_j*sin(tPhi*0.084));
conTranslation->translation.setValue(0,-2000, 0);

  tPhi+=0.001;
}

SoSeparator *makeOrbit(double a) {

  SoSeparator *sep=new SoSeparator();

  SoCoordinate3 *coords=new SoCoordinate3;
  unsigned int NPOINTS=100;
  for (unsigned int i=0;i<NPOINTS;i++) {
    double phi=2*M_PI*i/(double(NPOINTS)-1);
    coords->point.set1Value(i,a*cos(phi),0,a*sin(phi));
  }
  sep->addChild(coords);
  SoLineSet *lineSet=new SoLineSet;
  lineSet->numVertices=NPOINTS;
  sep->addChild(lineSet);

  return sep;
}




int main(int argc, char ** argv)
{

  QApplication app(argc, argv);
  QWidget mainwin;
  SoQt::init(&mainwin);

  // The root of a scene graph
  SoSeparator *root = new SoSeparator;
  root->ref();
  
  SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(&mainwin);
  eviewer->setSceneGraph(root);
  eviewer->show();

  static const double r_e=11663.0;
  root->addChild(makeOrbit(r_e));
  static const double r_v=8378;
  root->addChild(makeOrbit(r_v));
    static const double r_m=4665;
  root->addChild(makeOrbit(r_m));
  static const double r_j=58315;
  root->addChild(makeOrbit(r_j));
    static const double r_ma=23326;
  root->addChild(makeOrbit(r_ma));
  
  


  SoSeparator *conSep=new SoSeparator;
  SoBaseColor *color = new SoBaseColor; 
  color->rgb = SbColor(1, 1, 0); // Yellow 
  
  SoCone   *cone = new SoCone;
  cone->bottomRadius = 500;
  cone->height = 2000;
  conTranslation = new SoTranslation();
  conTranslation->translation.setValue(0,-2000,0);
  conSep->addChild(color);
  conSep->addChild (conTranslation);
  conSep->addChild (cone);
  root->addChild (conSep); 

  
  
  {
    SoTexture2 *txt=new SoTexture2;
    txt->filename="sun.jpg";
    root->addChild(txt);
  }

  
  SoSphere *sphere=new SoSphere;
  sphere->radius = 109;
  root->addChild(sphere);


  {
    SoTexture2 *txt=new SoTexture2;
    txt->filename="earth.png";
    root->addChild(txt);
  }




  
  // Schedule the update right here: 
  SoTimerSensor * timerSensor = new SoTimerSensor;
  timerSensor->setFunction(callback);
  timerSensor->setInterval(0.01);
  timerSensor->schedule();
  

  SoSeparator *earthSep=new SoSeparator;
  SoSphere    *earth = new SoSphere;
  earth->radius = 10;
  earthTranslation = new SoTranslation();
  earthTranslation->translation.setValue(r_e, 0, 0);
  earthSep->addChild(earthTranslation);
  earthSep->addChild(earth);
  earthSep->addChild(conSep);
  root->addChild(earthSep);
  
  
    {
    SoTexture2 *txt=new SoTexture2;
    txt->filename="venus.jpg";
    root->addChild(txt);
  }
  
  SoSeparator *venusSep=new SoSeparator;
  SoSphere    *venus = new SoSphere;
  venus->radius = 10;
  venusTranslation = new SoTranslation();
  venusTranslation->translation.setValue(r_v, 0, 0);
  venusSep->addChild(venusTranslation);
  venusSep->addChild(venus);
  venusSep->addChild(conSep);
  root->addChild(venusSep);
  

     {
    SoTexture2 *txt=new SoTexture2;
    txt->filename="jupiter.jpg";
    root->addChild(txt);
  }
  
  SoSeparator *jupiterSep=new SoSeparator;
  SoSphere    *jupiter = new SoSphere;
  jupiter->radius = 109;
  jupiterTranslation = new SoTranslation();
  jupiterTranslation->translation.setValue(r_j, 0, 0);
  jupiterSep->addChild(jupiterTranslation);
  jupiterSep->addChild(jupiter);
  jupiterSep->addChild(conSep);

  root->addChild(jupiterSep);

  

  {
    SoTexture2 *txt=new SoTexture2;
    txt->filename="mercury.jpg";
    root->addChild(txt);
  }
  
  SoSeparator *mercurySep=new SoSeparator;
  SoSphere    *mercury = new SoSphere;
  mercury->radius = 4;
  mercuryTranslation = new SoTranslation();
  mercuryTranslation->translation.setValue(r_m, 0, 0);
  mercurySep->addChild(mercuryTranslation);
  mercurySep->addChild(mercury);
  mercurySep->addChild(conSep);
  root->addChild(mercurySep);



  {
    SoTexture2 *txt=new SoTexture2;
    txt->filename="mars.jpg";
    root->addChild(txt);
  }
  
  SoSeparator *marsSep=new SoSeparator;
  SoSphere    *mars = new SoSphere;
  mars->radius = 5.4;
  marsTranslation = new SoTranslation();
  marsTranslation->translation.setValue(r_ma, 0, 0);
  marsSep->addChild(marsTranslation);
  marsSep->addChild(mars);
   marsSep->addChild(conSep);
  
  root->addChild(marsSep);

  // Pop up the main window.
  SoQt::show(&mainwin);

  eviewer->viewAll();
  
  // Loop until exit.
  SoQt::mainLoop();

  // Clean up resources.
  delete eviewer;
  root->unref();
}
