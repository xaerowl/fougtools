/****************************************************************************
**
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
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

#include "qcombo_box_utils.h"

namespace qtgui {

/*!
 * \class QComboBoxUtils
 * \brief Provides a collection of tools around QComboBox
 * \headerfile qcombo_box_utils.h <qttools/gui/qcombo_box_utils.h>
 * \ingroup qttools_gui
 */

QComboBoxUtils::SignalActivated_int QComboBoxUtils::signalActivated_int()
{
    return (QComboBoxUtils::SignalActivated_int)&QComboBox::activated;
}

QComboBoxUtils::SignalActivated_QString QComboBoxUtils::signalActivated_QString()
{
    return (QComboBoxUtils::SignalActivated_QString)&QComboBox::activated;
}

QComboBoxUtils::SignalCurrentIndexChanged_int QComboBoxUtils::signalCurrentIndexChanged_int()
{
    return (QComboBoxUtils::SignalCurrentIndexChanged_int)&QComboBox::currentIndexChanged;
}

QComboBoxUtils::SignalCurrentIndexChanged_QString QComboBoxUtils::signalCurrentIndexChanged_QString()
{
    return (QComboBoxUtils::SignalCurrentIndexChanged_QString)&QComboBox::currentIndexChanged;
}

QComboBoxUtils::SignalHighlighted_int QComboBoxUtils::signalHighlighted_int()
{
    return (QComboBoxUtils::SignalHighlighted_int)&QComboBox::highlighted;
}

QComboBoxUtils::SignalHighlighted_QString QComboBoxUtils::signalHighlighted_QString()
{
    return (QComboBoxUtils::SignalHighlighted_QString)&QComboBox::highlighted;
}

} // namespace qtgui
