/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language, the Qt and Open Cascade toolkits.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#ifndef OCC_BREP_POINT_ON_FACES_PROJECTION_H
#define OCC_BREP_POINT_ON_FACES_PROJECTION_H

#include "occtools/occtools.h"
#include <TopoDS_Face.hxx>
#include <gp_Vec.hxx>
#include <utility>
#include <vector>
class gp_Pnt;
class GeomAPI_ProjectPointOnSurf;

namespace occ {

class OCCTOOLS_EXPORT BRepPointOnFacesProjection
{
public:
  BRepPointOnFacesProjection();
  BRepPointOnFacesProjection(const TopoDS_Shape& faces);
  ~BRepPointOnFacesProjection();
  void releaseMemory();

  void prepare(const TopoDS_Shape& faces);
  BRepPointOnFacesProjection& compute(const gp_Pnt& point);
  bool isDone() const;

  const TopoDS_Face& solutionFace() const;
  gp_Pnt solutionPoint() const;
  std::pair<double, double> solutionUV() const;
  gp_Vec solutionNormal() const;

private:
  typedef GeomAPI_ProjectPointOnSurf Projector;
  typedef std::pair<Projector*, TopoDS_Face> ProjectorInfo;
  std::vector<ProjectorInfo> m_projectors;
  ProjectorInfo m_solProjector;
};

} // namespace occ

#endif // OCC_BREP_POINT_ON_FACES_PROJECTION_H
