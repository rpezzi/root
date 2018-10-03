// Author: Enrico Guiraud, Danilo Piparo CERN  09/2018

/*************************************************************************
 * Copyright (C) 1995-2016, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include "ROOT/RCustomColumnBase.hxx"
#include "ROOT/RLoopManager.hxx"
#include "ROOT/RStringView.hxx"
#include "RtypesCore.h" // Long64_t

#include <string>
#include <vector>

using ROOT::Detail::RDF::RCustomColumnBase;

RCustomColumnBase::RCustomColumnBase(RLoopManager *lm, std::string_view name, const unsigned int nSlots,
                                     const bool isDSColumn, const RDFInternal::RBookedCustomColumns &customColumns)
   : fLoopManager(lm), fName(name), fNSlots(nSlots), fIsDataSourceColumn(isDSColumn), fCustomColumns(customColumns)
{
   fLoopManager->RegisterCustomColumn(this);
}

// pin vtable. Work around cling JIT issue.
RCustomColumnBase::~RCustomColumnBase()
{
   fLoopManager->DeRegisterCustomColumn(this);
}

std::string RCustomColumnBase::GetName() const
{
   return fName;
}

void RCustomColumnBase::InitNode()
{
   fLastCheckedEntry = std::vector<Long64_t>(fNSlots, -1);
}
