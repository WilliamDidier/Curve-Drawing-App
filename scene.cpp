#include "scene.h"

// add all your types of 2D curves here
#include "curve1DBezier.h"
#include "curve2DBezier.h"
#include "curve2DBezierclosed.h"
#include "curve2DLinear.h"
#include "curve2DLinearclosed.h"
#include "curve1DLinear.h"
#include "curve1DLinearRessort.h"
#include "curve1DLagrange.h"
#include "curve_2D_lagrange.h"
#include "curve2DBsplines.h"
#include "curve1DHermite.h"
#include "curve1DLagrange.h"
#include "curve2Dhermite.h"
#include "curve1DRessortHermite.h"
#include "curve1DRebondHermite.h"
#include "curve1DBSplines.h"
#include "curve1DLinearRebond.h"
#include "curve1DHermiteChange.h"
#include "curve1DHermite_random.h"
#include "curve2DBezierSin.h"
#include "curve2DBezierWeird.h"
#include "curve2DBsplinesChordal.h"



Scene *Scene::_instance = NULL;

using namespace std;

// add 2D curve builders here
void Scene::initCurveBuilders() {
  addCurveBuilder(new Curve2DLinearConstructor());
  addCurveBuilder(new Curve2DLinearClosedConstructor());
  addCurveBuilder(new Curve2DlagrangeConstructor());
  addCurveBuilder(new Curve2DBezierConstructor());
  addCurveBuilder(new Curve2DBezierClosedConstructor());
  addCurveBuilder(new Curve2DBsplinesConstructor());
  addCurveBuilder(new Curve2DHermiteConstructor());
  addCurveBuilder(new Curve2DBezierSinConstructor());
  addCurveBuilder(new Curve2DBezierWeirdConstructor());
  addCurveBuilder(new Curve2DBsplinesChordalConstructor());


}

// add 1D curve builders (functions) here
void Scene::initFunctionBuilders() {
  addFunctionBuilder(new Curve1DLagrangeConstructor());
  addFunctionBuilder(new Curve1DHermiteConstructor());
  addFunctionBuilder(new Curve1DRessortHermiteConstructor());
  addFunctionBuilder(new Curve1DRebondHermiteConstructor());
  addFunctionBuilder(new Curve1DLinearConstructor());
  addFunctionBuilder(new Curve1DLinearRessortConstructor());
  addFunctionBuilder(new Curve1DLinearRebondConstructor());
  addFunctionBuilder(new Curve1DBezierConstructor());
  addFunctionBuilder(new Curve1DLagrangeConstructor());
  addFunctionBuilder(new Curve1DBsplinesConstructor());
  addFunctionBuilder(new Curve1DHermite_randomConstructor());
  addFunctionBuilder(new Curve1DHermiteChangeConstructor());
}


void Scene::cleanCurveBuilders() {
  map<QString,Curve2DConstructor *>::const_iterator mit(_curveBuilders.begin()),mend(_curveBuilders.end());

  for(;mit!=mend;++mit) {
    delete mit->second;
  }

  _curveBuilders.clear();
}

void Scene::cleanFunctionBuilders() {
  map<QString,Curve1DConstructor *>::const_iterator mit(_functionBuilders.begin()),mend(_functionBuilders.end());

  for(;mit!=mend;++mit) {
    delete mit->second;
  }

  _functionBuilders.clear();
}


Scene::Scene() {
  initFunctionBuilders();
  initCurveBuilders();
  setDefaultSettings();
}

Scene::~Scene() {
  clean();
  cleanFunctionBuilders();
  cleanCurveBuilders();
}
