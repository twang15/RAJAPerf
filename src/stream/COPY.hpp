/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Header file for Stream kernel COPY.
 *
 ******************************************************************************
 */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2017, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-xxxxxx
//
// All rights reserved.
//
// This file is part of the RAJA Performance Suite.
//
// For additional details, please read the file LICENSE.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


#ifndef RAJAPerf_Stream_COPY_HPP
#define RAJAPerf_Stream_COPY_HPP

#include "common/KernelBase.hpp"

namespace rajaperf 
{
class RunParams;

namespace stream
{

class COPY : public KernelBase
{
public:

  COPY(const RunParams& params);

  ~COPY();

  void setUp(VariantID vid);
  void runKernel(VariantID vid); 
  void updateChecksum(VariantID vid);
  void tearDown(VariantID vid);

private:
  Real_ptr m_a;
  Real_ptr m_c;
};

} // end namespace stream
} // end namespace rajaperf

#endif // closing endif for header file include guard