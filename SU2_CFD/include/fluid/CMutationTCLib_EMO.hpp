/*!
 * \file CMutationTCLib_EMO.hpp
 * \brief Defines the class for the link to Mutation++ ThermoChemistry library.
 * \author C. Garbacz
 * \version 8.5.0 "Harrier"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2026, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "CEMOGas.hpp"

#if defined(HAVE_MPP) && !defined(CODI_REVERSE_TYPE) && !defined(CODI_FORWARD_TYPE)
#include "mutation++.h"

/*!
 * \derived class CMutationTCLib
 * \brief Child class for Mutation++ Equilibrium gas model.
 * \author:  C. Garbacz
 */
class CMutationTCLib_EMO : public CEMOGas {

private:

  std::unique_ptr<Mutation::Mixture> mix; /*!< \brief Pointer to object Mixture from Mutation++ library. */

  vector<su2double> Cv_ks,                /*!< \brief Species specific heats at constant volume. */
  es,                                     /*!< \brief Species energies. */

  su2double Tref;                         /*!< \brief Reference temperature. */

public:

  /*!
   * \brief Constructor of the class.
   */
  CMutationTCLib_EMO(const CConfig* config, unsigned short val_nDim);

  /*!
   * \brief Destructor of the class.
   */
  virtual ~CMutationTCLib_EMO(void);

  /*!
   * \brief Set mixture therodynamic state.
   * \param[in] rhos - Species partial densities.
   * \param[in] T    - Translational/Rotational temperature.
   */
  void SetTDStateRhosTTv(vector<su2double>& val_rhos, su2double val_temperature, su2double val_temperature_ve) final;

  /*!
   * \brief Get species T-R specific heats at constant volume.
   */
  vector<su2double>& GetSpeciesCvTraRot() final;


  /*!
   * \brief Compute mixture energies (total internal energy and vibrational energy).
   */
  vector<su2double>& ComputeMixtureEnergies() final;


  /*!
   * \brief Compute species enthalpies.
   */
  vector<su2double>& ComputeSpeciesEnthalpy(su2double val_T, su2double val_Tve, su2double *val_eves) final;

  /*!
   * \brief Compute translational and vibrational temperatures vector.
   */
  vector<su2double>& ComputeTemperatures(vector<su2double>& val_rhos, su2double rhoE, su2double rhoEve, su2double rhoEvel, su2double Tve_old) final;

  /*!
   * \brief Get species molar mass.
   */
  vector<su2double>& GetSpeciesMolarMass() final;

  /*!
   * \brief Get reference temperature.
   */
  vector<su2double>& GetRefTemperature() final;

  /*!
   * \brief Get species formation enthalpy.
   */
  vector<su2double>& GetSpeciesFormationEnthalpy() final;

};
#endif
