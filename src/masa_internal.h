// -*-c++-*-
//
//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// MASA - Manufactured Analytical Solutions Abstraction Library
//
// Copyright (C) 2010 The PECOS Development Team
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
// $Author: nick $
// $Id: masa_core.cpp 12639 2010-08-24 23:33:29Z nick $
//
//
// masa_internal.h: internal MASA class definitions
//                  users are NOT recommended to muck around!
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//

#include <masa.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>

// Macro for declaring MASA classes with all supported Scalar types
#define MASA_INSTANTIATE_ALL(my_class) template class my_class<double>; \
                                       template class my_class<long double>
namespace MASA 
{
  // masa map functions here
  // probably want to hide this from the user eventually
  
  int masa_map_solution  (std::string, std::string);
  int masa_map_temporal  (std::string, std::string);
  int masa_map_coeff     (std::string, std::string); 
  int masa_map           (std::string, std::string);
  int masa_map_dimension (std::string, std::string);

  /* 
   * -------------------------------------------------------------------------------------------   
   *
   * manufactured_solution Base Class
   *
   * this is an abstract class
   * DO NOT EDIT THIS CLASS
   *
   * All manufactured solutions will inherit this class and it's methods 
   *
   * -------------------------------------------------------------------------------------------   
   */ 

  template <typename Scalar>
  class manufactured_solution
  {
    
  private: 
    Scalar Tan;                          // analytical solution 
    Scalar Q;                            // source term
    Scalar gradT;                        // gradient 
    
  protected:
    static const Scalar MASA_VAR_DEFAULT;   
    Scalar dummy;
    int num_vars;

    std::map<std::string,int> varmap;               // map to each variable
    std::vector<Scalar*>  vararr;              // arr of pointers to each variable
    std::string mmsname;                       // the name of the manufactured solution  
    int dimension;                        // dimension of the solution

  public: 
    static const Scalar pi;
    static const Scalar PI;

    // functions to override
    virtual ~manufactured_solution(){};   // destructor
    virtual int init_var() = 0;           // inits all variables to selected values

  /* 
   * -------------------------------------------------------------------------------------------   
   *
   * analytical solution(s)
   * 
   * -------------------------------------------------------------------------------------------
   */

    virtual Scalar eval_exact_t(Scalar)                {std::cout << "MASA ERROR:: Analytical Solution (T) is unavailable or not properly loaded.\n"; return -1.33;}; // returns value of analytical solution
    virtual Scalar eval_exact_t(Scalar,Scalar)         {std::cout << "MASA ERROR:: Analytical Solution (T) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 2d problems
    virtual Scalar eval_exact_t(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Analytical Solution (T) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 3d problems
    virtual Scalar eval_exact_t(Scalar,Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Analytical Solution (T) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 4d problems

    virtual Scalar eval_exact_u(Scalar)                {std::cout << "MASA ERROR:: Analytical Solution (u) is unavailable or not properly loaded.\n"; return -1.33;}; // returns value of analytical solution
    virtual Scalar eval_exact_u(Scalar,Scalar)         {std::cout << "MASA ERROR:: Analytical Solution (u) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 2d problems
    virtual Scalar eval_exact_u(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Analytical Solution (u) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 3d problems

    virtual Scalar eval_exact_v(Scalar)                {std::cout << "MASA ERROR:: Analytical Solution (v) is unavailable for 1D problems.\n"; return -1.33;};        // returns value of analytical solution
    virtual Scalar eval_exact_v(Scalar,Scalar)         {std::cout << "MASA ERROR:: Analytical Solution (v) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 2d problems
    virtual Scalar eval_exact_v(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Analytical Solution (v) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 3d problems

    virtual Scalar eval_exact_w(Scalar)                {std::cout << "MASA ERROR:: Analytical Solution (w) is unavailable for 1d problems.\n"; return -1.33;};        // returns value of analytical solution
    virtual Scalar eval_exact_w(Scalar,Scalar)         {std::cout << "MASA ERROR:: Analytical Solution (w) is unavailable for 2d problems.\n"; return -1.33;};        // overloaded for 2d problems
    virtual Scalar eval_exact_w(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Analytical Solution (w) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 3d problems
    
    virtual Scalar eval_exact_p(Scalar)                {std::cout << "MASA ERROR:: Analytical Solution (e) is unavailable or not properly loaded.\n"; return -1.33;}; // returns value of analytical solution
    virtual Scalar eval_exact_p(Scalar,Scalar)         {std::cout << "MASA ERROR:: Analytical Solution (e) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 2d problems
    virtual Scalar eval_exact_p(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Analytical Solution (e) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 3d problems

    virtual Scalar eval_exact_rho(Scalar)              {std::cout << "MASA ERROR:: Analytical Solution (rho) is unavailable or not properly loaded.\n"; return -1.33;}; // returns value of analytical solution
    virtual Scalar eval_exact_rho(Scalar,Scalar)       {std::cout << "MASA ERROR:: Analytical Solution (rho) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 2d problems
    virtual Scalar eval_exact_rho(Scalar,Scalar,Scalar){std::cout << "MASA ERROR:: Analytical Solution (rho) is unavailable or not properly loaded.\n"; return -1.33;}; // overloaded for 3d problems
   

  /* 
   * -------------------------------------------------------------------------------------------   
   *
   * source terms
   * 
   * -------------------------------------------------------------------------------------------
   */

    virtual Scalar eval_q_t(Scalar)                {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};                    // returns value of source term (temp)
    virtual Scalar eval_q_t(Scalar, Scalar)        {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};                    // returns value of source term (temp)
    virtual Scalar eval_q_t(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};                    // returns value of source term (temp)
    virtual Scalar eval_q_t(Scalar,Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};             // returns value of source term (x,y,z,t)

    virtual Scalar eval_q_u(Scalar)                {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};                    // returns value of source term (u)
    virtual Scalar eval_q_u(Scalar,Scalar)         {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};                    // overloaded for 2d problems
    virtual Scalar eval_q_u(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Solution has not been properly loaded.\n"; return -1.33;};                    // overloaded for 3d problems

    virtual Scalar eval_q_v(Scalar)                {std::cout << "MASA ERROR:: Source term (v) is unavailable for 1d problems -- eval_q_v has too few arguments.\n"; return -1.33;}; // returns value of source term (v)
    virtual Scalar eval_q_v(Scalar,Scalar)         {std::cout << "MASA ERROR:: Source term (v) is unavailable or not properly loaded.\n"; return -1.33;};                            // overloaded for 2d problems
    virtual Scalar eval_q_v(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Source term (v) is unavailable or not properly loaded.\n"; return -1.33;};                            // overloaded for 3d problems 

    virtual Scalar eval_q_w(Scalar)                {std::cout << "MASA ERROR:: Source term (w) is unavailable for 1d problems -- eval_q_w has too few arguments.\n"; return -1.33;};  // returns value of source term (w)
    virtual Scalar eval_q_w(Scalar,Scalar)         {std::cout << "MASA ERROR:: Source term (w) is unavailable for 2d problems -- eval_q_w has too few arguments.\n"; return -1.33;};  // overloaded for 2d problems
    virtual Scalar eval_q_w(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Source Term (w) is unavailable or not properly loaded.\n"; return -1.33;};                             // overloaded for 3d problems

    virtual Scalar eval_q_e(Scalar)                {std::cout << "MASA ERROR:: Source Term (e) is unavailable or not properly loaded.\n"; return -1.33;};    // returns value of source term (energy)
    virtual Scalar eval_q_e(Scalar,Scalar)         {std::cout << "MASA ERROR:: Source Term (e) is unavailable or not properly loaded.\n"; return -1.33;};    // returns value of source term (energy)
    virtual Scalar eval_q_e(Scalar,Scalar,Scalar)  {std::cout << "MASA ERROR:: Source Term (e) is unavailable or not properly loaded.\n"; return -1.33;};    // returns value of source term (energy)

    virtual Scalar eval_q_rho(Scalar)              {std::cout << "MASA ERROR:: Source Term (rho) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density)
    virtual Scalar eval_q_rho(Scalar,Scalar)       {std::cout << "MASA ERROR:: Source Term (rho) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density)
    virtual Scalar eval_q_rho(Scalar,Scalar,Scalar){std::cout << "MASA ERROR:: Source Term (rho) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density)

    virtual Scalar eval_q_rho_u(Scalar)              {std::cout << "MASA ERROR:: Source Term (rho*u) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*u)
    virtual Scalar eval_q_rho_u(Scalar,Scalar)       {std::cout << "MASA ERROR:: Source Term (rho*u) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*u)
    virtual Scalar eval_q_rho_u(Scalar,Scalar,Scalar){std::cout << "MASA ERROR:: Source Term (rho*u) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*u)

    virtual Scalar eval_q_rho_v(Scalar)              {std::cout << "MASA ERROR:: Source Term (rho*v) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*v)
    virtual Scalar eval_q_rho_v(Scalar,Scalar)       {std::cout << "MASA ERROR:: Source Term (rho*v) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*v)
    virtual Scalar eval_q_rho_v(Scalar,Scalar,Scalar){std::cout << "MASA ERROR:: Source Term (rho*v) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*v)

    virtual Scalar eval_q_rho_w(Scalar)              {std::cout << "MASA ERROR:: Source Term (rho*w) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*w)
    virtual Scalar eval_q_rho_w(Scalar,Scalar)       {std::cout << "MASA ERROR:: Source Term (rho*w) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*w)
    virtual Scalar eval_q_rho_w(Scalar,Scalar,Scalar){std::cout << "MASA ERROR:: Source Term (rho*w) is unavailable or not properly loaded.\n"; return -1.33;};  // returns value of source term (density*w)

  /* 
   * -------------------------------------------------------------------------------------------   
   *
   * Gradient Terms
   * 
   * -------------------------------------------------------------------------------------------
   */

    virtual Scalar eval_1d_g_u(Scalar)               {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 1d gradient
    virtual Scalar eval_2d_g_u(Scalar,Scalar,int)        {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 2d gradient
    virtual Scalar eval_3d_g_u(Scalar,Scalar,Scalar,int) {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 3d gradient

    virtual Scalar eval_1d_g_v(Scalar)               {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 1d gradient
    virtual Scalar eval_2d_g_v(Scalar,Scalar,int)        {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 2d gradient
    virtual Scalar eval_3d_g_v(Scalar,Scalar,Scalar,int) {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 3d gradient

    virtual Scalar eval_1d_g_w(Scalar)               {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 1d gradient
    virtual Scalar eval_2d_g_w(Scalar,Scalar,int)        {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 2d gradient
    virtual Scalar eval_3d_g_w(Scalar,Scalar,Scalar,int) {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 3d gradient

    virtual Scalar eval_1d_g_p(Scalar)               {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 1d gradient
    virtual Scalar eval_2d_g_p(Scalar,Scalar,int)        {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 2d gradient
    virtual Scalar eval_3d_g_p(Scalar,Scalar,Scalar,int) {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 3d gradient

    virtual Scalar eval_1d_g_rho(Scalar)               {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 1d gradient
    virtual Scalar eval_2d_g_rho(Scalar,Scalar,int)        {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 2d gradient
    virtual Scalar eval_3d_g_rho(Scalar,Scalar,Scalar,int) {std::cout << "MASA ERROR:: gradient is unavailable or not properly loaded.\n";   return -1.33;};         // returns value of 3d gradient

  /* 
   * -------------------------------------------------------------------------------------------   
   *
   * member functions solution classes will inherit (not override)
   * 
   * -------------------------------------------------------------------------------------------
   */
    manufactured_solution();                                     // constructor
    int set_var(std::string,Scalar);                                  // sets variable value    
    int register_var(std::string, Scalar*);                           // this registers a variable
    int sanity_check();                                          // checks that all variables to the class have been initalized
    int poly_test();                                             // regression method for poly class (see below)
    Scalar get_var(std::string);                                      // returns variable value
    void display_var();                                          // print all variable names and values
    void return_name(std::string* inname){inname->assign(mmsname);};  // method: returns name
    void return_dim (int* indim)    {*indim=dimension;};         // method: returns dimension of solution
    
  }; // done with MMS base class

  /* 
   * -------------------------------------------------------------------------------------------   
   * 
   * Polynomial Base Class
   *
   * Blatantly stealing paul bauman's polynomial class definitions in the name of science
   * 
   * In addition to inheriting manufactured class, must inherit polynomial 
   *
   * -------------------------------------------------------------------------------------------   
   */ 
  template <typename Scalar>
  class Polynomial
  {
  public:
    
    void set_coeffs( const std::vector<Scalar> & );
    
    // Evaluates polynomial.
    Scalar operator()( const Scalar &, int *) const;
    
    // Evaluates polynomial and deriviatives up to order specified by user.
    void eval_derivs( const Scalar, const int, std::vector<Scalar> & ) const;
    
    Scalar get_coeffs( const int & ) const;    
    
  protected:
    
    // We assume that the coefficents are ordered as follows:
    // y(x) = a0 + a1*x + a2*x^2 + ... + an*x^n
    // so that there should be n+1 coeff so that
    // coeffs[0] = a0
    // coeffs[1] = a1
    // and so on.
    std::vector<Scalar> coeffs;
    
  };  

  // ------------------------------------------------------
  // ---------- all other mms classes ---------------------
  // ------------------------------------------------------

  // just a demo class
  template <typename Scalar>
  class masa_test_function : public manufactured_solution<Scalar>
  {
  private:
    Scalar dummy;
    Scalar demo_var_2;
    Scalar demo_var_3;
  public:
    masa_test_function(); // constructor
    int init_var();        // default problem values
    int poly_test();
    //Scalar eval_q_t(Scalar);
  }; // done with masa_test


  // class with no source/analytical terms, to test virtual function defaults
  template <typename Scalar>
  class masa_uninit : public manufactured_solution<Scalar>
  {
  private:

  public:
    masa_uninit();  // constructor
    int init_var(); // default problem values
  }; 

  // ------------------------------------------------------
  // ---------- heat equation /steady / constant ----------
  // ------------------------------------------------------

  template <typename Scalar>
  class heateq_1d_steady_const : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar k_0;    
  public:
    heateq_1d_steady_const(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t (Scalar);  // source term evaluator
    Scalar eval_exact_t(Scalar);   //analytical solution

  };

  template <typename Scalar>
  class heateq_2d_steady_const : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar k_0;
    Scalar B_y;

  public:
    heateq_2d_steady_const();       // constructor
    int init_var();        // default problem values
    Scalar eval_q_t (Scalar,Scalar); // source term evaluator
    Scalar eval_exact_t(Scalar,Scalar); // analytical term evaluator
  };
  
  template <typename Scalar>
  class heateq_3d_steady_const : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar k_0;
    Scalar B_y;
    Scalar C_z;

  public:
    heateq_3d_steady_const(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t (Scalar,Scalar,Scalar); //evaluate source term
    Scalar eval_exact_t(Scalar,Scalar,Scalar); // analytical term evaluator
  };
  // ------------------------------------------------------
  // ---------- heat equation / unsteady / constant -------
  // ------------------------------------------------------

  template <typename Scalar>
  class heateq_1d_unsteady_const : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar A_t;
    Scalar D_t;
    Scalar k_0;
    Scalar cp_0;
    Scalar rho;
    
  public:
    heateq_1d_unsteady_const(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar); // needs x,t
  };

  template <typename Scalar>
  class heateq_2d_unsteady_const : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar A_t;
    Scalar B_y;
    Scalar B_t;
    Scalar D_t;
    Scalar rho;
    Scalar k_0;
    Scalar cp_0;

  public:
    heateq_2d_unsteady_const(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar,Scalar); // needs x,y,t
  };
  
  template <typename Scalar>
  class heateq_3d_unsteady_const : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar A_t;
    Scalar B_y;
    Scalar B_t;
    Scalar C_z;
    Scalar C_t;
    Scalar D_t;
    Scalar k_0;
    Scalar cp_0;
    Scalar rho;
    
  public:
    heateq_3d_unsteady_const(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar,Scalar,Scalar); // needs x,y,z,t    
  };

  // ------------------------------------------------------
  // ---------- heat equation / unsteady / var ------------
  // ------------------------------------------------------

  template <typename Scalar>
  class heateq_1d_unsteady_var : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar A_t;
    Scalar D_t;
    Scalar rho;
    Scalar k_0;
    Scalar k_1;
    Scalar k_2;
    Scalar cp_0;
    Scalar cp_1;
    Scalar cp_2;
    
  public:
    heateq_1d_unsteady_var(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar); // needs x,t
  };

  template <typename Scalar>
  class heateq_2d_unsteady_var : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar A_t;
    Scalar B_y;
    Scalar B_t;
    Scalar D_t;
    Scalar rho;
    Scalar k_0;
    Scalar k_1;
    Scalar k_2;
    Scalar cp_0;
    Scalar cp_1;
    Scalar cp_2;

  public:
    heateq_2d_unsteady_var(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar,Scalar); // needs x,y,t    
  };
  
  template <typename Scalar>
  class heateq_3d_unsteady_var : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar A_t;
    Scalar B_y;
    Scalar B_t;
    Scalar C_z;
    Scalar C_t;
    Scalar D_t;
    Scalar rho;
    Scalar k_0;
    Scalar k_1;
    Scalar k_2;
    Scalar cp_0;
    Scalar cp_1;
    Scalar cp_2;

  public:
    heateq_3d_unsteady_var(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar,Scalar,Scalar); // needs x,y,z,t    
  };

  // ------------------------------------------------------
  // ---------- heat equation / steady / var --------------
  // ------------------------------------------------------

  template <typename Scalar>
  class heateq_1d_steady_var : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar k_0;
    Scalar k_1;
    Scalar k_2;

  public:
    heateq_1d_steady_var(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar); // needs x
  };

  template <typename Scalar>
  class heateq_2d_steady_var : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar k_0;
    Scalar k_1;
    Scalar k_2;
    Scalar B_y;

  public:
    heateq_2d_steady_var(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar); // needs x,y
  };
  
  template <typename Scalar>
  class heateq_3d_steady_var : public manufactured_solution<Scalar>
  {
  private:
    Scalar A_x;
    Scalar k_0;
    Scalar k_1;
    Scalar k_2;
    Scalar B_y;
    Scalar C_z;

  public:
    heateq_3d_steady_var(); // constructor
    int init_var();        // default problem values
    Scalar eval_q_t(Scalar,Scalar,Scalar); // needs x,y,z
    
  };

  // ------------------------------------------------------
  // ------------------------- euler ----------------------
  // ------------------------------------------------------
  template <typename Scalar>
  class euler_1d : public manufactured_solution<Scalar>
  {
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;                             // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor
    Scalar k;                             // Boltzmanns constant

    Scalar u_0;
    Scalar u_x;
    Scalar rho_0;
    Scalar rho_x;
    Scalar p_0;
    Scalar p_x;
    Scalar a_px;
    Scalar a_rhox;
    Scalar a_ux;
    Scalar Gamma;
    Scalar mu;
    Scalar L;
    

  public:
    euler_1d(); // constructor    
    int init_var();          // default problem values

    Scalar eval_q_rho_u (Scalar); // source terms
    Scalar eval_q_e     (Scalar);
    Scalar eval_q_rho   (Scalar);
    
    Scalar eval_exact_u  (Scalar); // analytical
    Scalar eval_exact_p  (Scalar);
    Scalar eval_exact_rho(Scalar);

    Scalar eval_1d_g_u  (Scalar);   // gradient of source term
    Scalar eval_1d_g_p  (Scalar);
    Scalar eval_1d_g_rho(Scalar);

  };

  template <typename Scalar>
  class euler_2d : public manufactured_solution<Scalar>
  {
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;     // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor
    Scalar k;     // Boltzmanns constant

    Scalar u_0;
    Scalar u_x;
    Scalar u_y;
    Scalar v_0;
    Scalar v_x;
    Scalar v_y;
    Scalar rho_0;
    Scalar rho_x;
    Scalar rho_y;
    Scalar p_0;
    Scalar p_x;
    Scalar p_y;
    Scalar a_px;
    Scalar a_py;
    Scalar a_rhox;
    Scalar a_rhoy;
    Scalar a_ux;
    Scalar a_uy;
    Scalar a_vx;
    Scalar a_vy;
    Scalar Gamma;
    Scalar mu;
    Scalar L;
    
  public:
    euler_2d(); // constructor    
    int init_var();        // default problem values

    Scalar eval_q_rho_u (Scalar,Scalar);
    Scalar eval_q_rho_v (Scalar,Scalar);
    Scalar eval_q_e     (Scalar,Scalar);
    Scalar eval_q_rho   (Scalar,Scalar);

    Scalar eval_exact_u  (Scalar,Scalar); // analytical
    Scalar eval_exact_v  (Scalar,Scalar);
    Scalar eval_exact_p  (Scalar,Scalar);
    Scalar eval_exact_rho(Scalar,Scalar);

    Scalar eval_2d_g_u(Scalar,Scalar,int);   // gradient of source term
    Scalar eval_2d_g_v(Scalar,Scalar,int);
    Scalar eval_2d_g_p(Scalar,Scalar,int);

    Scalar eval_2d_g_rho(Scalar,Scalar,int);

  };

  template <typename Scalar>
  class euler_3d : public manufactured_solution<Scalar>
  {
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;     // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor
    Scalar k;     // Boltzmanns constant

    Scalar u_0;
    Scalar u_x;
    Scalar u_y;
    Scalar u_z;
    Scalar v_0;
    Scalar v_x;
    Scalar v_y;
    Scalar v_z;
    Scalar w_0;
    Scalar w_x;
    Scalar w_y;
    Scalar w_z;
    Scalar rho_0;
    Scalar rho_x;
    Scalar rho_y;
    Scalar rho_z;
    Scalar p_0;
    Scalar p_x;
    Scalar p_y;
    Scalar p_z;
    Scalar a_px;
    Scalar a_py;
    Scalar a_pz;
    Scalar a_rhox;
    Scalar a_rhoy;
    Scalar a_rhoz;
    Scalar a_ux;
    Scalar a_uy;
    Scalar a_uz;
    Scalar a_vx;
    Scalar a_vy;
    Scalar a_vz;
    Scalar a_wx;
    Scalar a_wy;
    Scalar a_wz;
    Scalar mu;
    Scalar Gamma;
    Scalar L;    
    
  public:
    euler_3d(); // constructor
    int init_var();        // default problem values

    Scalar eval_q_rho_u  (Scalar,Scalar,Scalar); // source terms
    Scalar eval_q_rho_v  (Scalar,Scalar,Scalar);
    Scalar eval_q_rho_w  (Scalar,Scalar,Scalar);
    Scalar eval_q_e      (Scalar,Scalar,Scalar);
    Scalar eval_q_rho    (Scalar,Scalar,Scalar);

    Scalar eval_exact_u  (Scalar,Scalar,Scalar); // analytical
    Scalar eval_exact_v  (Scalar,Scalar,Scalar);
    Scalar eval_exact_w  (Scalar,Scalar,Scalar);
    Scalar eval_exact_q  (Scalar,Scalar,Scalar);
    Scalar eval_exact_p  (Scalar,Scalar,Scalar);
    Scalar eval_exact_rho(Scalar,Scalar,Scalar);

    Scalar eval_3d_g_u(Scalar,Scalar,Scalar,int);   // gradient of source term
    Scalar eval_3d_g_v(Scalar,Scalar,Scalar,int);
    Scalar eval_3d_g_w(Scalar,Scalar,Scalar,int);

    Scalar eval_3d_g_p  (Scalar,Scalar,Scalar,int);
    Scalar eval_3d_g_rho(Scalar,Scalar,Scalar,int);

  };

  // ------------------------------------------------------
  // ---------------- axisymmetric euler ------------------
  // ------------------------------------------------------
  template <typename Scalar>
  class axi_euler : public manufactured_solution<Scalar>
  {
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;                             // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor

    Scalar p_0;
    Scalar p_1;
    Scalar rho_0;
    Scalar rho_1;
    Scalar u_1;
    Scalar w_0;
    Scalar w_1;
    Scalar a_pr;
    Scalar a_pz;
    Scalar a_rhor;
    Scalar a_rhoz;
    Scalar a_ur;
    Scalar a_uz;
    Scalar a_wr;
    Scalar a_wz;
    Scalar L;
    Scalar mu;
    Scalar Gamma;    

  public:
    axi_euler(); // constructor    
    int init_var();          // default problem values

    Scalar eval_q_rho_u (Scalar,Scalar); // radial velocity 
    Scalar eval_q_rho_w (Scalar,Scalar); // axial 
    Scalar eval_q_e     (Scalar,Scalar);
    Scalar eval_q_rho   (Scalar,Scalar);
    
    Scalar eval_exact_u  (Scalar,Scalar); // analytical
    Scalar eval_exact_w  (Scalar,Scalar);
    Scalar eval_exact_p  (Scalar,Scalar);
    Scalar eval_exact_rho(Scalar,Scalar);

  };

  // ------------------------------------------------------
  // ---------- axisymmetric compressible navier stokes ---
  // ------------------------------------------------------
  template <typename Scalar>
  class axi_cns : public manufactured_solution<Scalar>
  {
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;                             // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor
    Scalar k;                             // Boltzmanns constant

    Scalar p_0;
    Scalar p_1;
    Scalar rho_0;
    Scalar rho_1;
    Scalar u_1;
    Scalar w_0;
    Scalar w_1;
    Scalar a_pr;
    Scalar a_pz;
    Scalar a_rhor;
    Scalar a_rhoz;
    Scalar a_ur;
    Scalar a_uz;
    Scalar a_wr;
    Scalar a_wz;
    Scalar L;
    Scalar mu;
    Scalar Gamma;
   
  public:
    axi_cns(); // constructor    
    int init_var();          // default problem values

    Scalar eval_q_rho_u (Scalar,Scalar); // radial velocity 
    Scalar eval_q_rho_w (Scalar,Scalar); // axial 
    Scalar eval_q_e     (Scalar,Scalar);
    Scalar eval_q_rho   (Scalar,Scalar);
    
    Scalar eval_exact_u  (Scalar,Scalar); // analytical
    Scalar eval_exact_w  (Scalar,Scalar);
    Scalar eval_exact_p  (Scalar,Scalar);
    Scalar eval_exact_rho(Scalar,Scalar);

  };

  // ------------------------------------------------------
  // --------------------- sod 1d -------------------------
  // ------------------------------------------------------
  template <typename Scalar>
  class sod_1d : public manufactured_solution<Scalar>
  {
    Scalar Gamma;
    Scalar mu;
    Scalar pl, pr, rhol, rhor, cl, cr;

  public:
    sod_1d(); // constructor    
    int init_var();          // default problem values

    Scalar eval_q_rho   (Scalar,Scalar);
    Scalar eval_q_p     (Scalar,Scalar);
    Scalar eval_q_rho_u (Scalar,Scalar);
    Scalar func         (Scalar);  // helper function
    Scalar rtbis        (Scalar,Scalar,Scalar,int);
    Scalar eval_q_t     (Scalar); // regression test function
    Scalar eval_q_t     (Scalar,Scalar); // regression test function
  };

  // ------------------------------------------------------
  // ---------- RANS: Spelart Alamaras (Channel) ----------
  // ------------------------------------------------------
  template <typename Scalar>
  class rans_sa : public manufactured_solution<Scalar>
  {
    
    Scalar cb1;
    Scalar cb2;
    Scalar cv1;
    Scalar cw2;
    Scalar cw3;
    Scalar sigma;
    Scalar kappa;  
    Scalar re_tau;

    // adding for modified SA
    Scalar cv2;
    Scalar cv3;

    // parameters not for users
    Scalar etam;
    Scalar a1;
    Scalar b1;

  public:
    rans_sa(); // constructor    
    int init_var();          // default problem values
    
    Scalar eval_q_u (Scalar); // velocity term
    Scalar eval_q_v (Scalar); // eddy viscosity term
    Scalar eval_exact_u(Scalar); // analytical
    Scalar eval_exact_v(Scalar);

    // member functions not exposed by API
    Scalar   u(Scalar);
    Scalar  du(Scalar);
    Scalar d2u(Scalar);

    Scalar   nu(Scalar);
    Scalar  dnu(Scalar);
    Scalar d2nu(Scalar);

    Scalar production(Scalar);
    Scalar destruction(Scalar);
    Scalar transport(Scalar);
    
    Scalar cw1();
    Scalar chi(Scalar);
    Scalar fv1(Scalar);
    Scalar fv2(Scalar);
    Scalar   s(Scalar);
    Scalar  sb(Scalar);
    Scalar   r(Scalar);
    Scalar   g(Scalar);
    Scalar  fw(Scalar);
    Scalar dvt(Scalar);
    Scalar  vt(Scalar);

  };

  // ------------------------------------------------------
  // ------------- compressible navier stokes  ------------
  // ------------------------------------------------------

  template <typename Scalar>
  class navierstokes_2d_compressible : public manufactured_solution<Scalar>
  {    
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;     // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor
    Scalar k;     // Boltzmanns constant

    Scalar u_0;
    Scalar u_x;
    Scalar u_y;
    Scalar v_0;
    Scalar v_x;
    Scalar v_y;
    Scalar rho_0;
    Scalar rho_x;
    Scalar rho_y;
    Scalar p_0;
    Scalar p_x;
    Scalar p_y;
    Scalar a_px;
    Scalar a_py;
    Scalar a_rhox;
    Scalar a_rhoy;
    Scalar a_ux;
    Scalar a_uy;
    Scalar a_vx;
    Scalar a_vy;
    Scalar Gamma;
    Scalar mu;
    Scalar L;
    
  public:
    navierstokes_2d_compressible(); // constructor
    int init_var();        // default problem values

    Scalar eval_q_rho_u (Scalar,Scalar);
    Scalar eval_q_rho_v (Scalar,Scalar);
    Scalar eval_q_e     (Scalar,Scalar);
    Scalar eval_q_rho   (Scalar,Scalar);

    Scalar eval_exact_u  (Scalar,Scalar); // analytical
    Scalar eval_exact_v  (Scalar,Scalar);
    Scalar eval_exact_p  (Scalar,Scalar);
    Scalar eval_exact_rho(Scalar,Scalar);

    Scalar eval_2d_g_u(Scalar,Scalar,int);   // gradient of source term
    Scalar eval_2d_g_v(Scalar,Scalar,int);
    Scalar eval_2d_g_p(Scalar,Scalar,int);

    Scalar eval_2d_g_rho(Scalar,Scalar,int);


  };
  
  template <typename Scalar>
  class navierstokes_3d_compressible : public manufactured_solution<Scalar>
  {
    using manufactured_solution<Scalar>::pi;
    using manufactured_solution<Scalar>::PI;

    Scalar R;     // (or is this the ideal gas constant?) ratio of specific heat capacities, defined in constructor
    Scalar k;     // Boltzmanns constant

    Scalar u_0;
    Scalar u_x;
    Scalar u_y;
    Scalar u_z;
    Scalar v_0;
    Scalar v_x;
    Scalar v_y;
    Scalar v_z;
    Scalar w_0;
    Scalar w_x;
    Scalar w_y;
    Scalar w_z;
    Scalar rho_0;
    Scalar rho_x;
    Scalar rho_y;
    Scalar rho_z;
    Scalar p_0;
    Scalar p_x;
    Scalar p_y;
    Scalar p_z;
    Scalar a_px;
    Scalar a_py;
    Scalar a_pz;
    Scalar a_rhox;
    Scalar a_rhoy;
    Scalar a_rhoz;
    Scalar a_ux;
    Scalar a_uy;
    Scalar a_uz;
    Scalar a_vx;
    Scalar a_vy;
    Scalar a_vz;
    Scalar a_wx;
    Scalar a_wy;
    Scalar a_wz;
    Scalar mu;
    Scalar Gamma;
    Scalar L;    
    
  public:
    navierstokes_3d_compressible(); //constructor
    int init_var();        // default problem values

    Scalar eval_q_rho_u  (Scalar,Scalar,Scalar); // source terms
    Scalar eval_q_rho_v  (Scalar,Scalar,Scalar);
    Scalar eval_q_rho_w  (Scalar,Scalar,Scalar);
    Scalar eval_q_e      (Scalar,Scalar,Scalar);
    Scalar eval_q_rho    (Scalar,Scalar,Scalar);

    Scalar eval_exact_u  (Scalar,Scalar,Scalar); // analytical
    Scalar eval_exact_v  (Scalar,Scalar,Scalar);
    Scalar eval_exact_w  (Scalar,Scalar,Scalar);
    Scalar eval_exact_q  (Scalar,Scalar,Scalar);
    Scalar eval_exact_p  (Scalar,Scalar,Scalar);
    Scalar eval_exact_rho(Scalar,Scalar,Scalar);

    Scalar eval_3d_g_u(Scalar,Scalar,Scalar,int);   // gradient of source term
    Scalar eval_3d_g_v(Scalar,Scalar,Scalar,int);
    Scalar eval_3d_g_w(Scalar,Scalar,Scalar,int);

    Scalar eval_3d_g_p  (Scalar,Scalar,Scalar,int);
    Scalar eval_3d_g_rho(Scalar,Scalar,Scalar,int);

  }; // done with navier stokes 3d class
  
} // end MASA namespace
