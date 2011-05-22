#include "mevtkPolygon.h"

#include "vtkCellArray.h"
#include "vtkDataSet.h"
#include "vtkDoubleArray.h"
#include "vtkLine.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPlane.h"
#include "vtkPoints.h"
#include "vtkPriorityQueue.h"
#include "vtkQuad.h"
#include "vtkTriangle.h"
#include "vtkBox.h"
#include <cfloat>

#include "vtkPolyData.h"

#define M_PI  3.14159265358979323846

//----------------------------------
meVTKPolygon::meVTKPolygon()
//----------------------------------
{
  this->Tris = vtkIdList::New();
  this->Tris->Allocate(VTK_CELL_SIZE);
  this->Triangle = vtkTriangle::New();
  this->Quad = vtkQuad::New();
  this->TriScalars = vtkDoubleArray::New();
  this->TriScalars->Allocate(3);
  this->Line = vtkLine::New();
  this->Tolerance = 0.0;
  this->SuccessfulTriangulation = 0;
  this->Normal[0] = this->Normal[1] = this->Normal[2] = 0.0;
 }

//----------------------------------
meVTKPolygon::~meVTKPolygon()
//----------------------------------
{
  this->Tris->Delete();
  this->Triangle->Delete();
  this->Quad->Delete();
  this->TriScalars->Delete();
  this->Line->Delete();
}

//----------------------------------
meVTKPolygon* meVTKPolygon::New()
//----------------------------------
{return new meVTKPolygon;}

#define VTK_POLYGON_FAILURE -1
#define VTK_POLYGON_OUTSIDE 0
#define VTK_POLYGON_INSIDE 1
#define VTK_POLYGON_INTERSECTION 2
#define VTK_POLYGON_ON_LINE 3


//----------------------------------
void meVTKPolygon::ComputeNormal(vtkPoints *p, int numPts, vtkIdType *pts, double *n)
//----------------------------------
{
  int i;
  double v0[3], v1[3], v2[3];
  double ax, ay, az, bx, by, bz;
// 
// Check for special triangle case. Saves extra work.
// 
  n[0] = n[1] = n[2] = 0.0;
  if ( numPts == 2 || numPts == 1 ) 
    {
    return;
    }

  if ( numPts == 3 ) 
    {
    p->GetPoint(pts[0],v0);
    p->GetPoint(pts[1],v1);
    p->GetPoint(pts[2],v2);
    vtkTriangle::ComputeNormal(v0, v1, v2, n);
    return;
    }

  //  Because polygon may be concave, need to accumulate cross products to 
  //  determine true normal.
  //
  p->GetPoint(pts[0],v1); //set things up for loop
  p->GetPoint(pts[1],v2);

  for (i=0; i < numPts; i++) 
    {
    v0[0] = v1[0]; v0[1] = v1[1]; v0[2] = v1[2];
    v1[0] = v2[0]; v1[1] = v2[1]; v1[2] = v2[2];
    p->GetPoint(pts[(i+2)%numPts],v2);

    // order is important!!! to maintain consistency with polygon vertex order 
    ax = v2[0] - v1[0]; ay = v2[1] - v1[1]; az = v2[2] - v1[2];
    bx = v0[0] - v1[0]; by = v0[1] - v1[1]; bz = v0[2] - v1[2];

    n[0] += (ay * bz - az * by);
    n[1] += (az * bx - ax * bz);
    n[2] += (ax * by - ay * bx);
    }

  vtkMath::Normalize(n);
}

//----------------------------------------------------------------------------
// Compute the polygon normal from a list of doubleing points. This version
// will handle non-convex polygons.
//----------------------------------------------------------------------
void meVTKPolygon::ComputeNormal(vtkPoints *p, double *n)
//----------------------------------------------------------------------
{
  int i, numPts;
  double v0[3], v1[3], v2[3];
  double ax, ay, az, bx, by, bz;

  // Polygon is assumed non-convex -> need to accumulate cross products to 
  // find correct normal.
  //
  numPts = p->GetNumberOfPoints();
  p->GetPoint(0, v1); //set things up for loop
  p->GetPoint(1, v2);
  n[0] = n[1] = n[2] = 0.0;

  for (i=0; i < numPts; i++) 
    {
    memcpy(v0, v1, sizeof(v0));
    memcpy(v1, v2, sizeof(v1));
    p->GetPoint((i+2)%numPts, v2);

    // order is important!!! to maintain consistency with polygon vertex order 
    ax = v2[0] - v1[0]; ay = v2[1] - v1[1]; az = v2[2] - v1[2];
    bx = v0[0] - v1[0]; by = v0[1] - v1[1]; bz = v0[2] - v1[2];

    n[0] += (ay * bz - az * by);
    n[1] += (az * bx - ax * bz);
    n[2] += (ax * by - ay * bx);
    }//over all points

  vtkMath::Normalize(n);
}

//----------------------------------------------------------------------------
// Compute the polygon normal from an array of points. This version assumes
// that the polygon is convex, and looks for the first valid normal.
//----------------------------------------------------------------------
void meVTKPolygon::ComputeNormal (int numPts, double *pts, double n[3])
//----------------------------------------------------------------------
{
  int i;
  double *v1, *v2, *v3;
  double length;
  double ax, ay, az;
  double bx, by, bz;

  //  Because some polygon vertices are colinear, need to make sure
  //  first non-zero normal is found.
  //
  v1 = pts;
  v2 = pts + 3;
  v3 = pts + 6;

  for (i=0; i<numPts-2; i++)
    {
    ax = v2[0] - v1[0]; ay = v2[1] - v1[1]; az = v2[2] - v1[2];
    bx = v3[0] - v1[0]; by = v3[1] - v1[1]; bz = v3[2] - v1[2];

    n[0] = (ay * bz - az * by);
    n[1] = (az * bx - ax * bz);
    n[2] = (ax * by - ay * bx);

    length = sqrt (n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
    if (length != 0.0)
      {
      n[0] /= length;
      n[1] /= length;
      n[2] /= length;
      return;
      }
    else
      {
      v1 = v2;
      v2 = v3;
      v3 += 3;
      }
    } //over all points
}

//----------------------------------------------------------------------------
int meVTKPolygon::EvaluatePosition(double x[3], double* closestPoint,
                                 int& vtkNotUsed(subId), double pcoords[3],
                                 double& minDist2, double *weights)
//----------------------------------------------------------------------
{
  int i;
  double p0[3], p10[3], l10, p20[3], l20, n[3], cp[3];
  double ray[3];

  this->ParameterizePolygon(p0, p10, l10, p20, l20, n);
  this->InterpolateFunctions(x,weights);
  vtkPlane::ProjectPoint(x,p0,n,cp);

  for (i=0; i<3; i++)
    {
    ray[i] = cp[i] - p0[i];
    }
  pcoords[0] = vtkMath::Dot(ray,p10) / (l10*l10);
  pcoords[1] = vtkMath::Dot(ray,p20) / (l20*l20);

  if ( pcoords[0] >= 0.0 && pcoords[0] <= 1.0 &&
       pcoords[1] >= 0.0 && pcoords[1] <= 1.0 &&
       (this->PointInPolygon(cp, this->Points->GetNumberOfPoints(),
                             ((vtkDoubleArray *)this->Points->GetData())
                             ->GetPointer(0), this->GetBounds(),n)
        == VTK_POLYGON_INSIDE) )
    {
    if (closestPoint)
      {
      closestPoint[0] = cp[0];
      closestPoint[1] = cp[1];
      closestPoint[2] = cp[2];
      minDist2 = vtkMath::Distance2BetweenPoints(x,closestPoint);
      }
    return 1;
    }

  // If here, point is outside of polygon, so need to find distance to boundary
  //
  else
    {
    double t, dist2;
    int numPts;
    double closest[3];
    double pt1[3], pt2[3];

    if (closestPoint)
      {
      numPts = this->Points->GetNumberOfPoints();
      for (minDist2=VTK_DOUBLE_MAX,i=0; i<numPts; i++)
        {
        this->Points->GetPoint(i, pt1);
        this->Points->GetPoint((i+1)%numPts, pt2);
        dist2 = vtkLine::DistanceToLine(x, pt1, pt2, t, closest);
        if ( dist2 < minDist2 )
          {
          closestPoint[0] = closest[0];
          closestPoint[1] = closest[1];
          closestPoint[2] = closest[2];
          minDist2 = dist2;
          }
        }
      }
    return 0;
    }
}

//----------------------------------------------------------------------------
void meVTKPolygon::EvaluateLocation(int& vtkNotUsed(subId), double pcoords[3],
                                  double x[3], double *weights)
//----------------------------------------------------------------------
{
  int i;
  double p0[3], p10[3], l10, p20[3], l20, n[3];

  this->ParameterizePolygon(p0, p10, l10, p20, l20, n);
  for (i=0; i<3; i++)
    {
    x[i] = p0[i] + pcoords[0]*p10[i] + pcoords[1]*p20[i];
    }

  this->InterpolateFunctions(x,weights);
}

//----------------------------------------------------------------------------
// Compute interpolation weights using 1/r**2 normalized sum.
void meVTKPolygon::InterpolateFunctions(double x[3], double *weights)
//----------------------------------------------------------------------
{
  int i;
  int numPts=this->Points->GetNumberOfPoints();
  double sum, pt[3];

  for (sum=0.0, i=0; i<numPts; i++)
    {
    this->Points->GetPoint(i, pt);
    weights[i] = vtkMath::Distance2BetweenPoints(x,pt);
    if ( weights[i] == 0.0 ) //exact hit
      {
      for (int j=0; j<numPts; j++)
        {
        weights[j] = 0.0;
        }
      weights[i] = 1.0;
      return;
      }
    else
      {
      weights[i] = 1.0 / (weights[i]*weights[i]);
      sum += weights[i];
      }
    }

  for (i=0; i<numPts; i++)
    {
    weights[i] /= sum;
    }
}

//----------------------------------------------------------------------------
void meVTKPolygon::InterpolateDerivs(double pcoords[3], double *derivs)
//----------------------------------------------------------------------------
{
  (void)pcoords;
  (void)derivs;
}

//----------------------------------------------------------------------------
// Create a local s-t coordinate system for a polygon. The point p0 is
// the origin of the local system, p10 is s-axis vector, and p20 is the 
// t-axis vector. (These are expressed in the modelling coordinate system and
// are vectors of dimension [3].) The values l20 and l20 are the lengths of
// the vectors p10 and p20, and n is the polygon normal.
int meVTKPolygon::ParameterizePolygon(double *p0, double *p10, double& l10, 
                                   double *p20,double &l20, double *n)
//----------------------------------------------------------------------------
{
  int i, j;
  double s, t, p[3], p1[3], p2[3], sbounds[2], tbounds[2];
  int numPts=this->Points->GetNumberOfPoints();
  double x1[3], x2[3];

  //  This is a two pass process: first create a p' coordinate system
  //  that is then adjusted to insure that the polygon points are all in
  //  the range 0<=s,t<=1.  The p' system is defined by the polygon normal, 
  //  first vertex and the first edge.
  //
  this->ComputeNormal (this->Points,n);
  this->Points->GetPoint(0, x1);
  this->Points->GetPoint(1, x2);
  for (i=0; i<3; i++) 
    {
    p0[i] = x1[i];
    p10[i] = x2[i] - x1[i];
    }
  vtkMath::Cross (n,p10,p20);

  // Determine lengths of edges
  //
  if ( (l10=vtkMath::Dot(p10,p10)) == 0.0
       || (l20=vtkMath::Dot(p20,p20)) == 0.0 )
    {
    return 0;
    }

  //  Now evalute all polygon points to determine min/max parametric
  //  coordinate values.
  //
  // first vertex has (s,t) = (0,0)
  sbounds[0] = 0.0; sbounds[1] = 0.0;
  tbounds[0] = 0.0; tbounds[1] = 0.0;

  for(i=1; i<numPts; i++) 
    {
    this->Points->GetPoint(i, x1);
    for(j=0; j<3; j++)
      {
      p[j] = x1[j] - p0[j];
      }
#ifdef BAD_WITH_NODEBUG
    s = vtkMath::Dot(p,p10) / l10;
    t = vtkMath::Dot(p,p20) / l20;
#endif
    s = (p[0]*p10[0] + p[1]*p10[1] + p[2]*p10[2]) / l10;
    t = (p[0]*p20[0] + p[1]*p20[1] + p[2]*p20[2]) / l20;
    sbounds[0] = (s<sbounds[0]?s:sbounds[0]);
    sbounds[1] = (s>sbounds[1]?s:sbounds[1]);
    tbounds[0] = (t<tbounds[0]?t:tbounds[0]);
    tbounds[1] = (t>tbounds[1]?t:tbounds[1]);
    }

  //  Re-evaluate coordinate system
  //
  for (i=0; i<3; i++) 
    {
    p1[i] = p0[i] + sbounds[1]*p10[i] + tbounds[0]*p20[i];
    p2[i] = p0[i] + sbounds[0]*p10[i] + tbounds[1]*p20[i];
    p0[i] = p0[i] + sbounds[0]*p10[i] + tbounds[0]*p20[i];
    p10[i] = p1[i] - p0[i];
    p20[i] = p2[i] - p0[i];
    }
  l10 = vtkMath::Norm(p10);
  l20 = vtkMath::Norm(p20);

  return 1;
}

#define VTK_POLYGON_CERTAIN 1
#define VTK_POLYGON_UNCERTAIN 0
#define VTK_POLYGON_RAY_TOL 1.e-03 //Tolerance for ray firing
#define VTK_POLYGON_MAX_ITER 10    //Maximum iterations for ray-firing
#define VTK_POLYGON_VOTE_THRESHOLD 2

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

//----------------------------------------------------------------------------
// Determine whether point is inside polygon. Function uses ray-casting
// to determine if point is inside polygon. Works for arbitrary polygon shape
// (e.g., non-convex). Returns 0 if point is not in polygon; 1 if it is.
// Can also return -1 to indicate degenerate polygon. Note: a point in
// bounding box check is NOT performed prior to in/out check. You may want
// to do this to improve performance.
int meVTKPolygon::PointInPolygon (double x[3], int numPts, double *pts, 
                                double bounds[6], double *n)
//----------------------------------------------------------------------------
{
  double *x1, *x2, xray[3], u, v;
  double rayMag, mag=1, ray[3];
  int testResult, rayOK, status, numInts, i;
  int iterNumber;
  int maxComp, comps[2];
  int deltaVotes;

  // do a quick bounds check
  if ( x[0] < bounds[0] || x[0] > bounds[1] ||
       x[1] < bounds[2] || x[1] > bounds[3] ||
       x[2] < bounds[4] || x[2] > bounds[5])
    {
    return VTK_POLYGON_OUTSIDE;
    }
  
  //
  //  Define a ray to fire.  The ray is a random ray normal to the
  //  normal of the face.  The length of the ray is a function of the
  //  size of the face bounding box.
  //
  for (i=0; i<3; i++)
    {
    ray[i] = ( bounds[2*i+1] - bounds[2*i] )*1.1 +
      fabs((bounds[2*i+1] + bounds[2*i])/2.0 - x[i]);
    }

  if ( (rayMag = vtkMath::Norm(ray)) == 0.0 )
    {
    return VTK_POLYGON_OUTSIDE;
    }

  //  Get the maximum component of the normal.
  //
  if ( fabs(n[0]) > fabs(n[1]) )
    {
    if ( fabs(n[0]) > fabs(n[2]) ) 
      {
      maxComp = 0;
      comps[0] = 1;
      comps[1] = 2;
      } 
    else 
      {
      maxComp = 2;
      comps[0] = 0;
      comps[1] = 1;
      }
    }
  else
    {
    if ( fabs(n[1]) > fabs(n[2]) ) 
      {
      maxComp = 1;
      comps[0] = 0;
      comps[1] = 2;
      } 
    else 
      {
      maxComp = 2;
      comps[0] = 0;
      comps[1] = 1;
      }
    }

  //  Check that max component is non-zero
  //
  if ( n[maxComp] == 0.0 )
    {
    return VTK_POLYGON_FAILURE;
    }

  //  Enough information has been acquired to determine the random ray.
  //  Random rays are generated until one is satisfactory (i.e.,
  //  produces a ray of non-zero magnitude).  Also, since more than one
  //  ray may need to be fired, the ray-firing occurs in a large loop.
  //
  //  The variable iterNumber counts the number of iterations and is
  //  limited by the defined variable VTK_POLYGON_MAX_ITER.
  //
  //  The variable deltaVotes keeps track of the number of votes for
  //  "in" versus "out" of the face.  When delta_vote > 0, more votes
  //  have counted for "in" than "out".  When delta_vote < 0, more votes
  //  have counted for "out" than "in".  When the delta_vote exceeds or
  //  equals the defined variable VTK_POLYGON_VOTE_THRESHOLD, than the
  //  appropriate "in" or "out" status is returned.
  //
  for (deltaVotes = 0, iterNumber = 1;
       (iterNumber < VTK_POLYGON_MAX_ITER)
         && (abs(deltaVotes) < VTK_POLYGON_VOTE_THRESHOLD);
       iterNumber++) 
    {
    //
    //  Generate ray
    //
    for (rayOK = FALSE; rayOK == FALSE; ) 
      {
      ray[comps[0]] = vtkMath::Random(-rayMag, rayMag);
      ray[comps[1]] = vtkMath::Random(-rayMag, rayMag);
      ray[maxComp] = -(n[comps[0]]*ray[comps[0]] + 
                        n[comps[1]]*ray[comps[1]]) / n[maxComp];
      if ( (mag = vtkMath::Norm(ray)) > rayMag*VTK_TOL )
        {
        rayOK = TRUE;
        }
      }

    //  The ray must be appropriately sized.
    //
    for (i=0; i<3; i++)
      {
      xray[i] = x[i] + (rayMag/mag)*ray[i];
      }

    //  The ray may now be fired against all the edges
    //
    for (numInts=0, testResult=VTK_POLYGON_CERTAIN, i=0; i<numPts; i++) 
      {
      x1 = pts + 3*i;
      x2 = pts + 3*((i+1)%numPts);

      //   Fire the ray and compute the number of intersections.  Be careful
      //   of degenerate cases (e.g., ray intersects at vertex).
      //
      if ((status=vtkLine::Intersection(x,xray,x1,x2,u,v)) == VTK_POLYGON_INTERSECTION) 
        {
        if ( (VTK_POLYGON_RAY_TOL < v) && (v < 1.0-VTK_POLYGON_RAY_TOL) )
          {
          numInts++;
          }
        else
          {
          testResult = VTK_POLYGON_UNCERTAIN;
          }
        } 
      else if ( status == VTK_POLYGON_ON_LINE )
        {
        testResult = VTK_POLYGON_UNCERTAIN;
        }
      }
    if ( testResult == VTK_POLYGON_CERTAIN ) 
      {
      if ( (numInts % 2) == 0)
          {
          --deltaVotes;
          }
      else
        {
        ++deltaVotes;
        }
      }
    } //try another ray

  //   If the number of intersections is odd, the point is in the polygon.
  //
  if ( deltaVotes < 0 )
    {
    return VTK_POLYGON_OUTSIDE;
    }
  else
    {
    return VTK_POLYGON_INSIDE;
    }
}

#define VTK_POLYGON_TOLERANCE 1.0e-06

//----------------------------------------------------------------------------
// Triangulate polygon. 
//
int meVTKPolygon::Triangulate(vtkIdList *outTris)
//----------------------------------------------------------------------------
{
  int success;
  double *bounds, d;

  bounds = this->GetBounds();
  
  d = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
           (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
           (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));
  this->Tolerance = VTK_POLYGON_TOLERANCE * d;
  this->SuccessfulTriangulation = 1;

  this->Tris->Reset();
  success = this->EarCutTriangulation();
  
  if ( !success ) //degenerate triangle encountered
    {
    vtkWarningMacro(<< "Degenerate polygon encountered during triangulation");
    }

  outTris->DeepCopy(this->Tris);
  return success;
}


typedef struct _vtkPolyVertex 
  {
  int     id;
  double   x[3];
  double   measure;
  _vtkPolyVertex*    next;
  _vtkPolyVertex*    previous;
  } mevtkLocalPolyVertex;

class mevtkPolyVertexList { //structure to support triangulation
public:
  mevtkPolyVertexList(vtkIdList *ptIds, vtkPoints *pts, double tol2);
  ~mevtkPolyVertexList();
  
  int ComputeNormal();
  double ComputeMeasure(mevtkLocalPolyVertex *vtx);
  void RemoveVertex(int i, vtkIdList *, vtkPriorityQueue *);
  int CanRemoveVertex(int id, double tol);
  
  double ComputeAngle(mevtkLocalPolyVertex *vtx1 ,mevtkLocalPolyVertex *vtx2, mevtkLocalPolyVertex *vtx3, vtkPolyData *surrounding, int** lambda );
  // double ComputeAngle(mevtkLocalPolyVertex *vtx1 ,mevtkLocalPolyVertex *vtx2, mevtkLocalPolyVertex *vtx3 );
  double ComputeArea(mevtkLocalPolyVertex* vtx1, mevtkLocalPolyVertex *vtx2, mevtkLocalPolyVertex *vtx3);
  mevtkLocalPolyVertex* GetLocalVertex(int Id);
  int Trace(int i, int k, int** lambda, vtkIdList *tris);

  int NumberOfVerts;
  mevtkLocalPolyVertex *Array;
  mevtkLocalPolyVertex *Head;
  double Normal[3];
};
    
//----------------------------------------------------------------------------
// tolerance is squared
  mevtkPolyVertexList::mevtkPolyVertexList(vtkIdList *ptIds, vtkPoints *pts,
                                     double tol2)
//----------------------------------------------------------------------------
{
  int numVerts = ptIds->GetNumberOfIds();
  this->NumberOfVerts = numVerts; 
  this->Array = new mevtkLocalPolyVertex [numVerts];
  int i;

  // now load the data into the array
  double x[3];
  for (i=0; i<numVerts; i++)
    {
    this->Array[i].id = i;
    pts->GetPoint(i,x);
    this->Array[i].x[0] = x[0];
    this->Array[i].x[1] = x[1];
    this->Array[i].x[2] = x[2];
    this->Array[i].next = this->Array + (i+1)%numVerts;
    if ( i == 0 )
      {
      this->Array[i].previous = this->Array + numVerts - 1;
      }
    else
      {
      this->Array[i].previous = this->Array + i - 1;
      }
    }

  // Make sure that there are no coincident vertices.
  // Beware of multiple coincident vertices.
  mevtkLocalPolyVertex *vtx, *next;
  this->Head = this->Array;

  for (vtx=this->Head, i=0; i<numVerts; i++)
    {
    next = vtx->next;
    if ( vtkMath::Distance2BetweenPoints(vtx->x,next->x) < tol2 )
      {
      next->next->previous = vtx;
      vtx->next = next->next;
      if ( next == this->Head )
        {
        this->Head = vtx;
        }
      this->NumberOfVerts--;
      }
    else //can move forward
      {
      vtx = next;
      }
    }
}

//----------------------------------------------------------------------------
mevtkPolyVertexList::~mevtkPolyVertexList()
//----------------------------------------------------------------------------
{
  delete [] this->Array;
}

//----------------------------------------------------------------------------
// Remove the vertex from the polygon (forming a triangle with
// its previous and next neighbors, and reinsert the neighbors
// into the priority queue.
void mevtkPolyVertexList::RemoveVertex(int i, vtkIdList *tris, 
                                     vtkPriorityQueue *queue)
//----------------------------------------------------------------------------
{
  // Create triangle
  tris->InsertNextId(this->Array[i].id);
  tris->InsertNextId(this->Array[i].next->id);
  tris->InsertNextId(this->Array[i].previous->id);

  // remove vertex; special case if single triangle left
  if (this->NumberOfVerts < 3 )
    {
    return;
    }
  if ( (this->Array + i) == this->Head )
    {
    this->Head = this->Array[i].next;
    }
  this->Array[i].previous->next = this->Array[i].next;
  this->Array[i].next->previous = this->Array[i].previous;

  // recompute measure, reinsert into queue
  // note that id may have been previously deleted (with Pop()) if we
  // are dealing with a concave polygon and vertex couldn't be split.
  queue->DeleteId(this->Array[i].previous->id);
  queue->DeleteId(this->Array[i].next->id);
  if ( this->ComputeMeasure(this->Array[i].previous) > 0.0 )
    {
    queue->Insert(this->Array[i].previous->measure,
                  this->Array[i].previous->id);
    }
  if ( this->ComputeMeasure(this->Array[i].next) > 0.0 )
    {
    queue->Insert(this->Array[i].next->measure,
                  this->Array[i].next->id);
    }
}

//----------------------------------------------------------------------------
int mevtkPolyVertexList::ComputeNormal()
//----------------------------------------------------------------------------
{
  mevtkLocalPolyVertex *vtx=this->Head;
  double v1[3], v2[3], n[3], *anchor=vtx->x;

  this->Normal[0] = this->Normal[1] = this->Normal[2] = 0.0;
  for (vtx=vtx->next; vtx->next!=this->Head; vtx=vtx->next)
    {
    v1[0] = vtx->x[0] - anchor[0];
    v1[1] = vtx->x[1] - anchor[1];
    v1[2] = vtx->x[2] - anchor[2];
    v2[0] = vtx->next->x[0] - anchor[0];
    v2[1] = vtx->next->x[1] - anchor[1];
    v2[2] = vtx->next->x[2] - anchor[2];
    vtkMath::Cross(v1,v2,n);
    this->Normal[0] += n[0];
    this->Normal[1] += n[1];
    this->Normal[2] += n[2];
    }
  if ( vtkMath::Normalize(this->Normal) == 0.0 )
    {
    return 0;
    }
  else
    {
    return 1;
    }
}
  
//----------------------------------------------------------------------------
// The measure is the ratio of triangle perimeter^2 to area;
// the sign of the measure is determined by dotting the local
// vector with the normal (concave features return a negative
// measure).
double mevtkPolyVertexList::ComputeMeasure(mevtkLocalPolyVertex *vtx)
//----------------------------------------------------------------------------
{
  double v1[3], v2[3], v3[3], v4[3], area, perimeter;

  for (int i=0; i<3; i++)
    {
    v1[i] = vtx->x[i] - vtx->previous->x[i];
    v2[i] = vtx->next->x[i] - vtx->x[i];
    v3[i] = vtx->previous->x[i] - vtx->next->x[i];
    }
  vtkMath::Cross(v1,v2,v4); //|v4| is twice the area
  if ( (area=vtkMath::Dot(v4,this->Normal)) < 0.0 )
    {
    return (vtx->measure = -1.0); //concave or bad triangle
    }
  else if ( area == 0.0 )
    {
    return (vtx->measure = -VTK_DOUBLE_MAX); //concave or bad triangle
    }
  else
    {
    perimeter = vtkMath::Norm(v1) + vtkMath::Norm(v2) + 
                vtkMath::Norm(v3);
    return (vtx->measure = perimeter*perimeter/area);
    }
}

//----------------------------------------------------------------------------
// returns != 0 if vertex can be removed. Uses half-space
// comparison to determine whether ear-cut is valid, and may
// resort to line-plane intersections to resolve possible
// instersections with ear-cut.
int mevtkPolyVertexList::CanRemoveVertex(int id, double tolerance)
//----------------------------------------------------------------------------
{
  int i, sign, currentSign;
  double v[3], sN[3], *sPt, val, s, t;
  mevtkLocalPolyVertex *currentVtx, *previous, *next, *vtx;

  // Check for simple case
  if ( this->NumberOfVerts <= 3 )
    {
    return 1;
    }

  // Compute split plane, the point to be cut off
  // is always on the positive side of the plane.
  currentVtx = this->Array + id;
  previous = currentVtx->previous;
  next = currentVtx->next;

  sPt = previous->x; //point on plane
  for (i=0; i<3; i++)
    {
    v[i] = next->x[i] - previous->x[i]; //vector passing through point
    }

  vtkMath::Cross (v,this->Normal,sN);
  if ( (vtkMath::Normalize(sN)) == 0.0 )
    {
    return 0; //bad split, indeterminant
    }

  // Traverse the other points to see if a) they are all on the
  // other side of the plane; and if not b) whether they intersect
  // the split line.
  int oneNegative=0;
  val = vtkPlane::Evaluate(sN,sPt,next->next->x);
  currentSign = (val > tolerance ? 1 : (val < -tolerance ? -1 : 0));
  oneNegative = (currentSign < 0 ? 1 : 0); //very important

  // Intersections are only computed when the split half-space is crossed
  for (vtx=next->next->next; vtx != previous; vtx = vtx->next)
    {
    val = vtkPlane::Evaluate(sN,sPt,vtx->x);
    sign = (val > tolerance ? 1 : (val < -tolerance ? -1 : 0));
    if ( sign != currentSign )
      {
      if ( !oneNegative )
        {
        oneNegative = (sign < 0 ? 1 : 0); //very important
        }
      if (vtkLine::Intersection(sPt,next->x,vtx->x,vtx->previous->x,s,t) != 0 )
        {
        return 0;
        }
      else
        {
        currentSign = sign;
        }
      }//if crossing occurs
    }//for the rest of the loop

  if ( !oneNegative )
    {
    return 0; //entire loop is on this side of plane
    }
  else
    {
    return 1;
    }
}

//----------------------------------------------------------------------------
int meVTKPolygon::CellBoundary(int vtkNotUsed(subId), double pcoords[3], 
                             vtkIdList *pts)
//----------------------------------------------------------------------------
{
  int i, numPts=this->PointIds->GetNumberOfIds();
  double x[3], *weights;
  int closestPoint=0, previousPoint, nextPoint;
  double largestWeight=0.0;
  double p0[3], p10[3], l10, p20[3], l20, n[3];

  pts->Reset();
  weights = new double[numPts];

  // determine global coordinates given parametric coordinates
  this->ParameterizePolygon(p0, p10, l10, p20, l20, n);
  for (i=0; i<3; i++)
    {
    x[i] = p0[i] + pcoords[0]*p10[i] + pcoords[1]*p20[i];
    }

  //find edge with largest and next largest weight values. This will be
  //the closest edge.
  this->InterpolateFunctions(x,weights);
  for ( i=0; i < numPts; i++ )
    {
    if ( weights[i] > largestWeight )
      {
      closestPoint = i;
      largestWeight = weights[i];
      }
    }

  pts->InsertId(0,this->PointIds->GetId(closestPoint));

  previousPoint = closestPoint - 1;
  nextPoint = closestPoint + 1;
  if ( previousPoint < 0 )
    {
    previousPoint = numPts - 1;
    }
  if ( nextPoint >= numPts )
    {
    nextPoint = 0;
    }

  if ( weights[previousPoint] > weights[nextPoint] )
    {
    pts->InsertId(1,this->PointIds->GetId(previousPoint));
    }
  else
    {
    pts->InsertId(1,this->PointIds->GetId(nextPoint));
    }
  delete [] weights;

  // determine whether point is inside of polygon
  if ( pcoords[0] >= 0.0 && pcoords[0] <= 1.0 &&
       pcoords[1] >= 0.0 && pcoords[1] <= 1.0 &&
       (this->PointInPolygon(x, this->Points->GetNumberOfPoints(), 
                             ((vtkDoubleArray *)this->Points->GetData())
                             ->GetPointer(0), this->GetBounds(),n)
        == VTK_POLYGON_INSIDE) )
    {
    return 1;
    }
  else
    {
    return 0;
    }
}

//----------------------------------------------------------------------------
void meVTKPolygon::Contour(double value, vtkDataArray *cellScalars, 
                         vtkIncrementalPointLocator *locator,
                         vtkCellArray *verts, vtkCellArray *lines, 
                         vtkCellArray *polys,
                         vtkPointData *inPd, vtkPointData *outPd,
                         vtkCellData *inCd, vtkIdType cellId,
                         vtkCellData *outCd)
//----------------------------------------------------------------------------
{
  int i, success;
  double *bounds, d;
  int p1, p2, p3;

  this->TriScalars->SetNumberOfTuples(3);

  bounds = this->GetBounds();
  
  d = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
           (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
           (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));
  this->Tolerance = VTK_POLYGON_TOLERANCE * d;
  this->SuccessfulTriangulation = 1;
  this->ComputeNormal(this->Points, this->Normal);

  this->Tris->Reset();

    success = this->EarCutTriangulation();

  if ( !success ) // Just skip for now.
    {
    }
  else // Contour triangle
    {
    for (i=0; i<this->Tris->GetNumberOfIds(); i += 3)
      {
      p1 = this->Tris->GetId(i);
      p2 = this->Tris->GetId(i+1);
      p3 = this->Tris->GetId(i+2);

      this->Triangle->Points->SetPoint(0,this->Points->GetPoint(p1));
      this->Triangle->Points->SetPoint(1,this->Points->GetPoint(p2));
      this->Triangle->Points->SetPoint(2,this->Points->GetPoint(p3));

      if ( outPd )
        {
        this->Triangle->PointIds->SetId(0,this->PointIds->GetId(p1));
        this->Triangle->PointIds->SetId(1,this->PointIds->GetId(p2));
        this->Triangle->PointIds->SetId(2,this->PointIds->GetId(p3));
        }

      this->TriScalars->SetTuple(0,cellScalars->GetTuple(p1));
      this->TriScalars->SetTuple(1,cellScalars->GetTuple(p2));
      this->TriScalars->SetTuple(2,cellScalars->GetTuple(p3));

      this->Triangle->Contour(value, this->TriScalars, locator, verts,
                   lines, polys, inPd, outPd, inCd, cellId, outCd);
      }
    }
}

//----------------------------------------------------------------------------
vtkCell *meVTKPolygon::GetEdge(int edgeId)
//----------------------------------------------------------------------------
{
  int numPts=this->Points->GetNumberOfPoints();

  // load point id's
  this->Line->PointIds->SetId(0,this->PointIds->GetId(edgeId));
  this->Line->PointIds->SetId(1,this->PointIds->GetId((edgeId+1) % numPts));

  // load coordinates
  this->Line->Points->SetPoint(0,this->Points->GetPoint(edgeId));
  this->Line->Points->SetPoint(1,this->Points->GetPoint((edgeId+1) % numPts));

  return this->Line;
}

//----------------------------------------------------------------------------
//
// Intersect this plane with finite line defined by p1 & p2 with tolerance tol.
//
int meVTKPolygon::IntersectWithLine(double p1[3], double p2[3], double tol,double& t,
                                 double x[3], double pcoords[3], int& subId)
//----------------------------------------------------------------------------
{
  double pt1[3], n[3];
  double tol2 = tol*tol;
  double closestPoint[3];
  double dist2;
  int npts = this->GetNumberOfPoints();
  double *weights;

  subId = 0;
  pcoords[0] = pcoords[1] = pcoords[2] = 0.0;

  // Define a plane to intersect with
  //
  this->Points->GetPoint(1, pt1);
  this->ComputeNormal (this->Points,n);
 
  // Intersect plane of the polygon with line
  //
  if ( ! vtkPlane::IntersectWithLine(p1,p2,n,pt1,t,x) )
    {
    return 0;
    }

  // Evaluate position
  //
  weights = new double[npts];
  if ( this->EvaluatePosition(x, closestPoint, subId, pcoords, dist2, weights) >= 0)
    {
    if ( dist2 <= tol2 ) 
      {
      delete [] weights;
      return 1;
      }
    }
  delete [] weights;
  return 0;

}


//----------------------------------------------------------------------------
int meVTKPolygon::Triangulate(int vtkNotUsed(index), vtkIdList *ptIds, 
                            vtkPoints *pts)
//----------------------------------------------------------------------------
{
  int i, success;
  double *bounds, d;

  pts->Reset();
  ptIds->Reset();

  bounds = this->GetBounds();
  d = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
           (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
           (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));
  this->Tolerance = VTK_POLYGON_TOLERANCE * d;
  this->SuccessfulTriangulation = 1;
  this->ComputeNormal(this->Points, this->Normal);

  this->Tris->Reset();

    success = this->EarCutTriangulation();

  if ( !success ) // Indicate possible failure
    {
    vtkDebugMacro(<<"Possible triangulation failure");
    }
  for (i=0; i<this->Tris->GetNumberOfIds(); i++)
    {
    ptIds->InsertId(i,this->PointIds->GetId(this->Tris->GetId(i)));
    pts->InsertPoint(i,this->Points->GetPoint(this->Tris->GetId(i)));
    }

  return this->SuccessfulTriangulation;
}

//----------------------------------------------------------------------------
// Samples at three points to compute derivatives in local r-s coordinate
// system and projects vectors into 3D model coordinate system.
// Note that the results are usually inaccurate because
// this method actually returns the derivative of the interpolation
// function  which  is obtained using 1/r**2 normalized sum.
#define VTK_SAMPLE_DISTANCE 0.01
void meVTKPolygon::Derivatives(int vtkNotUsed(subId), double pcoords[3],
                             double *values, int dim, double *derivs)
//----------------------------------------------------------------------------
{
  int i, j, k, idx;

  if ( this->Points->GetNumberOfPoints() == 4 )
    {
    for(i=0; i<4; i++)
      {
      this->Quad->Points->SetPoint(i,this->Points->GetPoint(i));
      }
    this->Quad->Derivatives(0, pcoords, values, dim, derivs);
    return;
    }
  else if ( this->Points->GetNumberOfPoints() == 3 )
    {
    for(i=0; i<3; i++)
      {
      this->Triangle->Points->SetPoint(i,this->Points->GetPoint(i));
      }
    this->Triangle->Derivatives(0, pcoords, values, dim, derivs);
    return;
    }

  double p0[3], p10[3], l10, p20[3], l20, n[3];
  double x[3][3], l1, l2, v1[3], v2[3];
  int numVerts=this->PointIds->GetNumberOfIds();
  double *weights = new double[numVerts];
  double *sample = new double[dim*3];

  //setup parametric system and check for degeneracy
  if ( this->ParameterizePolygon(p0, p10, l10, p20, l20, n) == 0 )
    {
    for ( j=0; j < dim; j++ )
      {
      for ( i=0; i < 3; i++ )
        {
        derivs[j*dim + i] = 0.0;
        }
      }
    return;
    }

  //compute positions of three sample points
  for (i=0; i<3; i++)
    {
    x[0][i] = p0[i] + pcoords[0]*p10[i] + pcoords[1]*p20[i];
    x[1][i] = p0[i] + (pcoords[0]+VTK_SAMPLE_DISTANCE)*p10[i] +
              pcoords[1]*p20[i];
    x[2][i] = p0[i] + pcoords[0]*p10[i] +
              (pcoords[1]+VTK_SAMPLE_DISTANCE)*p20[i];
    }

  //for each sample point, sample data values
  for ( idx=0, k=0; k < 3; k++ ) //loop over three sample points
    {
    this->InterpolateFunctions(x[k],weights);
    for ( j=0; j < dim; j++, idx++) //over number of derivates requested
      {
      sample[idx] = 0.0;
      for ( i=0; i < numVerts; i++ )
        {
        sample[idx] += weights[i] * values[j + i*dim];
        }
      }
    }

  //compute differences along the two axes
  for ( i=0; i < 3; i++ )
    {
    v1[i] = x[1][i] - x[0][i];
    v2[i] = x[2][i] - x[0][i];
    }
  l1 = vtkMath::Normalize(v1);
  l2 = vtkMath::Normalize(v2);

  //compute derivatives along x-y-z axes
  double ddx, ddy;
  for ( j=0; j < dim; j++ )
    {
    ddx = (sample[dim+j] - sample[j]) / l1;
    ddy = (sample[2*dim+j] - sample[j]) / l2;

    //project onto global x-y-z axes
    derivs[3*j]     = ddx*v1[0] + ddy*v2[0];
    derivs[3*j + 1] = ddx*v1[1] + ddy*v2[1];
    derivs[3*j + 2] = ddx*v1[2] + ddy*v2[2];
    }

  delete [] weights;
  delete [] sample;
}

//----------------------------------------------------------------------------
void meVTKPolygon::Clip(double value, vtkDataArray *cellScalars,
                      vtkIncrementalPointLocator *locator, vtkCellArray *tris,
                      vtkPointData *inPD, vtkPointData *outPD,
                      vtkCellData *inCD, vtkIdType cellId, vtkCellData *outCD,
                      int insideOut)
//----------------------------------------------------------------------------
{
  int i, success;
  double *bounds, d;
  int p1, p2, p3;

  this->TriScalars->SetNumberOfTuples(3);

  bounds = this->GetBounds();
  d = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
           (bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
           (bounds[5]-bounds[4])*(bounds[5]-bounds[4]));
  this->Tolerance = VTK_POLYGON_TOLERANCE * d;

  this->SuccessfulTriangulation = 1;
  this->ComputeNormal(this->Points, this->Normal);

  this->Tris->Reset();

    success = this->EarCutTriangulation();

  if ( success ) // clip triangles
    {
    for (i=0; i<this->Tris->GetNumberOfIds(); i += 3)
      {
      p1 = this->Tris->GetId(i);
      p2 = this->Tris->GetId(i+1);
      p3 = this->Tris->GetId(i+2);

      this->Triangle->Points->SetPoint(0,this->Points->GetPoint(p1));
      this->Triangle->Points->SetPoint(1,this->Points->GetPoint(p2));
      this->Triangle->Points->SetPoint(2,this->Points->GetPoint(p3));

      this->Triangle->PointIds->SetId(0,this->PointIds->GetId(p1));
      this->Triangle->PointIds->SetId(1,this->PointIds->GetId(p2));
      this->Triangle->PointIds->SetId(2,this->PointIds->GetId(p3));

      this->TriScalars->SetTuple(0,cellScalars->GetTuple(p1));
      this->TriScalars->SetTuple(1,cellScalars->GetTuple(p2));
      this->TriScalars->SetTuple(2,cellScalars->GetTuple(p3));

      this->Triangle->Clip(value, this->TriScalars, locator, tris,
                          inPD, outPD, inCD, cellId, outCD, insideOut);
      }
    }
}

//----------------------------------------------------------------------------
// Method intersects two polygons. You must supply the number of points and
// point coordinates (npts, *pts) and the bounding box (bounds) of the two
// polygons. Also supply a tolerance squared for controlling
// error. The method returns 1 if there is an intersection, and 0 if
// not. A single point of intersection x[3] is also returned if there
// is an intersection.
int meVTKPolygon::IntersectPolygonWithPolygon(int npts, double *pts,double bounds[6],
                                            int npts2, double *pts2,
                                            double bounds2[6], double tol2,
                                            double x[3])
//----------------------------------------------------------------------------
{
  double n[3], coords[3];
  int i, j;
  double *p1, *p2, ray[3];
  double t;

  //  Intersect each edge of first polygon against second
  //
 meVTKPolygon::ComputeNormal(npts2, pts2, n);

  for (i=0; i<npts; i++)
    {
    p1 = pts + 3*i;
    p2 = pts + 3*((i+1)%npts);

    for (j=0; j<3; j++)
      {
      ray[j] = p2[j] - p1[j];
      }
    if ( ! vtkBox::IntersectBox(bounds2, p1, ray, coords, t) )
      {
      continue;
      }

    if ( (vtkPlane::IntersectWithLine(p1,p2,n,pts2,t,x)) == 1 )
      {
      if ( (npts2==3
            && vtkTriangle::PointInTriangle(x,pts2,pts2+3,pts2+6,tol2))
           || (npts2>3
               && meVTKPolygon::PointInPolygon(x,npts2,pts2,bounds2,n)
               ==VTK_POLYGON_INSIDE))
        {
        return 1;
        }
      }
    else
      {
      return 0;
      }
    }

  //  Intersect each edge of second polygon against first
  //
  meVTKPolygon::ComputeNormal(npts, pts, n);


  for (i=0; i<npts2; i++)
    {
    p1 = pts2 + 3*i;
    p2 = pts2 + 3*((i+1)%npts2);

    for (j=0; j<3; j++)
      {
      ray[j] = p2[j] - p1[j];
      }

    if ( ! vtkBox::IntersectBox(bounds, p1, ray, coords, t) )
      {
      continue;
      }

    if ( (vtkPlane::IntersectWithLine(p1,p2,n,pts,t,x)) == 1 )
      {
      if ( (npts==3 && vtkTriangle::PointInTriangle(x,pts,pts+3,pts+6,tol2))
           || (npts>3 && meVTKPolygon::PointInPolygon(x,npts,pts,bounds,n)
               ==VTK_POLYGON_INSIDE))
        {
        return 1;
        }
      }
    else
      {
      return 0;
      }
    }

  return 0;
}
/*
//----------------------------------------------------------------------------
void meVTKPolygon::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "Tolerance: " << this->Tolerance << "\n";
  os << indent << "SuccessfulTriangulation: " <<
    this->SuccessfulTriangulation << "\n";
  os << indent << "Normal: (" << this->Normal[0] << ", "
     << this->Normal[1] << ", " << this->Normal[2] << ")\n";
  os << indent << "Tris:\n";
  this->Tris->PrintSelf(os,indent.GetNextIndent());
  os << indent << "Triangle:\n";
  this->Triangle->PrintSelf(os,indent.GetNextIndent());
  os << indent << "Quad:\n";
  this->Quad->PrintSelf(os,indent.GetNextIndent());
  os << indent << "TriScalars:\n";
  this->TriScalars->PrintSelf(os,indent.GetNextIndent());
  os << indent << "Line:\n";
  this->Line->PrintSelf(os,indent.GetNextIndent());
  }
*/
//----------------------------------------------------------------------------
#ifndef VTK_LEGACY_REMOVE
void meVTKPolygon::ComputeWeights(double x[3], double *weights)
//----------------------------------------------------------------------------
{
  VTK_LEGACY_REPLACED_BODY(meVTKPolygon::ComputeWeights, "VTK 5.2",
                           meVTKPolygon::InterpolateFunctions);
  this->InterpolateFunctions(x, weights);
}
#endif

//----------------------------------------------------------------------------
int meVTKPolygon::EarCutTriangulation ()
//----------------------------------------------------------------------------
{
  mevtkPolyVertexList poly(this->PointIds, this->Points, 
                         this->Tolerance*this->Tolerance);
  mevtkLocalPolyVertex *vtx;
  int i, id;

  // First compute the polygon normal the correct way
  //
  if ( ! poly.ComputeNormal() )
    {
    return (this->SuccessfulTriangulation=0);
    }
  
  // Now compute the angles between edges incident to each
  // vertex. Place the structure into a priority queue (those
  // vertices with smallest angle are to be removed first).
  //
  vtkPriorityQueue *VertexQueue = vtkPriorityQueue::New();
  VertexQueue->Allocate(poly.NumberOfVerts);
  for (i=0, vtx=poly.Head; i < poly.NumberOfVerts; i++, vtx=vtx->next)
    {
    //concave (negative measure) vertices are not elgible for removal
    if ( poly.ComputeMeasure(vtx) > 0.0 )
      {
      VertexQueue->Insert(vtx->measure, vtx->id);
      }
    }
  
  // For each vertex in priority queue, and as long as there
  // are three or more vertices, remove the vertex (if possible)
  // and create a new triangle. If the number of vertices in the
  // queue is equal to the number of vertices, then the polygon
  // is convex and triangle removal can proceed without intersection
  // checks.
  //
  int numInQueue;
  while ( poly.NumberOfVerts > 2 && 
          (numInQueue=VertexQueue->GetNumberOfItems()) > 0)
    {
    if ( numInQueue == poly.NumberOfVerts ) //convex, pop away
      {
      id = VertexQueue->Pop();
      poly.RemoveVertex(id,this->Tris,VertexQueue);
      }//convex
    else
      {
      id = VertexQueue->Pop(); //removes it, even if can't be split
      if ( poly.CanRemoveVertex(id,this->Tolerance) )
        {
        poly.RemoveVertex(id,this->Tris,VertexQueue);
        }
      }//concave
    }//while
  
  // Clean up
  VertexQueue->Delete();

  if ( poly.NumberOfVerts > 2 ) //couldn't triangulate
    {
    return (this->SuccessfulTriangulation=0);
    }
  return (this->SuccessfulTriangulation=1);
}


//-------------------------------------------------
// PAPER IMPLEMENTATION
//-------------------------------------------------

//double mevtkPolyVertexList::ComputeAngle(mevtkLocalPolyVertex *vtx1, mevtkLocalPolyVertex *vtx2, mevtkLocalPolyVertex *vtx3 )

//---------------------------------------------------------------------------------------------------------------------------
double mevtkPolyVertexList::ComputeAngle(mevtkLocalPolyVertex *vtx1, mevtkLocalPolyVertex *vtx2, mevtkLocalPolyVertex *vtx3, vtkPolyData *mesh ,int** lambda)
//---------------------------------------------------------------------------------------------------------------------------
{  
  double v0[3],v1[3],v2[3], angle, n1[3], n2[3];
  vtkIdType Idctr = 0;
  vtkIdType npts = 0;
  vtkIdType *pts = NULL;
  vtkIdList *cellIds = vtkIdList::New();
  mevtkLocalPolyVertex *vtxk;
    
   if (vtx2->id == vtx1->next->id && vtx3->id == vtx2->next->id)
     {
             
   
             // Get cells sharing this point
             Idctr = mesh->FindPoint(vtx2->x);
	     mesh->GetPointCells( Idctr, cellIds );
	     // For each cell
	     std::cout<< "number of cell for vtx2 with id "<<vtx2->id<< " is "<<cellIds->GetNumberOfIds() <<std::endl;
	     for ( vtkIdType i = 0; i < cellIds->GetNumberOfIds(); i++ )
	       {
		 // Get points from cell
		 mesh->GetCellPoints( cellIds->GetId( i ), npts, pts );
		 
		 // Now npts = number of cells points, pts = list of point id
		 // For each point check if it is part of an adjacent edge
		  for ( vtkIdType j = 0; j < npts; j++ )
		   {
		     // Avoid compare ptId with itself and its boundary neighbours
		     if ( Idctr != pts[j] && mesh->FindPoint(vtx1->x)!= pts[j] &&  mesh->FindPoint(vtx3->x)!= pts[j])
		       {
			 if ( mesh->IsEdge( mesh->FindPoint(vtx1->x), pts[j] ))
			   {
			     vtxk=GetLocalVertex(pts[j]);
			     vtkTriangle::ComputeNormal(vtx1->x,vtx2->x, vtxk->x, n1);			    
			   }
			      
			 if ( mesh->IsEdge( mesh->FindPoint(vtx3->x), pts[j]))
			   {
			     vtxk=GetLocalVertex(pts[j]);
			     vtkTriangle::ComputeNormal(vtx2->x,vtx3->x, vtxk->x, n2);
			   }
		       }
		   }
	       }
		      

	       vtkMath::Normalize (n1);
	       vtkMath::Normalize (n2);
	       angle = acos(vtkMath::Dot(n1,n2));
         
     }
   else
     { 
       int im, mk;
       im = lambda[vtx1->id][vtx2->id];
       mk = lambda[vtx2->id][vtx3->id]; 
       if (im != 0 && mk != 0)
        {
	   vtxk=GetLocalVertex(im);
	   vtkTriangle::ComputeNormal(vtx1->x,vtxk->x, vtx2->x, n1);
	   vtxk=GetLocalVertex(mk);
	   vtkTriangle::ComputeNormal(vtx2->x,vtxk->x, vtx3->x, n2);
	   vtkMath::Normalize (n1);
	   vtkMath::Normalize (n2);
	   angle = acos(vtkMath::Dot(n1,n2));
	}
       else angle = 0;
             	   
     }

cellIds->Delete();

  return (angle);
  
}

//---------------------------------------------------------------------------------------------------------------------------
double mevtkPolyVertexList::ComputeArea(mevtkLocalPolyVertex *vtx1, mevtkLocalPolyVertex *vtx2, mevtkLocalPolyVertex *vtx3 )
//---------------------------------------------------------------------------------------------------------------------------
{
  double v1[3], v2[3], v3[3], v4[3], area;

  for (int i=0; i<3; i++)
    {
    v1[i] = vtx2->x[i] - vtx1->x[i];
    v2[i] = vtx3->x[i] - vtx2->x[i];
    v3[i] = vtx1->x[i] - vtx3->x[i];
    }

  vtkMath::Cross(v1,v2,v4); //|v4| is twice the area
  area=vtkMath::Dot(v4,this->Normal);
  return ( area);
  
}


//---------------------------------------------------------------------------------------------------------------------------
mevtkLocalPolyVertex* mevtkPolyVertexList::GetLocalVertex(int Id)
//---------------------------------------------------------------------------------------------------------------------------
{
  mevtkLocalPolyVertex *vtx;
  vtx=this->Array+Id;
  return (vtx);
}

//---------------------------------------------------------------------------------------------------------------------------
int mevtkPolyVertexList::Trace(int i, int k, int** lambda, vtkIdList *tris)
//---------------------------------------------------------------------------------------------------------------------------
{ 
  //mevtkLocalPolyVertex *vtx;
  if (i+2 == k)
    {
     
      tris->InsertNextId(this->Array[i].id);
      tris->InsertNextId(this->Array[i+1].id);
      tris->InsertNextId(this->Array[k].id);
      std::cout<<i<<" , "<<i+1<<" , "<<k<<std::endl;
      }
  else
    {  int m=lambda[i][k];
      if ( m!= i+1) 
	{
	   std::cout<<i<<" , "<<m<<" , "<<k<<std::endl;
	   tris->InsertNextId(this->Array[i].id);
	   tris->InsertNextId(this->Array[m].id);
	   tris->InsertNextId(this->Array[k].id);
	  this->Trace(i,m,lambda,tris);
	}
      if (m!=k-1)
	{
	  this->Trace(m,k,lambda,tris);
	}
    }

  return 1;
}

//---------------------------------------------------------------------------------------------------------------------------
int meVTKPolygon::Triangulation ( vtkPolyData* surrounding)
//---------------------------------------------------------------------------------------------------------------------------
{   
	mevtkPolyVertexList poly(this->PointIds, this->Points, 
                         this->Tolerance*this->Tolerance);
	mevtkLocalPolyVertex *vtx, *vtxtemp1, *vtxtemp2;
	int i, id ,j ,k ,m ;
	double mintempArea,mintempAngle,tempAngle,tempArea,maxtemp;
	
	double **weightArea;
	double **weightAngle; 
	weightArea= new double* [poly.NumberOfVerts];
	weightAngle= new double* [poly.NumberOfVerts];
	int** lambda;
	lambda=new int* [poly.NumberOfVerts];
	for (int it=0; it<poly.NumberOfVerts;it++)
	  {
	    weightArea[it] =  new double[poly.NumberOfVerts];
	    weightAngle[it] =  new double[poly.NumberOfVerts];
	    lambda[it] = new int[poly.NumberOfVerts];
	  }
	

	if ( ! poly.ComputeNormal() )
	  {
	    return (this->SuccessfulTriangulation=0);
	  }
	tempAngle=0;
	tempArea=0;
	
	vtkPriorityQueue *VertexQueue = vtkPriorityQueue::New();
	VertexQueue->Allocate(poly.NumberOfVerts);
	int nofvert = poly.NumberOfVerts -1;
	
	//Initialize W_{i,i+1} with (0,0) 
	for (i=0, vtx=poly.Head; i < nofvert - 1; i++, vtx=vtx->next)
	  {
	    if(i< nofvert - 1)
	      {
		weightAngle[i][(i+1)%(nofvert)]=0;
		weightArea[i][(i+1)%(nofvert)]=0;
	      }
	    if(i< nofvert - 2)
	      {
		weightArea[i][(i+2)%(nofvert)]=poly.ComputeArea(vtx,vtx->next,vtx->next->next);
		weightAngle[i][(i+2)%(nofvert)]=poly.ComputeAngle(vtx,vtx->next,vtx->next->next, surrounding, lambda);
		std::cout<< "W "<< i <<" , "<< (i+2)%(nofvert) << " is  ("<< weightAngle[i][(i+2)%(nofvert)]<<","<<weightArea[i][(i+2)%(nofvert)] <<")"<<std::endl;
	      }

	  }

	
	std::cout<< " Number of Vertices "<<poly.NumberOfVerts<<std::endl;

	
	for (j=3; j< nofvert ;j++)
	  {
	    std::cout<<" J = "<<j << " ============="<<std::endl;
	    vtx=poly.Head;
	   
	    for (i=0;i< nofvert-j;i++)
	      {
		k=(i+j)%(nofvert);
		vtxtemp1=poly.GetLocalVertex(k);
	       
		std::cout<<"GetLocalVertex k "<< poly.GetLocalVertex(k)->id<<std::endl;
		std::cout<<"GetLocalVertex i "<< poly.GetLocalVertex(i)->id<<std::endl;
	
		mintempAngle=M_PI;
		mintempArea=DBL_MAX;
		for ( m = i+1; m<k ; m++)
		  {
		    vtxtemp2=poly.GetLocalVertex(m);
		    std::cout<<"GetLocalVertex m "<< poly.GetLocalVertex(m)->id<<std::endl;
		    maxtemp = Max(weightAngle[i][m],weightAngle[m][k]);
		    tempAngle = Max(maxtemp,poly.ComputeAngle(vtx,vtxtemp2,vtxtemp1,surrounding,lambda));
		    tempArea =weightArea[i][m]+weightArea[m][k]+poly.ComputeArea(vtx,vtxtemp2,vtxtemp1);
		    while (tempAngle< mintempAngle || (tempAngle = mintempAngle && tempArea< mintempArea))
		      {
			mintempAngle = tempAngle;
			mintempArea = tempArea;
			lambda[i][k] = m;
			std::cout<< "m = "<< m <<" , "<<tempAngle << " , "<<tempArea<<std::endl; 
		      }
		   
		  }
		weightAngle[i][k]=mintempAngle;
		weightArea[i][k]=mintempArea;
		std::cout<<" lambda "<< i <<" , "<<k<<" , "<< lambda[i][k] <<std::endl;
		vtx=vtx->next;
	      }
	  }
	
	
	poly.Trace(0,nofvert -1,lambda, this->Tris);

//int numInQueue;


  // Clean up
  VertexQueue->Delete();
  
   delete weightAngle;
   delete weightArea;
   delete lambda;
  
  
  return (this->SuccessfulTriangulation=1);
}

//int meVTKPolygon::TriangulatePaper (vtkIdList *outTris)

//---------------------------------------------------------------------------------------------------------------------------
int meVTKPolygon::TriangulatePaper (vtkIdList *outTris, vtkPolyData* surrounding)
//---------------------------------------------------------------------------------------------------------------------------
{
	int success;
	this->Tris->Reset();
	
	//success= this->Triangulation();
	success= this->Triangulation(surrounding);
	outTris->DeepCopy(this->Tris);
	if ( !success ) //degenerate triangle encountered
	  {
	    vtkWarningMacro(<< "Degenerate polygon encountered during triangulation");
	  }
	return success;
}