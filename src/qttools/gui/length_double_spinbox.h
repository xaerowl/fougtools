/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
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

#ifndef QTTOOLS_LENGTH_DOUBLE_SPINBOX_H
#define QTTOOLS_LENGTH_DOUBLE_SPINBOX_H

#include "qttools/gui/gui.h"
#include "qttools/gui/abstract_length_editor.h"
#include <QtGui/QDoubleSpinBox>

namespace qttools {

class QTTOOLS_GUI_EXPORT LengthDoubleSpinBox :
    public QDoubleSpinBox,
    public AbstractLengthEditor
{
  Q_OBJECT
  Q_PROPERTY(double length READ length WRITE setLength)

public:
  LengthDoubleSpinBox(QWidget* parent);

  double length() const;
  Q_SLOT void setLength(double v);

public slots:
  void updateEditor(QLocale::MeasurementSystem newSys);

private slots:
  void onValueChanged(double v);

private:
  double m_orgLengthMm;
  bool m_valueHasChanged;
  bool m_isInternalUpdateContext;
};

} // namespace qttools

#endif // QTTOOLS_LENGTH_DOUBLE_SPINBOX_H
