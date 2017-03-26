/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Header file defining macros, routines, structures used in Apps
 *          kernels. 
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


#ifndef RAJAPerf_AppsData_HXX
#define RAJAPerf_AppsApps_HXX


namespace rajaperf
{
namespace apps
{

//
// Some macros used in kernels to mimic real app code style.
//
#define NDPTRSET(domain,v,v0,v1,v2,v3,v4,v5,v6,v7)  \
   v0 = v ;   \
   v1 = v0 + 1 ;  \
   v2 = v0 + domain.jp ; \
   v3 = v1 + domain.jp ; \
   v4 = v0 + domain.kp ; \
   v5 = v1 + domain.kp ; \
   v6 = v2 + domain.kp ; \
   v7 = v3 + domain.kp ;

#define NDSET2D(domain,v,v1,v2,v3,v4)  \
   v4 = v ;   \
   v1 = v4 + 1 ;  \
   v2 = v1 + domain.jp ;  \
   v3 = v4 + domain.jp ;

#define zabs2(z)    ( real(z)*real(z)+imag(z)*imag(z) )


//
// Domain structure to mimic structured mesh loops code style.
//
struct ADomain
{
   ADomain( Index_type rzmax, Index_type ndims ) 
      : ndims(ndims), NPNL(2), NPNR(1)
   {
      imin = NPNL;
      jmin = NPNL;
      imax = rzmax + NPNR;
      jmax = rzmax + NPNR;
      jp = imax - imin + 1 + NPNL + NPNR;

      if ( ndims == 2 ) {
         kmin = 0;
         kmax = 0;
         kp = 0;
         nnalls = jp * (jmax - jmin + 1 + NPNL + NPNR) ;
      } else if ( ndims == 3 ) {
         kmin = NPNL;
         kmax = rzmax + NPNR;
         kp = jp * (jmax - jmin + 1 + NPNL + NPNR);
         nnalls = kp * (kmax - kmin + 1 + NPNL + NPNR) ;
      }

      fpn = 0;
      lpn = nnalls - 1;
      frn = fpn + NPNL * (kp + jp) + NPNL;
      lrn = lpn - NPNR * (kp + jp) - NPNR;

      fpz = frn - jp - kp - 1;
      lpz = lrn;

      real_zones = new Index_type[nnalls];
      for (Index_type i = 0; i < nnalls; ++i) real_zones[i] = -1;

      n_real_zones = 0;

      if ( ndims == 2 ) {

         for (Index_type j = jmin; j < jmax; j++) {
            for (Index_type i = imin; i < imax; i++) {
               Index_type ip = i + j*jp ;

               Index_type id = n_real_zones;
               real_zones[id] = ip;
               n_real_zones++;
            }
         }

      } else if ( ndims == 3 ) {

         for (Index_type k = kmin; k < kmax; k++) { 
            for (Index_type j = jmin; j < jmax; j++) {
               for (Index_type i = imin; i < imax; i++) {
                  Index_type ip = i + j*jp + kp*k ;

                  Index_type id = n_real_zones;
                  real_zones[id] = ip;
                  n_real_zones++;
               }
            }
         } 

      }

   }

   ~ADomain() 
   {
      if (real_zones) delete [] real_zones; 
   }

   Index_type ndims;
   Index_type NPNL;
   Index_type NPNR;

   Index_type imin;
   Index_type jmin;
   Index_type kmin;
   Index_type imax;
   Index_type jmax;
   Index_type kmax;

   Index_type jp;
   Index_type kp;
   Index_type nnalls;

   Index_type fpn;
   Index_type lpn;
   Index_type frn;
   Index_type lrn;

   Index_type fpz;
   Index_type lpz;

   Index_type* real_zones;
   Index_type  n_real_zones;
};

} // end namespace apps
} // end namespace rajaperf

#endif  // closing endif for header file include guard
