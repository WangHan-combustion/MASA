// -*-c++-*-
//
//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// MASA - Manufactured Analytical Solutions Abstraction Library
//
// Copyright (C) 2010,2011,2012,2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
// $Author$
// $Id$
//
// heat-eq.cpp: example of the API used for the 2D heat equation
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//
#include <masa.h>

using namespace MASA;
typedef double Scalar;

int main()
{
  // declarations
  Scalar tfield;
  Scalar tempx,tempy;

  //problem size
  Scalar lx,ly;
  Scalar dx,dy;
  int nx,ny;

  // error condition
  int err = 0;

  // initialize
  nx = 10;  // number of points
  ny = 10;  
  lx=1;     // length
  ly=1; 

  dx=lx/nx;
  dy=ly/ny;

  // initialize the problem
  err += masa_init<Scalar>("heat equation example","heateq_2d_steady_const");

  // call the sanity check routine 
  // (tests that all variables have been initialized)
  err += masa_sanity_check<Scalar>();

  // evaluate source terms over the domain (0<x<1, 0<y<1) 
  for(int i=0;i<nx;i++)
    for(int j=0;j<nx;j++)
      {  
	tempx=i*dx;
	tempy=j*dy;


	tfield = masa_eval_source_t<Scalar>  (tempx,tempy);

	masa_test_default(tfield);
	
      }

  return err;

}// end program
