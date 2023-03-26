/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2020 ENERCON GmbH
    Copyright (C) 2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::fv::atmPlantCanopyMoistureSource

Group
    grpFvOptionsSources

Description
    Applies sources on moisture to incorporate effects of wet canopy evaporation.

    Corrections applied to:
    \verbatim
      s             | Moisture             
    \endverbatim

    Required fields:
    \verbatim
      s             | Moisture                                [-] 
      T             | Temperature                             [K]
      p             | Pressure                                [Pa]
      LAD           | Leaf Area Density                       [m/s]
    \endverbatim

Usage
    Example by using \c constant/fvOptions:
    \verbatim
    atmPlantMoistureSource1
    {
        // Mandatory entries (unmodifiable)
        type                atmPlantCanopyMoistureSource;

        atmPlantCanopyMoistureSourceCoeffs
        {
            // Mandatory (inherited) entries (unmodifiable)
            selectionMode   all;

            // Optional entries (unmodifiable)
            rho             rho;
            Cp0             1005.0;
        }

        // Optional (inherited) entries
        ...
    }
    \endverbatim

    where the entries mean:
    \table
      Property  | Description                      | Type   | Req'd  | Dflt
      type      | Type name: atmPlantCanopyMoistureSource | word   | yes    | -
      rho       | Name of density field            | word   | no     | rho
      Cp0       | Specific heat capacity [m2/s2/K] | scalar | no     | 1005.0
    \endtable

    The inherited entries are elaborated in:
      - \link fvOption.H \endlink
      - \link cellSetOption.H \endlink

SourceFiles
    atmPlantCanopyMoistureSource.C
    atmPlantCanopyMoistureSourceTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef fv_atmPlantCanopyMoistureSource_H
#define fv_atmPlantCanopyMoistureSource_H

#include "cellSetOption.H"
#include "fvMatrices.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{

/*---------------------------------------------------------------------------*\
               Class atmPlantCanopyMoistureSource Declaration
\*---------------------------------------------------------------------------*/

class atmPlantCanopyMoistureSource
:
    public fv::cellSetOption
{
    // Private Data

        //- Name of density field
        const word rhoName_;

        //- Specific heat capacity
        const dimensionedScalar Cp0_;

        //- Name of operand leaf area density field
        word LADname_;

        // Fields

            //- Moisture flux
            volScalarField s_;


public:

    //- Runtime type information
    TypeName("atmPlantCanopyMoistureSource");


    // Constructors

        //- Construct from explicit source name and mesh
        atmPlantCanopyMoistureSource
        (
            const word& sourceName,
            const word& modelType,
            const dictionary& dict,
            const fvMesh& mesh
        );

        //- No copy construct
        atmPlantCanopyMoistureSource(const atmPlantCanopyMoistureSource&) = delete;

        //- No copy assignment
        void operator=(const atmPlantCanopyMoistureSource&) = delete;


    // Member Functions

        //- Add explicit contribution to moisture transport equation
        //- for incompressible flow computations
        virtual void addSup
        (
            fvMatrix<scalar>& eqn,
            const label fieldi
        );

        //- Add explicit contribution to moisture transport equation
        //- for compressible flow computations
         virtual void addSup
        (
            const volScalarField& rho,
            fvMatrix<scalar>& eqn,
            const label fieldi
        );

        //- Add explicit contribution to moisture transport equation
        //- for multiphase flow computations
        virtual void addSup
        (
            const volScalarField& alpha,
            const volScalarField& rho,
            fvMatrix<scalar>& eqn,
            const label fieldi
        );

        //- Read source dictionary (effectively no-op)
        virtual bool read(const dictionary& dict)
        {
            return true;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
